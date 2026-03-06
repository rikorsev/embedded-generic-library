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

#include "egl_lib.h"

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

static void *mux_handle = NULL;
static const char *m_level_str[] =
{
    BLUE   "DEBUG" WHITE,
    GREEN  "INFO"  WHITE,
    YELLOW "WARN"  WHITE,
    RED    "ERROR" WHITE,
    RED    "FAIL"  WHITE
};

static egl_result_t egl_log_front_os_init(void)
{
    egl_result_t result;

    static egl_os_mux_ctx mux_ctx;

    result = egl_os_mux_create(SYSOS, &mux_handle, "radio_mux", EGL_OS_MUX_TYPE_REGULAR, &mux_ctx);
    EGL_RESULT_CHECK(result);

    return result;
}

static egl_result_t egl_log_front_os_lock(void)
{
    egl_result_t result;
    void *thread_handle = NULL;

    result = egl_os_thread_get(SYSOS, &thread_handle);
    EGL_RESULT_CHECK(result);

    if(thread_handle != NULL)
    {
        result = egl_os_mux_lock(SYSOS, mux_handle, EGL_OS_WAIT_FOREVER);
        EGL_RESULT_CHECK(result);
    }

    return result;
}

static egl_result_t egl_log_front_os_unlock(void)
{
    egl_result_t result;
    void *thread_handle = NULL;

    result = egl_os_thread_get(SYSOS, &thread_handle);
    EGL_RESULT_CHECK(result);

    if(thread_handle != NULL)
    {
        result = egl_os_mux_unlock(SYSOS, mux_handle);
        EGL_RESULT_CHECK(result);
    }

    return result;
}

static egl_result_t egl_log_front_os_format(char *output, size_t *size, egl_log_level_t lvl, char *module, char *fmt, va_list arg)
{
    int outlen;
    unsigned int offset = 0;
    void *thread_handle = NULL;
    egl_result_t result = EGL_SUCCESS;

    outlen = snprintf(output, *size, BOLD "[%08u]", (unsigned int)egl_timer_get(SYSTIMER));
    EGL_ASSERT_CHECK(outlen > 0, EGL_ASSERT_FAIL);
    offset += outlen;

    outlen = snprintf(output + offset, *size - offset, BOLD "[%s]", m_level_str[lvl]);
    EGL_ASSERT_CHECK(outlen > 0, EGL_ASSERT_FAIL);
    offset += outlen;

    if(thread_handle != NULL)
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

        outlen = snprintf(output + offset, *size - offset, BOLD "[%s:%u]", thread_name, thread_prio);
        EGL_ASSERT_CHECK(outlen > 0, EGL_ASSERT_FAIL);
        offset += outlen;
    }

    outlen = snprintf(output + offset, *size - offset, "%s: " RESET, module);
    EGL_ASSERT_CHECK(outlen > 0, EGL_ASSERT_FAIL);
    offset += outlen;

    outlen = vsnprintf(output + offset, *size - offset, fmt, arg);
    EGL_ASSERT_CHECK(outlen > 0, EGL_ASSERT_FAIL);
    offset += outlen;

    outlen = snprintf(output + offset, *size - offset, "\r\n");
    EGL_ASSERT_CHECK(outlen > 0, EGL_ASSERT_FAIL);
    offset += outlen;

    *size = offset;

    return result;
}

static egl_result_t egl_log_front_os_deinit(void)
{
    egl_result_t result;

    result = egl_os_mux_destroy(SYSOS, mux_handle);
    EGL_RESULT_CHECK(result);

    return result;
}

const egl_log_front_t egl_log_front_os_inst =
{
    .init = egl_log_front_os_init,
    .lock = egl_log_front_os_lock,
    .unlock = egl_log_front_os_unlock,
    .format = egl_log_front_os_format,
    .deinit = egl_log_front_os_deinit
};

egl_log_front_t *egl_log_front_os_get(void)
{
    return (egl_log_front_t *) &egl_log_front_os_inst;
}
