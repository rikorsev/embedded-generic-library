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

#ifndef EGL_RFM69_IFACE_H
#define EGL_RFM69_IFACE_H

#include "egl_rfm69_driver.h"

enum
{
    EGL_RFM69_IOCTL_RX_MODE_SET = 1,
    EGL_RFM69_IOCTL_RX_TIMEOUT_SET
};

typedef struct
{
    uint32_t              frequency;
    uint32_t              deviation;
    uint32_t              bitrate;
    uint16_t              preamble;
    egl_rfm69_bandwidth_t bandwidth;
    uint8_t               power;
    uint8_t               node_addr;
    char                  *sync;
    uint8_t               sync_size;
    int8_t                rssi_thresh;
}egl_rfm69_config_t;

typedef struct
{
    egl_rfm69_t      *rfm;
    uint8_t          node_addr;
    uint32_t         pm_wait;
    uint32_t         rx_timeout;
    uint32_t         tx_timeout;
    uint32_t         tx_inter_packet_delay;
    egl_rfm69_mode_t rx_exit_mode;
    egl_rfm69_mode_t tx_exit_mode;
    bool             is_rx_partial;
    bool             is_rx_inc_tout;
}egl_rfm69_iface_t;

egl_result_t egl_rfm69_iface_init(egl_rfm69_iface_t *iface, egl_rfm69_config_t *config);
egl_result_t egl_rfm69_iface_write(egl_rfm69_iface_t *iface, void *data, size_t *len);
egl_result_t egl_rfm69_iface_read(egl_rfm69_iface_t *iface, void *data, size_t *len);
egl_result_t egl_rfm69_iface_ioctl(egl_rfm69_iface_t *iface, uint8_t opcode, void *data, size_t *len);
egl_result_t egl_rfm69_iface_deinit(egl_rfm69_iface_t *iface);

#endif