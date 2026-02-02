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
#ifndef EGL_OS_H
#define EGL_OS_H

#include <limits.h>
#include "egl_result.h"

#define EGL_OS_WAIT_FOREWER (UINT_MAX)
#define EGL_OS_NO_WAIT (0)

typedef void (egl_os_thread_entry_func_t)(void *data);
typedef void (egl_os_timer_handler_func_t)(void *data);

typedef enum
{
    EGL_OS_FLAGS_OPT_WAIT_ANY = 0,
    EGL_OS_FLAGS_OPT_WAIT_ALL = 1,
    EGL_OS_FLAGS_OPT_NO_CLEAR = 2
}egl_os_flags_opt_t;

typedef enum
{
    EGL_OS_MUX_TYPE_REGULAR = 0,
    EGL_OS_MUX_TYPE_RECURSIVE = 1,
    EGL_OS_MUX_TYPE_INHERIT = 2
}egl_os_mux_type_t;

typedef enum
{
    EGL_OS_TIMER_TYPE_ONESHOT = 0,
    EGL_OS_TIMER_TYPE_PERIODIC = 1
}egl_os_timer_type_t;

typedef enum
{
    EGL_OS_NOT_INITED = 0,
    EGL_OS_RUNNING,
    EGL_OS_SUSPEND,
    EGL_OS_FAILED
}egl_os_state_t;

typedef struct
{
    egl_result_t (*init)(void);
    egl_result_t (*start)(void *param, ...);
    egl_result_t (*current)(void **handle);
    egl_result_t (*sleep)(unsigned int tick);
    egl_result_t (*state)(egl_os_state_t *state);

    struct
    {
        egl_result_t (*create)(void **handle, char *name,
                            egl_os_thread_entry_func_t entry,
                            void *data, void *stack,
                            size_t stack_size,
                            unsigned int priority, void *ctx);

        egl_result_t (*suspend)(void *handle);
        egl_result_t (*resume)(void *handle);
        egl_result_t (*name_get)(void *handle, char **name);
        egl_result_t (*prio_set)(void *handle, unsigned int prio);
        egl_result_t (*prio_get)(void *handle, unsigned int *prio);
        egl_result_t (*destroy)(void *handle);
    }thread;

    struct
    {
        egl_result_t (*create)(void **handle, char *name, void *ctx);
        egl_result_t (*set)(void *handle, unsigned int flags);
        egl_result_t (*clear)(void *handle, unsigned int flags);
        egl_result_t (*get)(void *handle, unsigned int *flags);
        egl_result_t (*wait)(void *handle, unsigned int req_flags, unsigned int *act_flags, egl_os_flags_opt_t opt, unsigned int timeout);
        egl_result_t (*destroy)(void *handle);
    }flags;

    struct
    {
        egl_result_t (*create)(void **handle, char *name, egl_os_mux_type_t type, void *ctx);
        egl_result_t (*lock)(void *handle, unsigned int timeout);
        egl_result_t (*unlock)(void *handle);
        egl_result_t (*destroy)(void *handle);
    }mux;

    struct
    {
        egl_result_t (*create)(void **handle, char *name, unsigned int max, unsigned int init, void *ctx);
        egl_result_t (*post)(void *handle);
        egl_result_t (*wait)(void *handle, unsigned int timeout);
        egl_result_t (*destroy)(void *handle);
    }sem;

    struct
    {
        egl_result_t (*create)(void **handle, char *name, unsigned int count, unsigned int size, void *mem, size_t memsize, void *ctx);
        egl_result_t (*get)(void *handle, void *msg, unsigned int timeout);
        egl_result_t (*put)(void *handle, void *msg, unsigned int timeout);
        egl_result_t (*destroy)(void *handle);
    }queue;

    struct
    {
        egl_result_t (*create)(void **handle, char *name, egl_os_timer_type_t type, egl_os_timer_handler_func_t func, void *param, void *ctx);
        egl_result_t (*start)(void *handle, unsigned int ticks);
        egl_result_t (*stop)(void *handle);
        egl_result_t (*destroy)(void *handle);
    }timer;
}egl_os_t;

