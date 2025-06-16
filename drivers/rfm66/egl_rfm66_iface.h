#ifndef EGL_RFM66_IFACE_H
#define EGL_RFM66_IFACE_H

typedef struct
{
    uint32_t frequency;
    uint32_t bandwith;
    uint32_t deviation;
    uint32_t bitrate;
}egl_rfm66_config_t;

egl_result_t egl_rfm66_iface_init(egl_rfm66_t *rfm, egl_rfm66_config_t *config);
size_t egl_rfm66_iface_write(egl_rfm66_t *rfm, void *data, size_t len);
size_t egl_rfm66_iface_read(egl_rfm66_t *rfm, void *data, size_t len);
egl_result_t egl_rfm66_iface_ioctl(egl_rfm66_t *rfm, uint8_t opcode, void *data, size_t len);
egl_result_t egl_rfm66_iface_deinit(egl_rfm66_t *rfm);

#endif