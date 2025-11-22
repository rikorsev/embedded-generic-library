/*
 * Copyright (c) 2025 rikorsev
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "egl_result.h"
#include "egl_rfm66_driver.h"
#include "egl_rfm66_iface.h"
#include "egl_system.h"

#define CHUNK_SIZE (32U)
#define MAX_VARIABLE_PACKET_PAYLOAD (254)

typedef struct __attribute__((packed))
{
    uint8_t len;
    uint8_t addr;
}packet_header_t;

static egl_result_t egl_rfm66_iface_dio_wait(egl_rfm66_iface_t *iface, egl_pio_t *dio, bool target_state, uint32_t *timeout)
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

static inline egl_result_t egl_rfm66_iface_mode_wait(egl_rfm66_iface_t *iface, uint32_t *timeout)
{
    return egl_rfm66_iface_dio_wait(iface, iface->rfm->dio5, true, timeout);
}

static inline egl_result_t egl_rfm66_iface_fifo_level_drop_wait(egl_rfm66_iface_t *iface, uint32_t *timeout)
{
    return egl_rfm66_iface_dio_wait(iface, iface->rfm->dio1, false, timeout);
}

static inline egl_result_t egl_rfm66_iface_fifo_level_reach_wait(egl_rfm66_iface_t *iface, uint32_t *timeout)
{
    return egl_rfm66_iface_dio_wait(iface, iface->rfm->dio1, true, timeout);
}

static inline egl_result_t egl_rfm66_iface_packet_sent_wait(egl_rfm66_iface_t *iface, uint32_t *timeout)
{
    return egl_rfm66_iface_dio_wait(iface, iface->rfm->dio0, true, timeout);
}

static inline egl_result_t egl_rfm66_iface_packet_recv_wait(egl_rfm66_iface_t *iface, uint32_t *timeout)
{
    return egl_rfm66_iface_dio_wait(iface, iface->rfm->dio0, true, timeout);
}

static inline egl_result_t egl_rfm66_iface_fifo_not_empty_wait(egl_rfm66_iface_t *iface, uint32_t *timeout)
{
    return egl_rfm66_iface_dio_wait(iface, iface->rfm->dio3, false, timeout);
}

static egl_result_t egl_rfm66_iface_mode_set(egl_rfm66_iface_t *iface, egl_rfm66_mode_t mode, uint32_t *timeout)
{
    egl_result_t result;

    result = egl_rfm66_mode_set(iface->rfm, mode);
    EGL_RESULT_CHECK(result);

    result = egl_rfm66_iface_mode_wait(iface, timeout);
    EGL_RESULT_CHECK(result);

    return result;
}

static egl_result_t egl_rfm66_iface_rx_mode_set(egl_rfm66_iface_t *iface, uint32_t *timeout)
{
    egl_result_t result;
    egl_rfm66_mode_t mode;

    result = egl_rfm66_mode_get(iface->rfm, &mode);
    EGL_RESULT_CHECK(result);

    /* Enable TX mode, if it is not enabled yet */
    if(mode != EGL_RFM66_RX_MODE)
    {
        result = egl_rfm66_iface_mode_set(iface, EGL_RFM66_FS_RX_MODE, timeout);
        EGL_RESULT_CHECK(result);

        result = egl_rfm66_iface_mode_set(iface, EGL_RFM66_RX_MODE, timeout);
        EGL_RESULT_CHECK(result);
    }

    return result;
}

static egl_result_t egl_rfm66_iface_tx_mode_set(egl_rfm66_iface_t *iface, uint32_t *timeout)
{
    egl_result_t result;
    egl_rfm66_mode_t mode;

    result = egl_rfm66_mode_get(iface->rfm, &mode);
    EGL_RESULT_CHECK(result);

    /* Set RX */
    if(mode != EGL_RFM66_TX_MODE)
    {
        /* Set RX */
        result = egl_rfm66_iface_mode_set(iface, EGL_RFM66_FS_TX_MODE, timeout);
        EGL_RESULT_CHECK(result);

        result = egl_rfm66_iface_mode_set(iface, EGL_RFM66_TX_MODE, timeout);
        EGL_RESULT_CHECK(result);
    }

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

    result = egl_rfm66_fifo_thresh_set(iface->rfm, CHUNK_SIZE);
    EGL_RESULT_CHECK(result);

    result = egl_rfm66_packet_length_set(iface->rfm, MAX_VARIABLE_PACKET_PAYLOAD + 1); // +1 address byte
    EGL_RESULT_CHECK(result);

    return result;
}

static egl_result_t egl_rfm66_packet_send(egl_rfm66_iface_t *iface, void *data, size_t *len, uint32_t *timeout)
{
    EGL_ASSERT_CHECK(len != NULL && *len <= MAX_VARIABLE_PACKET_PAYLOAD, EGL_INVALID_PARAM);

    /* If payload size is 0, just return success */
    if(*len == 0)
    {
        return EGL_SUCCESS;
    }

    size_t offset = 0;
    egl_result_t result;
    packet_header_t header =
    {
        .len = (uint8_t)(*len + 1), // +1 for address byte
        .addr = iface->node_addr
    };

    /* Push header to fifo */
    result = egl_rfm66_write_burst(iface->rfm, EGL_RFM66_REG_FIFO, &header, sizeof(header));
    EGL_RESULT_CHECK(result);

    while(*len > offset)
    {
        result = egl_rfm66_iface_fifo_level_drop_wait(iface, timeout);
        EGL_RESULT_CHECK(result);

        /* Push data to fifo */
        size_t chunk = *len - offset > CHUNK_SIZE ? CHUNK_SIZE : *len - offset;
        result = egl_rfm66_write_burst(iface->rfm, EGL_RFM66_REG_FIFO, data + offset, chunk);
        EGL_RESULT_CHECK(result);
        offset += chunk;
    }

    result = egl_rfm66_iface_packet_sent_wait(iface, timeout);
    EGL_RESULT_CHECK(result);

    return result;
}

