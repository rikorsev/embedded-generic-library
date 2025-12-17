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

#ifndef EGL_BLOCK_H
#define EGL_BLOCK_H

#include <stdint.h>
#include "egl_result.h"

typedef struct
{
    egl_result_t (*init)(void);
    egl_result_t (*read)(uint32_t addr, void *data);
    egl_result_t (*write)(uint32_t addr, void *data);
    egl_result_t (*deinit)(void);
}egl_block_t;

/**
 * @brief Init block device
 *
 * @param block - pointer to block device to init
 *
 * @return EGL_SUCCESS if the device is inited successfully
 */
static inline egl_result_t egl_block_init(egl_block_t *block)
{
    EGL_ASSERT_CHECK(block, EGL_ASSERT_FAIL);
    EGL_ASSERT_CHECK(block->init, EGL_NOT_SUPPORTED);

    return block->init();
}

/**
 * @brief Read from block device
 *
 * @param block - pointer to block device read from
 * @param addr - address to read from
 * @param data - pointer to buffer which whill store read data
 *
 * @return EGL_SUCCESS in case of successfull read
 */
static inline egl_result_t egl_block_read(egl_block_t *block, uint32_t addr, void *data)
{
    EGL_ASSERT_CHECK(block, EGL_ASSERT_FAIL);
    EGL_ASSERT_CHECK(block->read, EGL_NOT_SUPPORTED);

    return block->read(addr, data);
}

/**
 * @brief Write to block device
 *
 * @param block - pointer to block device to write
 * @param addr - address to write
 * @param data - data that shall be written to block device
 *
 * @return EGL_SUCCESS in case of successful write
 */
static inline egl_result_t egl_block_write(egl_block_t *block, uint32_t addr, void *data)
{
    EGL_ASSERT_CHECK(block, EGL_ASSERT_FAIL);
    EGL_ASSERT_CHECK(block->write, EGL_NOT_SUPPORTED);

    return block->write(addr, data);
}
/**
 * @brief Deinit block device
 *
 * @param block - pointer to block device to deinit
 */
egl_result_t egl_block_deinit(egl_block_t *block)
{
    EGL_ASSERT_CHECK(block, EGL_ASSERT_FAIL);
    EGL_ASSERT_CHECK(block->deinit, EGL_NOT_SUPPORTED);

    return block->deinit();
}

#endif
