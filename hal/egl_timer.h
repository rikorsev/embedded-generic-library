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

#ifndef EGL_TIMER_H
#define EGL_TIMER_H

#include <stdint.h>

#include "egl_result.h"

typedef struct
{
    egl_result_t    (*init)   (void);
    uint32_t        (*get) (void);
    egl_result_t    (*set)    (uint32_t val);
    egl_result_t    (*wait)   (uint32_t delay);
    egl_result_t    (*deinit) (void);
}egl_timer_t;

/**
 * @brief Init timer
 *
 * @param timer - pointer to timer to init
 *
 * @return EGL_SUCCESS in case of successful initialization
 */
static inline egl_result_t egl_timer_init(egl_timer_t *timer)
{
    EGL_ASSERT_CHECK(timer, EGL_ASSERT_FAIL);
    EGL_ASSERT_CHECK(timer->init, EGL_NOT_SUPPORTED);

    return timer->init();
}

/**
 * @brief Get timer value
 *
 * @param timer - pointer to th timer
 *
 * @return current value of the timer
 */
static inline uint32_t egl_timer_get(egl_timer_t *timer)
{
    EGL_ASSERT_CHECK(timer, 0);
    EGL_ASSERT_CHECK(timer->get, 0);

    return timer->get();
}

/**
 * @brief Set timer value
 *
 * @param timer - pointer to the timer
 * @param val - value to set
 *
 * @return EGL_SUCCES in case of successfull setting
 */
static inline egl_result_t egl_timer_set(egl_timer_t *timer, uint32_t val)
{
    EGL_ASSERT_CHECK(timer, EGL_ASSERT_FAIL);
    EGL_ASSERT_CHECK(timer->set, EGL_NOT_SUPPORTED);

    return timer->set(val);
}

/**
 * @brief Tick timer for a specified number of ticks
 *
 * @param timer - pointer to the timer
 * @param delay - ticks to wait
 *
 * @return EGL_SUCCESS in case of successful wait, or an error code if the wait failed
 */
static inline egl_result_t egl_timer_wait(egl_timer_t *timer, uint32_t cnt)
{
    EGL_ASSERT_CHECK(timer, EGL_ASSERT_FAIL);
    EGL_ASSERT_CHECK(timer->wait, EGL_NOT_SUPPORTED);

    return timer->wait(cnt);
}

/**
 * @brief Deinit the timer
 *
 * @param timer - pointer to the timer
 *
 * @return EGL_SUCCESS in case of successful deinitialization
 */
static inline egl_result_t egl_timer_deinit(egl_timer_t *timer)
{
    EGL_ASSERT_CHECK(timer, EGL_ASSERT_FAIL);
    EGL_ASSERT_CHECK(timer->deinit, EGL_NOT_SUPPORTED);

    return timer->deinit();
}

#endif /* EGL_TIMER_H */
