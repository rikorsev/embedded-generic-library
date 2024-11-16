#include <stdlib.h>

#include "egl_result.h"
#include "egl_timer.h"

egl_result_t egl_timer_init(egl_timer_t *timer)
{
    EGL_ASSERT_CHECK(timer, EGL_ASSERT_FAIL);
    EGL_ASSERT_CHECK(timer->init, EGL_NOT_SUPPORTED);

    return timer->init();
}

uint32_t egl_timer_get(egl_timer_t *timer)
{
    EGL_ASSERT_CHECK(timer, 0);
    EGL_ASSERT_CHECK(timer->get, 0);

    return timer->get();
}

egl_result_t egl_timer_set(egl_timer_t *timer, uint32_t val)
{
    EGL_ASSERT_CHECK(timer, EGL_ASSERT_FAIL);
    EGL_ASSERT_CHECK(timer->set, EGL_NOT_SUPPORTED);

    return timer->set(val);
}

egl_result_t egl_timer_deinit(egl_timer_t *timer)
{
    EGL_ASSERT_CHECK(timer, EGL_ASSERT_FAIL);
    EGL_ASSERT_CHECK(timer->deinit, EGL_NOT_SUPPORTED);

    return timer->deinit();
}
