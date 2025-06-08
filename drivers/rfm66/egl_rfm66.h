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
#define EGL_RFM66_REG_SYNC_CONFIG           (0x27)
#define EGL_RFM66_REG_SYNC_VALUE1           (0x28)
#define EGL_RFM66_REG_SYNC_VALUE2           (0x29)
#define EGL_RFM66_REG_SYNC_VALUE3           (0x2A)
#define EGL_RFM66_REG_SYNC_VALUE4           (0x2B)
#define EGL_RFM66_REG_SYNC_VALUE5           (0x2C)
#define EGL_RFM66_REG_SYNC_VALUE6           (0x2D)
#define EGL_RFM66_REG_SYNC_VALUE7           (0x2E)
#define EGL_RFM66_REG_SYNC_VALUE8           (0x2F)
#define EGL_RFM66_REG_PACKET_CONFIG1        (0x30)
#define EGL_RFM66_REG_PACKET_CONFIG2        (0x31)
#define EGL_RFM66_REG_PACKET_LENGTH         (0x32)
#define EGL_RFM66_REG_MODE_ADRS             (0x33)
#define EGL_RFM66_REG_BROADCAST_ADRS        (0x34)
#define EGL_RFM66_REG_FIFO_THRESH           (0x35)
#define EGL_RFM66_REG_SEQ_CONFIG1           (0x36)
#define EGL_RFM66_REG_SEQ_CONFIG2           (0x37)
#define EGL_RFM66_REG_TIMER_RESOL           (0x38)
#define EGL_RFM66_REG_TIMER1_COEF           (0x39)
#define EGL_RFM66_REG_TIMER2_COEF           (0x3A)
#define EGL_RFM66_REG_IMAGE_CAL             (0x3B)
#define EGL_RFM66_REG_TEMP                  (0x3C)
#define EGL_RFM66_REG_LOW_BAT               (0x3D)
#define EGL_RFM66_REG_VERSION               (0x42)

#define EGL_RFM66_RAW_PA_POWER_MAX          (15)
#define EGL_RFM66_SYNC_MAX_SIZE             (8U)

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

typedef enum
{
    EGL_RFM66_FIFO_FILL_COND_SYNC_ADDR,
    EGL_RFM66_FIFO_FILL_COND_FIFO_COND_SET
}egl_rfm66_fifo_fill_cond_t;

typedef enum
{
    EGL_RFM66_PREAMBLE_POL_AA,
    EGL_RFM66_PREAMBLE_POL_55
}egl_rfm66_preamble_pol_t;

typedef enum
{
    EGL_RFM66_AUTO_RESTART_RX_MODE_OFF,
    EGL_RFM66_AUTO_RESTART_RX_MODE_ON_WO_PLL,
    EGL_RFM66_AUTO_RESTART_RX_MODE_ON_WITH_PLL
}egl_rfm66_auto_restart_rx_mode_t;

typedef enum
{
    EGL_RFM66_CRC_WHITENING_TYPE_CCITT,
    EGL_RFM66_CRC_WHITENING_TYPE_IBM
}egl_rfm66_crc_whitening_t;

typedef enum
{
    EGL_RFM66_ADDRESS_FILTERING_NONE,
    EGL_RFM66_ADDRESS_FILTERING_MATCH_NODE_ADDRESS,
    EGK_RFM66_ADDRESS_FILTERING_MATCH_NODE_AND_BROADCAST_ADDRESS
}egl_rfm66_address_filtering_t;

typedef enum
{
    EGL_RFM66_DC_FREE_ENCODING_OFF,
    EGL_RFM66_DC_FREE_ENCODING_MANCHESTER,
    EGL_RFM66_DC_FREE_ENCODING_WHITENING
}egl_rfm66_dc_free_t;

typedef enum
{
    EGL_RFM66_PACKET_FORMAT_FIXED,
    EGL_RFM66_PACKET_FORMAT_VARIABLE
}egl_rfm66_packet_format_t;

