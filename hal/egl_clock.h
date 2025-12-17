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

#ifndef EGL_CLOCK_H
#define EGL_CLOCK_H

#include <stdint.h>
#include "egl_result.h"

typedef struct
{
    egl_result_t (*init)(void);
    uint32_t (*get)(void);
    egl_result_t (*deinit)(void);
}egl_clock_t;

/**
 * @brief Initi clock unit
 *
 * @param clock - pointer to clock unit to init
 * 
 * @return EGL_SUCCESS in case of successfull initialization
 */
static inline egl_result_t egl_clock_init(egl_clock_t *clock)
{
    EGL_ASSERT_CHECK(clock, EGL_ASSERT_FAIL);
    EGL_ASSERT_CHECK(clock->init, EGL_NOT_SUPPORTED);

    return clock->init();
}

/**
 * @brief Get frequency if the clock unit
 *
 * @param clock - pointer to clock to get frequency
 *
 * @return the clock unit frequency in Hz
 */
static inline uint32_t egl_clock_get(egl_clock_t *clock)
{
    EGL_ASSERT_CHECK(clock, 0);
    EGL_ASSERT_CHECK(clock->get, 0);

    return clock->get();
}

/**
 * @brief Deinit clock unit
 *
 * @param clock - pointer to clock unit to deinit
 *
 * @return EGL_SUCCESS in case of successfull deinitialization
 */
static inline egl_result_t egl_clock_deinit(egl_clock_t *clock)
{
    EGL_ASSERT_CHECK(clock, EGL_ASSERT_FAIL);
    EGL_ASSERT_CHECK(clock->deinit, EGL_NOT_SUPPORTED);

    return clock->deinit();
}

#endif
