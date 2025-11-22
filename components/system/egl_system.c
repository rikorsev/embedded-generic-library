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

#include "egl_system.h"

static egl_system_t *system_ptr = NULL;

egl_result_t egl_system_init(egl_system_t *system)
{
    egl_result_t result = EGL_SUCCESS;

    EGL_ASSERT_CHECK(system != NULL, EGL_NULL_POINTER);

    system_ptr = system;

    if(system->plat != NULL)
    {
        result = egl_plat_init(system->plat);
        EGL_ASSERT_CHECK(result == EGL_SUCCESS || result == EGL_NOT_SUPPORTED, result);
    }

    if(system->syspm != NULL)
    {
        result = egl_pm_init(system->syspm);
        EGL_ASSERT_CHECK(result == EGL_SUCCESS || result == EGL_NOT_SUPPORTED, result);
    }

    if(system->sysclock != NULL)
    {
        result = egl_clock_init(system->sysclock);
        EGL_ASSERT_CHECK(result == EGL_SUCCESS || result == EGL_NOT_SUPPORTED, result);
    }

    if(system->systimer != NULL)
    {
        result = egl_timer_init(system->systimer);
        EGL_ASSERT_CHECK(result == EGL_SUCCESS || result == EGL_NOT_SUPPORTED, result);
    }

#if CONFIG_EGL_LOG_ENABLED
    if(system->syslog != NULL)
    {
        result = egl_log_init(system->syslog);
        EGL_ASSERT_CHECK(result == EGL_SUCCESS || result == EGL_NOT_SUPPORTED, result);
    }
#endif

    return result;
}

egl_platform_t *egl_sys_plat_get(void)
{
    return system_ptr->plat;
}

#if CONFIG_EGL_LOG_ENABLED
egl_log_t *egl_sys_log_get(void)
{
    return system_ptr->syslog;
}
#endif

egl_clock_t *egl_sys_clock_get(void)
{
    return system_ptr->sysclock;
}

egl_pm_t *egl_sys_pm_get(void)
{
    return system_ptr->syspm;
}

egl_timer_t *egl_sys_timer_get(void)
{
    return system_ptr->systimer;
}

egl_result_t egl_sys_delay(uint32_t ms)
{
    EGL_ASSERT_CHECK(system_ptr != NULL, EGL_INVALID_STATE);
    EGL_ASSERT_CHECK(system_ptr->systimer != NULL, EGL_NOT_SUPPORTED);

    egl_result_t result;

    result = egl_timer_wait(system_ptr->systimer, ms);
    EGL_RESULT_CHECK(result);

    return result;
}

egl_result_t egl_system_deinit(void)
{
    EGL_ASSERT_CHECK(system_ptr != NULL, EGL_INVALID_STATE);

    egl_result_t result = EGL_SUCCESS;

#if CONFIG_EGL_LOG_ENABLED
    if(system_ptr->syslog != NULL)
    {
        result = egl_log_deinit(system_ptr->syslog);
        EGL_ASSERT_CHECK(result == EGL_SUCCESS || result == EGL_NOT_SUPPORTED, result);
    }
#endif

    if(system_ptr->systimer != NULL)
    {
        result = egl_timer_deinit(system_ptr->systimer);
        EGL_ASSERT_CHECK(result == EGL_SUCCESS || result == EGL_NOT_SUPPORTED, result);
    }

    if(system_ptr->syspm != NULL)
    {
        result = egl_pm_deinit(system_ptr->syspm);
        EGL_ASSERT_CHECK(result == EGL_SUCCESS || result == EGL_NOT_SUPPORTED, result);
    }

    if(system_ptr->sysclock != NULL)
    {
        result = egl_clock_deinit(system_ptr->sysclock);
        EGL_ASSERT_CHECK(result == EGL_SUCCESS || result == EGL_NOT_SUPPORTED, result);
    }

    if(system_ptr->plat != NULL)
    {
        result = egl_plat_deinit(system_ptr->plat);
        EGL_ASSERT_CHECK(result == EGL_SUCCESS || result == EGL_NOT_SUPPORTED, result);
    }

    return result;
}