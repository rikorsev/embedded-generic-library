#include "egl_block.h"

egl_result_t egl_block_init(egl_block_t *block)
{
    EGL_ASSERT_CHECK(block, EGL_ASSERT_FAIL);
    EGL_ASSERT_CHECK(block->init, EGL_NOT_SUPPORTED);

    return block->init();
}

egl_result_t egl_block_read(egl_block_t *block, uint32_t addr, void *data)
{
    EGL_ASSERT_CHECK(block, EGL_ASSERT_FAIL);
    EGL_ASSERT_CHECK(block->read, EGL_NOT_SUPPORTED);

    return block->read(addr, data);
}

egl_result_t egl_block_write(egl_block_t *block, uint32_t addr, void *data)
{
    EGL_ASSERT_CHECK(block, EGL_ASSERT_FAIL);
    EGL_ASSERT_CHECK(block->write, EGL_NOT_SUPPORTED);

    return block->write(addr, data);
}

egl_result_t egl_block_deinit(egl_block_t *block)
{
    EGL_ASSERT_CHECK(block, EGL_ASSERT_FAIL);
    EGL_ASSERT_CHECK(block->deinit, EGL_NOT_SUPPORTED);

    return block->deinit();
}