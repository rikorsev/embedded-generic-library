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

#include "egl_result.h"

static const char *egl_result_str[] =
{
    "EGL_SUCCESS",
    "EGL_UNKNOWN",
    "EGL_FAIL",
    "EGL_PROCESS",
    "EGL_NOT_SUPPORTED",
    "EGL_OUT_OF_BOUNDARY",
    "EGL_INVALID_PARAM",
    "EGL_INVALID_STATE",
    "EGL_ASSERT_FAIL",
    "EGL_TIMEOUT",
    "EGL_NULL_POINTER",
    "EGL_CHECKSUM_MISMATCH",
};

#if CONFIG_EGL_RESULT_ERROR_HANDLER_ENABLED
static egl_result_error_handler_t *egl_result_error_handler = NULL;
#endif

void egl_result_error_handler_set(egl_result_error_handler_t *handler)
{
#if CONFIG_EGL_RESULT_ERROR_HANDLER_ENABLED
    egl_result_error_handler = handler;
#endif
}

egl_result_error_handler_t *egl_result_error_handler_get(void)
{
#if CONFIG_EGL_RESULT_ERROR_HANDLER_ENABLED
    return egl_result_error_handler;
#else
    return NULL;
#endif
}

egl_result_t egl_result_error_handler_call(egl_result_t result, char *file, unsigned int line)
{
#if CONFIG_EGL_RESULT_ERROR_HANDLER_ENABLED
    if(egl_result_error_handler != NULL && egl_result_error_handler->func != NULL)
    {
        return egl_result_error_handler->func(result, file, line, egl_result_error_handler->ctx);
    }
#endif
    return result;
}

const char *egl_result_str_get(egl_result_t result)
{
    assert(result < EGL_LAST);

    return egl_result_str[result];
}
