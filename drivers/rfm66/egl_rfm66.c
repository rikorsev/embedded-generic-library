#include "egl_rfm66.h"
#include "egl_log.h"
#include "egl_util.h"

static egl_result_t egl_rfm66_hw_init(egl_rfm66_t *rfm)
{
    egl_result_t result;

    result = egl_pm_init(rfm->pm);
    EGL_RESULT_CHECK(result);

    result = egl_itf_init(rfm->iface);
    EGL_RESULT_CHECK(result);

    result = egl_pio_init(rfm->dio0);
    EGL_RESULT_CHECK(result);

    result = egl_pio_init(rfm->dio1);
    EGL_RESULT_CHECK(result);

    result = egl_pio_init(rfm->dio2);
    EGL_RESULT_CHECK(result);

    result = egl_pio_init(rfm->dio3);
    EGL_RESULT_CHECK(result);

    result = egl_pio_init(rfm->dio4);
    EGL_RESULT_CHECK(result);

    result = egl_pio_init(rfm->dio5);
    EGL_RESULT_CHECK(result);

    result = egl_pm_poweron(rfm->pm);
    EGL_RESULT_CHECK(result);

    result = egl_pm_reset(rfm->pm);
    EGL_RESULT_CHECK(result);

    result = egl_clock_init(rfm->clock, 0);
    EGL_RESULT_CHECK(result);

    return result;
}

egl_result_t egl_rfm66_init(egl_rfm66_t *rfm)
{
    egl_result_t result;

    result = egl_rfm66_hw_init(rfm);
    EGL_RESULT_CHECK(result);

    return result;
}

egl_result_t egl_rfm66_read_byte(egl_rfm66_t *rfm, uint8_t addr, uint8_t *value)
{
    egl_result_t result;
    size_t len = sizeof(*value);

    result = egl_itf_read_addr(rfm->iface, (uint32_t)addr, value, &len);
    EGL_RESULT_CHECK(result);
    EGL_ASSERT_CHECK(len == sizeof(*value), EGL_FAIL);

    return result;
}

egl_result_t egl_rfm66_write_byte(egl_rfm66_t *rfm, uint8_t addr, uint8_t value)
{
    egl_result_t result;
    size_t len = sizeof(value);

    result = egl_itf_write_addr(rfm->iface, (uint32_t)addr, &value, &len);
    EGL_RESULT_CHECK(result);
    EGL_ASSERT_CHECK(len == sizeof(value), EGL_FAIL);

    return result;
}

egl_result_t egl_rfm66_write_burst(egl_rfm66_t *rfm, uint8_t addr, void *data, size_t len)
{
    return egl_itf_write_addr(rfm->iface, (uint32_t)addr, data, &len);
}

egl_result_t egl_rfm66_read_burst(egl_rfm66_t *rfm, uint8_t addr, void *data, size_t len)
{
    return egl_itf_read_addr(rfm->iface, (uint32_t)addr, data, &len);
}

egl_result_t egl_rfm66_version_get(egl_rfm66_t *rfm, uint8_t *version)
{
    return egl_rfm66_read_byte(rfm, EGL_RFM66_REG_VERSION, version);
}