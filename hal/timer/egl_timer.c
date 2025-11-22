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
#include "egl_timer.h"

egl_result_t egl_timer_init(egl_timer_t *timer)
{
    EGL_ASSERT_CHECK(timer, EGL_ASSERT_FAIL);
    EGL_ASSERT_CHECK(timer->init, EGL_NOT_SUPPORTED);

    return timer->init();
}

uint32_t egl_timer_get(egl_timer_t *timer)
{
    EGL_ASSERT_CHECK(timer, 0);
    EGL_ASSERT_CHECK(timer->get, 0);

    return timer->get();
}

egl_result_t egl_timer_set(egl_timer_t *timer, uint32_t val)
{
    EGL_ASSERT_CHECK(timer, EGL_ASSERT_FAIL);
    EGL_ASSERT_CHECK(timer->set, EGL_NOT_SUPPORTED);

    return timer->set(val);
}

egl_result_t egl_timer_wait(egl_timer_t *timer, uint32_t cnt)
{
    EGL_ASSERT_CHECK(timer, EGL_ASSERT_FAIL);
    EGL_ASSERT_CHECK(timer->wait, EGL_NOT_SUPPORTED);

    return timer->wait(cnt);
}

egl_result_t egl_timer_deinit(egl_timer_t *timer)
{
    EGL_ASSERT_CHECK(timer, EGL_ASSERT_FAIL);
    EGL_ASSERT_CHECK(timer->deinit, EGL_NOT_SUPPORTED);

    return timer->deinit();
}
