#include "egl_result.h"
#include "egl_rfm69_driver.h"
#include "egl_rfm69_iface.h"
#include "egl_system.h"

#define CHUNK_SIZE (32U)
#define MAX_VARIABLE_PACKET_SIZE (255U)

typedef struct
{
    uint8_t len;
    uint8_t addr;
}packet_header_t;

static egl_result_t egl_rfm69_iface_dio_wait(egl_rfm69_iface_t *iface, egl_pio_t *dio, bool target_state, uint32_t *timeout)
{
    bool current_state;
    egl_result_t result;
    uint32_t time_prev = egl_timer_get(SYSTIMER);

    do
    {
        result = egl_pio_get(dio, &current_state);
        EGL_RESULT_CHECK(result);

        /* if DIO not set then wait */
        if(current_state != target_state)
        {
            result = egl_pm_mode_set(SYSPM, iface->pm_wait);
            EGL_RESULT_CHECK(result);
        }

        uint32_t time_curr = egl_timer_get(SYSTIMER);
        uint32_t delta = time_curr - time_prev;
        time_prev = time_curr;

        *timeout = delta < *timeout ? *timeout - delta : 0;

    }while(current_state != target_state && *timeout);

    return *timeout > 0 ? EGL_SUCCESS : EGL_TIMEOUT;
}

static inline egl_result_t egl_rfm69_iface_mode_wait(egl_rfm69_iface_t *iface, uint32_t *timeout)
{
    return egl_rfm69_iface_dio_wait(iface, iface->rfm->dio5, true, timeout);
}

static inline egl_result_t egl_rfm69_iface_fifo_level_drop_wait(egl_rfm69_iface_t *iface, uint32_t *timeout)
{
    return egl_rfm69_iface_dio_wait(iface, iface->rfm->dio1, false, timeout);
}

static inline egl_result_t egl_rfm69_iface_fifo_level_reach_wait(egl_rfm69_iface_t *iface, uint32_t *timeout)
{
    return egl_rfm69_iface_dio_wait(iface, iface->rfm->dio1, true, timeout);
}

static inline egl_result_t egl_rfm69_iface_packet_sent_wait(egl_rfm69_iface_t *iface, uint32_t *timeout)
{
    return egl_rfm69_iface_dio_wait(iface, iface->rfm->dio0, true, timeout);
}

static inline egl_result_t egl_rfm69_iface_packet_recv_wait(egl_rfm69_iface_t *iface, uint32_t *timeout)
{
    return egl_rfm69_iface_dio_wait(iface, iface->rfm->dio0, true, timeout);
}

static inline egl_result_t egl_rfm69_iface_fifo_not_empty_wait(egl_rfm69_iface_t *iface, uint32_t *timeout)
{
    return egl_rfm69_iface_dio_wait(iface, iface->rfm->dio2, true, timeout);
}

static egl_result_t egl_rfm69_iface_mode_set(egl_rfm69_iface_t *iface, egl_rfm69_mode_t mode, uint32_t *timeout)
{
    egl_result_t result;

    result = egl_rfm69_mode_set(iface->rfm, mode);
    EGL_RESULT_CHECK(result);

    result = egl_rfm69_iface_dio_wait(iface, iface->rfm->dio5, true, timeout);
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

    result = egl_rfm69_dio3_mode_set(iface->rfm, EGL_RFM69_DIO_MODE_2);
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

    result = egl_rfm69_fifo_thresh_set(iface->rfm, CHUNK_SIZE);
    EGL_RESULT_CHECK(result);

    result = egl_rfm69_packet_length_set(iface->rfm, MAX_VARIABLE_PACKET_SIZE);
    EGL_RESULT_CHECK(result);

    result = egl_rfm69_rssi_thresh_set(iface->rfm, config->rssi_thresh);
    EGL_RESULT_CHECK(result);

    return result;
}

