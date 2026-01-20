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

#include "egl_result.h"
#include "egl_os.h"

egl_result_t egl_os_init(egl_os_t *os)
{
    EGL_ASSERT_CHECK(os, EGL_NULL_POINTER);
    EGL_ASSERT_CHECK(os->init, EGL_NOT_SUPPORTED);

    return os->init();
}

egl_result_t egl_os_start(egl_os_t *os, void *param, ...)
{
    EGL_ASSERT_CHECK(os, EGL_NULL_POINTER);
    EGL_ASSERT_CHECK(os->start, EGL_NOT_SUPPORTED);

    egl_result_t result;

    va_list args;
    va_start(args, param);

    result = os->start(param, args);

    va_end(args);

    return result;
}

egl_result_t egl_os_thread_get(egl_os_t *os, void **handle)
{
    EGL_ASSERT_CHECK(os, EGL_NULL_POINTER);
    EGL_ASSERT_CHECK(os->start, EGL_NOT_SUPPORTED);

    return os->current(handle);
}

egl_result_t egl_os_thread_sleep(egl_os_t *os, unsigned int ticks)
{
    EGL_ASSERT_CHECK(os, EGL_NULL_POINTER);
    EGL_ASSERT_CHECK(os->sleep, EGL_NOT_SUPPORTED);

    return os->sleep(ticks);
}

egl_result_t egl_os_thread_create(egl_os_t *os,
                                  void **handle, char *name,
                                  egl_os_thread_entry_func_t entry,
                                  void *data, void *stack,
                                  size_t stack_size,
                                  unsigned int priority, void *ctx)
{
    EGL_ASSERT_CHECK(os, EGL_NULL_POINTER);
    EGL_ASSERT_CHECK(os->thread.create, EGL_NOT_SUPPORTED);

    return os->thread.create(handle, name, entry, data, stack, stack_size, priority, ctx);
}

egl_result_t egl_os_thread_suspend(egl_os_t *os, void *handle)
{
    EGL_ASSERT_CHECK(os, EGL_NULL_POINTER);
    EGL_ASSERT_CHECK(os->thread.suspend, EGL_NOT_SUPPORTED);

    return os->thread.suspend(handle);
}

egl_result_t egl_os_thread_resume(egl_os_t *os, void *handle)
{
    EGL_ASSERT_CHECK(os, EGL_NULL_POINTER);
    EGL_ASSERT_CHECK(os->thread.resume, EGL_NOT_SUPPORTED);

    return os->thread.resume(handle);
}

egl_result_t egl_os_thread_name_get(egl_os_t *os, void *handle, char **name)
{
    EGL_ASSERT_CHECK(os, EGL_NULL_POINTER);
    EGL_ASSERT_CHECK(os->thread.name_get, EGL_NOT_SUPPORTED);

    return os->thread.name_get(handle, name);
}

egl_result_t egl_os_thread_prio_set(egl_os_t *os, void *handle, unsigned int prio)
{
    EGL_ASSERT_CHECK(os, EGL_NULL_POINTER);
    EGL_ASSERT_CHECK(os->thread.prio_set, EGL_NOT_SUPPORTED);

    return os->thread.prio_set(handle, prio);
}

egl_result_t egl_os_thread_prio_get(egl_os_t *os, void *handle, unsigned int *prio)
{
    EGL_ASSERT_CHECK(os, EGL_NULL_POINTER);
    EGL_ASSERT_CHECK(os->thread.prio_get, EGL_NOT_SUPPORTED);

    return os->thread.prio_get(handle, prio);
}

egl_result_t egl_os_thread_destroy(egl_os_t *os, void *handle)
{
    EGL_ASSERT_CHECK(os, EGL_NULL_POINTER);
    EGL_ASSERT_CHECK(os->thread.prio_get, EGL_NOT_SUPPORTED);

    return os->thread.destroy(handle);
}

egl_result_t egl_os_flags_create(egl_os_t *os, void **handle, char *name, void *ctx)
{
    EGL_ASSERT_CHECK(os, EGL_NULL_POINTER);
    EGL_ASSERT_CHECK(os->flags.create, EGL_NOT_SUPPORTED);

    return os->flags.create(handle, name, ctx);
}

egl_result_t egl_os_flags_set(egl_os_t *os, void *handle, unsigned int flags)
{
    EGL_ASSERT_CHECK(os, EGL_NULL_POINTER);
    EGL_ASSERT_CHECK(os->flags.set, EGL_NOT_SUPPORTED);

    return os->flags.set(handle, flags);
}

egl_result_t egl_os_flags_clear(egl_os_t *os, void *handle, unsigned int flags)
{
    EGL_ASSERT_CHECK(os, EGL_NULL_POINTER);
    EGL_ASSERT_CHECK(os->flags.clear, EGL_NOT_SUPPORTED);

    return os->flags.clear(handle, flags);
}

egl_result_t egl_os_flags_get(egl_os_t *os, void *handle, unsigned int *flags)
{
    EGL_ASSERT_CHECK(os, EGL_NULL_POINTER);
    EGL_ASSERT_CHECK(os->flags.get, EGL_NOT_SUPPORTED);

    return os->flags.get(handle, flags);
}

egl_result_t egl_os_flags_wait(egl_os_t *os, void *handle, unsigned int req_flags, unsigned int *act_flags, egl_os_flags_opt_t opt, unsigned int timeout)
{
    EGL_ASSERT_CHECK(os, EGL_NULL_POINTER);
    EGL_ASSERT_CHECK(os->flags.wait, EGL_NOT_SUPPORTED);

    return os->flags.wait(handle, req_flags, act_flags, opt, timeout);
}

