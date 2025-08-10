#include "egl_result.h"
#include "egl_rfm66_driver.h"
#include "egl_rfm66_iface.h"
#include "egl_system.h"

typedef struct
{
    uint8_t len;
    uint8_t addr;
}packet_header_t;

static egl_result_t egl_rfm66_iface_dio_wait(egl_rfm66_iface_t *iface, egl_pio_t *dio, uint32_t *timeout)
{
    bool state;
    egl_result_t result;
    uint32_t time_prev = egl_timer_get(SYSTIMER);

    do
    {
        result = egl_pio_get(dio, &state);
        EGL_RESULT_CHECK(result);

        /* if DIO not set then wait */
        if(state != true)
        {
            result = egl_pm_mode_set(SYSPM, iface->pm_wait);
            EGL_RESULT_CHECK(result);
        }

        uint32_t time_curr = egl_timer_get(SYSTIMER);
        uint32_t delta = time_curr - time_prev;
        time_prev = time_curr;

        *timeout = delta < *timeout ? *timeout - delta : 0;

    }while(state != true && *timeout);

    return *timeout > 0 ? EGL_SUCCESS : EGL_TIMEOUT;
}

static egl_result_t egl_rfm66_iface_mode_set(egl_rfm66_iface_t *iface, egl_rfm66_mode_t mode, uint32_t *timeout)
{
    egl_result_t result;

    result = egl_rfm66_mode_set(iface->rfm, mode);
    EGL_RESULT_CHECK(result);

    result = egl_rfm66_iface_dio_wait(iface, iface->rfm->dio5, timeout);
    EGL_RESULT_CHECK(result);

    return result;
}

egl_result_t egl_rfm66_iface_init(egl_rfm66_iface_t *iface, egl_rfm66_config_t *config)
{
    egl_result_t result;

    iface->node_addr = config->node_addr;

    result = egl_rfm66_init(iface->rfm);
    EGL_RESULT_CHECK(result);

    result = egl_rfm66_frequency_set(iface->rfm, config->frequency);
    EGL_RESULT_CHECK(result);

    result = egl_rfm66_deviation_set(iface->rfm, config->deviation);
    EGL_RESULT_CHECK(result);

    result = egl_rfm66_bitrate_set(iface->rfm, config->bitrate);
    EGL_RESULT_CHECK(result);

    result = egl_rfm66_rx_bandwidth_set(iface->rfm, config->bandwidth);
    EGL_RESULT_CHECK(result);

    result = egl_rfm66_dio5_mode_set(iface->rfm, EGL_RFM66_DIO_MODE_3);
    EGL_RESULT_CHECK(result);

    result = egl_rfm66_preamble_set(iface->rfm, config->preamble);
    EGL_RESULT_CHECK(result);

    result = egl_rfm66_sync_set(iface->rfm, (unsigned char *)config->sync, config->sync_size);
    EGL_RESULT_CHECK(result);

    result = egl_rfm66_sync_state_set(iface->rfm, true);
    EGL_RESULT_CHECK(result);

    result = egl_rfm66_node_address_set(iface->rfm, config->node_addr);
    EGL_RESULT_CHECK(result);

    result = egl_rfm66_pa_power_set(iface->rfm, config->power);
    EGL_RESULT_CHECK(result);

    result = egl_rfm66_pa_select_set(iface->rfm, EGL_RFM66_PA_SELECT_PA_BOOST);
    EGL_RESULT_CHECK(result);

    result = egl_rfm66_address_filtering_set(iface->rfm, EGL_RFM66_ADDRESS_FILTERING_MATCH_NODE_ADDRESS);
    EGL_RESULT_CHECK(result);

    result = egl_rfm66_dc_free_set(iface->rfm, EGL_RFM66_DC_FREE_ENCODING_WHITENING);
    EGL_RESULT_CHECK(result);

    result = egl_rfm66_tx_start_condition_set(iface->rfm, EGL_RFM66_TX_START_CONDITION_FIFO_NOT_EMPTY);
    EGL_RESULT_CHECK(result);

    result = egl_rfm66_modulation_shaping_set(iface->rfm, EGL_RFM66_MODULATION_SHAPING_2);
    EGL_RESULT_CHECK(result);

    return result;
}

egl_result_t egl_rfm66_iface_write(egl_rfm66_iface_t *iface, void *data, size_t *len)
{
    egl_result_t result;
    uint32_t timeout = iface->tx_timeout;
    packet_header_t header =
    {
        .len = (uint8_t)(*len + 1), // +1 for address byte
        .addr = iface->node_addr
    };

    /* Push size to fifo */
    result = egl_rfm66_write_burst(iface->rfm, EGL_RFM66_REG_FIFO, &header, sizeof(header));
    EGL_RESULT_CHECK(result);

    /* Push data to fifo */
    result = egl_rfm66_write_burst(iface->rfm, EGL_RFM66_REG_FIFO, data, *len);
    EGL_RESULT_CHECK(result);

    /* Set TX mode */
    result = egl_rfm66_iface_mode_set(iface, EGL_RFM66_FS_TX_MODE, &timeout);
    EGL_RESULT_CHECK(result);

    result = egl_rfm66_iface_mode_set(iface, EGL_RFM66_TX_MODE, &timeout);
    EGL_RESULT_CHECK(result);

    /* Wait for packet sent event */
    result = egl_rfm66_iface_dio_wait(iface, iface->rfm->dio0, &timeout);
    EGL_RESULT_CHECK(result);

    result = egl_rfm66_iface_mode_set(iface, EGL_RFM66_STDBY_MODE, &timeout);
    EGL_RESULT_CHECK(result);

    return result;
}

egl_result_t egl_rfm66_iface_read(egl_rfm66_iface_t *iface, void *data, size_t *len)
{
    egl_result_t result;
    egl_result_t result2;
    uint32_t timeout = iface->rx_timeout;

    /* Set RX */
    result = egl_rfm66_iface_mode_set(iface, EGL_RFM66_FS_RX_MODE, &timeout);
    EGL_RESULT_CHECK(result);

    result = egl_rfm66_iface_mode_set(iface, EGL_RFM66_RX_MODE, &timeout);
    EGL_RESULT_CHECK(result);

    /* Wait for packet receive event */
    result = egl_rfm66_iface_dio_wait(iface, iface->rfm->dio0, &timeout);
    if(result == EGL_SUCCESS)
    {
        /* Read a packet header */
        packet_header_t header;
        result = egl_rfm66_read_burst(iface->rfm, EGL_RFM66_REG_FIFO, &header, sizeof(header));
        EGL_RESULT_CHECK(result);

        /* Read packet payload */
        *len = header.len - 1; // Exclude address byte
        result = egl_rfm66_read_burst(iface->rfm, EGL_RFM66_REG_FIFO, data, *len);
        EGL_RESULT_CHECK(result);
    }

    /* Save result in separate variable so that previous result will not be overwritten */
    result2 = egl_rfm66_iface_mode_set(iface, EGL_RFM66_STDBY_MODE, &timeout);
    EGL_RESULT_CHECK(result2);

    return result;
}

egl_result_t egl_rfm66_iface_ioctl(egl_rfm66_iface_t *iface, uint8_t opcode, void *data, size_t len)
{
    return EGL_FAIL;
}

egl_result_t egl_rfm66_iface_deinit(egl_rfm66_iface_t *iface)
{
    return EGL_FAIL;
}
