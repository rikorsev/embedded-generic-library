#ifndef EGL_RFM69_H
#define EGL_RFM69_H

#include "egl_result.h"
#include "egl_pm.h"
#include "egl_pio.h"
#include "egl_interface.h"

#define EGL_RFM69_REG_VERSION (0x10)

typedef struct
{
    egl_pm_t        *pm;
    egl_interface_t *iface;
    egl_pio_t       *dio0;
    egl_pio_t       *dio1;
    egl_pio_t       *dio2;
    egl_pio_t       *dio3;
    egl_pio_t       *dio4;
    egl_pio_t       *dio5;
}egl_rfm69_t;

egl_result_t egl_rfm69_init(egl_rfm69_t *rfm);
egl_result_t egl_rfm69_read_byte(egl_rfm69_t *rfm, uint8_t addr, uint8_t *value);

#endif