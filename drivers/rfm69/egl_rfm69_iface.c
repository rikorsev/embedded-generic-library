#include "egl_result.h"
#include "egl_rfm69_driver.h"
#include "egl_rfm69_iface.h"
#include "egl_system.h"

typedef struct
{
    uint8_t len;
    uint8_t addr;
}packet_header_t;

static egl_result_t egl_rfm69_iface_dio_wait(egl_rfm69_iface_t *iface, egl_pio_t *dio, uint32_t *timeout)
{
    egl_result_t result;
    uint32_t time_prev = egl_timer_get(SYSTIMER);

    do
    {
        result = egl_pio_get(dio);
        if(result == EGL_RESET)
        {
            result = egl_pm_mode_set(SYSPM, iface->pm_wait);
            EGL_RESULT_CHECK(result);
        }
        else if(result != EGL_SET)
        {
            /* Error */
            return result;
        }

        uint32_t time_curr = egl_timer_get(SYSTIMER);
        uint32_t delta = time_curr - time_prev;
        time_prev = time_curr;

        *timeout = delta < *timeout ? *timeout - delta : 0;

    }while(result != EGL_SET && *timeout);

    return *timeout > 0 ? EGL_SUCCESS : EGL_TIMEOUT;
}

static egl_result_t egl_rfm69_iface_mode_set(egl_rfm69_iface_t *iface, egl_rfm69_mode_t mode, uint32_t *timeout)
{
    egl_result_t result;

    result = egl_rfm69_mode_set(iface->rfm, mode);
    EGL_RESULT_CHECK(result);

    result = egl_rfm69_iface_dio_wait(iface, iface->rfm->dio5, timeout);
    EGL_RESULT_CHECK(result);

    return result;
}

egl_result_t egl_rfm69_iface_init(egl_rfm69_iface_t *iface, egl_rfm69_config_t *config)
{
    egl_result_t result;

    iface->node_addr = config->node_addr;

    result = egl_rfm69_init(iface->rfm);
    EGL_RESULT_CHECK(result);

    result = egl_rfm69_frequency_set(iface->rfm, config->frequency);
    EGL_RESULT_CHECK(result);

    result = egl_rfm69_deviation_set(iface->rfm, config->deviation);
    EGL_RESULT_CHECK(result);

    result = egl_rfm69_bitrate_set(iface->rfm, config->bitrate);
    EGL_RESULT_CHECK(result);

    result = egl_rfm69_rx_bandwidth_set(iface->rfm, config->bandwidth);
    EGL_RESULT_CHECK(result);

    result = egl_rfm69_afc_bandwidth_set(iface->rfm, config->bandwidth);
    EGL_RESULT_CHECK(result);

    result = egl_rfm69_dio5_mode_set(iface->rfm, EGL_RFM69_DIO_MODE_3);
    EGL_RESULT_CHECK(result);

    result = egl_rfm69_dio3_mode_set(iface->rfm, EGL_RFM69_DIO_MODE_1);
    EGL_RESULT_CHECK(result);

    result = egl_rfm69_preamble_set(iface->rfm, config->preamble);
    EGL_RESULT_CHECK(result);

    result = egl_rfm69_node_address_set(iface->rfm, config->node_addr);
    EGL_RESULT_CHECK(result);

    result = egl_rfm69_address_filtering_set(iface->rfm, EGL_RFM69_ADDRESS_FILTERING_NODE);
    EGL_RESULT_CHECK(result);

    result = egl_rfm69_sync_set(iface->rfm, (unsigned char *)config->sync, config->sync_size);
    EGL_RESULT_CHECK(result);

    result = egl_rfm69_sync_state_set(iface->rfm, true);
    EGL_RESULT_CHECK(result);

    result = egl_rfm69_power_set(iface->rfm, config->power);
    EGL_RESULT_CHECK(result);

    result = egl_rfm69_packet_format_set(iface->rfm, EGL_RFM69_PACKET_FORMAT_VARIABLE_LENGTH);
    EGL_RESULT_CHECK(result);

    result = egl_rfm69_tx_start_cond_set(iface->rfm, EGL_RFM69_TX_START_CONDITION_FIFO_NOT_EMPTY);
    EGL_RESULT_CHECK(result);

    result = egl_rfm69_modulation_shaping_set(iface->rfm, EGL_RFM69_MODULATION_SHAPING_2);
    EGL_RESULT_CHECK(result);

    result = egl_rfm69_dc_free_set(iface->rfm, EGL_RFM69_DC_FREE_WHITENING);
    EGL_RESULT_CHECK(result);

    return result;
}

egl_result_t egl_rfm69_iface_write(egl_rfm69_iface_t *iface, void *data, size_t *len)
{
    #define EGL_RFM69_MAX_PACKET_SIZE (64U)

    egl_result_t result;
    uint32_t timeout = iface->tx_timeout;
    packet_header_t header =
    {
        .len = (uint8_t)(*len + 1), // +1 for address byte
        .addr = iface->node_addr
    };

    /* Push size to fifo */
    result = egl_rfm69_write_burst(iface->rfm, EGL_RFM69_REG_FIFO, &header, sizeof(header));
    EGL_RESULT_CHECK(result);

    /* Push data to fifo */
    result = egl_rfm69_write_burst(iface->rfm, EGL_RFM69_REG_FIFO, data, *len);
    EGL_RESULT_CHECK(result);

    /* Set TX mode */
    result = egl_rfm69_iface_mode_set(iface, EGL_RFM69_TX_MODE, &timeout);
    EGL_RESULT_CHECK(result);

    /* Wait for packet sent event */
    result = egl_rfm69_iface_dio_wait(iface, iface->rfm->dio0, &timeout);
    EGL_RESULT_CHECK(result);

    result = egl_rfm69_iface_mode_set(iface, EGL_RFM69_STDBY_MODE, &timeout);
    EGL_RESULT_CHECK(result);

    return result;
}

egl_result_t egl_rfm69_iface_read(egl_rfm69_iface_t *iface, void *data, size_t *len)
{
    egl_result_t result;
    uint32_t timeout = iface->rx_timeout;

    /* Set RX */
    result = egl_rfm69_iface_mode_set(iface, EGL_RFM69_RX_MODE, &timeout);
    EGL_RESULT_CHECK(result);

    /* Wait for packet receive event */
    result = egl_rfm69_iface_dio_wait(iface, iface->rfm->dio0, &timeout);
    EGL_RESULT_CHECK(result);

    /* Read a packet header */
    packet_header_t header;
    result = egl_rfm69_read_burst(iface->rfm, EGL_RFM69_REG_FIFO, &header, sizeof(header));
    EGL_RESULT_CHECK(result);

    /* Read packet payload */
    *len = header.len - 1; // Exclude address byte
    result = egl_rfm69_read_burst(iface->rfm, EGL_RFM69_REG_FIFO, data, *len);
    EGL_RESULT_CHECK(result);

    result = egl_rfm69_iface_mode_set(iface, EGL_RFM69_STDBY_MODE, &timeout);
    EGL_RESULT_CHECK(result);

    return result;
}

egl_result_t egl_rfm69_iface_ioctl(egl_rfm69_iface_t *iface, uint8_t opcode, void *data, size_t len)
{
    return EGL_FAIL;
}

egl_result_t egl_rfm69_iface_deinit(egl_rfm69_iface_t *iface)
{
    return EGL_FAIL;
}