egl_result_t egl_os_flags_destroy(egl_os_t *os, void *handle)
{
    EGL_ASSERT_CHECK(os, EGL_NULL_POINTER);
    EGL_ASSERT_CHECK(os->flags.destroy, EGL_NOT_SUPPORTED);

    return os->flags.destroy(handle);
}

egl_result_t egl_os_mux_create(egl_os_t *os, void **handle, char *name, egl_os_mux_type_t type, void *ctx)
{
    EGL_ASSERT_CHECK(os, EGL_NULL_POINTER);
    EGL_ASSERT_CHECK(os->mux.create, EGL_NOT_SUPPORTED);

    return os->mux.create(handle, name, type, ctx);
}

egl_result_t egl_os_mux_lock(egl_os_t *os, void *handle, unsigned int timeout)
{
    EGL_ASSERT_CHECK(os, EGL_NULL_POINTER);
    EGL_ASSERT_CHECK(os->mux.lock, EGL_NOT_SUPPORTED);

    return os->mux.lock(handle, timeout);
}

egl_result_t egl_os_mux_unlock(egl_os_t *os, void *handle)
{
    EGL_ASSERT_CHECK(os, EGL_NULL_POINTER);
    EGL_ASSERT_CHECK(os->mux.unlock, EGL_NOT_SUPPORTED);

    return os->mux.unlock(handle);
}

egl_result_t egl_os_mux_destroy(egl_os_t *os, void *handle)
{
    EGL_ASSERT_CHECK(os, EGL_NULL_POINTER);
    EGL_ASSERT_CHECK(os->mux.destroy, EGL_NOT_SUPPORTED);

    return os->mux.destroy(handle);
}

egl_result_t egl_os_sem_create(egl_os_t *os, void **handle, char *name, unsigned int max, unsigned int init, void *ctx)
{
    EGL_ASSERT_CHECK(os, EGL_NULL_POINTER);
    EGL_ASSERT_CHECK(os->sem.create, EGL_NOT_SUPPORTED);

    return os->sem.create(handle, name, max, init, ctx);
}

egl_result_t egl_os_sem_post(egl_os_t *os, void *handle)
{
    EGL_ASSERT_CHECK(os, EGL_NULL_POINTER);
    EGL_ASSERT_CHECK(os->sem.post, EGL_NOT_SUPPORTED);

    return os->sem.post(handle);
}

egl_result_t egl_os_sem_wait(egl_os_t *os, void *handle, unsigned int timeout)
{
    EGL_ASSERT_CHECK(os, EGL_NULL_POINTER);
    EGL_ASSERT_CHECK(os->sem.wait, EGL_NOT_SUPPORTED);

    return os->sem.wait(handle, timeout);
}

egl_result_t egl_os_sem_destroy(egl_os_t *os, void *handle)
{
    EGL_ASSERT_CHECK(os, EGL_NULL_POINTER);
    EGL_ASSERT_CHECK(os->sem.destroy, EGL_NOT_SUPPORTED);

    return os->sem.destroy(handle);
}

egl_result_t egl_os_queue_create(egl_os_t *os, void **handle, char *name, unsigned int count, unsigned int size, void *mem, size_t memsize, void *ctx)
{
    EGL_ASSERT_CHECK(os, EGL_NULL_POINTER);
    EGL_ASSERT_CHECK(os->queue.create, EGL_NOT_SUPPORTED);

    return os->queue.create(handle, name, count, size, mem, memsize, ctx);
}

egl_result_t egl_os_queue_get(egl_os_t *os, void *handle, void *msg, unsigned int timeout)
{
    EGL_ASSERT_CHECK(os, EGL_NULL_POINTER);
    EGL_ASSERT_CHECK(os->queue.get, EGL_NOT_SUPPORTED);

    return os->queue.get(handle, msg, timeout);
}

egl_result_t egl_os_queue_put(egl_os_t *os, void *handle, void *msg, unsigned int timeout)
{
    EGL_ASSERT_CHECK(os, EGL_NULL_POINTER);
    EGL_ASSERT_CHECK(os->queue.put, EGL_NOT_SUPPORTED);

    return os->queue.put(handle, msg, timeout);
}

egl_result_t egl_os_queue_destroy(egl_os_t *os, void *handle)
{
    EGL_ASSERT_CHECK(os, EGL_NULL_POINTER);
    EGL_ASSERT_CHECK(os->queue.destroy, EGL_NOT_SUPPORTED);

    return os->queue.destroy(handle);
}

egl_result_t egl_os_timer_create(egl_os_t *os, void **handle, char *name, egl_os_timer_type_t type, egl_os_timer_handler_func_t func, void *param, void *ctx)
{
    EGL_ASSERT_CHECK(os, EGL_NULL_POINTER);
    EGL_ASSERT_CHECK(os->timer.create, EGL_NOT_SUPPORTED);

    return os->timer.create(handle, name, type, func, param, ctx);
}

egl_result_t egl_os_timer_start(egl_os_t *os, void *handle, unsigned int ticks)
{
    EGL_ASSERT_CHECK(os, EGL_NULL_POINTER);
    EGL_ASSERT_CHECK(os->timer.start, EGL_NOT_SUPPORTED);

    return os->timer.start(handle, ticks);
}

egl_result_t egl_os_timer_stop(egl_os_t *os, void *handle)
{
    EGL_ASSERT_CHECK(os, EGL_NULL_POINTER);
    EGL_ASSERT_CHECK(os->timer.stop, EGL_NOT_SUPPORTED);

    return os->timer.stop(handle);
}

egl_result_t egl_os_timer_destroy(egl_os_t *os, void *handle)
{
    EGL_ASSERT_CHECK(os, EGL_NULL_POINTER);
    EGL_ASSERT_CHECK(os->timer.destroy, EGL_NOT_SUPPORTED);

    return os->timer.destroy(handle);
}