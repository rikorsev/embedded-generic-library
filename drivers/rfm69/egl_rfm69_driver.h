#ifndef EGL_RFM69_DRIVER_H
#define EGL_RFM69_DRIVER_H

#include "egl_result.h"
#include "egl_pm.h"
#include "egl_pio.h"
#include "egl_iface.h"
#include "egl_clock.h"

#define EGL_RFM69_REG_FIFO                  (0x00)
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
#define EGL_RFM69_REG_OOK_PEAK              (0x1B)
#define EGL_RFM69_REG_OOK_AVG               (0x1C)
#define EGL_RFM69_REG_OOK_FIX               (0x1D)
#define EGL_RFM69_REG_AFC_FEI               (0x1E)
#define EGL_RFM69_REG_AFC_MSB               (0x1F)
#define EGL_RFM69_REG_AFC_LSB               (0x20)
#define EGL_RFM69_REG_FEI_MSB               (0x21)
#define EGL_RFM69_REG_FEI_LSB               (0x22)
#define EGL_RFM69_REG_RSSI_CONFIG           (0x23)
#define EGL_RFM69_REG_RSSI_VALUE            (0x24)
#define EGL_RFM69_REG_DIO_MAP1              (0x25)
#define EGL_RFM69_REG_DIO_MAP2              (0x26)
#define EGL_RFM69_REG_IRQ_FLAGS1            (0x27)
#define EGL_RFM69_REG_IRQ_FLAGS2            (0x28)
#define EGL_RFM69_REG_RSSI_THRESH           (0x29)
#define EGL_RFM69_REG_TIMEOUT1              (0x2A)
#define EGL_RFM69_REG_TIMEOUT2              (0x2B)
#define EGL_RFM69_REG_PREAMBLE_MSB          (0x2C)
#define EGL_RFM69_REG_PREAMBLE_LSB          (0x2D)
#define EGL_RFM69_REG_SYNC_CONFIG           (0x2E)
#define EGL_RFM69_REG_SYNC_VALUE1           (0x2F)
#define EGL_RFM69_REG_SYNC_VALUE2           (0x30)
#define EGL_RFM69_REG_SYNC_VALUE3           (0x31)
#define EGL_RFM69_REG_SYNC_VALUE4           (0x32)
#define EGL_RFM69_REG_SYNC_VALUE5           (0x33)
#define EGL_RFM69_REG_SYNC_VALUE6           (0x34)
#define EGL_RFM69_REG_SYNC_VALUE7           (0x35)
#define EGL_RFM69_REG_SYNC_VALUE8           (0x36)
#define EGL_RFM69_REG_PACKET_CONFIG1        (0x37)
#define EGL_RFM69_REG_PAYLOAD_LENGTH        (0x38)
#define EGL_RFM69_REG_NODE_ADDRESS          (0x39)
#define EGL_RFM69_REG_BROADCAST_ADDRESS     (0x3A)
#define EGL_RFM69_REG_AUTO_MODES            (0x3B)
#define EGL_RFM69_REG_FIFO_THRESH           (0x3C)
#define EGL_RFM69_REG_PACKET_CONFIG2        (0x3D)
#define EGL_RFM69_REG_AES_KEY1              (0x3E)
#define EGL_RFM69_REG_AES_KEY2              (0x3F)
#define EGL_RFM69_REG_AES_KEY3              (0x40)
#define EGL_RFM69_REG_AES_KEY4              (0x41)
#define EGL_RFM69_REG_AES_KEY5              (0x42)
#define EGL_RFM69_REG_AES_KEY6              (0x43)
#define EGL_RFM69_REG_AES_KEY7              (0x44)
#define EGL_RFM69_REG_AES_KEY8              (0x45)
#define EGL_RFM69_REG_AES_KEY9              (0x46)
#define EGL_RFM69_REG_AES_KEY10             (0x47)
#define EGL_RFM69_REG_AES_KEY11             (0x48)
#define EGL_RFM69_REG_AES_KEY12             (0x49)
#define EGL_RFM69_REG_AES_KEY13             (0x4A)
#define EGL_RFM69_REG_AES_KEY14             (0x4B)
#define EGL_RFM69_REG_AES_KEY15             (0x4C)
#define EGL_RFM69_REG_AES_KEY16             (0x4D)
#define EGL_RFM69_REG_TEMP1                 (0x4E)
#define EGL_RFM69_REG_TEMP2                 (0x4F)
#define EGL_RFM69_REG_TEST_LNA              (0x58)
#define EGL_RFM69_REG_TEST_PA1              (0x5A)
#define EGL_RFM69_REG_TEST_PA2              (0x5C)
#define EGL_RFM69_REG_TEST_DAGC             (0x6F)
#define EGL_RFM69_REG_TEST_AFC              (0x71)

