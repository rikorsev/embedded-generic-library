#ifndef EGL_RFM69_IFACE_H
#define EGL_RFM69_IFACE_H

#include "egl_rfm69_driver.h"

typedef struct
{
    uint32_t frequency;
    uint32_t deviation;
    uint32_t bitrate;
    uint16_t preamble;
    egl_rfm69_bandwidth_t bandwidth;
    uint8_t power;
    uint8_t node_addr;
    char *sync;
    uint8_t sync_size;
}egl_rfm69_config_t;

typedef struct
{
    egl_rfm69_t *rfm;
    uint32_t    pm_wait;
}egl_rfm69_iface_t;

egl_result_t egl_rfm69_iface_init(egl_rfm69_iface_t *iface, egl_rfm69_config_t *config);
egl_result_t egl_rfm69_iface_write(egl_rfm69_iface_t *iface, void *data, size_t *len);
egl_result_t egl_rfm69_iface_read(egl_rfm69_iface_t *iface, void *data, size_t *len);
egl_result_t egl_rfm69_iface_ioctl(egl_rfm69_iface_t *iface, uint8_t opcode, void *data, size_t len);
egl_result_t egl_rfm69_iface_deinit(egl_rfm69_iface_t *iface);

#endif