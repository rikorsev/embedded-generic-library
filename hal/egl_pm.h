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

#ifndef EGL_PM_H
#define EGL_PM_H

#include <stdint.h>

#include "egl_result.h"

typedef struct
{
    egl_result_t (*init)(void);
    egl_result_t (*poweron)(void);
    egl_result_t (*mode_set)(uint32_t mode);
    egl_result_t (*sleep)(uint32_t delay);
    egl_result_t (*reset)(void);
    egl_result_t (*shutdown)(void);
    egl_result_t (*deinit)(void);
}egl_pm_t;

/**
 * @brief Init specific power unit
 *
 * @param pm - pointer to PM instance
 *
 * @return EGL_SUCCESS in case of successful initialization
 */
static inline egl_result_t egl_pm_init(egl_pm_t *pm)
{
    EGL_ASSERT_CHECK(pm, EGL_ASSERT_FAIL);
    EGL_ASSERT_CHECK(pm->init, EGL_NOT_SUPPORTED);

    return pm->init();
}

/**
 * @brief Power On specific unit
 *
 * @param pm - pointer to PM instance
 *
 * @return EGL_SUCCESS in case of successful poweron
 */
static inline egl_result_t egl_pm_poweron(egl_pm_t *pm)
{
    EGL_ASSERT_CHECK(pm, EGL_ASSERT_FAIL);
    EGL_ASSERT_CHECK(pm->poweron, EGL_NOT_SUPPORTED);

    return pm->poweron();
}

/**
 * @brief Set specific power profile to the unit
 * 
 * @param pm - pointer to pm instance
 * @param mode - profile id to apply
 *
 * @return EGL_SUCCESS in case if the profile applied successfuly
 */
static inline egl_result_t egl_pm_mode_set(egl_pm_t *pm, uint32_t mode)
{
    EGL_ASSERT_CHECK(pm, EGL_ASSERT_FAIL);
    EGL_ASSERT_CHECK(pm->mode_set, EGL_NOT_SUPPORTED);

    return pm->mode_set(mode);
}

/**
 * @brief Sleep for specified amoutn of time
 *
 * @param pm - pointer to PM instance
 * @param delay - amount of time to sleep (ms)
 *
 * @return EGL_SUCCESS in case of successful delay
 */
static inline egl_result_t egl_pm_sleep(egl_pm_t *pm, uint32_t delay)
{
    EGL_ASSERT_CHECK(pm, EGL_ASSERT_FAIL);
    EGL_ASSERT_CHECK(pm->sleep, EGL_NOT_SUPPORTED);

    return pm->sleep(delay);
}

/**
 * @brief Perform a unit reset
 *
 * @param plat - pointer to PM instance
 *
 * @return EGL_SUCCESS in case of successful reset
 */
static inline egl_result_t egl_pm_reset(egl_pm_t *pm)
{
    EGL_ASSERT_CHECK(pm, EGL_ASSERT_FAIL);
    EGL_ASSERT_CHECK(pm->reset, EGL_NOT_SUPPORTED);

    return pm->reset();
}

/**
 * @brief Perform a unit shutdown
 *
 * @param pm - pointer to PM instance
 *
 * @return EGL_SUCCESS in case of successful shutdown
 */
static inline egl_result_t egl_pm_shutdown(egl_pm_t *pm)
{
    EGL_ASSERT_CHECK(pm, EGL_ASSERT_FAIL);
    EGL_ASSERT_CHECK(pm->shutdown, EGL_NOT_SUPPORTED);

    return pm->shutdown();
}

/**
 * @brief Denit specific power unit
 *
 * @param pm - pointer to PM instance
 *
 * @return EGL_SUCCESS in case of successful deinitialization
 */
static inline egl_result_t egl_pm_deinit(egl_pm_t *pm)
{
    EGL_ASSERT_CHECK(pm, EGL_ASSERT_FAIL);
    EGL_ASSERT_CHECK(pm->deinit, EGL_NOT_SUPPORTED);

    return pm->deinit();
}


#endif