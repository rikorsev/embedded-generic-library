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
#ifndef EGL_OS_THREADX_H
#define EGL_OS_THREADX_H

#include "egl_os.h"
#include "tx_api.h"

typedef TX_THREAD              egl_os_thread_ctx;
typedef TX_EVENT_FLAGS_GROUP   egl_os_flags_ctx;
typedef TX_MUTEX               egl_os_mux_ctx;
typedef TX_SEMAPHORE           egl_os_sem_ctx;
typedef TX_QUEUE               egl_os_queue_ctx;
typedef TX_TIMER               egl_os_timer_ctx;

typedef TX_THREAD            * egl_os_thread_handle;
typedef TX_EVENT_FLAGS_GROUP * egl_os_flags_handle;
typedef TX_MUTEX             * egl_os_mux_handle;
typedef TX_SEMAPHORE         * egl_os_sem_handle;
typedef TX_QUEUE             * egl_os_queue_handle;
typedef TX_TIMER             * egl_os_timer_handle;

#define THREADX egl_os_threadx_port_get()

egl_os_t *egl_os_threadx_port_get(void);

#endif