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

#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>

#include "egl_result.h"
#include "egl_pio.h"

egl_result_t egl_pio_init(egl_pio_t *pio)
{
    EGL_ASSERT_CHECK(pio, EGL_ASSERT_FAIL);
    EGL_ASSERT_CHECK(pio->init, EGL_NOT_SUPPORTED);

    return pio->init();
}

egl_result_t egl_pio_set(egl_pio_t *pio, bool state)
{
    EGL_ASSERT_CHECK(pio, EGL_ASSERT_FAIL);
    EGL_ASSERT_CHECK(pio->set, EGL_NOT_SUPPORTED);

    return pio->set(state);
}

egl_result_t egl_pio_get(egl_pio_t *pio, bool *state)
{
    EGL_ASSERT_CHECK(pio, EGL_ASSERT_FAIL);
    EGL_ASSERT_CHECK(pio->get, EGL_NOT_SUPPORTED);

    return pio->get(state);
}

egl_result_t egl_pio_toggle(egl_pio_t *pio)
{
    EGL_ASSERT_CHECK(pio, EGL_ASSERT_FAIL);

    bool state;

    egl_result_t result = egl_pio_get(pio, &state);
    EGL_RESULT_CHECK(result);

    if(state)
    {
        result = egl_pio_set(pio, false);
        EGL_RESULT_CHECK(result);
    }
    else
    {
        result = egl_pio_set(pio, true);
        EGL_RESULT_CHECK(result);
    }

    return result;
}

egl_result_t egl_pio_callback_set(egl_pio_t *pio, egl_pio_callback_t callback)
{
    EGL_ASSERT_CHECK(pio, EGL_ASSERT_FAIL);

    pio->callback = callback;

    return EGL_SUCCESS;
}

egl_result_t egl_pio_deinit(egl_pio_t *pio)
{
    EGL_ASSERT_CHECK(pio, EGL_ASSERT_FAIL);
    EGL_ASSERT_CHECK(pio->deinit, EGL_NOT_SUPPORTED);

    return pio->deinit();
}