#define EGL_RFM69_MAX_POWER_DB              (13)
#define EGL_RFM69_MIN_POWER_DB              (-18)
#define EGL_RFM69_MAX_OCP_MA                (120)
#define EGL_RFM69_MIN_OCP_MA                (45)
#define EGL_RFM69_OCP_STEP                  (5)
#define EGL_RFM69_SYNC_MAX_SIZE             (8)
#define EGL_RFM69_FIFO_THRESH_MAX           (127)
#define EGL_RFM69_INTERPACKET_DELAY_MAX     (15)
#define EGL_RFM69_AES_KEY_SIZE              (16)

typedef enum
{
    EGL_RFM69_SLEEP_MODE,
    EGL_RFM69_STDBY_MODE,
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

typedef enum
{
    EGL_RFM69_OOK_THRESH_DEC_ONCE_PER_CHIP,
    EGL_RFM69_OOK_THRESH_DEC_ONCE_PER_2_CHIPS,
    EGL_RFM69_OOK_THRESH_DEC_ONCE_PER_4_CHIPS,
    EGL_RFM69_OOK_THRESH_DEC_ONCE_PER_8_CHIPS,
    EGL_RFM69_OOK_THRESH_DEC_TWICE_IN_EACH_CHIP,
    EGL_RFM69_OOK_THRESH_DEC_4_TIMES_IN_EACH_CHIP,
    EGL_RFM69_OOK_THRESH_DEC_8_TIMES_IN_EACH_CHIP,
    EGL_RFM69_OOK_THRESH_DEC_16_TIMES_IN_EACH_CHIP
}egl_rfm69_ook_thresh_dec_t;

typedef enum
{
    EGL_RFM69_OOK_THRESH_STEP_0_5_DB,
    EGL_RFM69_OOK_THRESH_STEP_1_0_DB,
    EGL_RFM69_OOK_THRESH_STEP_1_5_DB,
    EGL_RFM69_OOK_THRESH_STEP_2_0_DB,
    EGL_RFM69_OOK_THRESH_STEP_3_0_DB,
    EGL_RFM69_OOK_THRESH_STEP_4_0_DB,
    EGL_RFM69_OOK_THRESH_STEP_5_0_DB,
    EGL_RFM69_OOK_THRESH_STEP_6_0_DB,
}egl_rfm69_ook_thresh_step_t;

typedef enum
{
    EGL_RFM69_OOK_THRESH_TYPE_FIXED,
    EGL_RFM69_OOK_THRESH_TYPE_AVERAGE,
    EGL_RFM69_OOK_THRESH_TYPE_PEAK
}egl_rfm69_ook_thresh_type_t;

typedef enum
{
    EGL_RFM69_OOK_CHIP_RATE_DIV_32P,
    EGL_RFM69_OOK_CHIP_RATE_DIV_8P,
    EGL_RFM69_OOK_CHIP_RATE_DIV_4P,
    EGL_RFM69_OOK_CHIP_RATE_DIV_2P
}egl_rfm69_ook_thresh_avg_filt_t;

typedef enum
{
    EGL_RFM69_DIO_MODE_0,
    EGL_RFM69_DIO_MODE_1,
    EGL_RFM69_DIO_MODE_2,
    EGL_RFM69_DIO_MODE_3,
}egl_rfm69_dio_mode_t;

typedef enum
{
    EGL_RFM69_CLK_OUT_FXOSC,
    EGL_RFM69_CLK_OUT_FXOSC_DIV_2,
    EGL_RFM69_CLK_OUT_FXOSC_DIV_4,
    EGL_RFM69_CLK_OUT_FXOSC_DIV_8,
    EGL_RFM69_CLK_OUT_FXOSC_DIV_16,
    EGL_RFM69_CLK_OUT_FXOSC_DIV_32,
    EGL_RFM69_CLK_OUT_RC,
    EGL_RFM69_CLK_OUT_OFF
}egl_rfm69_clk_out_t;

typedef enum
{
    EGL_RFM69_FIFO_FILL_COND_SYNC_ADDR_IRQ,
    EGL_RFM69_FIFO_FILL_COND_AS_LONG_AS_SET
}egl_rfm69_fifo_fill_cont_t;

typedef enum
{
    EGL_RFM69_ADDRESS_FILTERING_NONE,
    EGL_RFM69_ADDRESS_FILTERING_NODE,
    EGL_RFM69_ADDRESS_GILTERING_NODE_AND_BROADCAST
}egl_rfm69_address_filtering_t;

typedef enum
{
    EGL_RFM69_DC_FREE_NONE,
    EGL_RFM69_DC_FREE_MANCHESTER,
    EGL_RFM69_DC_FREE_WHITENING
}egl_rfm69_dc_free_t;

typedef enum
{
    EGL_RFM69_PACKET_FORMAT_FIXED_LENGTH,
    EGL_RFM69_PACKET_FORMAT_VARIABLE_LENGTH
}egl_rfm69_packet_format_t;

typedef enum
{
    EGL_RFM69_INTERMEDIATE_MODE_SLEEP,
    EGL_RFM69_INTERMEDIATE_MODE_STDBY,
    EGL_RFM69_INTERMEDIATE_MODE_RX,
    EGL_RFM69_INTERMEDIATE_MODE_TX
}egl_rfm69_intermediate_mode_t;

typedef enum
{
    EGL_RFM69_EXIT_CONDITION_NONE,
    EGL_RFM69_EXIT_CONDITION_FALL_EDGE_FIFO_NOT_EMPTY,
    EGL_RFM69_EXIT_CONDITION_RISE_EDGE_FIFO_LEVEL,
    EGL_RFM69_EXIT_CONDITION_RISE_EDGE_CRC_OK,
    EGL_RFM69_EXIT_CONDITION_RISE_EDGE_PAYLOAD_READY,
    EGL_RFM69_EXIT_CONDITION_RISE_EDGE_SYNC_ADDRESS,
    EGL_RFM69_EXIT_CONDITION_RISE_EDGE_PACKET_SENT,
    EGL_RFM69_EXIT_CONDITION_RISE_TIMEOUT
}egl_rfm69_exit_condition_t;

typedef enum
{
    EGL_RFM69_ENTER_CONDITION_NONE,
    EGL_RFM69_ENTER_CONDITION_RISE_EDGE_FIFO_NOT_EMPTY,
    EGL_RFM69_ENTER_CONDITION_RISE_EDGE_FIFO_LEVEL,
    EGL_RFM69_ENTER_CONDITION_RISE_CRC_OK,
    EGL_RFM69_ENTER_CONDITION_PAYLOAD_READY,
    EGL_RFM69_ENTER_CONDITION_SYNC_ADDRESS,
    EGL_RFM69_ENTER_CONDITION_PACKET_SENT,
    EGL_RFM69_ENTER_CONDITION_FAL_EDGE_FIFO_NOT_EMPTY
}egl_rfm69_enter_condition_t;

typedef enum
{
    EGL_RFM69_TX_START_CONDITION_FIFO_LEVEL,
    EGL_RFM69_TX_START_CONDITION_FIFO_NOT_EMPTY
}egl_rfm69_tx_start_cond_t;

typedef enum
{
    EGL_RFM69_SENSITIVITY_MODE_NORMAL = 0x1B,
    EGL_RFM69_SENSITIVITY_MODE_HIGH = 0x2D
}egl_rfm69_sensitivity_mode_t;

typedef enum
{
    EGL_RFM69_PA1_MODE_NORMAL = 0x55,
    EGL_RFM69_PA1_MODE_PLUS_13_DBM = 0x5D
}egl_rfm69_pa1_mode_t;

typedef enum
{
    EGL_RFM69_PA2_MODE_NORMAL = 0x70,
    EGL_RFM69_PA2_MODE_PLUS_13_DBM = 0x7C
}egl_rfm69_pa2_mode_t;

typedef enum
{
    EGL_RFM69_DAGC_MODE_NORMAL = 0x00,
    EGL_RFM69_DAGC_MODE_IMPROVED_MARGIN1 = 0x20,
    EGL_RFM69_DAGC_MODE_IMPROVED_MARGIN2 = 0x30
}egl_rfm69_dagc_mode_t;

typedef enum
{
    EGL_RFM69_BANDWIDTH_FSK_2600_OOK_1300,
    EGL_RFM69_BANDWIDTH_FSK_3100_OOK_1600,
    EGL_RFM69_BANDWIDTH_FSK_3900_OOK_2000,
    EGL_RFM69_BANDWIDTH_FSK_5200_OOK_2600,
    EGL_RFM69_BANDWIDTH_FSK_6300_OOK_3100,
    EGL_RFM69_BANDWIDTH_FSK_7800_OOK_3900,
    EGL_RFM69_BANDWIDTH_FSK_10400_OOK_5200,
    EGL_RFM69_BANDWIDTH_FSK_12500_OOK_6300,
    EGL_RFM69_BANDWIDTH_FSK_15600_OOK_7800,
    EGL_RFM69_BANDWIDTH_FSK_20800_OOK_10400,
    EGL_RFM69_BANDWIDTH_FSK_25000_OOK_12500,
    EGL_RFM69_BANDWIDTH_FSK_31300_OOK_15600,
    EGL_RFM69_BANDWIDTH_FSK_41700_OOK_20800,
    EGL_RFM69_BANDWIDTH_FSK_50000_OOK_25000,
    EGL_RFM69_BANDWIDTH_FSK_62500_OOK_31300,
    EGL_RFM69_BANDWIDTH_FSK_83300_OOK_41700,
    EGL_RFM69_BANDWIDTH_FSK_100000_OOK_50000,
    EGL_RFM69_BANDWIDTH_FSK_125000_OOK_62500,
    EGL_RFM69_BANDWIDTH_FSK_166700_OOK_83300,
    EGL_RFM69_BANDWIDTH_FSK_200000_OOK_100000,
    EGL_RFM69_BANDWIDTH_FSK_250000_OOK_125000,
    EGL_RFM69_BANDWIDTH_FSK_333333_OOK_166700,
    EGL_RFM69_BANDWIDTH_FSK_400000_OOK_200000,
    EGL_RFM69_BANDWIDTH_FSK_500000_OOK_250000
}egl_rfm69_bandwidth_t;

typedef union __attribute__((packed, aligned(1)))
{
    uint16_t raw;
    struct
    {
        uint16_t sync_addr_match : 1;
        uint16_t auto_mode : 1;
        uint16_t timeout : 1;
        uint16_t rssi : 1;
        uint16_t pll_lock : 1;
        uint16_t tx_ready : 1;
        uint16_t rx_ready : 1;
        uint16_t mode_ready : 1;
        uint16_t reserved : 1;
        uint16_t crc_ok : 1;
        uint16_t payload_ready : 1;
        uint16_t packet_sent : 1;
        uint16_t fifo_overrun : 1;
        uint16_t fifo_level : 1;
        uint16_t fifo_not_empty : 1;
        uint16_t fifo_full : 1;
    }bitfield;
}egl_rfm69_irq_flags_t;

typedef struct
{
    egl_pm_t        *pm;
    egl_iface_t     *iface;
    egl_clock_t     *clock;
    egl_pio_t       *dio0;
    egl_pio_t       *dio1;
    egl_pio_t       *dio2;
    egl_pio_t       *dio3;
    egl_pio_t       *dio4;
    egl_pio_t       *dio5;
    uint32_t        pm_wait;
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
egl_result_t egl_rfm69_listen_abort(egl_rfm69_t *rfm);
egl_result_t egl_rfm69_listen_state_set(egl_rfm69_t *rfm, bool state);
egl_result_t egl_rfm69_listen_state_get(egl_rfm69_t *rfm, bool *state);
egl_result_t egl_rfm69_sequencer_state_set(egl_rfm69_t *rfm, bool state);
egl_result_t egl_rfm69_sequencer_state_get(egl_rfm69_t *rfm, bool *state);
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
egl_result_t egl_rfm69_rc_calib_start(egl_rfm69_t *rfm);
egl_result_t egl_rfm69_rc_calib_state_get(egl_rfm69_t *rfm, egl_rfm69_rc_calib_state_t *state);
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
egl_result_t egl_rfm69_rx_bandwidth_set(egl_rfm69_t *rfm, egl_rfm69_bandwidth_t bw);
egl_result_t egl_rfm69_rx_bandwidth_get(egl_rfm69_t *rfm, egl_rfm69_bandwidth_t *bw);
egl_result_t egl_rfm69_afc_bandwidth_set(egl_rfm69_t *rfm, egl_rfm69_bandwidth_t bw);
egl_result_t egl_rfm69_afc_bandwidth_get(egl_rfm69_t *rfm, egl_rfm69_bandwidth_t *bw);
egl_result_t egl_rfm69_afc_bw_exp_set(egl_rfm69_t *rfm, uint8_t exp);
egl_result_t egl_rfm69_afc_bw_exp_get(egl_rfm69_t *rfm, uint8_t *exp);
egl_result_t egl_rfm69_afc_bw_mant_set(egl_rfm69_t *rfm, egl_rfm69_bw_mant_t mant);
egl_result_t egl_rfm69_afc_bw_mant_get(egl_rfm69_t *rfm, egl_rfm69_bw_mant_t *mant);
egl_result_t egl_rfm69_afc_dcc_freq_set(egl_rfm69_t *rfm, uint8_t freq);
egl_result_t egl_rfm69_afc_dcc_freq_get(egl_rfm69_t *rfm, uint8_t *freq);
egl_result_t egl_rfm69_ook_peak_thresh_dec_set(egl_rfm69_t *rfm, egl_rfm69_ook_thresh_dec_t dec);
egl_result_t egl_rfm69_ook_peak_thresh_dec_get(egl_rfm69_t *rfm, egl_rfm69_ook_thresh_dec_t *dec);
egl_result_t egl_rfm69_ook_peak_thresh_step_set(egl_rfm69_t *rfm, egl_rfm69_ook_thresh_step_t step);
egl_result_t egl_rfm69_ook_peak_thresh_step_get(egl_rfm69_t *rfm, egl_rfm69_ook_thresh_step_t *step);
egl_result_t egl_rfm69_ook_thresh_type_set(egl_rfm69_t *rfm, egl_rfm69_ook_thresh_type_t type);
egl_result_t egl_rfm69_ook_thresh_type_get(egl_rfm69_t *rfm, egl_rfm69_ook_thresh_type_t *type);
egl_result_t egl_rfm69_ook_thresh_avg_filt_set(egl_rfm69_t *rfm, egl_rfm69_ook_thresh_avg_filt_t filt);
egl_result_t egl_rfm69_ook_thresh_avg_filt_get(egl_rfm69_t *rfm, egl_rfm69_ook_thresh_avg_filt_t *filt);
egl_result_t egl_rfm69_ook_thresh_fixed_set(egl_rfm69_t *rfm, uint8_t db);
egl_result_t egl_rfm69_ook_thresh_fixed_get(egl_rfm69_t *rfm, uint8_t *db);
egl_result_t egl_rfm69_afc_start(egl_rfm69_t *rfm);
egl_result_t egl_rfm69_afc_clear(egl_rfm69_t *rfm);
egl_result_t egl_rfm69_afc_auto_start_set(egl_rfm69_t *rfm, bool state);
egl_result_t egl_rfm69_afc_auto_start_get(egl_rfm69_t *rfm, bool *state);
egl_result_t egl_rfm69_afc_auto_clear_set(egl_rfm69_t *rfm, bool state);
egl_result_t egl_rfm69_afc_auto_clear_get(egl_rfm69_t *rfm, bool *state);
egl_result_t egl_rfm69_afc_state_get(egl_rfm69_t *rfm, bool *state);
egl_result_t egl_rfm69_afc_get(egl_rfm69_t *rfm, int16_t *hz);
egl_result_t egl_rfm69_fei_start(egl_rfm69_t *rfm);
egl_result_t egl_rfm69_fei_state_get(egl_rfm69_t *rfm, bool *state);
egl_result_t egl_rfm69_fei_get(egl_rfm69_t *rfm, int16_t *hz);
egl_result_t egl_rfm69_rssi_start(egl_rfm69_t *rfm);
egl_result_t egl_rfm69_rssi_state_get(egl_rfm69_t *rfm, bool *state);
egl_result_t egl_rfm69_rssi_get(egl_rfm69_t *rfm, int8_t *db);
egl_result_t egl_rfm69_dio0_mode_set(egl_rfm69_t *rfm, egl_rfm69_dio_mode_t mode);
egl_result_t egl_rfm69_dio0_mode_get(egl_rfm69_t *rfm, egl_rfm69_dio_mode_t *mode);
egl_result_t egl_rfm69_dio1_mode_set(egl_rfm69_t *rfm, egl_rfm69_dio_mode_t mode);
egl_result_t egl_rfm69_dio1_mode_get(egl_rfm69_t *rfm, egl_rfm69_dio_mode_t *mode);
egl_result_t egl_rfm69_dio2_mode_set(egl_rfm69_t *rfm, egl_rfm69_dio_mode_t mode);
egl_result_t egl_rfm69_dio2_mode_get(egl_rfm69_t *rfm, egl_rfm69_dio_mode_t *mode);
egl_result_t egl_rfm69_dio3_mode_set(egl_rfm69_t *rfm, egl_rfm69_dio_mode_t mode);
egl_result_t egl_rfm69_dio3_mode_get(egl_rfm69_t *rfm, egl_rfm69_dio_mode_t *mode);
egl_result_t egl_rfm69_dio4_mode_set(egl_rfm69_t *rfm, egl_rfm69_dio_mode_t mode);
egl_result_t egl_rfm69_dio4_mode_get(egl_rfm69_t *rfm, egl_rfm69_dio_mode_t *mode);
egl_result_t egl_rfm69_dio5_mode_set(egl_rfm69_t *rfm, egl_rfm69_dio_mode_t mode);
egl_result_t egl_rfm69_dio5_mode_get(egl_rfm69_t *rfm, egl_rfm69_dio_mode_t *mode);
egl_result_t egl_rfm69_clk_out_set(egl_rfm69_t *rfm, egl_rfm69_clk_out_t out);
egl_result_t egl_rfm69_clk_out_get(egl_rfm69_t *rfm, egl_rfm69_clk_out_t *out);
egl_result_t egl_rfm69_flags_get(egl_rfm69_t *rfm, egl_rfm69_irq_flags_t *flags);
egl_result_t egl_rfm69_rssi_thresh_set(egl_rfm69_t *rfm, int8_t db);
egl_result_t egl_rfm69_rssi_thresh_get(egl_rfm69_t *rfm, int8_t *db);
egl_result_t egl_rfm69_timeout_rx_start_set(egl_rfm69_t *rfm, uint8_t tout);
egl_result_t egl_rfm69_timeout_rx_start_get(egl_rfm69_t *rfm, uint8_t *tout);
egl_result_t egl_rfm69_timeout_rssi_thresh_set(egl_rfm69_t *rfm, uint8_t tout);
egl_result_t egl_rfm69_timeout_rssi_thresh_get(egl_rfm69_t *rfm, uint8_t *tout);
egl_result_t egl_rfm69_preamble_set(egl_rfm69_t *rfm, uint16_t len);
egl_result_t egl_rfm69_preamble_get(egl_rfm69_t *rfm, uint16_t *len);
egl_result_t egl_rfm69_sync_tol_set(egl_rfm69_t *rfm, uint8_t tol);
egl_result_t egl_rfm69_sync_tol_get(egl_rfm69_t *rfm, uint8_t *tol);
egl_result_t egl_rfm69_sync_size_set(egl_rfm69_t *rfm, uint8_t size);
egl_result_t egl_rfm69_sync_size_get(egl_rfm69_t *rfm, uint8_t *size);
egl_result_t egl_rfm69_fifo_fill_cond_set(egl_rfm69_t *rfm, egl_rfm69_fifo_fill_cont_t cond);
egl_result_t egl_rfm69_fifo_fill_cond_get(egl_rfm69_t *rfm, egl_rfm69_fifo_fill_cont_t *cond);
egl_result_t egl_rfm69_sync_state_set(egl_rfm69_t *rfm, bool state);
egl_result_t egl_rfm69_sync_state_get(egl_rfm69_t *rfm, bool *state);
egl_result_t egl_rfm69_sync_set(egl_rfm69_t *rfm, uint8_t *sync, uint8_t size);
egl_result_t egl_rfm69_sync_get(egl_rfm69_t *rfm, uint8_t *sync, uint8_t *size);
egl_result_t egl_rfm69_address_filtering_set(egl_rfm69_t *rfm, egl_rfm69_address_filtering_t filtering);
egl_result_t egl_rfm69_address_filtering_get(egl_rfm69_t *rfm, egl_rfm69_address_filtering_t *filtering);
egl_result_t egl_rfm69_crc_auto_clear_state_set(egl_rfm69_t *rfm, bool state);
egl_result_t egl_rfm69_crc_auto_clear_state_get(egl_rfm69_t *rfm, bool *state);
egl_result_t egl_rfm69_crc_check_state_set(egl_rfm69_t *rfm, bool state);
egl_result_t egl_rfm69_crc_check_state_get(egl_rfm69_t *rfm, bool *state);
egl_result_t egl_rfm69_dc_free_set(egl_rfm69_t *rfm, egl_rfm69_dc_free_t type);
egl_result_t egl_rfm69_dc_free_get(egl_rfm69_t *rfm, egl_rfm69_dc_free_t *type);
egl_result_t egl_rfm69_packet_format_set(egl_rfm69_t *rfm, egl_rfm69_packet_format_t format);
egl_result_t egl_rfm69_packet_format_get(egl_rfm69_t *rfm, egl_rfm69_packet_format_t *format);
egl_result_t egl_rfm69_payload_length_set(egl_rfm69_t *rfm, uint8_t len);
egl_result_t egl_rfm69_payload_length_get(egl_rfm69_t *rfm, uint8_t *len);
egl_result_t egl_rfm69_node_address_set(egl_rfm69_t *rfm, uint8_t addr);
egl_result_t egl_rfm69_node_address_get(egl_rfm69_t *rfm, uint8_t *addr);
egl_result_t egl_rfm69_broadcast_address_set(egl_rfm69_t *rfm, uint8_t addr);
egl_result_t egl_rfm69_broadcast_address_get(egl_rfm69_t *rfm, uint8_t *addr);
egl_result_t egl_rfm69_intermediate_mode_set(egl_rfm69_t *rfm, egl_rfm69_intermediate_mode_t mode);
egl_result_t egl_rfm69_intermediate_mode_get(egl_rfm69_t *rfm, egl_rfm69_intermediate_mode_t *mode);
egl_result_t egl_rfm69_exit_condition_set(egl_rfm69_t *rfm, egl_rfm69_exit_condition_t cond);
egl_result_t egl_rfm69_exit_condition_get(egl_rfm69_t *rfm, egl_rfm69_exit_condition_t *cond);
egl_result_t egl_rfm69_enter_condition_set(egl_rfm69_t *rfm, egl_rfm69_enter_condition_t cond);
egl_result_t egl_rfm69_enter_condition_get(egl_rfm69_t *rfm, egl_rfm69_enter_condition_t *cond);
egl_result_t egl_rfm69_fifo_thresh_set(egl_rfm69_t *rfm, uint8_t thresh);
egl_result_t egl_rfm69_fifo_thresh_get(egl_rfm69_t *rfm, uint8_t *thresh);
egl_result_t egl_rfm69_tx_start_cond_set(egl_rfm69_t *rfm, egl_rfm69_tx_start_cond_t cond);
egl_result_t egl_rfm69_tx_start_cond_get(egl_rfm69_t *rfm, egl_rfm69_tx_start_cond_t *cond);
egl_result_t egl_rfm69_aes_state_set(egl_rfm69_t *rfm, bool state);
egl_result_t egl_rfm69_aes_state_get(egl_rfm69_t *rfm, bool *state);
egl_result_t egl_rfm69_auto_rx_restart_state_set(egl_rfm69_t *rfm, bool state);
egl_result_t egl_rfm69_auto_rx_restart_state_get(egl_rfm69_t *rfm, bool *state);
egl_result_t egl_rfm69_rx_restart(egl_rfm69_t *rfm);
egl_result_t egl_rfm69_interpacket_delay_set(egl_rfm69_t *rfm, uint8_t delay);
egl_result_t egl_rfm69_interpacket_delay_get(egl_rfm69_t *rfm, uint8_t *delay);
egl_result_t egl_rfm69_aes_key_set(egl_rfm69_t *rfm, uint8_t *key, size_t size);
egl_result_t egl_rfm69_temp_meas_start(egl_rfm69_t *rfm);
egl_result_t egl_rfm69_temp_meas_state_get(egl_rfm69_t *rfm, bool *state);
egl_result_t egl_rfm69_temp_get(egl_rfm69_t *rfm, int8_t *temp);
egl_result_t egl_rfm69_sensitivity_mode_set(egl_rfm69_t *rfm, egl_rfm69_sensitivity_mode_t mode);
egl_result_t egl_rfm69_sensitivity_mode_get(egl_rfm69_t *rfm, egl_rfm69_sensitivity_mode_t *mode);
egl_result_t egl_rfm69_pa1_mode_set(egl_rfm69_t *rfm, egl_rfm69_pa1_mode_t mode);
egl_result_t egl_rfm69_pa1_mode_get(egl_rfm69_t *rfm, egl_rfm69_pa1_mode_t *mode);
egl_result_t egl_rfm69_pa2_mode_set(egl_rfm69_t *rfm, egl_rfm69_pa2_mode_t mode);
egl_result_t egl_rfm69_pa2_mode_get(egl_rfm69_t *rfm, egl_rfm69_pa2_mode_t *mode);
egl_result_t egl_rfm69_dagc_mode_set(egl_rfm69_t *rfm, egl_rfm69_dagc_mode_t mode);
egl_result_t egl_rfm69_dagc_mode_get(egl_rfm69_t *rfm, egl_rfm69_dagc_mode_t *mode);
egl_result_t egl_rfm69_afc_offset_set(egl_rfm69_t *rfm, uint32_t hz);
egl_result_t egl_rfm69_afc_offset_get(egl_rfm69_t *rfm, uint32_t *hz);
egl_result_t egl_rfm69_version_get(egl_rfm69_t *rfm, uint8_t *version);

#endif