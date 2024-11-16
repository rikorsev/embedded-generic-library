#include <stdlib.h>
#include "egl_clock.h"

egl_result_t egl_clock_init(egl_clock_t *clock, uint32_t profile)
{
    EGL_ASSERT_CHECK(clock);
    EGL_ASSERT_CHECK(clock->init(profile));

    return clock->init(profile);
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
