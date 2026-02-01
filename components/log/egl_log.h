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

#ifndef EGL_LOG_H
#define EGL_LOG_H

#include <stdarg.h>

#include "egl_timer.h"
#include "egl_iface.h"

typedef enum
{
    EGL_LOG_LEVEL_DEBUG,
    EGL_LOG_LEVEL_INFO,
    EGL_LOG_LEVEL_WARN,
    EGL_LOG_LEVEL_ERROR,
    EGL_LOG_LEVEL_FAIL,
    EGL_LOG_LEVEL_LAST
}egl_log_level_t;

typedef egl_result_t (*egl_log_frontend_func_t)(char *output, size_t *size, egl_timer_t *timer, egl_log_level_t lvl, char *module, char *fmt, va_list arg);

typedef struct
{
    egl_log_frontend_func_t frontend;
    egl_iface_t             *iface;
    egl_timer_t             *timer;
    char                    *buff;
    size_t                  size;
}egl_log_t;

#if CONFIG_EGL_LOG_ENABLED
#include "egl_system.h"

#define EGL_LOG_DEBUG(fmt, ...) egl_log(SYSLOG, EGL_LOG_LEVEL_DEBUG, __FILENAME__, fmt, ##__VA_ARGS__)
#define EGL_LOG_INFO(fmt, ...)  egl_log(SYSLOG, EGL_LOG_LEVEL_INFO,  __FILENAME__, fmt, ##__VA_ARGS__)
#define EGL_LOG_WARN(fmt, ...)  egl_log(SYSLOG, EGL_LOG_LEVEL_WARN,  __FILENAME__, fmt, ##__VA_ARGS__)
#define EGL_LOG_ERROR(fmt, ...) egl_log(SYSLOG, EGL_LOG_LEVEL_ERROR, __FILENAME__, fmt, ##__VA_ARGS__)
#define EGL_LOG_FAIL(fmt, ...)  egl_log(SYSLOG, EGL_LOG_LEVEL_FAIL,  __FILENAME__, fmt, ##__VA_ARGS__)

/**
 * @brief Init log module
 *
 * @param log   - pointer to log module
 *
 * @return EGL_SUCCESS in case of siccessfull initialization
 */
egl_result_t egl_log_init(egl_log_t *log);

/**
 * @brief Deinit log module
 *
 * @param log - pointer to log module
 *
 * @return EGL_SUCCESS in case of successfull deinitialization
 */
egl_result_t egl_log_deinit(egl_log_t *log);

/**
 * @brief Finction to log specific message
 *
 * Usually the function is not used directly. It is triggered through corresponding macroses
 * Like: EGL_LOG_INFO, EGL_LOG_ERROR etc
 *
 * @param log    - pointer to the log instance
 * @param lvl    - log level of the message like EGL_LOG_LEVEL_DEBUG, EGL_LOG_LEVEL_INFO etc
 * @param module - pointer to module name from which log function has called
 * @param format - pointer to format stirng
 * @param args   - variable number of arguments
 *
 * @return EGL_SUCCESS in case if the message has been logged successfully
 */
egl_result_t egl_log(egl_log_t *log, egl_log_level_t lvl, char *module, char *format, ...);

/**
 * @brief Setter for log frontend
 *
 * @param log - pointer to the log instance
 * @param frontend - frontend function to set
 *
 * @return EGL_SUCCESS if log frontend has been set successfully
 */
egl_result_t egl_log_frontend_set(egl_log_t *log, egl_log_frontend_func_t frontend);

/**
 * @brief Helper function (uitil) for logging out different kind of buffers in hexedecemal format
 *
 * @param log - pointer to the log instance
 * @param lvl - log level of the message like EGL_LOG_LEVEL_DEBUG, EGL_LOG_LEVEL_INFO etc
 * @param name - name of output block (name of the buffer to logout)
 * @param buff - buffer to logout
 * @param len - length of the buffer
 * @param row - number of elements in row
 *
 * @return EGL_SUCCESS in case if the buffer has been logged successfully
 */
egl_result_t egl_log_buff(egl_log_t *log, egl_log_level_t lvl, char *name, uint8_t *buff, size_t len, size_t row);

#else
#define EGL_LOG_DEBUG(fmt, ...)
#define EGL_LOG_INFO(fmt, ...)
#define EFL_LOG_WARN(fmt, ...)
#define EGL_LOG_ERROR(fmt, ...)
#define EGL_LOG_FAIL(fmt, ...)

egl_result_t egl_log_init(egl_log_t *log) { return EGL_SUCCESS; }
egl_result_t egl_log_deinit(egl_log_t *log) { return EGL_SUCCESS; }
egl_result_t egl_log(egl_log_t *log, egl_log_level_t lvl, char *module, char *format, ...) { return EGL_SUCCESS; }
egl_result_t egl_log_buff(egl_log_t *log, egl_log_level_t lvl, char *name, uint8_t *buff, size_t len, size_t row) { return EGL_SUCCESS; }
#endif

#endif /* EGL_LOG_H */
