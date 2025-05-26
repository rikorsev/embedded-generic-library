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
#define EGL_RFM66_REG_PA_CONFIG             (0x09)
#define EGL_RFM66_REG_PA_RAMP               (0x0A)
#define EGL_RFM66_REG_OCP                   (0x0B)
#define EGL_RFM66_REG_LNA                   (0x0C)
#define EGL_RFM66_REG_RX_CONFIG             (0x0D)
#define EGL_RFM66_REG_RSSI_CONFIG           (0x0E)
#define EGL_RFM66_REG_RSSI_COLLISION        (0x0F)
#define EGL_RFM66_REG_RSSI_THRESHOLD        (0x10)
#define EGL_RFM66_REG_RSSI_VALUE            (0x11)
#define EGL_RFM66_REG_RX_BW                 (0x12)
#define EGL_RFM66_REG_AFC_BW                (0x13)
#define EGL_RFM66_REG_OOK_PEAK              (0x14)
#define EGL_RFM66_REG_OOK_FIX               (0x15)
#define EGL_RFM66_REG_OOK_AVG               (0x16)
#define EGL_RFM66_REG_AFC_FEI               (0x1A)
#define EGL_RFM66_REG_AFC_MSB               (0x1B)
#define EGL_RFM66_REG_AFC_LSB               (0x1C)
#define EGL_RFM66_REG_FEI_MSB               (0x1D)
#define EGL_RFM66_REG_FEI_LSB               (0x1E)
#define EGL_RFM66_REG_PREAMBLE_DETECT       (0x1F)
#define EGL_RFM66_REG_RX_TIMEOUT1           (0x20)
#define EGL_RFM66_REG_RX_TIMEOUT2           (0x21)
#define EGL_RFM66_REG_RX_TIMEOUT3           (0x22)
#define EGL_RFM66_REG_RX_DELAY              (0x23)
#define EGL_RFM66_REG_OSC                   (0x24)
#define EGL_RFM66_REG_PREAMBLE_MSB          (0x25)
#define EGL_RFM66_REG_PREAMBLE_LSB          (0x26)
#define EGL_RFM66_REG_VERSION               (0x42)

#define EGL_RFM66_RAW_PA_POWER_MAX          (15)

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

typedef enum
{
    EGL_RFM66_PA_SELECT_RFO_PIN,
    EGL_RFM66_PA_SELECT_PA_BOOST,
}egl_rfm66_pa_select_t;

typedef enum
{
    EGL_RFM66_POWER_RAMP_3_4_MS,
    EGL_RFM66_POWER_RAMP_2_MS,
    EGL_RFM66_POWER_RAMP_1_MS,
    EGL_RFM66_POWER_RAMP_500_US,
    EGL_RFM66_POWER_RAMP_250_US,
    EGL_RFM66_POWER_RAMP_125_US,
    EGL_RFM66_POWER_RAMP_100_US,
    EGL_RFM66_POWER_RAMP_62_US,
    EGL_RFM66_POWER_RAMP_50_US,
    EGL_RFM66_POWER_RAMP_40_US,
    EGL_RFM66_POWER_RAMP_31_US,
    EGL_RFM66_POWER_RAMP_25_US,
    EGL_RFM66_POWER_RAMP_20_US,
    EGL_RFM66_POWER_RAMP_15_US,
    EGL_RFM66_POWER_RAMP_12_US,
    EGL_RFM66_POWER_RAMP_10_US,
}egl_rfm66_power_ramp_t;

typedef enum
{
    EGL_RFM66_LNA_GAIN_HIGHEST = 1,
    EGL_RFM66_LNA_GAIN_HIGHEST_MINUS_6_DB,
    EGL_RFM66_LNA_GAIN_HIGHEST_MINUS_12_DB,
    EGL_RFM66_LNA_GAIN_HIGHEST_MINUS_24_DB,
    EGL_RFM66_LNA_GAIN_HIGHEST_MINUS_36_DB,
    EGL_RFM66_LNA_GAIN_HIGHEST_MINUS_48_DB,
}egl_rfm66_lna_gain_t;

