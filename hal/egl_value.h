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

#ifndef EGL_VALUE_H
#define EGL_VALUE_H

#include <stdint.h>

#include "egl_result.h"

typedef struct
{
    egl_result_t (*init)(void);
    egl_result_t (*set)(int8_t val);
    egl_result_t (*get)(int8_t *val);
    egl_result_t (*deinit)(void);
}egl_value_i8_t;

typedef struct
{
    egl_result_t (*init)(void);
    egl_result_t (*set)(uint8_t val);
    egl_result_t (*get)(uint8_t *val);
    egl_result_t (*deinit)(void);
}egl_value_u8_t;

typedef struct
{
    egl_result_t (*init)(void);
    egl_result_t (*set)(int16_t val);
    egl_result_t (*get)(int16_t *val);
    egl_result_t (*deinit)(void);
}egl_value_i16_t;

typedef struct
{
    egl_result_t (*init)(void);
    egl_result_t (*set)(uint16_t val);
    egl_result_t (*get)(uint16_t *val);
    egl_result_t (*deinit)(void);
}egl_value_u16_t;

typedef struct
{
    egl_result_t (*init)(void);
    egl_result_t (*set)(int32_t val);
    egl_result_t (*get)(int32_t *val);
    egl_result_t (*deinit)(void);
}egl_value_i32_t;

typedef struct
{
    egl_result_t (*init)(void);
    egl_result_t (*set)(uint32_t val);
    egl_result_t (*get)(uint32_t *val);
    egl_result_t (*deinit)(void);
}egl_value_u32_t;

typedef struct
{
    egl_result_t (*init)(void);
    egl_result_t (*set)(int64_t val);
    egl_result_t (*get)(int64_t *val);
    egl_result_t (*deinit)(void);
}egl_value_i64_t;

typedef struct
{
    egl_result_t (*init)(void);
    egl_result_t (*set)(uint64_t val);
    egl_result_t (*get)(uint64_t *val);
    egl_result_t (*deinit)(void);
}egl_value_u64_t;

typedef struct
{
    egl_result_t (*init)(void);
    egl_result_t (*set)(void *val);
    egl_result_t (*get)(void **val);
    egl_result_t (*deinit)(void);
}egl_value_ptr_t;

static inline egl_result_t egl_value_i8_init(egl_value_i8_t *value)
{
    EGL_ASSERT_CHECK(value, EGL_NULL_POINTER);
    EGL_ASSERT_CHECK(value->init, EGL_NOT_SUPPORTED);

    return value->init();
}

static inline egl_result_t egl_value_i8_set(egl_value_i8_t *value, int8_t val)
{
    EGL_ASSERT_CHECK(value, EGL_NULL_POINTER);
    EGL_ASSERT_CHECK(value->set, EGL_NOT_SUPPORTED);

    return value->set(val);
}

static inline egl_result_t egl_value_i8_get(egl_value_i8_t *value, int8_t *val)
{
    EGL_ASSERT_CHECK(value, EGL_NULL_POINTER);
    EGL_ASSERT_CHECK(val, EGL_NULL_POINTER);
    EGL_ASSERT_CHECK(value->get, EGL_NOT_SUPPORTED);

    return value->get(val);
}

static inline egl_result_t egl_value_i8_deinit(egl_value_i8_t *value)
{
    EGL_ASSERT_CHECK(value, EGL_NULL_POINTER);
    EGL_ASSERT_CHECK(value->deinit, EGL_NOT_SUPPORTED);

    return value->deinit();
}

static inline egl_result_t egl_value_u8_init(egl_value_u8_t *value)
{
    EGL_ASSERT_CHECK(value, EGL_NULL_POINTER);
    EGL_ASSERT_CHECK(value->init, EGL_NOT_SUPPORTED);

    return value->init();
}

static inline egl_result_t egl_value_u8_set(egl_value_u8_t *value, uint8_t val)
{
    EGL_ASSERT_CHECK(value, EGL_NULL_POINTER);
    EGL_ASSERT_CHECK(value->set, EGL_NOT_SUPPORTED);

    return value->set(val);
}

static inline egl_result_t egl_value_u8_get(egl_value_u8_t *value, uint8_t *val)
{
    EGL_ASSERT_CHECK(value, EGL_NULL_POINTER);
    EGL_ASSERT_CHECK(val, EGL_NULL_POINTER);
    EGL_ASSERT_CHECK(value->get, EGL_NOT_SUPPORTED);

    return value->get(val);
}

