#ifndef EGL_RFM66_H
#define EGL_RFM66_H

#include "egl_result.h"
#include "egl_pm.h"
#include "egl_pio.h"
#include "egl_interface.h"
#include "egl_clock.h"

#define EGL_RFM66_REG_VERSION               (0x42)

typedef struct
{
    egl_pm_t        *pm;
    egl_interface_t *iface;
    egl_clock_t     *clock;
    egl_pio_t       *dio0;
    egl_pio_t       *dio1;
    egl_pio_t       *dio2;
    egl_pio_t       *dio3;
    egl_pio_t       *dio4;
    egl_pio_t       *dio5;
}egl_rfm66_t;

egl_result_t egl_rfm66_init(egl_rfm66_t *rfm);
egl_result_t egl_rfm66_read_byte(egl_rfm66_t *rfm, uint8_t addr, uint8_t *value);
egl_result_t egl_rfm66_write_byte(egl_rfm66_t *rfm, uint8_t addr, uint8_t value);
egl_result_t egl_rfm66_write_burst(egl_rfm66_t *rfm, uint8_t addr, void *data, size_t len);
egl_result_t egl_rfm66_read_burst(egl_rfm66_t *rfm, uint8_t addr, void *data, size_t len);
egl_result_t egl_rfm66_version_get(egl_rfm66_t *rfm, uint8_t *version);

#endif