typedef enum
{
    EGL_RFM66_LNA_BOOST_OFF = 0x00,
    EGL_RFM66_LNA_BOOST_ON = 0x03
}egl_rfm66_lna_boost_t;

typedef enum
{
    EGL_RFM66_RX_TRIGGER_0 = 0,
    EGL_RFM66_RX_TRIGGER_1 = 1,
    EGL_RFM66_RX_TRIGGER_2 = 6,
    EGL_RFM66_RX_TRIGGER_3 = 7
}egl_rfm66_rx_trigger_t;

typedef enum
{
    EGL_RFM66_RSSI_SMOOTHING_2_SAMPLES,
    EGL_RFM66_RSSI_SMOOTHING_4_SAMPLES,
    EGL_RFM66_RSSI_SMOOTHING_8_SAMPLES,
    EGL_RFM66_RSSI_SMOOTHING_16_SAMPLES,
    EGL_RFM66_RSSI_SMOOTHING_32_SAMPLES,
    EGL_RFM66_RSSI_SMOOTHING_64_SAMPLES,
    EGL_RFM66_RSSI_SMOOTHING_128_SAMPLES,
    EGL_RFM66_RSSI_SMOOTHING_256_SAMPLES,
}egl_rfm66_rssi_smoothing_t;

typedef enum
{
    EGL_RFM66_BW_MANT_16,
    EGL_RFM66_BW_MANT_20,
    EGL_RFM66_BW_MANT_24
}egl_rfm66_bw_mant_t;

typedef enum
{
    EGL_RFM66_OOK_THRESH_STEP_0_5_DB,
    EGL_RFM66_OOK_THRESH_STEP_1_0_DB,
    EGL_RFM66_OOK_THRESH_STEP_1_5_DB,
    EGL_RFM66_OOK_THRESH_STEP_2_0_DB,
    EGL_RFM66_OOK_THRESH_STEP_3_0_DB,
    EGL_RFM66_OOK_THRESH_STEP_4_0_DB,
    EGL_RFM66_OOK_THRESH_STEP_5_0_DB,
    EGL_RFM66_OOK_THRESH_STEP_6_0_DB,
}egl_rfm66_ook_thresh_step_t;

typedef enum
{
    EGL_RFM66_OOK_THRESH_TYPE_FIXED,
    EGL_RFM66_OOK_THRESH_TYPE_AVERAGE,
    EGL_RFM66_OOK_THRESH_TYPE_PEAK
}egl_rfm66_ook_thresh_type_t;

typedef enum
{
    EGL_RFM66_OOK_THRESH_DEC_ONCE_PER_CHIP,
    EGL_RFM66_OOK_THRESH_DEC_ONCE_PER_2_CHIPS,
    EGL_RFM66_OOK_THRESH_DEC_ONCE_PER_4_CHIPS,
    EGL_RFM66_OOK_THRESH_DEC_ONCE_PER_8_CHIPS,
    EGL_RFM66_OOK_THRESH_DEC_TWICE_IN_EACH_CHIP,
    EGL_RFM66_OOK_THRESH_DEC_4_TIMES_IN_EACH_CHIP,
    EGL_RFM66_OOK_THRESH_DEC_8_TIMES_IN_EACH_CHIP,
    EGL_RFM66_OOK_THRESH_DEC_16_TIMES_IN_EACH_CHIP
}egl_rfm66_ook_thresh_dec_t;

typedef enum
{
    EGL_RFM66_OOK_CHIP_RATE_DIV_32P,
    EGL_RFM66_OOK_CHIP_RATE_DIV_8P,
    EGL_RFM66_OOK_CHIP_RATE_DIV_4P,
    EGL_RFM66_OOK_CHIP_RATE_DIV_2P
}egl_rfm66_ook_thresh_avg_filt_t;

