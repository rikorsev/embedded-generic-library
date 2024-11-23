#include "egl_result.h"
#include "egl_interface.h"

egl_result_t egl_itf_init(egl_interface_t *itf)
{
    EGL_ASSERT_CHECK(itf, EGL_ASSERT_FAIL);
    EGL_ASSERT_CHECK(itf->init, EGL_NOT_SUPPORTED);

    return itf->init();
}

egl_result_t egl_itf_open(egl_interface_t* itf)
{
    EGL_ASSERT_CHECK(itf, EGL_ASSERT_FAIL);
    EGL_ASSERT_CHECK(itf->open, EGL_NOT_SUPPORTED);

    return itf->open();
}

egl_result_t egl_itf_write(egl_interface_t *itf, void *buff, size_t *len)
{
    EGL_ASSERT_CHECK(itf, EGL_ASSERT_FAIL);
    EGL_ASSERT_CHECK(buff, EGL_ASSERT_FAIL);
    EGL_ASSERT_CHECK(len, EGL_ASSERT_FAIL);
    EGL_ASSERT_CHECK(itf->write, EGL_NOT_SUPPORTED);

    *len = itf->write(buff, *len);

    return EGL_SUCCESS;
}

egl_result_t efl_itf_write_addr(egl_interface_t *itf, uint32_t addr, void *buff, size_t *len)
{
    EGL_ASSERT_CHECK(itf, EGL_ASSERT_FAIL);
    EGL_ASSERT_CHECK(buff, EGL_ASSERT_FAIL);
    EGL_ASSERT_CHECK(len, EGL_ASSERT_FAIL);
    EGL_ASSERT_CHECK(itf->write_addr, EGL_NOT_SUPPORTED);

    *len = itf->write_addr(addr, buff, *len);

    return EGL_SUCCESS;
}

egl_result_t egl_itf_ioctl(egl_interface_t *itf, uint8_t opcode, void *data, size_t len)
{
    EGL_ASSERT_CHECK(itf, EGL_ASSERT_FAIL);
    EGL_ASSERT_CHECK(itf->ioctl, EGL_NOT_SUPPORTED);

    return itf->ioctl(opcode, data, len);
}

egl_result_t egl_itf_read(egl_interface_t *itf, void *buff, size_t *len)
{
    EGL_ASSERT_CHECK(itf, EGL_ASSERT_FAIL);
    EGL_ASSERT_CHECK(buff, EGL_ASSERT_FAIL);
    EGL_ASSERT_CHECK(len, EGL_ASSERT_FAIL);
    EGL_ASSERT_CHECK(itf->read, EGL_NOT_SUPPORTED);

    *len = itf->read(buff, *len);

    return EGL_SUCCESS;
}

egl_result_t egl_itf_read_addr(egl_interface_t *itf, uint32_t addr, void *buff, size_t *len)
{
    EGL_ASSERT_CHECK(itf, EGL_ASSERT_FAIL);
    EGL_ASSERT_CHECK(buff, EGL_ASSERT_FAIL);
    EGL_ASSERT_CHECK(len, EGL_ASSERT_FAIL);
    EGL_ASSERT_CHECK(itf->read_addr, EGL_NOT_SUPPORTED);

    *len = itf->read_addr(addr, buff, *len);

    return EGL_SUCCESS;
}

egl_result_t egl_itf_close(egl_interface_t *itf)
{
    EGL_ASSERT_CHECK(itf, EGL_ASSERT_FAIL);
    EGL_ASSERT_CHECK(itf->close, EGL_NOT_SUPPORTED);

    return itf->close();
}

egl_result_t egl_itf_deinit(egl_interface_t *itf)
{
    EGL_ASSERT_CHECK(itf, EGL_ASSERT_FAIL);
    EGL_ASSERT_CHECK(itf->deinit, EGL_NOT_SUPPORTED);

    return itf->deinit();
}