typedef enum
{
    EGL_RFM66_DATA_MODE_CONTINIOUS,
    EGL_RFM66_DATA_MODE_PACKET
}egl_rfm66_data_mode_t;

typedef enum
{
    EGL_RFM66_TX_START_CONDITION_FIFO_LEVEL,
    EGL_RFM66_TX_START_CONDITION_FIFO_EMPTY
}egl_rfm66_tx_start_condition_t;

typedef enum
{
    EGL_RFM66_FROM_TRANSMIT_TO_LOW_POWER,
    EGL_RFM66_FROM_TRANSMIT_TO_RECEIVE
}egl_rfm66_from_transmit_t;

typedef enum
{
    EGL_RFM66_FROM_IDLE_TO_TRANSMIT,
    EGL_RFM66_FROM_IDLE_TO_RECEIVE,
}egl_rfm66_from_idle_t;

typedef enum
{
    EGL_RFM66_LOW_POWER_SELECTION_SEQUENCER_OFF,
    EGL_RFM66_LOW_POWER_SELECTION_IDLE_STATE
}egl_rfm66_low_power_selection_t;

typedef enum
{
    EGL_RFM66_FROM_START_TO_LOW_POWER,
    EGL_RFM66_FROM_START_TO_RECEIVE,
    EGL_RFM66_FROM_START_TO_TRANSMIT,
    EGL_RFM66_FROM_START_TO_TRANSMIT_ON_FIFO_LEVEL
}egl_rfm66_from_start_t;

typedef enum
{
    EGL_RFM66_IDLE_MODE_STANDBY,
    EGL_RFM66_IDLE_MODE_SLEEP
}egl_rfm66_idle_mode_t;

typedef enum
{
    EGL_RFM66_FROM_PACKET_RECEIVED_TO_SEQUENCER_OFF,
    EGL_RFM66_FROM_PACKET_RECEIVED_TO_TRANSMIT_ON_FIFO_EMPTY,
    EGL_RFM66_FROM_PACKET_RECEIVED_TO_LOW_POWER,
    EGL_RFM66_FROM_PACKET_RECEIVED_TO_RECEIVE_VIA_FS_MODE,
    EGL_RFM66_FROM_PACKET_RECEIVED_TO_RECEIVE
}egl_rfm66_from_packet_received_t;

typedef enum
{
    EGL_RFM66_FROM_RX_TIMEOUT_TO_RECEIVE,
    EGL_RFM66_FROM_RX_TIMEOUT_TO_TRANSMIT,
    EGL_RFM66_FROM_RX_TIMEOUT_TO_LOW_POWER,
    EGL_RFM66_FROM_RX_TIMEOUT_TO_SEQUENCER_OFF
}egl_rfm66_from_rx_timeout_t;

typedef enum
{
    EGL_RFM66_FROM_RECEIVE_TO_PACKET_RECEIVED_ON_PAYLOAD_READY,
    EGL_RFM66_FROM_RECEIVE_TO_LOW_POWER_ON_PAYLOAD_READY,
    EGL_RFM66_FROM_RECEIVE_TO_PACKET_RECEIVED_ON_CRC_OK,
    EGL_RFM66_FROM_RECEIVE_TO_SEQUENCER_OFF_ON_RSSI_INERRUPT,
    EGL_RFM66_FROM_RECEIVE_TO_SEQUENCER_OFF_ON_SYNC_ADDRESS,
    EGL_RFM66_FROM_RECEIVE_TO_SEQUENCER_OFF_ON_PREAMBLE_DETECT
}egl_rfm66_from_receive_t;

typedef enum
{
    EGL_RFM66_TIMER_DISABLED,
    EGL_RFM66_TIMER_RESOLUTION_64_US,
    EGL_RFM66_TIMER_RESOLUTION_4_1_MS,
    EGL_RFM66_TIMER_RESOLUTION_262_MS
}egl_rfm66_timer_resolution_t;

