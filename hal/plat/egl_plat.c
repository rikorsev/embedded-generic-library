#include <stdlib.h>

#include "egl_result.h"
#include "egl_plat.h"

egl_result_t egl_plat_init(egl_platform_t *plat)
{
    EGL_ASSERT_CHECK(plat);
    EGL_ASSERT_CHECK(plat->init);

    return plat->init();
}

egl_result_t egl_plat_boot(egl_platform_t *plat, unsigned int slot_idx)
{
    EGL_ASSERT_CHECK(plat);
    EGL_ASSERT_CHECK(plat->boot);

    return plat->boot(slot_idx);
}

void *egl_plat_info(egl_platform_t *plat)
{
    if(plat == NULL || plat->info == NULL)
    {
        return NULL;
    }

    return plat->info();
}

void *egl_plat_slot_info(egl_platform_t *plat, unsigned int slot_idx)
{
    if(plat == NULL || plat->slot_info == NULL)
    {
        return NULL;
    }

    return plat->slot_info(slot_idx);
}
