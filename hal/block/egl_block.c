/*
 * Copyright (c) 2025 rikorsev
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

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