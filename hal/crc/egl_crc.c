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

#include "egl_crc.h"

egl_result_t egl_crc_init(egl_crc_t *crc, uint32_t poly, uint32_t start_val)
{
    EGL_ASSERT_CHECK(crc, EGL_ASSERT_FAIL);
    EGL_ASSERT_CHECK(crc->init, EGL_NOT_SUPPORTED);

    return crc->init(poly, start_val);
}

egl_result_t egl_crc_reset(egl_crc_t *crc)
{
    EGL_ASSERT_CHECK(crc, EGL_ASSERT_FAIL);
    EGL_ASSERT_CHECK(crc->reset, EGL_NOT_SUPPORTED);

    return crc->reset();
}

uint8_t egl_crc8_calc(egl_crc_t *crc, void *data, size_t len)
{
    EGL_ASSERT_CHECK(crc, EGL_ASSERT_FAIL);
    EGL_ASSERT_CHECK(crc->calc8, EGL_NOT_SUPPORTED);
    EGL_ASSERT_CHECK(data, EGL_ASSERT_FAIL);

    return crc->calc8(data, len);
}

uint16_t egl_crc16_calc(egl_crc_t *crc, void *data, size_t len)
{
    EGL_ASSERT_CHECK(crc, EGL_ASSERT_FAIL);
    EGL_ASSERT_CHECK(crc->calc16, EGL_NOT_SUPPORTED);
    EGL_ASSERT_CHECK(data, EGL_ASSERT_FAIL);

    return crc->calc8(data, len);
}

uint32_t egl_crc32_calc(egl_crc_t *crc, void *data, size_t len)
{
    EGL_ASSERT_CHECK(crc, EGL_ASSERT_FAIL);
    EGL_ASSERT_CHECK(crc->calc32, EGL_NOT_SUPPORTED);
    EGL_ASSERT_CHECK(data, EGL_ASSERT_FAIL);

    return crc->calc32(data, len);
}

egl_result_t egl_crc_deinit(egl_crc_t *crc)
{
    EGL_ASSERT_CHECK(crc, EGL_ASSERT_FAIL);
    EGL_ASSERT_CHECK(crc->deinit, EGL_NOT_SUPPORTED);

    return crc->deinit();
}