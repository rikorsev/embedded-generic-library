#include "egl_result.h"
#include "egl_rfm66_driver.h"
#include "egl_rfm66_iface.h"

egl_result_t egl_rfm66_iface_init(egl_rfm66_t *rfm, egl_rfm66_config_t *config)
{
    egl_result_t result;

    result = egl_rfm66_init(rfm);
    EGL_RESULT_CHECK(result);

    result = egl_rfm66_frequency_set(rfm, config->frequency);
    EGL_RESULT_CHECK(result);

    result = egl_rfm66_deviation_set(rfm, config->deviation);
    EGL_RESULT_CHECK(result);

    result = egl_rfm66_bitrate_set(rfm, config->bitrate);
    EGL_RESULT_CHECK(result);

    return result;
}

size_t egl_rfm66_iface_write(egl_rfm66_t *rfm, void *data, size_t len)
{
    return EGL_FAIL;
}

size_t egl_rfm66_iface_read(egl_rfm66_t *rfm, void *data, size_t len)
{
    return EGL_FAIL;
}

egl_result_t egl_rfm66_iface_ioctl(egl_rfm66_t *rfm, uint8_t opcode, void *data, size_t len)
{
    return EGL_FAIL;
}

egl_result_t egl_rfm66_iface_deinit(egl_rfm66_t *rfm)
{
    return EGL_FAIL;
}
