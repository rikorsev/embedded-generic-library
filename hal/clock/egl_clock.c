#include <stdlib.h>
#include "egl_clock.h"

egl_result_t egl_clock_init(egl_clock_t *clock)
{
    EGL_ASSERT_CHECK(clock, EGL_ASSERT_FAIL);
    EGL_ASSERT_CHECK(clock->init, EGL_NOT_SUPPORTED);

    return clock->init();
}

uint32_t egl_clock_get(egl_clock_t *clock)
{
    if(clock == NULL)
    {
        return 0;
    }

    if(clock->get == NULL)
    {
        return 0;
    }

    return clock->get();
}

egl_result_t egl_clock_deinit(egl_clock_t *clock)
{
    EGL_ASSERT_CHECK(clock, EGL_ASSERT_FAIL);
    EGL_ASSERT_CHECK(clock->deinit, EGL_NOT_SUPPORTED);

    return clock->deinit();
}

