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

#include "egl_os.h"
#include "tx_api.h"

static egl_result_t (*start_func)(void *param, ...) = NULL;

void tx_application_define(void *first_unused_memory)
{
    EGL_ASSERT_CHECK(start_func, RETURN_VOID);

    egl_result_t result;

    result = start_func(first_unused_memory);
    EGL_ASSERT_CHECK(result == EGL_SUCCESS, RETURN_VOID);
}

static egl_result_t egl_os_threadx_init(void)
{
    return EGL_SUCCESS;
}

static egl_result_t egl_os_threadx_start(void *param, ...)
{
    start_func = param;

    tx_kernel_enter();

    return EGL_SUCCESS;
}

static egl_result_t egl_os_threadx_thread_sleep(unsigned int ticks)
{
    UINT tx_result;

    tx_result = tx_thread_sleep(ticks);
    EGL_ASSERT_CHECK(tx_result == TX_SUCCESS, EGL_FAIL);

    return EGL_SUCCESS;
}

static egl_result_t egl_os_threadx_thread_current(void **handle)
{
    *handle = tx_thread_identify();

    return EGL_SUCCESS;
}

static egl_result_t egl_os_threadx_state(egl_os_state_t *state)
{
    extern ULONG _tx_thread_system_state;

    if(_tx_thread_system_state == 0)
    {
        *state = EGL_OS_RUNNING;
    }
    else
    {
        *state = EGL_OS_NOT_INITED;
    }

    return EGL_SUCCESS;
}

static egl_result_t egl_os_threadex_thread_create(void **handle, char *name,
                            egl_os_thread_entry_func_t entry,
                            void *param, void *stack,
                            size_t stack_size,
                            unsigned int priority, void *ctx)
{
    EGL_ASSERT_CHECK(ctx, EGL_NULL_POINTER);

    UINT tx_result = tx_thread_create(ctx, name, (void (*)(ULONG))entry, (ULONG)param, stack, stack_size,
                                      priority, priority, TX_NO_TIME_SLICE, TX_AUTO_START);
    EGL_ASSERT_CHECK(tx_result == TX_SUCCESS, EGL_FAIL);

    *handle = ctx;

    return EGL_SUCCESS;
}


static egl_result_t egl_os_threadx_thread_resume(void *handle)
{
    UINT tx_result;

    tx_result = tx_thread_resume((TX_THREAD *)handle);
    EGL_ASSERT_CHECK(tx_result == TX_SUCCESS, EGL_FAIL);

    return EGL_SUCCESS;
}

static egl_result_t egl_os_threadx_thread_suspend(void *handle)
{
    UINT tx_result;

    tx_result = tx_thread_suspend((TX_THREAD *)handle);
    EGL_ASSERT_CHECK(tx_result == TX_SUCCESS, EGL_FAIL);

    return EGL_SUCCESS;
}

static egl_result_t egl_os_threadx_thread_name_get(void *handle, char **name)
{
    TX_THREAD *thread = handle;

    *name = thread->tx_thread_name;

    return EGL_SUCCESS;
}

static egl_result_t egl_os_threadx_thread_prio_get(void *handle, unsigned int *prio)
{
    TX_THREAD *thread = handle;

    *prio = thread->tx_thread_priority;

    return EGL_SUCCESS;
}

static egl_result_t egl_os_threadx_thread_prio_set(void *handle, unsigned int prio)
{
    UINT old;
    UINT tx_result;

    tx_result = tx_thread_priority_change((TX_THREAD *)handle, prio, &old);
    EGL_ASSERT_CHECK(tx_result == TX_SUCCESS, EGL_FAIL);

    return EGL_SUCCESS;
}

static egl_result_t egl_os_threadx_thread_destroy(void *handle)
{
    UINT tx_result;

    tx_result = tx_thread_delete((TX_THREAD *)handle);
    EGL_ASSERT_CHECK(tx_result == TX_SUCCESS, EGL_FAIL);

    return EGL_SUCCESS;
}

