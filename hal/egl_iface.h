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

#ifndef EGL_IFACE_H
#define EGL_IFACE_H

#include "stdint.h"
#include "stdlib.h"

typedef struct
{
    egl_result_t     (*init)          (void);
    egl_result_t     (*open)          (void);
    egl_result_t     (*write)         (void *data, size_t *len);
    egl_result_t     (*read)          (void *data, size_t *len);
    egl_result_t     (*write_addr)    (uint32_t addr, void *data, size_t *len);
    egl_result_t     (*read_addr)     (uint32_t addr, void *data, size_t *len);
    egl_result_t     (*ioctl)         (uint8_t opcode, void *data, size_t *len);
    egl_result_t     (*close)         (void);
    egl_result_t     (*deinit)        (void);
}egl_iface_t;

/**
 * @brief Init serial interface
 *
 * @param iface - pointer to serial interface to init
 *
 * @return EGL_SUCCESS in case of successful initialization
 */
static inline egl_result_t egl_iface_init(egl_iface_t *iface)
{
    EGL_ASSERT_CHECK(iface, EGL_ASSERT_FAIL);
    EGL_ASSERT_CHECK(iface->init, EGL_NOT_SUPPORTED);

    return iface->init();
}

/**
 * @brief Open serial interface
 *
 * @param iface - pointer to serial interface to open
 *
 * @return EGL_SUCCESS in case of successful opening
 */
static inline egl_result_t egl_iface_open(egl_iface_t *iface)
{
    EGL_ASSERT_CHECK(iface, EGL_ASSERT_FAIL);
    EGL_ASSERT_CHECK(iface->open, EGL_NOT_SUPPORTED);

    return iface->open();
}

/**
 * @brief Write to serial interface
 *
 * @param iface - pionter to serial interface to write
 * @param buff - pointer to data to write
 * @param len - size of data to write in bytes
 *
 * @return EGL_SUCCESS in case of successfull write
 */
static inline egl_result_t egl_iface_write(egl_iface_t *iface, void *buff, size_t *len)
{
    EGL_ASSERT_CHECK(iface, EGL_ASSERT_FAIL);
    EGL_ASSERT_CHECK(buff, EGL_ASSERT_FAIL);
    EGL_ASSERT_CHECK(len, EGL_ASSERT_FAIL);
    EGL_ASSERT_CHECK(iface->write, EGL_NOT_SUPPORTED);

    return iface->write(buff, len);
}

/**
 * @brief Write to serial interface by address/register
 *
 * @param iface - pionter to serial interface to write
 * @param addr - address/register of serial device to write
 * @param buff - pointer to data to write
 * @param len - size of data to write in bytes
 *
 * @return EGL_SUCCESS in case of successfull write
 */
static inline egl_result_t egl_iface_write_addr(egl_iface_t *iface, uint32_t addr, void *buff, size_t *len)
{
    EGL_ASSERT_CHECK(iface, EGL_ASSERT_FAIL);
    EGL_ASSERT_CHECK(buff, EGL_ASSERT_FAIL);
    EGL_ASSERT_CHECK(len, EGL_ASSERT_FAIL);
    EGL_ASSERT_CHECK(iface->write_addr, EGL_NOT_SUPPORTED);

    return iface->write_addr(addr, buff, len);
}

/**
 * @brief Perform IOCTL operation
 *
 * @param iface - pointer to serial interface
 * @param opcode - Operational code to perform
 * @param data - additional data required to perform IOCTL
 * @param len - size of data
 *
 * @return EGL_SUCCESS in case of success
 */
static inline egl_result_t egl_iface_ioctl(egl_iface_t *iface, uint8_t opcode, void *data, size_t *len)
{
    EGL_ASSERT_CHECK(iface, EGL_ASSERT_FAIL);
    EGL_ASSERT_CHECK(iface->ioctl, EGL_NOT_SUPPORTED);

    return iface->ioctl(opcode, data, len);
}

/**
 * @brief Read from serial interface
 *
 * @param iface - pointer to serial interface to read from
 * @param buff - pointer to buffer to store read data
 * @param len - len of buffer/len of read data
 *
 * @return EGL_SUCCESS in case of successful read
 */
static inline egl_result_t egl_iface_read(egl_iface_t *iface, void *buff, size_t *len)
{
    EGL_ASSERT_CHECK(iface, EGL_ASSERT_FAIL);
    EGL_ASSERT_CHECK(buff, EGL_ASSERT_FAIL);
    EGL_ASSERT_CHECK(len, EGL_ASSERT_FAIL);
    EGL_ASSERT_CHECK(iface->read, EGL_NOT_SUPPORTED);

    return iface->read(buff, len);
}

/**
 * @brief Read from serial interface by address/register
 *
 * @param iface - pointer to serial interface to read from
 * @param addr - address/register of sertal device to read from
 * @param buff - pointer to buffer to store read data
 * @param len - len of buffer/len of read data
 *
 * @return EGL_SUCCESS in case of successful read
 */
static inline egl_result_t egl_iface_read_addr(egl_iface_t *iface, uint32_t addr, void *buff, size_t *len)
{
    EGL_ASSERT_CHECK(iface, EGL_ASSERT_FAIL);
    EGL_ASSERT_CHECK(buff, EGL_ASSERT_FAIL);
    EGL_ASSERT_CHECK(len, EGL_ASSERT_FAIL);
    EGL_ASSERT_CHECK(iface->read_addr, EGL_NOT_SUPPORTED);

    return iface->read_addr(addr, buff, len);
}

/**
 * @brief Close serial interface
 *
 * @param iface - pointer to serial interface to close
 *
 * @return EGL_SUCCESS in case if successful closeing
 */
static inline egl_result_t egl_iface_close(egl_iface_t *iface)
{
    EGL_ASSERT_CHECK(iface, EGL_ASSERT_FAIL);
    EGL_ASSERT_CHECK(iface->close, EGL_NOT_SUPPORTED);

    return iface->close();
}

/**
 * @brief Deinit serial interface
 *
 * @param iface - pointer to serial interface to deinit
 *
 * @return EGL_SUCCESS in case of successful deinitialization
 */
static inline egl_result_t egl_iface_deinit(egl_iface_t *iface)
{
    EGL_ASSERT_CHECK(iface, EGL_ASSERT_FAIL);
    EGL_ASSERT_CHECK(iface->deinit, EGL_NOT_SUPPORTED);

    return iface->deinit();
}

#endif /* EGL_IFACE_H */
