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

#ifndef EGL_RESULT_H
#define EGL_RESULT_H

#include <assert.h>

/** @brief list of EGL results */
typedef enum
{
    EGL_SUCCESS = 0,       /// Operation is successful
    EGL_UNKNOWN,           /// Result of operation is unknown
    EGL_FAIL,              /// Operation has failed
    EGL_PROCESS,           /// Operation still in process
    EGL_NOT_SUPPORTED,     /// Operation is not supported
    EGL_OUT_OF_BOUNDARY,   /// Operation calue is out of boundary
    EGL_INVALID_PARAM,     /// Passed paramiter is invalid
    EGL_INVALID_STATE,     /// The instance is in invalid state
    EGL_ASSERT_FAIL,       /// Assertion fail
    EGL_TIMEOUT,           /// Operation timeout
    EGL_NULL_POINTER,      /// NULL pointer fail
    EGL_CHECKSUM_MISMATCH, /// Checksum mismatch

    EGL_LAST
}egl_result_t;

typedef egl_result_t (*egl_result_error_handler_func_t)(egl_result_t result, char *file, unsigned int line, void *ctx);

typedef struct
{
    egl_result_error_handler_func_t func;
    void *ctx;
}egl_result_error_handler_t;


#define EGL_RESULT(x) egl_result_str_get((x))

#define RETURN_VOID

#if CONFIG_EGL_RESULT_CHECK_ENABLED
#if CONFIG_EGL_RESULT_ERROR_HANDLER_ENABLED
#define __HANDLER(result, file, line) egl_result_error_handler_call(result, file, line)
#else
#define __HANDLER(result, file, line) result
#endif

#define __FILENAME__ (__builtin_strrchr(__FILE__, '/') ? __builtin_strrchr(__FILE__, '/') + 1 : __FILE__)

#define EGL_ASSERT_CHECK(x, retval) if(!(x)) { (void)__HANDLER(EGL_ASSERT_FAIL, __FILENAME__, __LINE__); return retval; }
#define EGL_RESULT_CHECK(x) if((x) != EGL_SUCCESS) { return __HANDLER((x), __FILENAME__, __LINE__); }
#define EGL_RESULT_CHECK_EXIT(x) if((x) != EGL_SUCCESS) { x = __HANDLER((x), __FILENAME__, __LINE__); goto exit; }
#else
#define EGL_ASSERT_CHECK(x, retval)
#define EGL_RESULT_CHECK(x) ((void)(x))
#define EGL_RESULT_CHECK_EXIT(x)
#endif

/**
 * @brief Convert egl result value to string
 */
const char *egl_result_str_get(egl_result_t result);

void egl_result_error_handler_set(egl_result_error_handler_t *hook);
egl_result_error_handler_t *egl_result_error_handler_get(void);
egl_result_t egl_result_error_handler_call(egl_result_t result, char *file, unsigned int line);

#endif
