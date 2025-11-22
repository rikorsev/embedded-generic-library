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

#include <stdlib.h>

#include "egl_result.h"
#include "egl_plat.h"

egl_result_t egl_plat_init(egl_platform_t *plat)
{
    EGL_ASSERT_CHECK(plat, EGL_ASSERT_FAIL);
    EGL_ASSERT_CHECK(plat->init, EGL_NOT_SUPPORTED);

    return plat->init();
}

egl_result_t egl_plat_boot(egl_platform_t *plat, unsigned int slot_idx)
{
    EGL_ASSERT_CHECK(plat, EGL_ASSERT_FAIL);
    EGL_ASSERT_CHECK(plat->boot, EGL_NOT_SUPPORTED);

    return plat->boot(slot_idx);
}

egl_result_t egl_plat_deinit(egl_platform_t *plat)
{
    EGL_ASSERT_CHECK(plat, EGL_ASSERT_FAIL);
    EGL_ASSERT_CHECK(plat->deinit, EGL_NOT_SUPPORTED);

    return plat->deinit();
}
