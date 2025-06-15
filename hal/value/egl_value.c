#include "egl_value.h"

egl_result_t egl_value_i8_init(egl_value_i8_t *value)
{
    EGL_ASSERT_CHECK(value, EGL_NULL_POINTER);
    EGL_ASSERT_CHECK(value->init, EGL_NOT_SUPPORTED);

    return value->init();
}

egl_result_t egl_value_i8_set(egl_value_i8_t *value, int8_t val)
{
    EGL_ASSERT_CHECK(value, EGL_NULL_POINTER);
    EGL_ASSERT_CHECK(value->set, EGL_NOT_SUPPORTED);

    return value->set(val);
}

egl_result_t egl_value_i8_get(egl_value_i8_t *value, int8_t *val);
egl_result_t egl_value_i8_get(egl_value_i8_t *value, int8_t *val)
{
    EGL_ASSERT_CHECK(value, EGL_NULL_POINTER);
    EGL_ASSERT_CHECK(val, EGL_NULL_POINTER);
    EGL_ASSERT_CHECK(value->get, EGL_NOT_SUPPORTED);

    return value->get(val);
}

egl_result_t egl_value_i8_deinit(egl_value_i8_t *value)
{
    EGL_ASSERT_CHECK(value, EGL_NULL_POINTER);
    EGL_ASSERT_CHECK(value->deinit, EGL_NOT_SUPPORTED);

    return value->deinit();
}

egl_result_t egl_value_u8_init(egl_value_u8_t *value)
{
    EGL_ASSERT_CHECK(value, EGL_NULL_POINTER);
    EGL_ASSERT_CHECK(value->init, EGL_NOT_SUPPORTED);

    return value->init();
}

egl_result_t egl_value_u8_set(egl_value_u8_t *value, uint8_t val)
{
    EGL_ASSERT_CHECK(value, EGL_NULL_POINTER);
    EGL_ASSERT_CHECK(value->set, EGL_NOT_SUPPORTED);

    return value->set(val);
}

egl_result_t egl_value_u8_get(egl_value_u8_t *value, uint8_t *val)
{
    EGL_ASSERT_CHECK(value, EGL_NULL_POINTER);
    EGL_ASSERT_CHECK(val, EGL_NULL_POINTER);
    EGL_ASSERT_CHECK(value->get, EGL_NOT_SUPPORTED);

    return value->get(val);
}

egl_result_t egl_value_u8_deinit(egl_value_u8_t *value)
{
    EGL_ASSERT_CHECK(value, EGL_NULL_POINTER);
    EGL_ASSERT_CHECK(value->deinit, EGL_NOT_SUPPORTED);

    return value->deinit();
}

egl_result_t egl_value_i16_init(egl_value_i16_t *value)
{
    EGL_ASSERT_CHECK(value, EGL_NULL_POINTER);
    EGL_ASSERT_CHECK(value->init, EGL_NOT_SUPPORTED);

    return value->init();
}

egl_result_t egl_value_i16_set(egl_value_i16_t *value, int16_t val)
{
    EGL_ASSERT_CHECK(value, EGL_NULL_POINTER);
    EGL_ASSERT_CHECK(value->set, EGL_NOT_SUPPORTED);

    return value->set(val);
}

egl_result_t egl_value_i16_get(egl_value_i16_t *value, int16_t *val)
{
    EGL_ASSERT_CHECK(value, EGL_NULL_POINTER);
    EGL_ASSERT_CHECK(val, EGL_NULL_POINTER);
    EGL_ASSERT_CHECK(value->get, EGL_NOT_SUPPORTED);

    return value->get(val);
}

egl_result_t egl_value_i16_deinit(egl_value_i16_t *value)
{
    EGL_ASSERT_CHECK(value, EGL_NULL_POINTER);
    EGL_ASSERT_CHECK(value->deinit, EGL_NOT_SUPPORTED);

    return value->deinit();
}

egl_result_t egl_value_u16_init(egl_value_u16_t *value)
{
    EGL_ASSERT_CHECK(value, EGL_NULL_POINTER);
    EGL_ASSERT_CHECK(value->init, EGL_NOT_SUPPORTED);

    return value->init();
}

egl_result_t egl_value_u16_set(egl_value_u16_t *value, uint16_t val)
{
    EGL_ASSERT_CHECK(value, EGL_NULL_POINTER);
    EGL_ASSERT_CHECK(value->set, EGL_NOT_SUPPORTED);

    return value->set(val);
}

egl_result_t egl_value_u16_get(egl_value_u16_t *value, uint16_t *val)
{
    EGL_ASSERT_CHECK(value, EGL_NULL_POINTER);
    EGL_ASSERT_CHECK(val, EGL_NULL_POINTER);
    EGL_ASSERT_CHECK(value->get, EGL_NOT_SUPPORTED);

    return value->get(val);
}

egl_result_t egl_value_u16_deinit(egl_value_u16_t *value)
{
    EGL_ASSERT_CHECK(value, EGL_NULL_POINTER);
    EGL_ASSERT_CHECK(value->deinit, EGL_NOT_SUPPORTED);

    return value->deinit();
}

egl_result_t egl_value_i32_init(egl_value_i32_t *value)
{
    EGL_ASSERT_CHECK(value, EGL_NULL_POINTER);
    EGL_ASSERT_CHECK(value->init, EGL_NOT_SUPPORTED);

    return value->init();
}

egl_result_t egl_value_i32_set(egl_value_i32_t *value, int32_t val)
{
    EGL_ASSERT_CHECK(value, EGL_NULL_POINTER);
    EGL_ASSERT_CHECK(value->set, EGL_NOT_SUPPORTED);

    return value->set(val);
}

