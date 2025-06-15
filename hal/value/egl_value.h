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

egl_result_t egl_value_i8_init(egl_value_i8_t *value);
egl_result_t egl_value_i8_set(egl_value_i8_t *value, int8_t val);
egl_result_t egl_value_i8_get(egl_value_i8_t *value, int8_t *val);
egl_result_t egl_value_i8_deinit(egl_value_i8_t *value);

egl_result_t egl_value_u8_init(egl_value_u8_t *value);
egl_result_t egl_value_u8_set(egl_value_u8_t *value, uint8_t val);
egl_result_t egl_value_u8_get(egl_value_u8_t *value, uint8_t *val);
egl_result_t egl_value_u8_deinit(egl_value_u8_t *value);

egl_result_t egl_value_i16_init(egl_value_i16_t *value);
egl_result_t egl_value_i16_set(egl_value_i16_t *value, int16_t val);
egl_result_t egl_value_i16_get(egl_value_i16_t *value, int16_t *val);
egl_result_t egl_value_i16_deinit(egl_value_i16_t *value);

egl_result_t egl_value_u16_init(egl_value_u16_t *value);
egl_result_t egl_value_u16_set(egl_value_u16_t *value, uint16_t val);
egl_result_t egl_value_u16_get(egl_value_u16_t *value, uint16_t *val);
egl_result_t egl_value_u16_deinit(egl_value_u16_t *value);

egl_result_t egl_value_i32_init(egl_value_i32_t *value);
egl_result_t egl_value_i32_set(egl_value_i32_t *value, int32_t val);
egl_result_t egl_value_i32_get(egl_value_i32_t *value, int32_t *val);
egl_result_t egl_value_i32_deinit(egl_value_i32_t *value);

egl_result_t egl_value_u32_init(egl_value_u32_t *value);
egl_result_t egl_value_u32_set(egl_value_u32_t *value, uint32_t val);
egl_result_t egl_value_u32_get(egl_value_u32_t *value, uint32_t *val);
egl_result_t egl_value_u32_deinit(egl_value_u32_t *value);

egl_result_t egl_value_i64_init(egl_value_i64_t *value);
egl_result_t egl_value_i64_set(egl_value_i64_t *value, int64_t val);
egl_result_t egl_value_i64_get(egl_value_i64_t *value, int64_t *val);
egl_result_t egl_value_i64_deinit(egl_value_i64_t *value);

egl_result_t egl_value_u64_init(egl_value_u64_t *value);
egl_result_t egl_value_u64_set(egl_value_u64_t *value, uint64_t val);
egl_result_t egl_value_u64_get(egl_value_u64_t *value, uint64_t *val);
egl_result_t egl_value_u64_deinit(egl_value_u64_t *value);

egl_result_t egl_value_ptr_init(egl_value_ptr_t *value);
egl_result_t egl_value_ptr_set(egl_value_ptr_t *value, void *val);
egl_result_t egl_value_ptr_get(egl_value_ptr_t *value, void **val);
egl_result_t egl_value_ptr_deinit(egl_value_ptr_t *value);

#endif