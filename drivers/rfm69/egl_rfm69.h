#ifndef EGL_RFM69_H
#define EGL_RFM69_H

#include "egl_result.h"
#include "egl_pm.h"
#include "egl_pio.h"
#include "egl_interface.h"
#include "egl_clock.h"

#define EGL_RFM69_REG_MODE                  (0x01)
#define EGL_RFM69_REG_DATA_MODUL            (0x02)
#define EGL_RFM69_REG_BITRATE_MSB           (0x03)
#define EGL_RFM69_REG_BITRATE_LSB           (0x04)
#define EGL_RFM69_REG_DEVIATION_MSB         (0x05)
#define EGL_RFM69_REG_DEVIATION_LSB         (0x06)
#define EGL_RFM69_REG_FREQUENCY_MSB         (0x07)
#define EGL_RFM69_REG_FREQUENCY_MID         (0x08)
#define EGL_RFM69_REG_FREQUENCY_LSB         (0x09)
#define EGL_RFM69_REG_OSC1                  (0x0A)
#define EGL_RFM69_REG_AFC_CTRL              (0x0B)
#define EGL_RFM69_REG_LISTEN1               (0x0D)
#define EGL_RFM69_REG_LISTEN2               (0x0E)
#define EGL_RFM69_REG_LISTEN3               (0x0F)
#define EGL_RFM69_REG_VERSION               (0x10)
#define EGL_RFM69_REG_PA_LEVEL              (0x11)
#define EGL_RFM69_REG_PA_RAMP               (0x12)
#define EGL_RFM69_REG_OCP                   (0x13)
#define EGL_RFM69_REG_LNA                   (0x18)
#define EGL_RFM69_REG_RX_BW                 (0x19)
#define EGL_RFM69_REG_AFC_BW                (0x1A)

#define EGL_RFM69_MAX_POWER_DB              (13)
#define EGL_RFM69_MIN_POWER_DB              (-18)

#define EGL_RFM69_MAX_OCP_MA                (120)
#define EGL_RFM69_MIN_OCP_MA                (45)
#define EGL_RFM69_OCP_STEP                  (5)

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

typedef enum
{
    EGL_RFM69_RC_CALIB_STATE_IN_PROGRESS,
    EGL_RFM69_RC_CALIB_STATE_DONE
}egl_rfm69_rc_calib_state_t;

typedef enum
{
    EGL_RFM69_AFC_ROUTINE_STANDART,
    EGL_RFM69_AFC_ROUTINE_IMPROVED
}egl_rfm69_afc_routine_t;

typedef enum
{
    EGL_RFM69_LISTEN_STAY_RX,
    EGL_RFM69_LISTEN_STAY_RX_THEN_STOP,
    EGL_RFM69_LISTEN_STAY_RX_THEN_IDLE
}egl_rfm69_listen_end_t;

typedef enum
{
    EGL_RFM69_LISTEN_CRITERIA_ABOVE_RSSI,
    EGL_RFM69_LISTEN_CRITERIA_ABOVE_RSSI_AND_SYNC_ADDR
}egl_rfm69_listen_criteria_t;

typedef enum
{
    EGL_RFM69_LISTEN_RESOL_64US = 1,
    EGL_RFM69_LISTEN_RESOL_4_1MS,
    EGL_RFM69_LISTEN_RESOL_262MS
}egl_rfm69_listen_resolution_t;

typedef enum
{
    EGL_RFM69_POWER_RAMP_3_4_MS,
    EGL_RFM69_POWER_RAMP_2_MS,
    EGL_RFM69_POWER_RAMP_1_MS,
    EGL_RFM69_POWER_RAMP_500_US,
    EGL_RFM69_POWER_RAMP_250_US,
    EGL_RFM69_POWER_RAMP_125_US,
    EGL_RFM69_POWER_RAMP_100_US,
    EGL_RFM69_POWER_RAMP_62_US,
    EGL_RFM69_POWER_RAMP_50_US,
    EGL_RFM69_POWER_RAMP_40_US,
    EGL_RFM69_POWER_RAMP_31_US,
    EGL_RFM69_POWER_RAMP_25_US,
    EGL_RFM69_POWER_RAMP_20_US,
    EGL_RFM69_POWER_RAMP_15_US,
    EGL_RFM69_POWER_RAMP_12_US,
    EGL_RFM69_POWER_RAMP_10_US,
}egl_rfm69_power_ramp_t;