static inline egl_result_t egl_value_u8_deinit(egl_value_u8_t *value)
{
    EGL_ASSERT_CHECK(value, EGL_NULL_POINTER);
    EGL_ASSERT_CHECK(value->deinit, EGL_NOT_SUPPORTED);

    return value->deinit();
}

static inline egl_result_t egl_value_i16_init(egl_value_i16_t *value)
{
    EGL_ASSERT_CHECK(value, EGL_NULL_POINTER);
    EGL_ASSERT_CHECK(value->init, EGL_NOT_SUPPORTED);

    return value->init();
}

static inline egl_result_t egl_value_i16_set(egl_value_i16_t *value, int16_t val)
{
    EGL_ASSERT_CHECK(value, EGL_NULL_POINTER);
    EGL_ASSERT_CHECK(value->set, EGL_NOT_SUPPORTED);

    return value->set(val);
}

static inline egl_result_t egl_value_i16_get(egl_value_i16_t *value, int16_t *val)
{
    EGL_ASSERT_CHECK(value, EGL_NULL_POINTER);
    EGL_ASSERT_CHECK(val, EGL_NULL_POINTER);
    EGL_ASSERT_CHECK(value->get, EGL_NOT_SUPPORTED);

    return value->get(val);
}

static inline egl_result_t egl_value_i16_deinit(egl_value_i16_t *value)
{
    EGL_ASSERT_CHECK(value, EGL_NULL_POINTER);
    EGL_ASSERT_CHECK(value->deinit, EGL_NOT_SUPPORTED);

    return value->deinit();
}


static inline egl_result_t egl_value_u16_init(egl_value_u16_t *value)
{
    EGL_ASSERT_CHECK(value, EGL_NULL_POINTER);
    EGL_ASSERT_CHECK(value->init, EGL_NOT_SUPPORTED);

    return value->init();
}

static inline egl_result_t egl_value_u16_set(egl_value_u16_t *value, uint16_t val)
{
    EGL_ASSERT_CHECK(value, EGL_NULL_POINTER);
    EGL_ASSERT_CHECK(value->set, EGL_NOT_SUPPORTED);

    return value->set(val);
}

static inline egl_result_t egl_value_u16_get(egl_value_u16_t *value, uint16_t *val)
{
    EGL_ASSERT_CHECK(value, EGL_NULL_POINTER);
    EGL_ASSERT_CHECK(val, EGL_NULL_POINTER);
    EGL_ASSERT_CHECK(value->get, EGL_NOT_SUPPORTED);

    return value->get(val);
}

static inline egl_result_t egl_value_u16_deinit(egl_value_u16_t *value)
{
    EGL_ASSERT_CHECK(value, EGL_NULL_POINTER);
    EGL_ASSERT_CHECK(value->deinit, EGL_NOT_SUPPORTED);

    return value->deinit();
}

static inline egl_result_t egl_value_i32_init(egl_value_i32_t *value)
{
    EGL_ASSERT_CHECK(value, EGL_NULL_POINTER);
    EGL_ASSERT_CHECK(value->init, EGL_NOT_SUPPORTED);

    return value->init();
}

static inline egl_result_t egl_value_i32_set(egl_value_i32_t *value, int32_t val)
{
    EGL_ASSERT_CHECK(value, EGL_NULL_POINTER);
    EGL_ASSERT_CHECK(value->set, EGL_NOT_SUPPORTED);

    return value->set(val);
}

static inline egl_result_t egl_value_i32_get(egl_value_i32_t *value, int32_t *val)
{
    EGL_ASSERT_CHECK(value, EGL_NULL_POINTER);
    EGL_ASSERT_CHECK(val, EGL_NULL_POINTER);
    EGL_ASSERT_CHECK(value->get, EGL_NOT_SUPPORTED);

    return value->get(val);
}

static inline egl_result_t egl_value_i32_deinit(egl_value_i32_t *value)
{
    EGL_ASSERT_CHECK(value, EGL_NULL_POINTER);
    EGL_ASSERT_CHECK(value->deinit, EGL_NOT_SUPPORTED);

    return value->deinit();
}

static inline egl_result_t egl_value_u32_init(egl_value_u32_t *value)
{
    EGL_ASSERT_CHECK(value, EGL_NULL_POINTER);
    EGL_ASSERT_CHECK(value->init, EGL_NOT_SUPPORTED);

    return value->init();
}

static inline egl_result_t egl_value_u32_set(egl_value_u32_t *value, uint32_t val)
{
    EGL_ASSERT_CHECK(value, EGL_NULL_POINTER);
    EGL_ASSERT_CHECK(value->set, EGL_NOT_SUPPORTED);

    return value->set(val);
}

