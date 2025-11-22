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
#include "egl_clock.h"

egl_result_t egl_clock_init(egl_clock_t *clock)
{
    EGL_ASSERT_CHECK(clock, EGL_ASSERT_FAIL);
    EGL_ASSERT_CHECK(clock->init, EGL_NOT_SUPPORTED);

    return clock->init();
}

uint32_t egl_clock_get(egl_clock_t *clock)
{
    if(clock == NULL)
    {
        return 0;
    }

    if(clock->get == NULL)
    {
        return 0;
    }

    return clock->get();
}

egl_result_t egl_clock_deinit(egl_clock_t *clock)
{
    EGL_ASSERT_CHECK(clock, EGL_ASSERT_FAIL);
    EGL_ASSERT_CHECK(clock->deinit, EGL_NOT_SUPPORTED);

    return clock->deinit();
}

