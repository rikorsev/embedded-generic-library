#include "egl_result.h"
#include "egl_iface.h"

egl_result_t egl_iface_init(egl_iface_t *iface)
{
    EGL_ASSERT_CHECK(iface, EGL_ASSERT_FAIL);
    EGL_ASSERT_CHECK(iface->init, EGL_NOT_SUPPORTED);

    return iface->init();
}

egl_result_t egl_iface_open(egl_iface_t *iface)
{
    EGL_ASSERT_CHECK(iface, EGL_ASSERT_FAIL);
    EGL_ASSERT_CHECK(iface->open, EGL_NOT_SUPPORTED);

    return iface->open();
}

egl_result_t egl_iface_write(egl_iface_t *iface, void *buff, size_t *len)
{
    EGL_ASSERT_CHECK(iface, EGL_ASSERT_FAIL);
    EGL_ASSERT_CHECK(buff, EGL_ASSERT_FAIL);
    EGL_ASSERT_CHECK(len, EGL_ASSERT_FAIL);
    EGL_ASSERT_CHECK(iface->write, EGL_NOT_SUPPORTED);

    return iface->write(buff, len);
}

egl_result_t egl_iface_write_addr(egl_iface_t *iface, uint32_t addr, void *buff, size_t *len)
{
    EGL_ASSERT_CHECK(iface, EGL_ASSERT_FAIL);
    EGL_ASSERT_CHECK(buff, EGL_ASSERT_FAIL);
    EGL_ASSERT_CHECK(len, EGL_ASSERT_FAIL);
    EGL_ASSERT_CHECK(iface->write_addr, EGL_NOT_SUPPORTED);

    return iface->write_addr(addr, buff, len);
}

egl_result_t egl_iface_ioctl(egl_iface_t *iface, uint8_t opcode, void *data, size_t *len)
{
    EGL_ASSERT_CHECK(iface, EGL_ASSERT_FAIL);
    EGL_ASSERT_CHECK(iface->ioctl, EGL_NOT_SUPPORTED);

    return iface->ioctl(opcode, data, len);
}

egl_result_t egl_iface_read(egl_iface_t *iface, void *buff, size_t *len)
{
    EGL_ASSERT_CHECK(iface, EGL_ASSERT_FAIL);
    EGL_ASSERT_CHECK(buff, EGL_ASSERT_FAIL);
    EGL_ASSERT_CHECK(len, EGL_ASSERT_FAIL);
    EGL_ASSERT_CHECK(iface->read, EGL_NOT_SUPPORTED);

    return iface->read(buff, len);
}

egl_result_t egl_iface_read_addr(egl_iface_t *iface, uint32_t addr, void *buff, size_t *len)
{
    EGL_ASSERT_CHECK(iface, EGL_ASSERT_FAIL);
    EGL_ASSERT_CHECK(buff, EGL_ASSERT_FAIL);
    EGL_ASSERT_CHECK(len, EGL_ASSERT_FAIL);
    EGL_ASSERT_CHECK(iface->read_addr, EGL_NOT_SUPPORTED);

    return iface->read_addr(addr, buff, len);
}

egl_result_t egl_iface_close(egl_iface_t *iface)
{
    EGL_ASSERT_CHECK(iface, EGL_ASSERT_FAIL);
    EGL_ASSERT_CHECK(iface->close, EGL_NOT_SUPPORTED);

    return iface->close();
}

egl_result_t egl_iface_deinit(egl_iface_t *iface)
{
    EGL_ASSERT_CHECK(iface, EGL_ASSERT_FAIL);
    EGL_ASSERT_CHECK(iface->deinit, EGL_NOT_SUPPORTED);

    return iface->deinit();
}