static egl_result_t egl_os_threadx_flags_create(void **handle, char *name, void *ctx)
{
    EGL_ASSERT_CHECK(ctx, EGL_NULL_POINTER);

    UINT tx_result;

    tx_result = tx_event_flags_create(ctx, name);
    EGL_ASSERT_CHECK(tx_result == TX_SUCCESS, EGL_FAIL);

    *handle = ctx;

    return EGL_SUCCESS;
}

static egl_result_t egl_os_threadx_flags_set(void *handle, unsigned int flags)
{
    UINT tx_result;

    tx_result = tx_event_flags_set((TX_EVENT_FLAGS_GROUP *)handle, flags, TX_OR);
    EGL_ASSERT_CHECK(tx_result == TX_SUCCESS, EGL_FAIL);

    return EGL_SUCCESS;
}

static egl_result_t egl_os_threadx_flags_clear(void *handle, unsigned int flags)
{
    UINT tx_result;

    tx_result = tx_event_flags_set((TX_EVENT_FLAGS_GROUP *)handle, ~(flags), TX_AND);
    EGL_ASSERT_CHECK(tx_result == TX_SUCCESS, EGL_FAIL);

    return EGL_SUCCESS;
}

static egl_result_t egl_os_threadx_flags_get(void *handle, unsigned int *flags)
{
    UINT tx_result;

    tx_result = tx_event_flags_info_get((TX_EVENT_FLAGS_GROUP *)handle, NULL, (ULONG *)flags, NULL, NULL, NULL);
    EGL_ASSERT_CHECK(tx_result == TX_SUCCESS, EGL_FAIL);

    return EGL_SUCCESS;
}

static egl_result_t egl_os_threadx_flags_wait(void *handle, unsigned int req_flags, unsigned int *act_flags,
                                              egl_os_flags_opt_t opt, unsigned int timeout)
{
    UINT tx_result;
    UINT get_option;

    if(opt & EGL_OS_FLAGS_OPT_WAIT_ALL)
    {
        if(opt & EGL_OS_FLAGS_OPT_NO_CLEAR)
        {
            get_option = TX_AND;
        }
        else
        {
            get_option = TX_AND_CLEAR;
        }
    }
    else
    {
        if(opt & EGL_OS_FLAGS_OPT_NO_CLEAR)
        {
            get_option = TX_OR;
        }
        else
        {
            get_option = TX_OR_CLEAR;
        }
    }

    tx_result = tx_event_flags_get((TX_EVENT_FLAGS_GROUP *)handle, req_flags, get_option, (ULONG *)act_flags, timeout);
    EGL_ASSERT_CHECK(tx_result == TX_SUCCESS || tx_result == TX_NO_EVENTS, EGL_FAIL);

    return tx_result == TX_SUCCESS ? EGL_SUCCESS : EGL_TIMEOUT;
}

static egl_result_t egl_os_threadx_flags_destroy(void *handle)
{
    UINT tx_result;

    tx_result = tx_event_flags_delete((TX_EVENT_FLAGS_GROUP *)handle);
    EGL_ASSERT_CHECK(tx_result == TX_SUCCESS, EGL_FAIL);

    return EGL_SUCCESS;
}

static egl_result_t egl_os_threadx_mux_create(void **handle, char *name, egl_os_mux_type_t type, void *ctx)
{
    EGL_ASSERT_CHECK(ctx, EGL_NULL_POINTER);

    UINT tx_result;
    UINT inherit;

    if(type & EGL_OS_MUX_TYPE_INHERIT)
    {
        inherit = TX_INHERIT;
    }
    else
    {
        inherit = TX_NO_INHERIT;
    }

    tx_result = tx_mutex_create(ctx, name, inherit);
    EGL_ASSERT_CHECK(tx_result == TX_SUCCESS, EGL_FAIL);

    *handle = ctx;

    return EGL_SUCCESS;
}

static egl_result_t egl_os_threadx_mux_lock(void *handle, unsigned int timeout)
{
    UINT tx_result;

    tx_result = tx_mutex_get((TX_MUTEX *)handle, timeout);
    EGL_ASSERT_CHECK(tx_result == TX_SUCCESS, EGL_FAIL);

    return EGL_SUCCESS;
}

