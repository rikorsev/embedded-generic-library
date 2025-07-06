/**
 * @file The module represents different kind of serial interfaces like UART, SPI, I2C etc.
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
egl_result_t egl_iface_init(egl_iface_t *iface);

/**
 * @brief Open serial interface
 *
 * @param iface - pointer to serial interface to open
 *
 * @return EGL_SUCCESS in case of successful opening
 */
egl_result_t egl_iface_open(egl_iface_t *iface);

/**
 * @brief Write to serial interface
 *
 * @param iface - pionter to serial interface to write
 * @param buff - pointer to data to write
 * @param len - size of data to write in bytes
 *
 * @return EGL_SUCCESS in case of successfull write
 */
egl_result_t egl_iface_write(egl_iface_t *iface, void *buff, size_t *len);

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
egl_result_t egl_iface_write_addr(egl_iface_t *iface, uint32_t addr, void *buff, size_t *len);

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
egl_result_t egl_iface_ioctl(egl_iface_t *iface, uint8_t opcode, void *data, size_t *len);

/**
 * @brief Read from serial interface
 *
 * @param iface - pointer to serial interface to read from
 * @param buff - pointer to buffer to store read data
 * @param len - len of buffer/len of read data
 *
 * @return EGL_SUCCESS in case of successful read
 */
egl_result_t egl_iface_read(egl_iface_t *iface, void *buff, size_t *len);

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
egl_result_t egl_iface_read_addr(egl_iface_t *iface, uint32_t addr, void *buff, size_t *len);

/**
 * @brief Close serial interface
 *
 * @param iface - pointer to serial interface to close
 *
 * @return EGL_SUCCESS in case if successful closeing
 */
egl_result_t egl_iface_close(egl_iface_t *iface);

/**
 * @brief Deinit serial interface
 *
 * @param iface - pointer to serial interface to deinit
 *
 * @return EGL_SUCCESS in case of successful deinitialization
 */
egl_result_t egl_iface_deinit(egl_iface_t *iface);

#endif /* EGL_IFACE_H */
