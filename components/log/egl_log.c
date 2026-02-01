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

#include <stdarg.h>
#include <string.h>
#include <stdio.h>

#include "egl_result.h"
#include "egl_log.h"

egl_result_t egl_log_init(egl_log_t *log)
{
    EGL_ASSERT_CHECK(log, EGL_ASSERT_FAIL);
    EGL_ASSERT_CHECK(log->iface, EGL_ASSERT_FAIL);

    egl_result_t result;

    result = egl_iface_init(log->iface);
    EGL_RESULT_CHECK(result);

    if(log->timer)
    {
        result = egl_timer_init(log->timer);
        EGL_RESULT_CHECK(result);
    }

    return result;
}

egl_result_t egl_log(egl_log_t *log, egl_log_level_t lvl, char *module, char *format, ...)
{
    va_list arg;

    EGL_ASSERT_CHECK(log, EGL_NULL_POINTER);
    EGL_ASSERT_CHECK(format, EGL_NULL_POINTER);
    EGL_ASSERT_CHECK(lvl < EGL_LOG_LEVEL_LAST, EGL_INVALID_PARAM);
    EGL_ASSERT_CHECK(log->frontend, EGL_NULL_POINTER);
    EGL_ASSERT_CHECK(log->iface, EGL_NULL_POINTER);

    egl_result_t result;
    unsigned int size = log->size;

    va_start(arg, format);
    result = log->frontend(log->buff, &size, log->timer, lvl, module, format, arg);
    va_end(arg);
    EGL_RESULT_CHECK(result);

    result = egl_iface_write(log->iface, log->buff, &size);
    EGL_RESULT_CHECK(result);

    return result;
}

egl_result_t egl_log_frontend_set(egl_log_t *log, egl_log_frontend_func_t frontend)
{
    EGL_ASSERT_CHECK(log, EGL_NULL_POINTER);

    log->frontend = frontend;

    return EGL_SUCCESS;
}

egl_result_t egl_log_buff(egl_log_t *log, egl_log_level_t lvl, char *name, uint8_t *buff, size_t len, size_t row)
{
    EGL_ASSERT_CHECK(log, EGL_NULL_POINTER);
    EGL_ASSERT_CHECK(buff, EGL_NULL_POINTER);
    EGL_ASSERT_CHECK(name, EGL_NULL_POINTER);

    egl_result_t result;
    char formatted[row * 3 + 1]; // 2 hex digits + space + null terminator

    result = egl_log(log, lvl, name, "Size(%u):", (unsigned int)len);
    EGL_RESULT_CHECK(result);

    for(size_t i = 0; i < len; i += row)
    {
        memset(formatted, 0, sizeof(formatted));

        for(size_t j = 0; j < row; j++)
        {
            snprintf(formatted + j * 3, sizeof(formatted) - j * 3, "%02x ", buff[i + j]);
        }

        result = egl_log(log, lvl, name, "%s", formatted);
        EGL_RESULT_CHECK(result);
    }

    return EGL_SUCCESS;
}

egl_result_t egl_log_deinit(egl_log_t *log)
{
    EGL_ASSERT_CHECK(log, EGL_ASSERT_FAIL);
    EGL_ASSERT_CHECK(log->iface, EGL_ASSERT_FAIL);

    egl_result_t result;

    result = egl_iface_deinit(log->iface);
    EGL_RESULT_CHECK(result);

    if(log->timer)
    {
        result = egl_timer_deinit(log->timer);
        EGL_RESULT_CHECK(result);
    }

    return result;
}
