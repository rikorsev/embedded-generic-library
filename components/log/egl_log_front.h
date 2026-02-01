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

#ifndef EGL_LOG_FRONT_H
#define EGL_LOG_FRONT_H

#include <stdarg.h>

#include "egl_result.h"
#include "egl_timer.h"

egl_result_t egl_log_frontend_default_bare(char *output, size_t *size, egl_timer_t *timer, egl_log_level_t lvl, char *module, char *fmt, va_list arg);
egl_result_t egl_log_frontend_default_os(char *output, size_t *size, egl_timer_t *timer, egl_log_level_t lvl, char *module, char *fmt, va_list arg);

#endif