egl_result_t egl_value_i32_get(egl_value_i32_t *value, int32_t *val)
{
    EGL_ASSERT_CHECK(value, EGL_NULL_POINTER);
    EGL_ASSERT_CHECK(val, EGL_NULL_POINTER);
    EGL_ASSERT_CHECK(value->get, EGL_NOT_SUPPORTED);

    return value->get(val);
}

egl_result_t egl_value_i32_deinit(egl_value_i32_t *value)
{
    EGL_ASSERT_CHECK(value, EGL_NULL_POINTER);
    EGL_ASSERT_CHECK(value->deinit, EGL_NOT_SUPPORTED);

    return value->deinit();
}

egl_result_t egl_value_u32_init(egl_value_u32_t *value)
{
    EGL_ASSERT_CHECK(value, EGL_NULL_POINTER);
    EGL_ASSERT_CHECK(value->init, EGL_NOT_SUPPORTED);

    return value->init();
}

egl_result_t egl_value_u32_set(egl_value_u32_t *value, uint32_t val)
{
    EGL_ASSERT_CHECK(value, EGL_NULL_POINTER);
    EGL_ASSERT_CHECK(value->set, EGL_NOT_SUPPORTED);

    return value->set(val);
}

egl_result_t egl_value_u32_get(egl_value_u32_t *value, uint32_t *val)
{
    EGL_ASSERT_CHECK(value, EGL_NULL_POINTER);
    EGL_ASSERT_CHECK(val, EGL_NULL_POINTER);
    EGL_ASSERT_CHECK(value->get, EGL_NOT_SUPPORTED);

    return value->get(val);
}

egl_result_t egl_value_u32_deinit(egl_value_u32_t *value)
{
    EGL_ASSERT_CHECK(value, EGL_NULL_POINTER);
    EGL_ASSERT_CHECK(value->deinit, EGL_NOT_SUPPORTED);

    return value->deinit();
}

egl_result_t egl_value_i64_init(egl_value_i64_t *value)
{
    EGL_ASSERT_CHECK(value, EGL_NULL_POINTER);
    EGL_ASSERT_CHECK(value->init, EGL_NOT_SUPPORTED);

    return value->init();
}

egl_result_t egl_value_i64_set(egl_value_i64_t *value, int64_t val)
{
    EGL_ASSERT_CHECK(value, EGL_NULL_POINTER);
    EGL_ASSERT_CHECK(value->set, EGL_NOT_SUPPORTED);

    return value->set(val);
}

egl_result_t egl_value_i64_get(egl_value_i64_t *value, int64_t *val)
{
    EGL_ASSERT_CHECK(value, EGL_NULL_POINTER);
    EGL_ASSERT_CHECK(val, EGL_NULL_POINTER);
    EGL_ASSERT_CHECK(value->get, EGL_NOT_SUPPORTED);

    return value->get(val);
}

egl_result_t egl_value_i64_deinit(egl_value_i64_t *value)
{
    EGL_ASSERT_CHECK(value, EGL_NULL_POINTER);
    EGL_ASSERT_CHECK(value->deinit, EGL_NOT_SUPPORTED);

    return value->deinit();
}

egl_result_t egl_value_u64_init(egl_value_u64_t *value)
{
    EGL_ASSERT_CHECK(value, EGL_NULL_POINTER);
    EGL_ASSERT_CHECK(value->init, EGL_NOT_SUPPORTED);

    return value->init();
}

egl_result_t egl_value_u64_set(egl_value_u64_t *value, uint64_t val)
{
    EGL_ASSERT_CHECK(value, EGL_NULL_POINTER);
    EGL_ASSERT_CHECK(value->set, EGL_NOT_SUPPORTED);

    return value->set(val);
}

egl_result_t egl_value_u64_get(egl_value_u64_t *value, uint64_t *val)
{
    EGL_ASSERT_CHECK(value, EGL_NULL_POINTER);
    EGL_ASSERT_CHECK(val, EGL_NULL_POINTER);
    EGL_ASSERT_CHECK(value->get, EGL_NOT_SUPPORTED);

    return value->get(val);
}

egl_result_t egl_value_u64_deinit(egl_value_u64_t *value)
{
    EGL_ASSERT_CHECK(value, EGL_NULL_POINTER);
    EGL_ASSERT_CHECK(value->deinit, EGL_NOT_SUPPORTED);

    return value->deinit();
}

egl_result_t egl_value_ptr_init(egl_value_ptr_t *value)
{
    EGL_ASSERT_CHECK(value, EGL_NULL_POINTER);
    EGL_ASSERT_CHECK(value->init, EGL_NOT_SUPPORTED);

    return value->init();
}

egl_result_t egl_value_ptr_set(egl_value_ptr_t *value, void *val)
{
    EGL_ASSERT_CHECK(value, EGL_NULL_POINTER);
    EGL_ASSERT_CHECK(value->set, EGL_NOT_SUPPORTED);

    return value->set(val);
}

egl_result_t egl_value_ptr_get(egl_value_ptr_t *value, void **val)
{
    EGL_ASSERT_CHECK(value, EGL_NULL_POINTER);
    EGL_ASSERT_CHECK(val, EGL_NULL_POINTER);
    EGL_ASSERT_CHECK(value->get, EGL_NOT_SUPPORTED);

    return value->get(val);
}

egl_result_t egl_value_ptr_deinit(egl_value_ptr_t *value)
{
    EGL_ASSERT_CHECK(value, EGL_NULL_POINTER);
    EGL_ASSERT_CHECK(value->deinit, EGL_NOT_SUPPORTED);

    return value->deinit();
}