static egl_result_t egl_os_threadx_mux_unlock(void *handle)
{
    UINT tx_result;

    tx_result = tx_mutex_put((TX_MUTEX *)handle);
    EGL_ASSERT_CHECK(tx_result == TX_SUCCESS, EGL_FAIL);

    return EGL_SUCCESS;
}

static egl_result_t egl_os_threadx_mux_destroy(void *handle)
{
    UINT tx_result;

    tx_result = tx_mutex_delete((TX_MUTEX *)handle);
    EGL_ASSERT_CHECK(tx_result == TX_SUCCESS, EGL_FAIL);

    return EGL_SUCCESS;

}

static egl_result_t egl_os_threadx_sem_create(void **handle, char *name,
                                              unsigned int max, unsigned int init, void *ctx)
{
    EGL_ASSERT_CHECK(ctx, EGL_NULL_POINTER);
    EGL_ASSERT_CHECK(init <= max, EGL_INVALID_PARAM);

    UINT tx_result;
    unsigned int diff = max - init;

    tx_result = tx_semaphore_create(ctx, name, max);
    EGL_ASSERT_CHECK(tx_result == TX_SUCCESS, EGL_FAIL);

    /* Set initial value */
    for(unsigned int i = 0; i < diff; i++)
    {
        tx_result = tx_semaphore_get(ctx, TX_NO_WAIT);
        EGL_ASSERT_CHECK(tx_result == TX_SUCCESS, EGL_FAIL);
    }

    *handle = ctx;

    return EGL_SUCCESS;
}

static egl_result_t egl_os_threadx_sem_post(void *handle)
{
    UINT tx_result;

    tx_result = tx_semaphore_put((TX_SEMAPHORE *)handle);
    EGL_ASSERT_CHECK(tx_result == TX_SUCCESS, EGL_FAIL);

    return EGL_SUCCESS;
}

static egl_result_t egl_os_threadx_sem_wait(void *handle, unsigned int timeout)
{
    UINT tx_result;

    tx_result = tx_semaphore_get((TX_SEMAPHORE *)handle, timeout);
    EGL_ASSERT_CHECK(tx_result == TX_SUCCESS, EGL_FAIL);

    return EGL_SUCCESS;
}

static egl_result_t egl_os_threadx_sem_destroy(void *handle)
{
    UINT tx_result;

    tx_result = tx_semaphore_delete((TX_SEMAPHORE *)handle);
    EGL_ASSERT_CHECK(tx_result == TX_SUCCESS, EGL_FAIL);

    return EGL_SUCCESS;
}

static egl_result_t egl_os_threadx_queue_create(void **handle, char *name, unsigned int count,
                                                unsigned int size, void *mem, size_t memsize, void *ctx)
{
    UINT tx_result;

    tx_result = tx_queue_create(ctx, name, size / 4, mem, memsize);
    EGL_ASSERT_CHECK(tx_result == TX_SUCCESS, EGL_FAIL);

    *handle = ctx;

    return EGL_SUCCESS;
}

static egl_result_t egl_os_threadx_queueu_get(void *handle, void *msg, unsigned int timeout)
{
    UINT tx_result;

    tx_result = tx_queue_receive((TX_QUEUE *)handle, msg, timeout);
    EGL_ASSERT_CHECK(tx_result == TX_SUCCESS, EGL_FAIL);

    return EGL_SUCCESS;
}

static egl_result_t egl_os_threadx_queue_put(void *handle, void *msg, unsigned int timeout)
{
    UINT tx_result;

    tx_result = tx_queue_send((TX_QUEUE *)handle, msg, timeout);
    EGL_ASSERT_CHECK(tx_result == TX_SUCCESS, EGL_FAIL);

    return EGL_SUCCESS;
}

static egl_result_t egl_os_threadx_queue_destroy(void *handle)
{
    UINT tx_result;

    tx_result = tx_queue_delete((TX_QUEUE *)handle);
    EGL_ASSERT_CHECK(tx_result == TX_SUCCESS, EGL_FAIL);

    return EGL_SUCCESS;
}

