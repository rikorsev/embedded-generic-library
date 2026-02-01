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

#include <stdio.h>
#include <stdarg.h>

#include "egl_log.h"

#if CONFIG_EGL_LOG_COLOR_ENABLED
#define RESET   "\x1b[0m"
#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define WHITE   "\x1b[37m"
#define BOLD    "\x1b[1m"
#else
#define RESET
#define RED
#define GREEN
#define YELLOW
#define BLUE
#define WHITE
#define BOLD
#endif

static const char *m_level_str[] =
{
    BLUE   "DEBUG" WHITE,
    GREEN  "INFO"  WHITE,
    YELLOW "WARN"  WHITE,
    RED    "ERROR" WHITE,
    RED    "FAIL"  WHITE
};

egl_result_t egl_log_frontend_default_bare(char *output, size_t *size, egl_timer_t *timer, egl_log_level_t lvl, char *module, char *fmt, va_list arg)
{
    int result;
    unsigned int offset = 0;

    if(timer)
    {
        result = snprintf(output, *size, BOLD "[%08u]",
                                                (unsigned int)egl_timer_get(timer));
        EGL_ASSERT_CHECK(result > 0, EGL_ASSERT_FAIL);
        offset += result;
    }

    result = snprintf(output + offset, *size - offset, BOLD "[%s]", m_level_str[lvl]);
    EGL_ASSERT_CHECK(result > 0, EGL_ASSERT_FAIL);
    offset += result;

    result = snprintf(output + offset, *size - offset, "%s: " RESET, module);
    EGL_ASSERT_CHECK(result > 0, EGL_ASSERT_FAIL);
    offset += result;

    result = vsnprintf(output + offset, *size - offset, fmt, arg);
    EGL_ASSERT_CHECK(result > 0, EGL_ASSERT_FAIL);
    offset += result;

    result = snprintf(output + offset, *size - offset, "\r\n");
    EGL_ASSERT_CHECK(result > 0, EGL_ASSERT_FAIL);
    offset += result;

    *size = offset;

    return EGL_SUCCESS;
}

egl_result_t egl_log_frontend_default_os(char *output, size_t *size, egl_timer_t *timer, egl_log_level_t lvl, char *module, char *fmt, va_list arg)
{
    int result;
    unsigned int offset = 0;
    void *thread_handle = NULL;

    if(timer)
    {
        result = snprintf(output, *size, BOLD "[%08u]",
                                                (unsigned int)egl_timer_get(timer));
        EGL_ASSERT_CHECK(result > 0, EGL_ASSERT_FAIL);
        offset += result;
    }

    result = snprintf(output + offset, *size - offset, BOLD "[%s]", m_level_str[lvl]);
    EGL_ASSERT_CHECK(result > 0, EGL_ASSERT_FAIL);
    offset += result;

    result = egl_os_thread_get(SYSOS, &thread_handle);
    EGL_RESULT_CHECK(result);

    if(thread_handle)
    {
        char *thread_name = NULL;
        unsigned int thread_prio = 0;

        result = egl_os_thread_name_get(SYSOS, thread_handle, &thread_name);
        EGL_RESULT_CHECK(result);

        if(thread_name == NULL)
        {
            thread_name = "unnamed";
        }

        result = egl_os_thread_prio_get(SYSOS, thread_handle, &thread_prio);
        EGL_RESULT_CHECK(result);

        result = snprintf(output + offset, *size - offset, BOLD "[%s:%u]", thread_name, thread_prio);
        EGL_ASSERT_CHECK(result > 0, EGL_ASSERT_FAIL);
        offset += result;
    }

    result = snprintf(output + offset, *size - offset, "%s: " RESET, module);
    EGL_ASSERT_CHECK(result > 0, EGL_ASSERT_FAIL);
    offset += result;

    result = vsnprintf(output + offset, *size - offset, fmt, arg);
    EGL_ASSERT_CHECK(result > 0, EGL_ASSERT_FAIL);
    offset += result;

    result = snprintf(output + offset, *size - offset, "\r\n");
    EGL_ASSERT_CHECK(result > 0, EGL_ASSERT_FAIL);
    offset += result;

    *size = offset;

    return EGL_SUCCESS;
}