static inline egl_result_t egl_value_u32_get(egl_value_u32_t *value, uint32_t *val)
{
    EGL_ASSERT_CHECK(value, EGL_NULL_POINTER);
    EGL_ASSERT_CHECK(val, EGL_NULL_POINTER);
    EGL_ASSERT_CHECK(value->get, EGL_NOT_SUPPORTED);

    return value->get(val);
}

static inline egl_result_t egl_value_u32_deinit(egl_value_u32_t *value)
{
    EGL_ASSERT_CHECK(value, EGL_NULL_POINTER);
    EGL_ASSERT_CHECK(value->deinit, EGL_NOT_SUPPORTED);

    return value->deinit();
}

static inline egl_result_t egl_value_i64_init(egl_value_i64_t *value)
{
    EGL_ASSERT_CHECK(value, EGL_NULL_POINTER);
    EGL_ASSERT_CHECK(value->init, EGL_NOT_SUPPORTED);

    return value->init();
}

static inline egl_result_t egl_value_i64_set(egl_value_i64_t *value, int64_t val)
{
    EGL_ASSERT_CHECK(value, EGL_NULL_POINTER);
    EGL_ASSERT_CHECK(value->set, EGL_NOT_SUPPORTED);

    return value->set(val);
}

static inline egl_result_t egl_value_i64_get(egl_value_i64_t *value, int64_t *val)
{
    EGL_ASSERT_CHECK(value, EGL_NULL_POINTER);
    EGL_ASSERT_CHECK(val, EGL_NULL_POINTER);
    EGL_ASSERT_CHECK(value->get, EGL_NOT_SUPPORTED);

    return value->get(val);
}

static inline egl_result_t egl_value_i64_deinit(egl_value_i64_t *value)
{
    EGL_ASSERT_CHECK(value, EGL_NULL_POINTER);
    EGL_ASSERT_CHECK(value->deinit, EGL_NOT_SUPPORTED);

    return value->deinit();
}

static inline egl_result_t egl_value_u64_init(egl_value_u64_t *value)
{
    EGL_ASSERT_CHECK(value, EGL_NULL_POINTER);
    EGL_ASSERT_CHECK(value->init, EGL_NOT_SUPPORTED);

    return value->init();
}

static inline egl_result_t egl_value_u64_set(egl_value_u64_t *value, uint64_t val)
{
    EGL_ASSERT_CHECK(value, EGL_NULL_POINTER);
    EGL_ASSERT_CHECK(value->set, EGL_NOT_SUPPORTED);

    return value->set(val);
}

static inline egl_result_t egl_value_u64_get(egl_value_u64_t *value, uint64_t *val)
{
    EGL_ASSERT_CHECK(value, EGL_NULL_POINTER);
    EGL_ASSERT_CHECK(val, EGL_NULL_POINTER);
    EGL_ASSERT_CHECK(value->get, EGL_NOT_SUPPORTED);

    return value->get(val);
}

static inline egl_result_t egl_value_u64_deinit(egl_value_u64_t *value)
{
    EGL_ASSERT_CHECK(value, EGL_NULL_POINTER);
    EGL_ASSERT_CHECK(value->deinit, EGL_NOT_SUPPORTED);

    return value->deinit();
}

static inline egl_result_t egl_value_ptr_init(egl_value_ptr_t *value)
{
    EGL_ASSERT_CHECK(value, EGL_NULL_POINTER);
    EGL_ASSERT_CHECK(value->init, EGL_NOT_SUPPORTED);

    return value->init();
}

static inline egl_result_t egl_value_ptr_set(egl_value_ptr_t *value, void *val)
{
    EGL_ASSERT_CHECK(value, EGL_NULL_POINTER);
    EGL_ASSERT_CHECK(value->set, EGL_NOT_SUPPORTED);

    return value->set(val);
}

static inline egl_result_t egl_value_ptr_get(egl_value_ptr_t *value, void **val)
{
    EGL_ASSERT_CHECK(value, EGL_NULL_POINTER);
    EGL_ASSERT_CHECK(val, EGL_NULL_POINTER);
    EGL_ASSERT_CHECK(value->get, EGL_NOT_SUPPORTED);

    return value->get(val);
}

static inline egl_result_t egl_value_ptr_deinit(egl_value_ptr_t *value)
{
    EGL_ASSERT_CHECK(value, EGL_NULL_POINTER);
    EGL_ASSERT_CHECK(value->deinit, EGL_NOT_SUPPORTED);

    return value->deinit();
}


#endif