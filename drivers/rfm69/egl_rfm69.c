#include "egl_rfm69.h"
#include "egl_result.h"
#include "egl_log.h"

#define EGL_MODULE_NAME "egl_rfm69"

static egl_result_t egl_rfm69_hw_init(egl_rfm69_t *rfm)
{
    egl_result_t result;

    result = egl_pm_init(rfm->pm);
    if(result != EGL_SUCCESS)
    {
        EGL_LOG_ERROR("Fail to init rfm69 PM component. Result: %s", EGL_RESULT(result));
        return result;
    }

    result = egl_itf_init(rfm->iface);
    if(result != EGL_SUCCESS)
    {
        EGL_LOG_ERROR("Fail to init rfm69 iface component. Result: %s", EGL_RESULT(result));
        return result;
    }

    result = egl_pio_init(rfm->dio0);
    if(result != EGL_SUCCESS)
    {
        EGL_LOG_ERROR("Fail to init rfm69 DIO0 component. Result: %s", EGL_RESULT(result));
        return result;
    }

    result = egl_pio_init(rfm->dio1);
    if(result != EGL_SUCCESS)
    {
        EGL_LOG_ERROR("Fail to init rfm69 DIO1 component. Result: %s", EGL_RESULT(result));
        return result;
    }

    result = egl_pio_init(rfm->dio2);
    if(result != EGL_SUCCESS)
    {
        EGL_LOG_ERROR("Fail to init rfm69 DIO2 component. Result: %s", EGL_RESULT(result));
        return result;
    }

    result = egl_pio_init(rfm->dio3);
    if(result != EGL_SUCCESS)
    {
        EGL_LOG_ERROR("Fail to init rfm69 DIO3 component. Result: %s", EGL_RESULT(result));
        return result;
    }

    result = egl_pio_init(rfm->dio4);
    if(result != EGL_SUCCESS)
    {
        EGL_LOG_ERROR("Fail to init rfm69 DIO4 component. Result: %s", EGL_RESULT(result));
        return result;
    }

    result = egl_pio_init(rfm->dio5);
    if(result != EGL_SUCCESS)
    {
        EGL_LOG_ERROR("Fail to init rfm69 DIO5 component. Result: %s", EGL_RESULT(result));
        return result;
    }

    result = egl_pm_poweron(rfm->pm);
    if(result != EGL_SUCCESS)
    {
        EGL_LOG_ERROR("Fail to poweron rfm69. Result: %s", EGL_RESULT(result));
        return result;
    }

    result = egl_pm_reset(rfm->pm);
    if(result != EGL_SUCCESS)
    {
        EGL_LOG_ERROR("Fail to reset rfm69. Result: %s", EGL_RESULT(result));
        return result;
    }

    return result;
}

egl_result_t egl_rfm69_init(egl_rfm69_t *rfm)
{
    egl_result_t result;

    result = egl_rfm69_hw_init(rfm);
    if(result != EGL_SUCCESS)
    {
        EGL_LOG_ERROR("Failt to init rfm69 hardware. Result: %s", EGL_RESULT(result));
        return result;
    }

    return result;
}

egl_result_t egl_rfm69_read_byte(egl_rfm69_t *rfm, uint8_t addr, uint8_t *value)
{
    egl_result_t result;
    size_t len = sizeof(*value);

    result = egl_itf_read_addr(rfm->iface, (uint32_t)addr, value, &len);
    EGL_RESULT_CHECK(result);
    EGL_ASSERT_CHECK(len == sizeof(*value), EGL_FAIL);

    return result;
}