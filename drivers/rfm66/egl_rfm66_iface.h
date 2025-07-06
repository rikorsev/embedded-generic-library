#ifndef EGL_RFM66_IFACE_H
#define EGL_RFM66_IFACE_H

#include "egl_rfm66_driver.h"

typedef struct
{
    uint32_t frequency;
    uint32_t deviation;
    uint32_t bitrate;
    uint16_t preamble;
    egl_rfm66_bandwidth_t bandwidth;
    uint8_t power;
    uint8_t node_addr;
    char *sync;
    uint8_t sync_size;
}egl_rfm66_config_t;

typedef struct
{
    egl_rfm66_t *rfm;
    uint32_t    pm_wait;
    uint32_t    rx_timeout;
    uint32_t    tx_timeout;
}egl_rfm66_iface_t;

egl_result_t egl_rfm66_iface_init(egl_rfm66_iface_t *iface, egl_rfm66_config_t *config);
egl_result_t egl_rfm66_iface_write(egl_rfm66_iface_t *iface, void *data, size_t *len);
egl_result_t egl_rfm66_iface_read(egl_rfm66_iface_t *iface, void *data, size_t *len);
egl_result_t egl_rfm66_iface_ioctl(egl_rfm66_iface_t *iface, uint8_t opcode, void *data, size_t len);
egl_result_t egl_rfm66_iface_deinit(egl_rfm66_iface_t *iface);

#endif