egl_result_t egl_rfm69_iface_write(egl_rfm69_iface_t *iface, void *data, size_t *len)
{
    EGL_ASSERT_CHECK(len != NULL && *len < MAX_VARIABLE_PACKET_SIZE, EGL_INVALID_PARAM);

    size_t offset = 0;
    egl_result_t result;
    egl_result_t result2;
    uint32_t timeout = iface->tx_timeout;
    packet_header_t header =
    {
        .len = (uint8_t)(*len + 1), // +1 for address byte
        .addr = iface->node_addr
    };

    egl_rfm69_mode_t mode;
    result = egl_rfm69_mode_get(iface->rfm, &mode);
    EGL_RESULT_CHECK(result);

    if(mode != EGL_RFM69_TX_MODE)
    {
        result = egl_rfm69_iface_mode_set(iface, EGL_RFM69_STDBY_MODE, &timeout);
        EGL_RESULT_CHECK(result);
    }

    /* Push header to fifo */
    result = egl_rfm69_write_burst(iface->rfm, EGL_RFM69_REG_FIFO, &header, sizeof(header));
    EGL_RESULT_CHECK_EXIT(result);

    /* Set TX mode */
    result = egl_rfm69_iface_mode_set(iface, EGL_RFM69_TX_MODE, &timeout);
    EGL_RESULT_CHECK_EXIT(result);

    while(*len > offset)
    {
        result = egl_rfm69_iface_fifo_level_drop_wait(iface, &timeout);
        EGL_RESULT_CHECK_EXIT(result);

        /* Push data to fifo */
        size_t chunk = *len - offset > CHUNK_SIZE ? CHUNK_SIZE : *len - offset;
        result = egl_rfm69_write_burst(iface->rfm, EGL_RFM69_REG_FIFO, data + offset, chunk);
        EGL_RESULT_CHECK_EXIT(result);
        offset += chunk;
    }

    /* Wait for packet sent event */
    result = egl_rfm69_iface_packet_sent_wait(iface, &timeout);
    EGL_RESULT_CHECK_EXIT(result);

exit:
    result2 = egl_rfm69_iface_mode_set(iface, iface->tx_exit_mode, &timeout);
    EGL_RESULT_CHECK(result2);

    return result;
}

egl_result_t egl_rfm69_iface_read(egl_rfm69_iface_t *iface, void *data, size_t *len)
{
    egl_result_t result;
    egl_result_t result2;
    uint32_t timeout = iface->rx_timeout;
    packet_header_t header = {0};
    size_t offset = 0;

    /* Set RX */
    result = egl_rfm69_iface_mode_set(iface, EGL_RFM69_RX_MODE, &timeout);
    EGL_RESULT_CHECK_EXIT(result);

    /* Wait for header */
    result = egl_rfm69_iface_fifo_not_empty_wait(iface, &timeout);
    EGL_RESULT_CHECK_EXIT(result);

    result = egl_rfm69_read_byte(iface->rfm, EGL_RFM69_REG_FIFO, &header.len);
    EGL_RESULT_CHECK_EXIT(result);

    /* Wait for address byte */
    result = egl_rfm69_iface_fifo_not_empty_wait(iface, &timeout);
    EGL_RESULT_CHECK_EXIT(result);

    result = egl_rfm69_read_byte(iface->rfm, EGL_RFM69_REG_FIFO, &header.addr);
    EGL_RESULT_CHECK_EXIT(result);

    do
    {
        size_t left = header.len - offset - 1; /* -1 for address byte */
        uint8_t *data_ptr = (uint8_t *)data + offset;
        size_t read_len;

        if(left > CHUNK_SIZE)
        {
            result = egl_rfm69_iface_fifo_level_reach_wait(iface, &timeout);
            EGL_RESULT_CHECK_EXIT(result);

            read_len = CHUNK_SIZE;
        }
        else
        {
            result = egl_rfm69_iface_packet_recv_wait(iface, &timeout);
            EGL_RESULT_CHECK_EXIT(result);

            read_len = left;
        }

        result = egl_rfm69_read_burst(iface->rfm, EGL_RFM69_REG_FIFO, data_ptr, read_len);
        EGL_RESULT_CHECK_EXIT(result);

        offset += read_len;
    }while(timeout && offset < header.len - 1);

    *len = offset;

exit:
    /* Save result in separate variable so that previous result will not be overwritten */
    result2 = egl_rfm69_iface_mode_set(iface, iface->rx_exit_mode, &timeout);
    EGL_RESULT_CHECK(result2);

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
