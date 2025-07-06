#include "egl_result.h"
#include "egl_rfm66_driver.h"
#include "egl_rfm66_iface.h"
#include "egl_system.h"

static egl_result_t egl_rfm66_iface_dio_wait(egl_rfm66_t *rfm, egl_pio_t *dio)
{
    egl_result_t result;

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
    }while(result != EGL_SET);

    return EGL_SUCCESS;
}

static egl_result_t egl_rfm66_iface_mode_set(egl_rfm66_t *rfm, egl_rfm66_mode_t mode)
{
    egl_result_t result;

    result = egl_rfm66_mode_set(rfm, mode);
    EGL_RESULT_CHECK(result);

    result = egl_rfm66_iface_dio_wait(rfm, rfm->dio5);
    EGL_RESULT_CHECK(result);

    return result;
}

egl_result_t egl_rfm66_iface_init(egl_rfm66_t *rfm, egl_rfm66_config_t *config)
{
    egl_result_t result;

    result = egl_rfm66_init(rfm);
    EGL_RESULT_CHECK(result);

    result = egl_rfm66_frequency_set(rfm, config->frequency);
    EGL_RESULT_CHECK(result);

    result = egl_rfm66_deviation_set(rfm, config->deviation);
    EGL_RESULT_CHECK(result);

    result = egl_rfm66_bitrate_set(rfm, config->bitrate);
    EGL_RESULT_CHECK(result);

    result = egl_rfm66_rx_bandwidth_set(rfm, config->bandwidth);
    EGL_RESULT_CHECK(result);

    result = egl_rfm66_dio5_mode_set(rfm, EGL_RFM66_DIO_MODE_3);
    EGL_RESULT_CHECK(result);

    result = egl_rfm66_preamble_set(rfm, config->preamble);
    EGL_RESULT_CHECK(result);

    result = egl_rfm66_sync_set(rfm, (unsigned char *)config->sync, config->sync_size);
    EGL_RESULT_CHECK(result);

    result = egl_rfm66_sync_state_set(rfm, true);
    EGL_RESULT_CHECK(result);

    result = egl_rfm66_node_address_set(rfm, config->node_addr);
    EGL_RESULT_CHECK(result);

    result = egl_rfm66_pa_power_set(rfm, config->power);
    EGL_RESULT_CHECK(result);

    result = egl_rfm66_address_filtering_set(rfm, EGL_RFM66_ADDRESS_FILTERING_MATCH_NODE_ADDRESS);
    EGL_RESULT_CHECK(result);

    result = egl_rfm66_tx_start_condition_set(rfm, EGL_RFM66_TX_START_CONDITION_FIFO_NOT_EMPTY);
    EGL_RESULT_CHECK(result);

    return result;
}

egl_result_t egl_rfm66_iface_write(egl_rfm66_t *rfm, void *data, size_t *len)
{
    egl_result_t result;

    /* Push size to fifo */
    result = egl_rfm66_write_burst(rfm, EGL_RFM66_REG_FIFO, len, sizeof(uint8_t));
    EGL_RESULT_CHECK(result);

    /* Push data to fifo */
    result = egl_rfm66_write_burst(rfm, EGL_RFM66_REG_FIFO, data, *len);
    EGL_RESULT_CHECK(result);

    /* Set TX mode */
    result = egl_rfm66_iface_mode_set(rfm, EGL_RFM66_FS_TX_MODE);
    EGL_RESULT_CHECK(result);

    result = egl_rfm66_iface_mode_set(rfm, EGL_RFM66_TX_MODE);
    EGL_RESULT_CHECK(result);

    /* Wait for packet sent event */
    result = egl_rfm66_iface_dio_wait(rfm, rfm->dio0);
    EGL_RESULT_CHECK(result);

    result = egl_rfm66_iface_mode_set(rfm, EGL_RFM66_STDBY_MODE);
    EGL_RESULT_CHECK(result);

    return result;
}

egl_result_t egl_rfm66_iface_read(egl_rfm66_t *rfm, void *data, size_t *len)
{
    return EGL_FAIL;
}

egl_result_t egl_rfm66_iface_ioctl(egl_rfm66_t *rfm, uint8_t opcode, void *data, size_t len)
{
    return EGL_FAIL;
}

egl_result_t egl_rfm66_iface_deinit(egl_rfm66_t *rfm)
{
    return EGL_FAIL;
}