static egl_result_t egl_os_threadx_timer_create(void **handle, char *name,
                                                egl_os_timer_type_t type,
                                                egl_os_timer_handler_func_t func,
                                                void *param, void *ctx)
{
    UINT tx_result;

    tx_result = tx_timer_create(ctx, name, (void (*)(ULONG))func, (ULONG)param, 0, 0, TX_NO_ACTIVATE);
    EGL_ASSERT_CHECK(tx_result == TX_SUCCESS, EGL_FAIL);

    *handle = ctx;

    return EGL_SUCCESS;
}

static egl_result_t egl_os_threadx_timer_start(void *handle, unsigned int ticks)
{
    UINT tx_result;

    tx_result = tx_timer_change((TX_TIMER *)handle, ticks, ticks);
    EGL_ASSERT_CHECK(tx_result == TX_SUCCESS, EGL_FAIL);

    tx_result = tx_timer_activate((TX_TIMER *)handle);
    EGL_ASSERT_CHECK(tx_result == TX_SUCCESS, EGL_FAIL);

    return EGL_SUCCESS;
}

static egl_result_t egl_os_threadx_timer_stop(void *handle)
{
    UINT tx_result;

    tx_result = tx_timer_deactivate((TX_TIMER *)handle);
    EGL_ASSERT_CHECK(tx_result == TX_SUCCESS, EGL_FAIL);

    return EGL_SUCCESS;
}

static egl_result_t egl_os_threadx_timer_destroy(void *handle)
{
    UINT tx_result;

    tx_result = tx_timer_delete((TX_TIMER *)handle);
    EGL_ASSERT_CHECK(tx_result == TX_SUCCESS, EGL_FAIL);

    return EGL_SUCCESS;
}

const egl_os_t egl_os_threadx_port =
{
    .init    = egl_os_threadx_init,
    .start   = egl_os_threadx_start,
    .sleep   = egl_os_threadx_thread_sleep,
    .current = egl_os_threadx_thread_current,
    .state   = egl_os_threadx_state,

    .thread =
    {
        .create   = egl_os_threadex_thread_create,
        .resume   = egl_os_threadx_thread_resume,
        .suspend  = egl_os_threadx_thread_suspend,
        .name_get = egl_os_threadx_thread_name_get,
        .prio_get = egl_os_threadx_thread_prio_get,
        .prio_set = egl_os_threadx_thread_prio_set,
        .destroy  = egl_os_threadx_thread_destroy
    },

    .flags =
    {
        .create  = egl_os_threadx_flags_create,
        .set     = egl_os_threadx_flags_set,
        .clear   = egl_os_threadx_flags_clear,
        .get     = egl_os_threadx_flags_get,
        .wait    = egl_os_threadx_flags_wait,
        .destroy = egl_os_threadx_flags_destroy
    },

    .mux =
    {
        .create  = egl_os_threadx_mux_create,
        .lock    = egl_os_threadx_mux_lock,
        .unlock  = egl_os_threadx_mux_unlock,
        .destroy = egl_os_threadx_mux_destroy
    },

    .sem =
    {
        .create  = egl_os_threadx_sem_create,
        .post    = egl_os_threadx_sem_post,
        .wait    = egl_os_threadx_sem_wait,
        .destroy = egl_os_threadx_sem_destroy
    },

    .queue =
    {
        .create  = egl_os_threadx_queue_create,
        .get     = egl_os_threadx_queueu_get,
        .put     = egl_os_threadx_queue_put,
        .destroy = egl_os_threadx_queue_destroy
    },

    .timer =
    {
        .create  = egl_os_threadx_timer_create,
        .start   = egl_os_threadx_timer_start,
        .stop    = egl_os_threadx_timer_stop,
        .destroy = egl_os_threadx_timer_destroy
    }
};

egl_os_t *egl_os_threadx_port_get(void)
{
    return (egl_os_t *)&egl_os_threadx_port;
}
