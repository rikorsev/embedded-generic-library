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

#include "egl_plat.h"

egl_result_t egl_plat_init(egl_platform_t *plat)
{
    EGL_ASSERT_CHECK(plat, EGL_ASSERT_FAIL);
    EGL_ASSERT_CHECK(plat->init, EGL_NOT_SUPPORTED);

    return plat->init();
}

egl_result_t egl_plat_cmd_exec(egl_platform_t *plat, unsigned int id, void *data, size_t *len)
{
    EGL_ASSERT_CHECK(plat, EGL_ASSERT_FAIL);
    EGL_ASSERT_CHECK(plat->cmd, EGL_NOT_SUPPORTED);

    return plat->cmd(id, data, len);
}

egl_result_t egl_plat_deinit(egl_platform_t *plat)
{
    EGL_ASSERT_CHECK(plat, EGL_ASSERT_FAIL);
    EGL_ASSERT_CHECK(plat->deinit, EGL_NOT_SUPPORTED);

    return plat->deinit();
}