typedef enum
{
    EGL_RFM66_TEMP_THRESHOLD_5_C,
    EGL_RFM66_TEMP_THRESHOLD_10_C,
    EGL_RFM66_TEMP_THRESHOLD_15_C,
    EGL_RFM66_TEMP_THRESHOLD_20_C
}egl_rfm66_temp_threshold_t;

typedef enum
{
    EGL_RFM66_TEMP_CHANGE_LOWER_THAN_THRESHOLD,
    EGL_RFM66_TEMP_CHANGE_HIGHER_THAN_THRESHOLD,
}egl_rfm66_temp_change_t;

typedef enum
{
    EGL_RFM66_LOW_BAT_TRIM_1695_MV,
    EGL_RFM66_LOW_BAT_TRIM_1764_MV,
    EGL_RFM66_LOW_BAT_TRIM_1835_MV,
    EGL_RFM66_LOW_BAT_TRIM_1905_MV,
    EGL_RFM66_LOW_BAT_TRIM_1976_MV,
    EGL_RFM66_LOW_BAT_TRIM_2045_MV,
    EGL_RFM66_LOW_BAT_TRIM_2116_MV,
    EGL_RFM66_LOW_BAT_TRIM_2185_MV,
}egl_rfm66_low_bat_trim_t;

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
egl_result_t egl_rfm66_sync_size_set(egl_rfm66_t *rfm, uint8_t size);
egl_result_t egl_rfm66_sync_size_get(egl_rfm66_t *rfm, uint8_t *size);
egl_result_t egl_rfm66_fifo_fill_cond_set(egl_rfm66_t *rfm, egl_rfm66_fifo_fill_cond_t cond);
egl_result_t egl_rfm66_fifo_fill_cond_get(egl_rfm66_t *rfm, egl_rfm66_fifo_fill_cond_t *cond);
egl_result_t egl_rfm66_sync_state_set(egl_rfm66_t *rfm, bool state);
egl_result_t egl_rfm66_sync_state_get(egl_rfm66_t *rfm, bool *state);
egl_result_t egl_rfm66_preamble_polarity_set(egl_rfm66_t *rfm, egl_rfm66_preamble_pol_t polarity);
egl_result_t egl_rfm66_preamble_polarity_get(egl_rfm66_t *rfm, egl_rfm66_preamble_pol_t *polarity);
egl_result_t egl_rfm66_auto_restart_rx_mode_set(egl_rfm66_t *rfm, egl_rfm66_auto_restart_rx_mode_t mode);
egl_result_t egl_rfm66_auto_restart_rx_mode_get(egl_rfm66_t *rfm, egl_rfm66_auto_restart_rx_mode_t *mode);
egl_result_t egl_rfm66_sync_set(egl_rfm66_t *rfm, uint8_t *sync, uint8_t size);
egl_result_t egl_rfm66_sync_get(egl_rfm66_t *rfm, uint8_t *sync, uint8_t *size);
egl_result_t egl_rfm66_crc_whitening_type_set(egl_rfm66_t *rfm, egl_rfm66_crc_whitening_t whitening);
egl_result_t egl_rfm66_crc_whitening_type_get(egl_rfm66_t *rfm, egl_rfm66_crc_whitening_t *whitening);
egl_result_t egl_rfm66_address_filtering_set(egl_rfm66_t *rfm, egl_rfm66_address_filtering_t filteing);
egl_result_t egl_rfm66_address_filtering_get(egl_rfm66_t *rfm, egl_rfm66_address_filtering_t *filteing);
egl_result_t egl_rfm66_crc_autoclear_state_set(egl_rfm66_t *rfm, bool state);
egl_result_t egl_rfm66_crc_autoclear_state_get(egl_rfm66_t *rfm, bool *state);
egl_result_t egl_rfm66_crc_state_set(egl_rfm66_t *rfm, bool state);
egl_result_t egl_rfm66_crc_state_get(egl_rfm66_t *rfm, bool *state);
egl_result_t egl_rfm66_dc_free_set(egl_rfm66_t *rfm, egl_rfm66_dc_free_t type);
egl_result_t egl_rfm66_dc_free_get(egl_rfm66_t *rfm, egl_rfm66_dc_free_t *type);
egl_result_t egl_rfm66_packet_format_set(egl_rfm66_t *rfm, egl_rfm66_packet_format_t format);
egl_result_t egl_rfm66_packet_format_get(egl_rfm66_t *rfm, egl_rfm66_packet_format_t *format);
egl_result_t egl_rfm66_packet_length_set(egl_rfm66_t *rfm, uint16_t length);
egl_result_t egl_rfm66_packet_length_get(egl_rfm66_t *rfm, uint16_t *length);
egl_result_t egl_rfm66_beacon_mode_set(egl_rfm66_t *rfm, bool state);
egl_result_t egl_rfm66_beacon_mode_get(egl_rfm66_t *rfm, bool *state);
egl_result_t egl_rfm66_io_home_power_frame_state_set(egl_rfm66_t *rfm, bool state);
egl_result_t egl_rfm66_io_home_power_frame_state_get(egl_rfm66_t *rfm, bool *state);
egl_result_t egl_rfm66_io_home_state_set(egl_rfm66_t *rfm, bool state);
egl_result_t egl_rfm66_io_home_state_get(egl_rfm66_t *rfm, bool *state);
egl_result_t egl_rfm66_data_mode_set(egl_rfm66_t *rfm, egl_rfm66_data_mode_t mode);
egl_result_t egl_rfm66_data_mode_get(egl_rfm66_t *rfm, egl_rfm66_data_mode_t *mode);
egl_result_t egl_rfm66_node_address_set(egl_rfm66_t *rfm, uint8_t address);
egl_result_t egl_rfm66_node_address_get(egl_rfm66_t *rfm, uint8_t *address);
egl_result_t egl_rfm66_broadcast_address_set(egl_rfm66_t *rfm, uint8_t address);
egl_result_t egl_rfm66_broadcast_address_get(egl_rfm66_t *rfm, uint8_t *address);
egl_result_t egl_rfm66_fifo_thresh_set(egl_rfm66_t *rfm, uint8_t thresh);
egl_result_t egl_rfm66_fifo_thresh_get(egl_rfm66_t *rfm, uint8_t *thresh);
egl_result_t egl_rfm66_tx_start_condition_set(egl_rfm66_t *rfm, egl_rfm66_tx_start_condition_t cond);
egl_result_t egl_rfm66_tx_start_condition_get(egl_rfm66_t *rfm, egl_rfm66_tx_start_condition_t *cond);
egl_result_t egl_rfm66_from_transmit_set(egl_rfm66_t *rfm, egl_rfm66_from_transmit_t to);
egl_result_t egl_rfm66_from_transmit_get(egl_rfm66_t *rfm, egl_rfm66_from_transmit_t *to);
egl_result_t egl_rfm66_from_idle_set(egl_rfm66_t *rfm, egl_rfm66_from_idle_t to);
egl_result_t egl_rfm66_from_idle_get(egl_rfm66_t *rfm, egl_rfm66_from_idle_t *to);
egl_result_t egl_rfm66_low_power_selection_set(egl_rfm66_t *rfm, egl_rfm66_low_power_selection_t selection);
egl_result_t egl_rfm66_low_power_selection_get(egl_rfm66_t *rfm, egl_rfm66_low_power_selection_t *selection);
egl_result_t egl_rfm66_from_start_set(egl_rfm66_t *rfm, egl_rfm66_from_start_t to);
egl_result_t egl_rfm66_from_start_get(egl_rfm66_t *rfm, egl_rfm66_from_start_t *to);
egl_result_t egl_rfm66_idle_mode_set(egl_rfm66_t *rfm, egl_rfm66_idle_mode_t mode);
egl_result_t egl_rfm66_idle_mode_get(egl_rfm66_t *rfm, egl_rfm66_idle_mode_t *mode);
egl_result_t egl_rfm66_sequencer_start(egl_rfm66_t *rfm);
egl_result_t egl_rfm66_sequencer_stop(egl_rfm66_t *rfm);
egl_result_t egl_rfm66_from_packet_received_set(egl_rfm66_t *rfm, egl_rfm66_from_packet_received_t to);
egl_result_t egl_rfm66_from_packet_received_get(egl_rfm66_t *rfm, egl_rfm66_from_packet_received_t *to);
egl_result_t egl_rfm66_from_rx_timeout_set(egl_rfm66_t *rfm, egl_rfm66_from_rx_timeout_t to);
egl_result_t egl_rfm66_from_rx_timeout_get(egl_rfm66_t *rfm, egl_rfm66_from_rx_timeout_t *to);
egl_result_t egl_rfm66_from_receive_set(egl_rfm66_t *rfm, egl_rfm66_from_receive_t to);
egl_result_t egl_rfm66_from_receive_get(egl_rfm66_t *rfm, egl_rfm66_from_receive_t *to);
egl_result_t egl_rfm66_timer1_resolution_set(egl_rfm66_t *rfm, egl_rfm66_timer_resolution_t resolution);
egl_result_t egl_rfm66_timer1_resolution_get(egl_rfm66_t *rfm, egl_rfm66_timer_resolution_t *resolution);
egl_result_t egl_rfm66_timer2_resolution_set(egl_rfm66_t *rfm, egl_rfm66_timer_resolution_t resolution);
egl_result_t egl_rfm66_timer2_resolution_get(egl_rfm66_t *rfm, egl_rfm66_timer_resolution_t *resolution);
egl_result_t egl_rfm66_timer1_coef_set(egl_rfm66_t *rfm, uint8_t coef);
egl_result_t egl_rfm66_timer1_coef_get(egl_rfm66_t *rfm, uint8_t *coef);
egl_result_t egl_rfm66_timer2_coef_set(egl_rfm66_t *rfm, uint8_t coef);
egl_result_t egl_rfm66_timer2_coef_get(egl_rfm66_t *rfm, uint8_t *coef);
egl_result_t egl_rfm66_temp_monitor_state_set(egl_rfm66_t *rfm, bool state);
egl_result_t egl_rfm66_temp_monitor_state_get(egl_rfm66_t *rfm, bool *state);
egl_result_t egl_rfm66_temp_threshold_set(egl_rfm66_t *rfm, egl_rfm66_temp_threshold_t threshold);
egl_result_t egl_rfm66_temp_threshold_get(egl_rfm66_t *rfm, egl_rfm66_temp_threshold_t *threshold);
egl_result_t egl_rfm66_temp_change_set(egl_rfm66_t *rfm, egl_rfm66_temp_change_t change);
egl_result_t egl_rfm66_temp_change_get(egl_rfm66_t *rfm, egl_rfm66_temp_change_t *change);
egl_result_t egl_rfm66_image_cal_start(egl_rfm66_t *rfm);
egl_result_t egl_rfm66_image_cal_state_get(egl_rfm66_t *rfm, bool *state);
egl_result_t egl_rfm66_auto_image_cal_state_set(egl_rfm66_t *rfm, bool state);
egl_result_t egl_rfm66_auto_image_cal_state_get(egl_rfm66_t *rfm, bool *state);
egl_result_t egl_rfm66_temp_get(egl_rfm66_t *rfm, int8_t *temp);
egl_result_t egl_rfm66_low_bat_trim_set(egl_rfm66_t *rfm, egl_rfm66_low_bat_trim_t trim);
egl_result_t egl_rfm66_low_bat_trim_get(egl_rfm66_t *rfm, egl_rfm66_low_bat_trim_t *trim);
egl_result_t egl_rfm66_low_bat_state_set(egl_rfm66_t *rfm, bool state);
egl_result_t egl_rfm66_low_bat_state_get(egl_rfm66_t *rfm, bool *state);

#endif