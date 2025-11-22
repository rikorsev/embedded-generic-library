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

#ifndef EGL_PLAT_H
#define EGL_PLAT_H

#include <stdint.h>

#include "egl_result.h"

typedef struct
{
    egl_result_t    (*init)(void);
    egl_result_t    (*boot)(unsigned int slot_idx);
    egl_result_t    (*deinit)(void);
}egl_platform_t;

/**
 * @brief General platform initialization
 *
 * @param plat - pointer to platform
 *
 * @return EGL_SUCCESS in case of successful deinitialization
 */
egl_result_t egl_plat_init(egl_platform_t *plat);

/**
 * @brief Deinitialize platform
 *
 * @param plat - pointer to platform instance
 *
 * @return EGL_SUCCESS in case of successful deinitialization
 */
egl_result_t egl_plat_deinit(egl_platform_t *plat);

/**
 * @brief Boot application from specific slot
 *
 * @param plat - pointer to platform instance
 * @param slot_idx - slot index to boot
 *
 * @return Usualli it shouldn't return from the function. If it returns, return value will carry
 *         some nrgative result
 */
egl_result_t egl_plat_boot(egl_platform_t *plat, unsigned int slot_idx);

#endif