egl_result_t egl_rfm66_iface_write(egl_rfm66_iface_t *iface, void *data, size_t *len)
{
    egl_result_t result;
    egl_result_t result2;
    uint32_t timeout = iface->tx_timeout;
    size_t offset = 0;

    result = egl_rfm66_iface_tx_mode_set(iface, &timeout);
    EGL_RESULT_CHECK_EXIT(result);

    do
    {
        size_t chunk_size = *len - offset >= MAX_VARIABLE_PACKET_PAYLOAD ?
                                             MAX_VARIABLE_PACKET_PAYLOAD : *len - offset;

        result = egl_rfm66_packet_send(iface, data + offset, &chunk_size, &timeout);

        offset += chunk_size;

        result = egl_sys_delay(iface->tx_inter_packet_delay);
        EGL_RESULT_CHECK_EXIT(result);
    }while(timeout && result == EGL_SUCCESS && offset < *len);

exit:
    *len = offset;

    result2 = egl_rfm66_iface_mode_set(iface, iface->tx_exit_mode, &timeout);
    EGL_RESULT_CHECK(result2);

    return result;
}

static egl_result_t egl_rfm66_iface_packet_recv(egl_rfm66_iface_t *iface, void *data, size_t *len, uint32_t *timeout)
{
    egl_result_t result;
    size_t offset = 0;
    packet_header_t header = {0};

    /* Wait for header */
    result = egl_rfm66_iface_fifo_not_empty_wait(iface, timeout);
    EGL_RESULT_CHECK(result);

    result = egl_rfm66_read_byte(iface->rfm, EGL_RFM66_REG_FIFO, &header.len);
    EGL_RESULT_CHECK(result);

    /* Wait for address byte */
    result = egl_rfm66_iface_fifo_not_empty_wait(iface, timeout);
    EGL_RESULT_CHECK(result);

    result = egl_rfm66_read_byte(iface->rfm, EGL_RFM66_REG_FIFO, &header.addr);
    EGL_RESULT_CHECK(result);

    do
    {
        size_t left = header.len - offset - 1; /* -1 for address byte */
        uint8_t *data_ptr = (uint8_t *)data + offset;
        size_t read_len;

        if(left > CHUNK_SIZE)
        {
            result = egl_rfm66_iface_fifo_level_reach_wait(iface, timeout);
            EGL_RESULT_CHECK(result);

            read_len = CHUNK_SIZE;
        }
        else
        {
            result = egl_rfm66_iface_packet_recv_wait(iface, timeout);
            EGL_RESULT_CHECK(result);

            read_len = left;
        }

        result = egl_rfm66_read_burst(iface->rfm, EGL_RFM66_REG_FIFO, data_ptr, read_len);
        EGL_RESULT_CHECK(result);

        offset += read_len;

        if(iface->is_rx_inc_tout)
        {
            *timeout = iface->rx_timeout;
        }
    }while(timeout && offset < header.len - 1);

    *len = offset;

    return result;
}

egl_result_t egl_rfm66_iface_read(egl_rfm66_iface_t *iface, void *data, size_t *len)
{
    egl_result_t result;
    uint32_t timeout = iface->rx_timeout;
    size_t offset = 0;

    result = egl_rfm66_iface_rx_mode_set(iface, &timeout);
    EGL_RESULT_CHECK_EXIT(result);

    do
    {
        size_t chunk_size = *len - offset >= MAX_VARIABLE_PACKET_PAYLOAD ?
                                             MAX_VARIABLE_PACKET_PAYLOAD : *len - offset;

        result = egl_rfm66_iface_packet_recv(iface, data + offset, &chunk_size, &timeout);
        EGL_RESULT_CHECK_EXIT(result);

        offset += chunk_size;
    }while(timeout && offset < *len);

exit:
    *len = offset;

    /* If we receive at leas something, we may consider it as success*/
    if(iface->is_rx_partial && (*len) > 0 && result == EGL_TIMEOUT)
    {
        result = EGL_SUCCESS;
    }

    egl_rfm66_iface_mode_set(iface, iface->rx_exit_mode, &timeout);

    return result;
}

egl_result_t egl_rfm66_iface_ioctl(egl_rfm66_iface_t *iface, uint8_t opcode, void *data, size_t *len)
{
    egl_result_t result;
    uint32_t timeout;

    switch(opcode)
    {
        case EGL_RFM66_IOCTL_RX_MODE_SET:
            timeout = 100;
            result = egl_rfm66_iface_rx_mode_set(iface, &timeout);
            break;

        default:
            result = EGL_NOT_SUPPORTED;
    }

    return result;
}

egl_result_t egl_rfm66_iface_deinit(egl_rfm66_iface_t *iface)
{
    return EGL_FAIL;
}
