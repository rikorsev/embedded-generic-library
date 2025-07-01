#include "egl_result.h"
#include "egl_pm.h"

egl_result_t egl_pm_init(egl_pm_t *pm)
{
    EGL_ASSERT_CHECK(pm, EGL_ASSERT_FAIL);
    EGL_ASSERT_CHECK(pm->init, EGL_NOT_SUPPORTED);

    return pm->init();
}

egl_result_t egl_pm_poweron(egl_pm_t *pm)
{
    EGL_ASSERT_CHECK(pm, EGL_ASSERT_FAIL);
    EGL_ASSERT_CHECK(pm->poweron, EGL_NOT_SUPPORTED);

    return pm->poweron();
}

egl_result_t egl_pm_mode_set(egl_pm_t *pm, uint32_t mode)
{
    EGL_ASSERT_CHECK(pm, EGL_ASSERT_FAIL);
    EGL_ASSERT_CHECK(pm->mode_set, EGL_NOT_SUPPORTED);

    return pm->mode_set(mode);
}

egl_result_t egl_pm_sleep(egl_pm_t *pm, uint32_t delay)
{
    EGL_ASSERT_CHECK(pm, EGL_ASSERT_FAIL);
    EGL_ASSERT_CHECK(pm->sleep, EGL_NOT_SUPPORTED);

    return pm->sleep(delay);
}

egl_result_t egl_pm_reset(egl_pm_t *pm)
{
    EGL_ASSERT_CHECK(pm, EGL_ASSERT_FAIL);
    EGL_ASSERT_CHECK(pm->reset, EGL_NOT_SUPPORTED);

    return pm->reset();
}

egl_result_t egl_pm_shutdown(egl_pm_t *pm)
{
    EGL_ASSERT_CHECK(pm, EGL_ASSERT_FAIL);
    EGL_ASSERT_CHECK(pm->shutdown, EGL_NOT_SUPPORTED);

    return pm->shutdown();
}

egl_result_t egl_pm_deinit(egl_pm_t *pm)
{
    EGL_ASSERT_CHECK(pm, EGL_ASSERT_FAIL);
    EGL_ASSERT_CHECK(pm->deinit, EGL_NOT_SUPPORTED);

    return pm->deinit();
}