egl_result_t egl_os_init(egl_os_t *os);
egl_result_t egl_os_start(egl_os_t *os, void *param, ...);
egl_result_t egl_os_thread_get(egl_os_t *os, void **handle);
egl_result_t egl_os_thread_sleep(egl_os_t *os, unsigned int ticks);
egl_result_t egl_os_state_get(egl_os_t *os, egl_os_state_t *state);

egl_result_t egl_os_thread_create(egl_os_t *os,
                                  void **handle, char *name,
                                  egl_os_thread_entry_func_t entry,
                                  void *data, void *stack,
                                  size_t stack_size,
                                  unsigned int priority, void *ctx);
egl_result_t egl_os_thread_suspend(egl_os_t *os, void *handle);
egl_result_t egl_os_thread_resume(egl_os_t *os, void *handle);
egl_result_t egl_os_thread_name_get(egl_os_t *os, void *handle, char **name);
egl_result_t egl_os_thread_prio_set(egl_os_t *os, void *handle, unsigned int prio);
egl_result_t egl_os_thread_prio_get(egl_os_t *os, void *handle, unsigned int *prio);
egl_result_t egl_os_thread_destroy(egl_os_t *os, void *handle);

egl_result_t egl_os_flags_create(egl_os_t *os, void **handle, char *name, void *ctx);
egl_result_t egl_os_flags_set(egl_os_t *os, void *handle, unsigned int flags);
egl_result_t egl_os_flags_clear(egl_os_t *os, void *handle, unsigned int flags);
egl_result_t egl_os_flags_get(egl_os_t *os, void *handle, unsigned int *flags);
egl_result_t egl_os_flags_wait(egl_os_t *os, void *handle, unsigned int req_flags, unsigned int *act_flags,
                               egl_os_flags_opt_t opt, unsigned int timeout);
egl_result_t egl_os_flags_destroy(egl_os_t *os, void *handle);

egl_result_t egl_os_mux_create(egl_os_t *os, void **handle, char *name, egl_os_mux_type_t type, void *ctx);
egl_result_t egl_os_mux_lock(egl_os_t *os, void *handle, unsigned int timeout);
egl_result_t egl_os_mux_unlock(egl_os_t *os, void *handle);
egl_result_t egl_os_mux_destroy(egl_os_t *os, void *handle);

egl_result_t egl_os_sem_create(egl_os_t *os, void **handle, char *name,
                               unsigned int max, unsigned int init, void *ctx);
egl_result_t egl_os_sem_post(egl_os_t *os, void *handle);
egl_result_t egl_os_sem_wait(egl_os_t *os, void *handle, unsigned int timeout);
egl_result_t egl_os_sem_destroy(egl_os_t *os, void *handle);

egl_result_t egl_os_queue_create(egl_os_t *os, void **handle, char *name,
                                 unsigned int count, unsigned int size,
                                 void *mem, size_t memsize, void *ctx);
egl_result_t egl_os_queue_get(egl_os_t *os, void *handle, void *msg, unsigned int timeout);
egl_result_t egl_os_queue_put(egl_os_t *os, void *handle, void *msg, unsigned int timeout);
egl_result_t egl_os_queue_destroy(egl_os_t *os, void *handle);

egl_result_t egl_os_timer_create(egl_os_t *os, void **handle, char *name,
                                 egl_os_timer_type_t type,
                                 egl_os_timer_handler_func_t func,
                                 void *param, void *ctx);
egl_result_t egl_os_timer_start(egl_os_t *os, void *handle, unsigned int ticks);
egl_result_t egl_os_timer_stop(egl_os_t *os, void *handle);
egl_result_t egl_os_timer_destroy(egl_os_t *os, void *handle);

// egl_result_t egl_os_stream_create(egl_os_t *os, void *handle, void *mem, size_t memsize, void *ctx);

#endif
