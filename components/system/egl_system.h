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

#ifndef EGL_SYSTEM_H
#define EGL_SYSTEM_H

#include "egl_result.h"
#include "egl_log.h"
#include "egl_clock.h"
#include "egl_pm.h"
#include "egl_timer.h"
#include "egl_plat.h"
#include "egl_os.h"

#define SYSPLAT egl_sys_plat_get()
#define SYSLOG egl_sys_log_get()
#define SYSCLOCK egl_sys_clock_get()
#define SYSPM egl_sys_pm_get()
#define SYSTIMER egl_sys_timer_get()
#define SYSOS egl_sys_os_get()

typedef struct
{
    egl_platform_t *plat;
    egl_log_t *syslog;
    egl_clock_t *sysclock;
    egl_pm_t *syspm;
    egl_timer_t *systimer;
    egl_os_t *sysos;
}egl_system_t;

egl_result_t   egl_system_init(egl_system_t *system);
egl_platform_t *egl_sys_plat_get(void);
egl_log_t      *egl_sys_log_get(void);
egl_clock_t    *egl_sys_clock_get(void);
egl_pm_t       *egl_sys_pm_get(void);
egl_timer_t    *egl_sys_timer_get(void);
egl_result_t   egl_sys_delay(uint32_t ms);
egl_result_t   egl_system_deinit(void);
egl_os_t       *egl_sys_os_get(void);

#endif