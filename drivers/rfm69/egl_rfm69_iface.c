#include "egl_result.h"
#include "egl_rfm69_driver.h"
#include "egl_rfm69_iface.h"
#include "egl_system.h"

static egl_result_t egl_rfm69_iface_dio_wait(egl_rfm69_t *rfm, egl_pio_t *dio)
{
    egl_result_t result;
    uint32_t timeout_time = egl_timer_get(SYSTIMER) + 1000;

    do
    {
        result = egl_pio_get(dio);
        if(result == EGL_RESET)
        {
            result = egl_pm_mode_set(SYSPM, rfm->pm_wait);
            EGL_RESULT_CHECK(result);
        }
        else if(result != EGL_SET)
        {
            /* Error */
            return result;
        }
    }while(result != EGL_SET && egl_timer_get(SYSTIMER) <= timeout_time);

    if(egl_timer_get(SYSTIMER) > timeout_time)
    {
        return EGL_TIMEOUT;
    }

    return EGL_SUCCESS;
}

static egl_result_t egl_rfm69_iface_mode_set(egl_rfm69_t *rfm, egl_rfm69_mode_t mode)
{
    egl_result_t result;

    result = egl_rfm69_mode_set(rfm, mode);
    EGL_RESULT_CHECK(result);

    result = egl_rfm69_iface_dio_wait(rfm, rfm->dio5);
    EGL_RESULT_CHECK(result);

    return result;
}

egl_result_t egl_rfm69_iface_init(egl_rfm69_t *rfm, egl_rfm69_config_t *config)
{
    egl_result_t result;

    result = egl_rfm69_init(rfm);
    EGL_RESULT_CHECK(result);

    result = egl_rfm69_frequency_set(rfm, config->frequency);
    EGL_RESULT_CHECK(result);

    result = egl_rfm69_deviation_set(rfm, config->deviation);
    EGL_RESULT_CHECK(result);

    result = egl_rfm69_bitrate_set(rfm, config->bitrate);
    EGL_RESULT_CHECK(result);

    result = egl_rfm69_rx_bandwidth_set(rfm, config->bandwidth);
    EGL_RESULT_CHECK(result);

    result = egl_rfm69_afc_bandwidth_set(rfm, config->bandwidth);
    EGL_RESULT_CHECK(result);

    result = egl_rfm69_dio5_mode_set(rfm, EGL_RFM69_DIO_MODE_3);
    EGL_RESULT_CHECK(result);

    result = egl_rfm69_dio3_mode_set(rfm, EGL_RFM69_DIO_MODE_1);
    EGL_RESULT_CHECK(result);

    result = egl_rfm69_preamble_set(rfm, config->preamble);
    EGL_RESULT_CHECK(result);

    result = egl_rfm69_node_address_set(rfm, config->node_addr);
    EGL_RESULT_CHECK(result);

    result = egl_rfm69_address_filtering_set(rfm, EGL_RFM69_ADDRESS_FILTERING_NODE);
    EGL_RESULT_CHECK(result);

    // result = egl_rfm69_sync_set(rfm, (unsigned char *)config->sync, config->sync_size);
    // EGL_RESULT_CHECK(result);

    // result = egl_rfm69_sync_state_set(rfm, true);
    // EGL_RESULT_CHECK(result);

    result = egl_rfm69_rssi_thresh_set(rfm, -64);
    EGL_RESULT_CHECK(result);

    result = egl_rfm69_power_set(rfm, config->power);
    EGL_RESULT_CHECK(result);

    result = egl_rfm69_packet_format_set(rfm, EGL_RFM69_PACKET_FORMAT_VARIABLE_LENGTH);
    EGL_RESULT_CHECK(result);

    return result;
}

egl_result_t egl_rfm69_iface_write(egl_rfm69_t *rfm, void *data, size_t *len)
{
    return EGL_FAIL;
}

egl_result_t egl_rfm69_iface_read(egl_rfm69_t *rfm, void *data, size_t *len)
{
    egl_result_t result;
    egl_rfm69_irq_flags_t flags;

    result = egl_rfm69_flags_get(rfm, &flags);
    EGL_RESULT_CHECK(result);

    EGL_LOG_DEBUG("Flags[0]: %04x", flags.raw);

    /* Set RX */
    result = egl_rfm69_iface_mode_set(rfm, EGL_RFM69_RX_MODE);
    EGL_RESULT_CHECK(result);

    result = egl_rfm69_flags_get(rfm, &flags);
    EGL_RESULT_CHECK(result);

    EGL_LOG_DEBUG("Flags[1]: %04x", flags.raw);

    // egl_sys_delay(2000);

    // egl_rfm69_irq_flags_t flags;
    // result = egl_rfm69_flags_get(rfm, &flags);
    // EGL_RESULT_CHECK(result);

    // EGL_LOG_DEBUG("Flags: %04x", flags.raw);

    // result = egl_rfm69_read_burst(rfm, EGL_RFM69_REG_FIFO, data, 5);
    // EGL_RESULT_CHECK(result);

    // uint8_t *buff = data;
    // EGL_LOG_DEBUG("Data: %02x %02x %02x %02x %02x", buff[0], buff[1], buff[2], buff[3], buff[4]);

    /* Wait for packet receive event */
    result = egl_rfm69_iface_dio_wait(rfm, rfm->dio0);
    // EGL_RESULT_CHECK(result);

    if(result != EGL_SUCCESS)
    {
        result = egl_rfm69_flags_get(rfm, &flags);
        EGL_RESULT_CHECK(result);

        EGL_LOG_DEBUG("Flags[2]: %04x", flags.raw);

        // result = egl_rfm69_read_burst(rfm, EGL_RFM69_REG_FIFO, data, 5);
        // EGL_RESULT_CHECK(result);

        // uint8_t *buff = data;
        // EGL_LOG_DEBUG("Data: %02x %02x %02x %02x %02x", buff[0], buff[1], buff[2], buff[3], buff[4]);

        result = egl_rfm69_iface_mode_set(rfm, EGL_RFM69_STDBY_MODE);
        EGL_RESULT_CHECK(result);

        return EGL_FAIL;
    }

    /* Read a packet len */
    result = egl_rfm69_read_byte(rfm, EGL_RFM69_REG_FIFO, (uint8_t *)len);
    EGL_RESULT_CHECK(result);

    /* Read packet payload */
    result = egl_rfm69_read_burst(rfm, EGL_RFM69_REG_FIFO, data, *len);
    EGL_RESULT_CHECK(result);

    result = egl_rfm69_iface_mode_set(rfm, EGL_RFM69_STDBY_MODE);
    EGL_RESULT_CHECK(result);

    return result;
}

egl_result_t egl_rfm69_iface_ioctl(egl_rfm69_t *rfm, uint8_t opcode, void *data, size_t len)
{
    return EGL_FAIL;
}

egl_result_t egl_rfm69_iface_deinit(egl_rfm69_t *rfm)
{
    return EGL_FAIL;
}