typedef enum
{
    EGL_RFM66_OOK_AVERAGE_OFFSET_0_DB,
    EGL_RFM66_OOK_AVERAGE_OFFSET_2_DB,
    EGL_RFM66_OOK_AVERAGE_OFFSET_4_DB,
    EGL_RFM66_OOK_AVERAGE_OFFSET_6_DB,
}egl_rfm66_ook_avg_offset_t;

typedef enum
{
    EGL_RFM66_PREAMBLE_DETECT_SIZE_1_BYTE,
    EGL_RFM66_PREAMBLE_DETECT_SIZE_2_BYTE,
    EGL_RFM66_PREAMBLE_DETECT_SIZE_3_BYTE,
}egl_rfm66_preamble_detect_size_t;

typedef enum
{
    EGL_RFM66_CLK_OUT_FXOSC,
    EGL_RFM66_CLK_OUT_FXOSC_DIV_2,
    EGL_RFM66_CLK_OUT_FXOSC_DIV_4,
    EGL_RFM66_CLK_OUT_FXOSC_DIV_8,
    EGL_RFM66_CLK_OUT_FXOSC_DIV_16,
    EGL_RFM66_CLK_OUT_FXOSC_DIV_32,
    EGL_RFM66_CLK_OUT_RC,
    EGL_RFM66_CLK_OUT_OFF
}egl_rfm66_clk_out_t;

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
egl_result_t egl_rfm66_pa_power_set(egl_rfm66_t *rfm, uint8_t power);
egl_result_t egl_rfm66_pa_power_get(egl_rfm66_t *rfm, uint8_t *power);
egl_result_t egl_rfm66_pa_select_set(egl_rfm66_t *rfm, egl_rfm66_pa_select_t select);
egl_result_t egl_rfm66_pa_select_get(egl_rfm66_t *rfm, egl_rfm66_pa_select_t *select);
egl_result_t egl_rfm66_pa_ramp_set(egl_rfm66_t *rfm, egl_rfm66_power_ramp_t ramp);
egl_result_t egl_rfm66_pa_ramp_get(egl_rfm66_t *rfm, egl_rfm66_power_ramp_t *ramp);
egl_result_t egl_rfm66_low_pn_tx_state_set(egl_rfm66_t *rfm, bool state);
egl_result_t egl_rfm66_low_pn_tx_state_get(egl_rfm66_t *rfm, bool *state);
egl_result_t egl_rfm66_ocp_trim_set(egl_rfm66_t *rfm, uint8_t ma);
egl_result_t egl_rfm66_ocp_trim_get(egl_rfm66_t *rfm, uint8_t *ma);
egl_result_t egl_rfm66_ocp_state_set(egl_rfm66_t *rfm, bool state);
egl_result_t egl_rfm66_ocp_state_get(egl_rfm66_t *rfm, bool *state);
egl_result_t egl_rfm66_lna_boost_state_set(egl_rfm66_t *rfm, egl_rfm66_lna_boost_t state);
egl_result_t egl_rfm66_lna_boost_state_get(egl_rfm66_t *rfm, egl_rfm66_lna_boost_t *state);
egl_result_t egl_rfm66_lna_gain_set(egl_rfm66_t *rfm, egl_rfm66_lna_gain_t gain);
egl_result_t egl_rfm66_lna_gain_get(egl_rfm66_t *rfm, egl_rfm66_lna_gain_t *gain);
egl_result_t egl_rfm66_rx_trigger_set(egl_rfm66_t *rfm, egl_rfm66_rx_trigger_t trigger);
egl_result_t egl_rfm66_rx_trigger_get(egl_rfm66_t *rfm, egl_rfm66_rx_trigger_t *trigger);
egl_result_t egl_rfm66_auto_agc_state_set(egl_rfm66_t *rfm, bool state);
egl_result_t egl_rfm66_auto_agc_state_get(egl_rfm66_t *rfm, bool *state);
egl_result_t egl_rfm66_auto_afc_state_set(egl_rfm66_t *rfm, bool state);
egl_result_t egl_rfm66_auto_afc_state_get(egl_rfm66_t *rfm, bool *state);
egl_result_t egl_rfm66_restart_rx_with_pll_lock_state_set(egl_rfm66_t *rfm, bool state);
egl_result_t egl_rfm66_restart_rx_with_pll_lock_state_get(egl_rfm66_t *rfm, bool *state);
egl_result_t egl_rfm66_restart_rx_wo_pll_lock_state_set(egl_rfm66_t *rfm, bool state);
egl_result_t egl_rfm66_restart_rx_wo_pll_lock_state_get(egl_rfm66_t *rfm, bool *state);
egl_result_t egl_rfm66_restart_rx_on_collision_state_set(egl_rfm66_t *rfm, bool state);
egl_result_t egl_rfm66_restart_rx_on_collision_state_get(egl_rfm66_t *rfm, bool *state);
egl_result_t egl_rfm66_rssi_offset_set(egl_rfm66_t *rfm, int8_t offset);
egl_result_t egl_rfm66_rssi_offset_get(egl_rfm66_t *rfm, int8_t *offset);
egl_result_t egl_rfm66_rssi_smoothing_set(egl_rfm66_t *rfm, egl_rfm66_rssi_smoothing_t smoothing);
egl_result_t egl_rfm66_rssi_smoothing_get(egl_rfm66_t *rfm, egl_rfm66_rssi_smoothing_t *smoothing);
egl_result_t egl_rfm66_rssi_collision_set(egl_rfm66_t *rfm, uint8_t collision);
egl_result_t egl_rfm66_rssi_collision_get(egl_rfm66_t *rfm, uint8_t *collision);
egl_result_t egl_rfm66_rssi_threshold_set(egl_rfm66_t *rfm, int8_t threshold);
egl_result_t egl_rfm66_rssi_threshold_get(egl_rfm66_t *rfm, int8_t *threshold);
egl_result_t egl_rfm66_rssi_get(egl_rfm66_t *rfm, int8_t *rssi);
egl_result_t egl_rfm66_rx_bw_exp_set(egl_rfm66_t *rfm, uint8_t exp);
egl_result_t egl_rfm66_rx_bw_exp_get(egl_rfm66_t *rfm, uint8_t *exp);
egl_result_t egl_rfm66_rx_bw_mant_set(egl_rfm66_t *rfm, egl_rfm66_bw_mant_t mant);
egl_result_t egl_rfm66_rx_bw_mant_get(egl_rfm66_t *rfm, egl_rfm66_bw_mant_t *mant);
egl_result_t egl_rfm66_afc_bw_exp_set(egl_rfm66_t *rfm, uint8_t exp);
egl_result_t egl_rfm66_afc_bw_exp_get(egl_rfm66_t *rfm, uint8_t *exp);
egl_result_t egl_rfm66_afc_bw_mant_set(egl_rfm66_t *rfm, egl_rfm66_bw_mant_t mant);
egl_result_t egl_rfm66_afc_bw_mant_get(egl_rfm66_t *rfm, egl_rfm66_bw_mant_t *mant);
egl_result_t egl_rfm66_ook_peak_thresh_step_set(egl_rfm66_t *rfm, egl_rfm66_ook_thresh_step_t step);
egl_result_t egl_rfm66_ook_peak_thresh_step_get(egl_rfm66_t *rfm, egl_rfm66_ook_thresh_step_t *step);
egl_result_t egl_rfm66_ook_thresh_type_set(egl_rfm66_t *rfm, egl_rfm66_ook_thresh_type_t type);
egl_result_t egl_rfm66_ook_thresh_type_get(egl_rfm66_t *rfm, egl_rfm66_ook_thresh_type_t *type);
egl_result_t egl_rfm66_bit_sync_state_set(egl_rfm66_t *rfm, bool state);
egl_result_t egl_rfm66_bit_sync_state_get(egl_rfm66_t *rfm, bool *state);
egl_result_t egl_rfm66_ook_thresh_fixed_set(egl_rfm66_t *rfm, uint8_t thresh);
egl_result_t egl_rfm66_ook_thresh_fixed_get(egl_rfm66_t *rfm, uint8_t *thresh);
egl_result_t egl_rfm66_ook_thresh_avg_filt_set(egl_rfm66_t *rfm, egl_rfm66_ook_thresh_avg_filt_t filt);
egl_result_t egl_rfm66_ook_thresh_avg_filt_get(egl_rfm66_t *rfm, egl_rfm66_ook_thresh_avg_filt_t *filt);
egl_result_t egl_rfm66_ook_peak_thresh_dec_set(egl_rfm66_t *rfm, egl_rfm66_ook_thresh_dec_t dec);
egl_result_t egl_rfm66_ook_peak_thresh_dec_get(egl_rfm66_t *rfm, egl_rfm66_ook_thresh_dec_t *dec);
egl_result_t egl_rfm66_ook_avg_offset_set(egl_rfm66_t *rfm, egl_rfm66_ook_avg_offset_t offset);
egl_result_t egl_rfm66_ook_avg_offset_get(egl_rfm66_t *rfm, egl_rfm66_ook_avg_offset_t *offset);
egl_result_t egl_rfm66_afc_clear(egl_rfm66_t *rfm);
egl_result_t egl_rfm66_afc_auto_clear_set(egl_rfm66_t *rfm, bool state);
egl_result_t egl_rfm66_afc_auto_clear_get(egl_rfm66_t *rfm, bool *state);
egl_result_t egl_rfm66_agc_start(egl_rfm66_t *rfm);
egl_result_t egl_rfm66_afc_get(egl_rfm66_t *rfm, int16_t *hz);
egl_result_t egl_rfm66_fei_get(egl_rfm66_t *rfm, int16_t *hz);
egl_result_t egl_rfm66_preamble_detect_tol_set(egl_rfm66_t *rfm, uint8_t tol);
egl_result_t egl_rfm66_preamble_detect_tol_get(egl_rfm66_t *rfm, uint8_t *tol);
egl_result_t egl_rfm66_preamble_detect_size_set(egl_rfm66_t *rfm, egl_rfm66_preamble_detect_size_t size);
egl_result_t egl_rfm66_preamble_detect_size_get(egl_rfm66_t *rfm, egl_rfm66_preamble_detect_size_t *size);
egl_result_t egl_rfm66_preamble_detect_state_set(egl_rfm66_t *rfm, bool state);
egl_result_t egl_rfm66_preamble_detect_state_get(egl_rfm66_t *rfm, bool *state);
egl_result_t egl_rfm66_timeout_rx_rssi_set(egl_rfm66_t *rfm, uint8_t timeout);
egl_result_t egl_rfm66_timeout_rx_rssi_get(egl_rfm66_t *rfm, uint8_t *timeout);
egl_result_t egl_rfm66_timeout_rx_preamble_set(egl_rfm66_t *rfm, uint8_t timeout);
egl_result_t egl_rfm66_timeout_rx_preamble_get(egl_rfm66_t *rfm, uint8_t *timeout);
egl_result_t egl_rfm66_timeout_rx_signal_sync_set(egl_rfm66_t *rfm, uint8_t timeout);
egl_result_t egl_rfm66_timeout_rx_signal_sync_get(egl_rfm66_t *rfm, uint8_t *timeout);
egl_result_t egl_rfm66_timeout_rx_delay_set(egl_rfm66_t *rfm, uint8_t delay);
egl_result_t egl_rfm66_timeout_rx_delay_get(egl_rfm66_t *rfm, uint8_t *delay);
egl_result_t egl_rfm66_clk_out_set(egl_rfm66_t *rfm, egl_rfm66_clk_out_t out);
egl_result_t egl_rfm66_clk_out_get(egl_rfm66_t *rfm, egl_rfm66_clk_out_t *out);
egl_result_t egl_rfm66_rc_calibration_start(egl_rfm66_t *rfm);
egl_result_t egl_rfm66_preamble_set(egl_rfm66_t *rfm, uint16_t bytes);
egl_result_t egl_rfm66_preamble_get(egl_rfm66_t *rfm, uint16_t *bytes);

#endif