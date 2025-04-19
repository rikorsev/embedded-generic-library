#ifndef EGL_RFM69_H
#define EGL_RFM69_H

#include "egl_result.h"
#include "egl_pm.h"
#include "egl_pio.h"
#include "egl_interface.h"
#include "egl_clock.h"

#define EGL_RFM69_REG_MODE                  (0x01)
#define EGL_RFM69_REG_DATA_MODUL            (0x02)
#define EGL_RFM69_REG_BITRATE_LSB           (0x03)
#define EGL_RFM69_REG_BITRATE_MSB           (0x04)
#define EGL_RFM69_REG_DEVIATION_LSB         (0x05)
#define EGL_RFM69_REG_DEVIATION_MSB         (0x06)
#define EGL_RFM69_REG_VERSION               (0x10)

typedef enum
{
    EGL_RFM69_SLEEP_MODE,
    EGL_RFM69_STANDBY_MODE,
    EGL_RFM69_FS_MODE,
    EGL_RFM69_TX_MODE,
    EGL_RFM69_RX_MODE
}egl_rfm69_mode_t;

typedef enum
{
    EGL_RFM69_MODULATION_SHAPING_NO,
    EGL_RFM69_MODULATION_SHAPING_1,
    EGL_RFM69_MODULATION_SHAPING_2,
    EGL_RFM69_MODULATION_SHAPING_3
}egl_rfm69_modulation_shaping_t;

typedef enum
{
    EGL_RFM69_MODULATION_TYPE_FSK,
    EGL_RFM69_MODULATION_TYPE_OOK
}egl_rfm69_modulation_type_t;

typedef enum
{
    EGL_RFM69_DATA_MODE_PACKET,
    EGL_RFM69_DATA_MODE_CONTINIOUS_W_SYNC = 2,
    EGL_RFM69_DATA_MODE_CONTINIOUS_WO_SYNC
}egl_rfm69_data_mode_t;

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
}egl_rfm69_t;

egl_result_t egl_rfm69_init(egl_rfm69_t *rfm);
egl_result_t egl_rfm69_read_byte(egl_rfm69_t *rfm, uint8_t addr, uint8_t *value);
egl_result_t egl_rfm69_write_byte(egl_rfm69_t *rfm, uint8_t addr, uint8_t value);
egl_result_t egl_rfm69_write_burst(egl_rfm69_t *rfm, uint8_t addr, void *data, size_t len);
egl_result_t egl_rfm69_read_burst(egl_rfm69_t *rfm, uint8_t addr, void *data, size_t len);
egl_result_t egl_rfm69_bitrate_get(egl_rfm69_t *rfm, uint32_t *bitrate);
egl_result_t egl_rfm69_bitrate_set(egl_rfm69_t *rfm, uint32_t bitrate);
egl_result_t egl_rfm69_mode_set(egl_rfm69_t *rfm, egl_rfm69_mode_t mode);
egl_result_t egl_rfm69_mode_get(egl_rfm69_t *rfm, egl_rfm69_mode_t *mode);
egl_result_t egl_rfm69_modulation_shaping_set(egl_rfm69_t *rfm, egl_rfm69_modulation_shaping_t modsh);
egl_result_t egl_rfm69_modulation_shaping_get(egl_rfm69_t *rfm, egl_rfm69_modulation_shaping_t *modsh);
egl_result_t egl_rfm69_modulation_type_set(egl_rfm69_t *rfm, egl_rfm69_modulation_type_t modtype);
egl_result_t egl_rfm69_modulation_type_get(egl_rfm69_t *rfm, egl_rfm69_modulation_type_t *modtype);
egl_result_t egl_rfm69_data_mode_set(egl_rfm69_t *rfm, egl_rfm69_data_mode_t mode);
egl_result_t egl_rfm69_data_mode_get(egl_rfm69_t *rfm, egl_rfm69_data_mode_t *mode);
egl_result_t egl_rfm69_deviation_set(egl_rfm69_t *rfm, uint32_t deviation);
egl_result_t egl_rfm69_deviation_get(egl_rfm69_t *rfm, uint32_t *deviation);

#endif