#ifndef EGL_RFM66_H
#define EGL_RFM66_H

#include "egl_result.h"
#include "egl_pm.h"
#include "egl_pio.h"
#include "egl_interface.h"
#include "egl_clock.h"

#define EGL_RFM66_REG_FIFO                  (0x00)
#define EGL_RFM66_REG_MODE                  (0x01)
#define EGL_RFM66_REG_BITRATE_MSB           (0x02)
#define EGL_RFM66_REG_BITRATE_LSB           (0x03)
#define EGL_RFM66_REG_DEVIATION_MSB         (0x04)
#define EGL_RFM66_REG_DEVIATION_LSB         (0x05)
#define EGL_RFM66_REG_FREQUENCY_MSB         (0x06)
#define EGL_RFM66_REG_FREQUENCY_MID         (0x07)
#define EGL_RFM66_REG_FREQUENCY_LSB         (0x08)
#define EGL_RFM66_REG_VERSION               (0x42)

typedef enum
{
    EGL_RFM66_SLEEP_MODE,
    EGL_RFM66_STDBY_MODE,
    EGL_RFM66_FS_TX_MODE,
    EGL_RFM66_TX_MODE,
    EGL_RFM66_FS_RX_MODE,
    EGL_RFM66_RX_MODE
}egl_rfm66_mode_t;

typedef enum
{
    EGL_RFM66_MODULATION_SHAPING_NO,
    EGL_RFM66_MODULATION_SHAPING_1,
    EGL_RFM66_MODULATION_SHAPING_2,
    EGL_RFM66_MODULATION_SHAPING_3
}egl_rfm66_modulation_shaping_t;

typedef enum
{
    EGL_RFM66_MODULATION_TYPE_FSK,
    EGL_RFM66_MODULATION_TYPE_OOK
}egl_rfm66_modulation_type_t;

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
egl_result_t egl_rfm66_mode_set(egl_rfm66_t *rfm, egl_rfm66_mode_t mode);
egl_result_t egl_rfm66_mode_get(egl_rfm66_t *rfm, egl_rfm66_mode_t *mode);
egl_result_t egl_rfm66_modulation_shaping_set(egl_rfm66_t *rfm, egl_rfm66_modulation_shaping_t modsh);
egl_result_t egl_rfm66_modulation_shaping_get(egl_rfm66_t *rfm, egl_rfm66_modulation_shaping_t *modsh);
egl_result_t egl_rfm66_modulation_type_set(egl_rfm66_t *rfm, egl_rfm66_modulation_type_t modtype);
egl_result_t egl_rfm66_modulation_type_get(egl_rfm66_t *rfm, egl_rfm66_modulation_type_t *modtype);
egl_result_t egl_rfm66_bitrate_set(egl_rfm66_t *rfm, uint32_t kbs);
egl_result_t egl_rfm66_bitrate_get(egl_rfm66_t *rfm, uint32_t *kbs);
egl_result_t egl_rfm66_deviation_set(egl_rfm66_t *rfm, uint32_t hz);
egl_result_t egl_rfm66_deviation_get(egl_rfm66_t *rfm, uint32_t *hz);
egl_result_t egl_rfm66_frequency_set(egl_rfm66_t *rfm, uint32_t hz);
egl_result_t egl_rfm66_frequency_get(egl_rfm66_t *rfm, uint32_t *hz);

#endif