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
#include "egl_iface.h"
#include "egl_pio.h"
#include "egl_plat.h"
#include "egl_timer.h"
#include "egl_log.h"
#include "egl_log_front.h"
#include "egl_crc.h"
#include "egl_block.h"
#include "egl_clock.h"
#include "egl_pm.h"
#include "egl_rfm69_driver.h"
#include "egl_rfm69_iface.h"
#include "egl_rfm66_driver.h"
#include "egl_rfm66_iface.h"
#include "egl_system.h"
#include "egl_value.h"
#include "egl_util.h"

#if CONFIG_EGL_OS_ENABLED
#include "egl_os.h"
#endif

#if CONFIG_EGL_OS_THREADX_ENABLED
#include "egl_os_threadx.h"
#endif
