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

#ifndef EGL_PIO_H
#define EGL_PIO_H

#include <stdbool.h>

typedef void (*egl_pio_callback_t)(void *data);

typedef struct
{
    egl_result_t (*init)   (void);
    egl_result_t (*set)    (bool state);
    egl_result_t (*toggle) (void);
    egl_result_t (*get)    (bool *state);
    egl_result_t (*deinit) (void);
    egl_pio_callback_t callback;
}egl_pio_t;

/**
 * @brief Init PIO
 *
 * @param pio - pointer to pio to init
 *
 * @return EGL_SUCCESS in case of successful initialization
 */
static inline egl_result_t egl_pio_init(egl_pio_t *pio)
{
    EGL_ASSERT_CHECK(pio, EGL_ASSERT_FAIL);
    EGL_ASSERT_CHECK(pio->init, EGL_NOT_SUPPORTED);

    return pio->init();
}

/**
 * @brief Set state of PIO
 *
 * @param pio - pointer to pio to set state
 * @param state - state valie to set
 *
 * @return EGL_SUCCES in case of successful setting
 */
static inline egl_result_t egl_pio_set(egl_pio_t *pio, bool state)
{
    EGL_ASSERT_CHECK(pio, EGL_ASSERT_FAIL);
    EGL_ASSERT_CHECK(pio->set, EGL_NOT_SUPPORTED);

    return pio->set(state);
}

/**
 * @brief Get PIO state
 *
 * @param pio - pionter to pio to get statte
 *
 * @return EGL_SUCCES in case of successful getting
 */
static inline egl_result_t egl_pio_get(egl_pio_t *pio, bool *state)
{
    EGL_ASSERT_CHECK(pio, EGL_ASSERT_FAIL);
    EGL_ASSERT_CHECK(pio->get, EGL_NOT_SUPPORTED);

    return pio->get(state);
}

/**
 * @brief Toggle PIO state
 *
 * @param pio - pointer to pio to toggle state
 *
 * @return EGL_SUCCESS in case of successfull toggling
 */
static inline egl_result_t egl_pio_toggle(egl_pio_t *pio)
{
    EGL_ASSERT_CHECK(pio, EGL_ASSERT_FAIL);
    EGL_ASSERT_CHECK(pio->toggle, EGL_NOT_SUPPORTED);

    return pio->toggle();
}

/**
 * @brief Set callback for PIO
 *
 * The call back will be triggered as soon as pio will change it state according to it settings
 * Usefull to track button state
 *
 * @param pio - pionter to pio to set callback
 * @param callback - pointer to callback function
 *
 * @return EGL_SUCCESS on case if callback has been set successfully
 */
static inline egl_result_t egl_pio_callback_set(egl_pio_t *pio, egl_pio_callback_t callback)
{
    EGL_ASSERT_CHECK(pio, EGL_ASSERT_FAIL);

    pio->callback = callback;

    return EGL_SUCCESS;
}

/**
 * @brief Deinit PIO
 *
 * @param pio - poiniter to pio to deinit
 *
 * @return EGL_SUCCESS in case of successful deinitialization
 */
static inline egl_result_t egl_pio_deinit(egl_pio_t *pio)
{
    EGL_ASSERT_CHECK(pio, EGL_ASSERT_FAIL);
    EGL_ASSERT_CHECK(pio->deinit, EGL_NOT_SUPPORTED);

    return pio->deinit();
}

#endif