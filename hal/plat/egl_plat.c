#include <stdlib.h>

#include "egl_result.h"
#include "egl_plat.h"

egl_result_t egl_plat_init(egl_platform_t *plat)
{
    EGL_ASSERT_CHECK(plat, EGL_ASSERT_FAIL);
    EGL_ASSERT_CHECK(plat->init, EGL_NOT_SUPPORTED);

    return plat->init();
}

egl_result_t egl_plat_boot(egl_platform_t *plat, unsigned int slot_idx)
{
    EGL_ASSERT_CHECK(plat, EGL_ASSERT_FAIL);
    EGL_ASSERT_CHECK(plat->boot, EGL_NOT_SUPPORTED);

    return plat->boot(slot_idx);
}

egl_result_t egl_plat_deinit(egl_platform_t *plat)
{
    EGL_ASSERT_CHECK(plat, EGL_ASSERT_FAIL);
    EGL_ASSERT_CHECK(plat->deinit, EGL_NOT_SUPPORTED);

    return plat->deinit();
}