typedef enum
{
    EGL_RFM69_LNA_GAIN_AGC,
    EGL_RFM69_LNA_GAIN_HIGHEST,
    EGL_RFM69_LNA_GAIN_HIGHEST_MINUS_6_DB,
    EGL_RFM69_LNA_GAIN_HIGHEST_MINUS_12_DB,
    EGL_RFM69_LNA_GAIN_HIGHEST_MINUS_24_DB,
    EGL_RFM69_LNA_GAIN_HIGHEST_MINUS_36_DB,
    EGL_RFM69_LNA_GAIN_HIGHEST_MINUS_48_DB,
}egl_rfm69_lna_gain_t;

typedef enum
{
    EGL_RFM69_LNA_ZIN_50_OHMS,
    EGL_RFM69_LNA_ZIN_200_OHMS
}egl_rfm69_lna_zin_t;

typedef enum
{
    EGL_RFM69_BW_MANT_16,
    EGL_RFM69_BW_MANT_20,
    EGL_RFM69_BW_MANT_24
}egl_rfm69_bw_mant_t;

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
egl_result_t egl_rfm69_frequency_set(egl_rfm69_t *rfm, uint32_t frequency);
egl_result_t egl_rfm69_frequency_get(egl_rfm69_t *rfm, uint32_t *frequency);
egl_result_t egl_rfm_rc_calib_start(egl_rfm69_t *rfm);
egl_result_t egl_rfm_rc_calib_state_get(egl_rfm69_t *rfm, egl_rfm69_rc_calib_state_t *state);
egl_result_t egl_rfm69_afc_routine_set(egl_rfm69_t *rfm, egl_rfm69_afc_routine_t routine);
egl_result_t egl_rfm69_afc_routine_get(egl_rfm69_t *rfm, egl_rfm69_afc_routine_t *routine);
egl_result_t egl_rfm69_listen_end_set(egl_rfm69_t *rfm, egl_rfm69_listen_end_t end_action);
egl_result_t egl_rfm69_listen_end_get(egl_rfm69_t *rfm, egl_rfm69_listen_end_t *end_action);
egl_result_t egl_rfm69_listen_criteria_set(egl_rfm69_t *rfm, egl_rfm69_listen_criteria_t criteria);
egl_result_t egl_rfm69_listen_criteria_get(egl_rfm69_t *rfm, egl_rfm69_listen_criteria_t *criteria);
egl_result_t egl_rfm69_listen_rx_resolution_set(egl_rfm69_t *rfm, egl_rfm69_listen_resolution_t resolution);
egl_result_t egl_rfm69_listen_rx_resolution_get(egl_rfm69_t *rfm, egl_rfm69_listen_resolution_t *resolution);
egl_result_t egl_rfm69_listen_idle_resolution_set(egl_rfm69_t *rfm, egl_rfm69_listen_resolution_t resolution);
egl_result_t egl_rfm69_listen_idle_resolution_get(egl_rfm69_t *rfm, egl_rfm69_listen_resolution_t *resolution);
egl_result_t egl_rfm69_listen_idle_coef_set(egl_rfm69_t *rfm, uint8_t coef);
egl_result_t egl_rfm69_listen_idle_coef_get(egl_rfm69_t *rfm, uint8_t *coef);
egl_result_t egl_rfm69_listen_rx_coef_set(egl_rfm69_t *rfm, uint8_t coef);
egl_result_t egl_rfm69_listen_rx_coef_get(egl_rfm69_t *rfm, uint8_t *coef);
egl_result_t egl_rfm69_power_set(egl_rfm69_t *rfm, int8_t db);
egl_result_t egl_rfm69_power_get(egl_rfm69_t *rfm, int8_t *db);
egl_result_t egl_rfm69_pa0_set(egl_rfm69_t *rfm, bool state);
egl_result_t egl_rfm69_pa0_get(egl_rfm69_t *rfm, bool *state);
egl_result_t egl_rfm69_pa1_set(egl_rfm69_t *rfm, bool state);
egl_result_t egl_rfm69_pa1_get(egl_rfm69_t *rfm, bool *state);
egl_result_t egl_rfm69_pa2_set(egl_rfm69_t *rfm, bool state);
egl_result_t egl_rfm69_pa2_get(egl_rfm69_t *rfm, bool *state);
egl_result_t egl_rfm69_power_ramp_set(egl_rfm69_t *rfm, egl_rfm69_power_ramp_t ramp);
egl_result_t egl_rfm69_power_ramp_get(egl_rfm69_t *rfm, egl_rfm69_power_ramp_t *ramp);
egl_result_t egl_rfm69_ocp_trim_set(egl_rfm69_t *rfm, uint8_t ma);
egl_result_t egl_rfm69_ocp_trim_get(egl_rfm69_t *rfm, uint8_t *ma);
egl_result_t egl_rfm69_ocp_state_set(egl_rfm69_t *rfm, bool state);
egl_result_t egl_rfm69_ocp_state_get(egl_rfm69_t *rfm, bool *state);
egl_result_t egl_rfm69_lna_select_gain_set(egl_rfm69_t *rfm, egl_rfm69_lna_gain_t gain);
egl_result_t egl_rfm69_lna_select_gain_get(egl_rfm69_t *rfm, egl_rfm69_lna_gain_t *gain);
egl_result_t egl_rfm69_lna_current_gain_get(egl_rfm69_t *rfm, egl_rfm69_lna_gain_t *gain);
egl_result_t egl_rfm69_lna_zin_set(egl_rfm69_t *rfm, egl_rfm69_lna_zin_t zin);
egl_result_t egl_rfm69_lna_zin_get(egl_rfm69_t *rfm, egl_rfm69_lna_zin_t *zin);
egl_result_t egl_rfm69_rx_bw_exp_set(egl_rfm69_t *rfm, uint8_t exp);
egl_result_t egl_rfm69_rx_bw_exp_get(egl_rfm69_t *rfm, uint8_t *exp);
egl_result_t egl_rfm69_rx_bw_mant_set(egl_rfm69_t *rfm, egl_rfm69_bw_mant_t mant);
egl_result_t egl_rfm69_rx_bw_mant_get(egl_rfm69_t *rfm, egl_rfm69_bw_mant_t *mant);
egl_result_t egl_rfm69_rx_dcc_freq_set(egl_rfm69_t *rfm, uint8_t freq);
egl_result_t egl_rfm69_rx_dcc_freq_get(egl_rfm69_t *rfm, uint8_t *freq);
egl_result_t egl_rfm69_afc_bw_exp_set(egl_rfm69_t *rfm, uint8_t exp);
egl_result_t egl_rfm69_afc_bw_exp_get(egl_rfm69_t *rfm, uint8_t *exp);
egl_result_t egl_rfm69_afc_bw_mant_set(egl_rfm69_t *rfm, egl_rfm69_bw_mant_t mant);
egl_result_t egl_rfm69_afc_bw_mant_get(egl_rfm69_t *rfm, egl_rfm69_bw_mant_t *mant);
egl_result_t egl_rfm69_afc_dcc_freq_set(egl_rfm69_t *rfm, uint8_t freq);
egl_result_t egl_rfm69_afc_dcc_freq_get(egl_rfm69_t *rfm, uint8_t *freq);

#endif