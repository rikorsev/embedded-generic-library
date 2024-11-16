#include "egl_result.h"
#include "egl_pm.h"

egl_result_t egl_pm_poweron(egl_pm_t *pm)
{
    EGL_ASSERT_CHECK(pm);
    EGL_ASSERT_CHECK(pm->poweron);

    return pm->poweron();
}

egl_result_t egl_pm_profile_set(egl_pm_t *pm, uint32_t profile)
{
    EGL_ASSERT_CHECK(pm);
    EGL_ASSERT_CHECK(pm->profile_set);

    return pm->profile_set(profile);
}

egl_result_t egl_pm_sleep(egl_pm_t *pm, uint32_t delay)
{
    EGL_ASSERT_CHECK(pm);
    EGL_ASSERT_CHECK(pm->sleep);

    return pm->sleep(delay);
}

egl_result_t egl_pm_reset(egl_pm_t *pm)
{
    EGL_ASSERT_CHECK(pm);
    EGL_ASSERT_CHECK(pm->reset);

    return pm->reset();
}

egl_result_t egl_pm_shutdown(egl_pm_t *pm)
{
    EGL_ASSERT_CHECK(pm);
    EGL_ASSERT_CHECK(pm->shutdown);

    return pm->shutdown();
}