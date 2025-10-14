#include "egl_rfm69_driver.h"
#include "egl_log.h"
#include "egl_util.h"

#define EGL_RFM69_FSTEP_COEF                (524288U)
#define EGL_RFM69_AFC_OFFSET_COEF           (488U)
#define EGL_RFM69_FIFO_SIZE                 (66U)

#pragma pack(push, 1)
typedef union
{
    uint8_t raw;
    struct
    {
        uint8_t reserved : 2;
        uint8_t mode : 3;
        uint8_t listen_abort : 1;
        uint8_t listen_on : 1;
        uint8_t sequencer_off : 1;
    }bitfield;
}egl_rfm69_reg_op_mode_t;

typedef union
{
    uint8_t raw;
    struct
    {
        uint8_t modulation_shaping : 2;
        uint8_t reserved           : 1;
        uint8_t modulation_type    : 2;
        uint8_t data_mode          : 2;
    }bitfield;
}egl_rfm69_reg_data_modul_t;

typedef union
{
    uint8_t raw;
    struct
    {
        uint8_t reserved    : 6;
        uint8_t calib_state : 1;
        uint8_t calib_start : 1;
    }bitfield;
}egl_rfm69_reg_osc1_t;

typedef union
{
    uint8_t raw;
    struct
    {
        uint8_t reserved : 5;
        uint8_t afc_low_beta_on : 1;
    }bitfield;
}egl_rfm69_reg_afc_ctrl_t;

typedef union
{
    uint8_t raw;
    struct
    {
        uint8_t reserved : 1;
        uint8_t listen_end : 2;
        uint8_t listen_criteria : 1;
        uint8_t listen_resol_rx : 2;
        uint8_t listen_resol_idle : 2;
    }bitfield;
}egl_rfm69_reg_listen1_t;

typedef union
{
    uint8_t raw;
    struct
    {
        uint8_t out_power : 5;
        uint8_t pa2_enable : 1;
        uint8_t pa1_enable : 1;
        uint8_t pa0_enable : 1;
    }bitfield;
}egl_rfm69_reg_pa_level_t;

typedef union
{
    uint8_t raw;
    struct
    {
        uint8_t ocp_trim : 4;
        uint8_t ocp_on : 1;
    }bitfield;
}egl_rfm69_reg_ocp_t;

typedef union
{
    uint8_t raw;
    struct
    {
        uint8_t lna_gain_select : 3;
        uint8_t lna_current_gain : 3;
        uint8_t reserved : 1;
        uint8_t lna_zin : 1;
    }bitfield;
}egl_rfm69_reg_lna_t;

typedef union
{
    uint8_t raw;
    struct
    {
        uint8_t bw_exp : 3;
        uint8_t bw_mant : 2;
        uint8_t dcc_freq : 3;
    }bitfield;
}egl_rfm69_reg_bw_t;

typedef union
{
    uint8_t raw;
    struct
    {
        uint8_t ook_peak_thresh_dec : 3;
        uint8_t ook_peak_thresh_step : 3;
        uint8_t ook_thresh_type : 2;
    }bitfield;
}egl_rfm69_reg_ook_peak_t;

typedef union
{
    uint8_t raw;
    struct
    {
        uint8_t reserved : 6;
        uint8_t ook_average_thresh_filt : 2;
    }bitfield;
}egl_rfm69_reg_ook_avg_t;

typedef union
{
    uint8_t raw;
    struct
    {
        uint8_t afc_start : 1;
        uint8_t afc_clear : 1;
        uint8_t afc_auto_on : 1;
        uint8_t afc_auto_clear_on : 1;
        uint8_t afc_done : 1;
        uint8_t fei_start : 1;
        uint8_t fei_done : 1;
    }bitfield;
}egl_rfm69_reg_afc_fei_t;

typedef union
{
    uint8_t raw;
    struct
    {
        uint8_t rssi_start : 1;
        uint8_t rssi_done : 1;
    }bitfield;
}egl_rfm69_reg_rssi_config_t;

typedef union
{
    uint8_t raw;
    struct
    {
        uint8_t dio3 : 2;
        uint8_t dio2 : 2;
        uint8_t dio1 : 2;
        uint8_t dio0 : 2;
    }bitfield;
}egl_rfm69_reg_dio_map1_t;

typedef union
{
    uint8_t raw;
    struct
    {
        uint8_t clk_out : 3;
        uint8_t reserved : 1;
        uint8_t dio5 : 2;
        uint8_t dio4 : 2;
    }bitfield;
}egl_rfm69_reg_dio_map2_t;

typedef union
{
    uint8_t raw;
    struct
    {
        uint8_t sync_tol : 3;
        uint8_t sync_size : 3;
        uint8_t fifo_fill_condition : 1;
        uint8_t sync_on : 1;
    }bitfield;
}egl_rfm69_reg_sync_config_t;

typedef union
{
    uint8_t raw;
    struct
    {
        uint8_t reserved : 1;
        uint8_t address_filtering : 2;
        uint8_t crc_auto_clear_off : 1;
        uint8_t crc_on : 1;
        uint8_t dc_free : 2;
        uint8_t packet_format : 1;
    }bitfield;
}egl_rfm69_reg_packet_config1_t;

typedef union
{
    uint8_t raw;
    struct
    {
        uint8_t intermediate_mode : 2;
        uint8_t exit_condition : 3;
        uint8_t enter_condition : 3;
    }bitfield;
}egl_rfm69_reg_auto_modes_t;

typedef union
{
    uint8_t raw;
    struct
    {
        uint8_t fifo_thresh : 7;
        uint8_t tx_start_condition : 1;
    }bitfield;
}egl_rfm69_reg_fifo_thresh_t;

typedef union
{
    uint8_t raw;
    struct
    {
        uint8_t aes_on : 1;
        uint8_t auto_rx_restart_on : 1;
        uint8_t restart_rx : 1;
        uint8_t reserved : 1;
        uint8_t interpacket_rx_delay : 4;
    }bitfield;
}egl_rfm69_reg_packet_config2_t;

typedef union
{
    uint8_t raw;
    struct
    {
        uint8_t reserved : 2;
        uint8_t temp_meas_running : 1;
        uint8_t temp_meas_start : 1;
    }bitfield;
}egl_rfm69_reg_temp1_t;
#pragma pack(pop)

typedef struct
{
    uint8_t exp;
    egl_rfm69_bw_mant_t mant;
}egl_rfm69_bw_param_t;

static const egl_rfm69_bw_param_t egl_rfm69_bw_table[] =
{
    { .exp = 7, .mant = EGL_RFM69_BW_MANT_24 },
    { .exp = 7, .mant = EGL_RFM69_BW_MANT_20 },
    { .exp = 7, .mant = EGL_RFM69_BW_MANT_16 },
    { .exp = 6, .mant = EGL_RFM69_BW_MANT_24 },
    { .exp = 6, .mant = EGL_RFM69_BW_MANT_20 },
    { .exp = 6, .mant = EGL_RFM69_BW_MANT_16 },
    { .exp = 5, .mant = EGL_RFM69_BW_MANT_24 },
    { .exp = 5, .mant = EGL_RFM69_BW_MANT_20 },
    { .exp = 5, .mant = EGL_RFM69_BW_MANT_16 },
    { .exp = 4, .mant = EGL_RFM69_BW_MANT_24 },
    { .exp = 4, .mant = EGL_RFM69_BW_MANT_20 },
    { .exp = 4, .mant = EGL_RFM69_BW_MANT_16 },
    { .exp = 3, .mant = EGL_RFM69_BW_MANT_24 },
    { .exp = 3, .mant = EGL_RFM69_BW_MANT_20 },
    { .exp = 3, .mant = EGL_RFM69_BW_MANT_16 },
    { .exp = 2, .mant = EGL_RFM69_BW_MANT_24 },
    { .exp = 2, .mant = EGL_RFM69_BW_MANT_20 },
    { .exp = 2, .mant = EGL_RFM69_BW_MANT_16 },
    { .exp = 1, .mant = EGL_RFM69_BW_MANT_24 },
    { .exp = 1, .mant = EGL_RFM69_BW_MANT_20 },
    { .exp = 1, .mant = EGL_RFM69_BW_MANT_16 },
    { .exp = 0, .mant = EGL_RFM69_BW_MANT_24 },
    { .exp = 0, .mant = EGL_RFM69_BW_MANT_20 },
    { .exp = 0, .mant = EGL_RFM69_BW_MANT_16 },
};

static egl_result_t egl_rfm69_hw_init(egl_rfm69_t *rfm)
{
    egl_result_t result;

    result = egl_pm_init(rfm->pm);
    EGL_RESULT_CHECK(result);

    result = egl_iface_init(rfm->iface);
    EGL_RESULT_CHECK(result);

    result = egl_pio_init(rfm->dio0);
    EGL_RESULT_CHECK(result);

    result = egl_pio_init(rfm->dio1);
    EGL_RESULT_CHECK(result);

    result = egl_pio_init(rfm->dio2);
    EGL_RESULT_CHECK(result);

    result = egl_pio_init(rfm->dio3);
    EGL_RESULT_CHECK(result);

    result = egl_pio_init(rfm->dio4);
    EGL_RESULT_CHECK(result);

    result = egl_pio_init(rfm->dio5);
    EGL_RESULT_CHECK(result);

    result = egl_pm_poweron(rfm->pm);
    EGL_RESULT_CHECK(result);

    result = egl_pm_reset(rfm->pm);
    EGL_RESULT_CHECK(result);

    result = egl_clock_init(rfm->clock);
    EGL_RESULT_CHECK(result);

    return result;
}

egl_result_t egl_rfm69_init(egl_rfm69_t *rfm)
{
    egl_result_t result;

    result = egl_rfm69_hw_init(rfm);
    EGL_RESULT_CHECK(result);

    return result;
}

egl_result_t egl_rfm69_read_byte(egl_rfm69_t *rfm, uint8_t addr, uint8_t *value)
{
    egl_result_t result;
    size_t len = sizeof(*value);

    result = egl_iface_read_addr(rfm->iface, (uint32_t)addr, value, &len);
    EGL_RESULT_CHECK(result);
    EGL_ASSERT_CHECK(len == sizeof(*value), EGL_FAIL);

    return result;
}

egl_result_t egl_rfm69_write_byte(egl_rfm69_t *rfm, uint8_t addr, uint8_t value)
{
    egl_result_t result;
    size_t len = sizeof(value);

    result = egl_iface_write_addr(rfm->iface, (uint32_t)addr, &value, &len);
    EGL_RESULT_CHECK(result);
    EGL_ASSERT_CHECK(len == sizeof(value), EGL_FAIL);

    return result;
}

egl_result_t egl_rfm69_write_burst(egl_rfm69_t *rfm, uint8_t addr, void *data, size_t len)
{
    return egl_iface_write_addr(rfm->iface, (uint32_t)addr, data, &len);
}

egl_result_t egl_rfm69_read_burst(egl_rfm69_t *rfm, uint8_t addr, void *data, size_t len)
{
    return egl_iface_read_addr(rfm->iface, (uint32_t)addr, data, &len);
}

egl_result_t egl_rfm69_bitrate_set(egl_rfm69_t *rfm, uint32_t bitrate)
{
    /* Calculate bitrate value */
    uint16_t bitrate_val = egl_swap16((uint16_t)(egl_clock_get(rfm->clock) / bitrate));

    /* Write bautrate value */
    return egl_rfm69_write_burst(rfm, EGL_RFM69_REG_BITRATE_MSB, (uint8_t *)&bitrate_val, sizeof(bitrate_val));
}

egl_result_t egl_rfm69_bitrate_get(egl_rfm69_t *rfm, uint32_t *bitrate)
{
    egl_result_t result;
    uint16_t bitrate_val;

    result = egl_rfm69_read_burst(rfm, EGL_RFM69_REG_BITRATE_MSB, &bitrate_val, sizeof(bitrate_val));
    EGL_RESULT_CHECK(result);

    /* Calculate bitrate in bits per second */
    *bitrate = egl_clock_get(rfm->clock) / egl_swap16(bitrate_val);

    return result;
}

egl_result_t egl_rfm69_mode_set(egl_rfm69_t *rfm, egl_rfm69_mode_t mode)
{
    egl_result_t result;
    egl_rfm69_reg_op_mode_t regval;

    result = egl_rfm69_read_byte(rfm, EGL_RFM69_REG_MODE, &regval.raw);
    EGL_RESULT_CHECK(result);

    regval.bitfield.mode = mode;

    return egl_rfm69_write_byte(rfm, EGL_RFM69_REG_MODE, regval.raw);
}

egl_result_t egl_rfm69_mode_get(egl_rfm69_t *rfm, egl_rfm69_mode_t *mode)
{
    egl_result_t result;
    egl_rfm69_reg_op_mode_t regval;

    result = egl_rfm69_read_byte(rfm, EGL_RFM69_REG_MODE, &regval.raw);
    EGL_RESULT_CHECK(result);

    *mode = regval.bitfield.mode;

    return result;
}

egl_result_t egl_rfm69_listen_abort(egl_rfm69_t *rfm)
{
    egl_result_t result;
    egl_rfm69_reg_op_mode_t regval;

    result = egl_rfm69_read_byte(rfm, EGL_RFM69_REG_MODE, &regval.raw);
    EGL_RESULT_CHECK(result);

    regval.bitfield.listen_on = false;
    regval.bitfield.listen_abort = true;

    return egl_rfm69_write_byte(rfm, EGL_RFM69_REG_MODE, regval.raw);
}

egl_result_t egl_rfm69_listen_state_set(egl_rfm69_t *rfm, bool state)
{
    egl_result_t result;
    egl_rfm69_reg_op_mode_t regval;

    result = egl_rfm69_read_byte(rfm, EGL_RFM69_REG_MODE, &regval.raw);
    EGL_RESULT_CHECK(result);

    regval.bitfield.listen_on = state;

    return egl_rfm69_write_byte(rfm, EGL_RFM69_REG_MODE, regval.raw);
}

egl_result_t egl_rfm69_listen_state_get(egl_rfm69_t *rfm, bool *state)
{
    egl_result_t result;
    egl_rfm69_reg_op_mode_t regval;

    result = egl_rfm69_read_byte(rfm, EGL_RFM69_REG_MODE, &regval.raw);
    EGL_RESULT_CHECK(result);

    *state = regval.bitfield.listen_on;

    return result;
}

egl_result_t egl_rfm69_sequencer_state_set(egl_rfm69_t *rfm, bool state)
{
    egl_result_t result;
    egl_rfm69_reg_op_mode_t regval;

    result = egl_rfm69_read_byte(rfm, EGL_RFM69_REG_MODE, &regval.raw);
    EGL_RESULT_CHECK(result);

    regval.bitfield.sequencer_off = !state;

    return egl_rfm69_write_byte(rfm, EGL_RFM69_REG_MODE, regval.raw);
}

egl_result_t egl_rfm69_sequencer_state_get(egl_rfm69_t *rfm, bool *state)
{
    egl_result_t result;
    egl_rfm69_reg_op_mode_t regval;

    result = egl_rfm69_read_byte(rfm, EGL_RFM69_REG_MODE, &regval.raw);
    EGL_RESULT_CHECK(result);

    *state = !regval.bitfield.sequencer_off;

    return result;
}

egl_result_t egl_rfm69_modulation_shaping_set(egl_rfm69_t *rfm, egl_rfm69_modulation_shaping_t modsh)
{
    egl_result_t result;
    egl_rfm69_reg_data_modul_t regval;

    result = egl_rfm69_read_byte(rfm, EGL_RFM69_REG_DATA_MODUL, &regval.raw);
    EGL_RESULT_CHECK(result);

    regval.bitfield.modulation_shaping = modsh;

    return egl_rfm69_write_byte(rfm, EGL_RFM69_REG_DATA_MODUL, regval.raw);
}

egl_result_t egl_rfm69_modulation_shaping_get(egl_rfm69_t *rfm, egl_rfm69_modulation_shaping_t *modsh)
{
    egl_result_t result;
    egl_rfm69_reg_data_modul_t regval;

    result = egl_rfm69_read_byte(rfm, EGL_RFM69_REG_DATA_MODUL, &regval.raw);
    EGL_RESULT_CHECK(result);

    *modsh = regval.bitfield.modulation_shaping;

    return result;
}

egl_result_t egl_rfm69_modulation_type_set(egl_rfm69_t *rfm, egl_rfm69_modulation_type_t modtype)
{
    egl_result_t result;
    egl_rfm69_reg_data_modul_t regval;

    result = egl_rfm69_read_byte(rfm, EGL_RFM69_REG_DATA_MODUL, &regval.raw);
    EGL_RESULT_CHECK(result);

    regval.bitfield.modulation_type = modtype;

    return egl_rfm69_write_byte(rfm, EGL_RFM69_REG_DATA_MODUL, regval.raw);
}

egl_result_t egl_rfm69_modulation_type_get(egl_rfm69_t *rfm, egl_rfm69_modulation_type_t *modtype)
{
    egl_result_t result;
    egl_rfm69_reg_data_modul_t regval;

    result = egl_rfm69_read_byte(rfm, EGL_RFM69_REG_DATA_MODUL, &regval.raw);
    EGL_RESULT_CHECK(result);

    *modtype = regval.bitfield.modulation_type;

    return result;
}

egl_result_t egl_rfm69_data_mode_set(egl_rfm69_t *rfm, egl_rfm69_data_mode_t mode)
{
    egl_result_t result;
    egl_rfm69_reg_data_modul_t regval;

    result = egl_rfm69_read_byte(rfm, EGL_RFM69_REG_DATA_MODUL, &regval.raw);
    EGL_RESULT_CHECK(result);

    regval.bitfield.data_mode = mode;

    return egl_rfm69_write_byte(rfm, EGL_RFM69_REG_DATA_MODUL, regval.raw);
}

egl_result_t egl_rfm69_data_mode_get(egl_rfm69_t *rfm, egl_rfm69_data_mode_t *mode)
{
    egl_result_t result;
    egl_rfm69_reg_data_modul_t regval;

    result = egl_rfm69_read_byte(rfm, EGL_RFM69_REG_DATA_MODUL, (uint8_t *)&regval);
    EGL_RESULT_CHECK(result);

    *mode = regval.bitfield.data_mode;

    return result;
}

egl_result_t egl_rfm69_deviation_set(egl_rfm69_t *rfm, uint32_t deviation)
{
    uint16_t deviation_val;

    deviation_val = egl_swap16((uint16_t)(((uint64_t)deviation * EGL_RFM69_FSTEP_COEF) / egl_clock_get(rfm->clock)));

    return egl_rfm69_write_burst(rfm, EGL_RFM69_REG_DEVIATION_MSB, (uint8_t *)&deviation_val, sizeof(deviation_val));
}

egl_result_t egl_rfm69_deviation_get(egl_rfm69_t *rfm, uint32_t *deviation)
{
    egl_result_t result;
    uint16_t deviation_val;

    result = egl_rfm69_read_burst(rfm, EGL_RFM69_REG_DEVIATION_MSB, &deviation_val, sizeof(deviation_val));
    EGL_RESULT_CHECK(result);

    /* Calculate bitrate in bits per second */
    *deviation = (uint32_t)(((uint64_t)egl_swap16(deviation_val) * egl_clock_get(rfm->clock)) / EGL_RFM69_FSTEP_COEF);

    return result;
}

egl_result_t egl_rfm69_frequency_set(egl_rfm69_t *rfm, uint32_t frequency)
{
    uint8_t freq_val[3];
    frequency = (((uint64_t)frequency * EGL_RFM69_FSTEP_COEF) / egl_clock_get(rfm->clock));

    freq_val[0] = frequency >> 16 & 0xFF;
    freq_val[1] = frequency >> 8 & 0xFF;
    freq_val[2] = frequency & 0xFF;

    return egl_rfm69_write_burst(rfm, EGL_RFM69_REG_FREQUENCY_MSB, freq_val, sizeof(freq_val));
}

egl_result_t egl_rfm69_frequency_get(egl_rfm69_t *rfm, uint32_t *frequency)
{
    egl_result_t result;
    uint8_t freq_val[3];

    result = egl_rfm69_read_burst(rfm, EGL_RFM69_REG_FREQUENCY_MSB, &freq_val, sizeof(freq_val));
    EGL_RESULT_CHECK(result);

    *frequency = 0;
    *frequency |= freq_val[0] << 16;
    *frequency |= freq_val[1] << 8;
    *frequency |= freq_val[2];
    *frequency = ((uint64_t)(*frequency) * egl_clock_get(rfm->clock)) / EGL_RFM69_FSTEP_COEF;

    return result;
}

egl_result_t egl_rfm69_rc_calib_start(egl_rfm69_t *rfm)
{
    egl_rfm69_reg_osc1_t regval;

    regval.bitfield.calib_start = true;

    return egl_rfm69_write_byte(rfm, EGL_RFM69_REG_OSC1, regval.raw);
}

egl_result_t egl_rfm69_rc_calib_state_get(egl_rfm69_t *rfm, egl_rfm69_rc_calib_state_t *state)
{
    egl_result_t result;
    egl_rfm69_reg_osc1_t regval;

    result = egl_rfm69_read_byte(rfm, EGL_RFM69_REG_OSC1, &regval.raw);
    EGL_RESULT_CHECK(result);

    *state = regval.bitfield.calib_state;

    return result;
}

egl_result_t egl_rfm69_afc_routine_set(egl_rfm69_t *rfm, egl_rfm69_afc_routine_t routine)
{
    egl_rfm69_reg_afc_ctrl_t regval;

    regval.bitfield.afc_low_beta_on = routine;

    return egl_rfm69_write_byte(rfm, EGL_RFM69_REG_AFC_CTRL, regval.raw);
}

egl_result_t egl_rfm69_afc_routine_get(egl_rfm69_t *rfm, egl_rfm69_afc_routine_t *routine)
{
    egl_result_t result;
    egl_rfm69_reg_afc_ctrl_t regval;

    result = egl_rfm69_read_byte(rfm, EGL_RFM69_REG_AFC_CTRL, &regval.raw);
    EGL_RESULT_CHECK(result);

    *routine = regval.bitfield.afc_low_beta_on;

    return result;
}

egl_result_t egl_rfm69_listen_end_set(egl_rfm69_t *rfm, egl_rfm69_listen_end_t end_action)
{
    egl_result_t result;
    egl_rfm69_reg_listen1_t regval;

    result = egl_rfm69_read_byte(rfm, EGL_RFM69_REG_LISTEN1, &regval.raw);
    EGL_RESULT_CHECK(result);

    regval.bitfield.listen_end = end_action;

    return egl_rfm69_write_byte(rfm, EGL_RFM69_REG_LISTEN1, regval.raw);
}

egl_result_t egl_rfm69_listen_end_get(egl_rfm69_t *rfm, egl_rfm69_listen_end_t *end_action)
{
    egl_result_t result;
    egl_rfm69_reg_listen1_t regval;

    result = egl_rfm69_read_byte(rfm, EGL_RFM69_REG_LISTEN1, &regval.raw);
    EGL_RESULT_CHECK(result);

    *end_action = regval.bitfield.listen_end;

    return result;
}

egl_result_t egl_rfm69_listen_criteria_set(egl_rfm69_t *rfm, egl_rfm69_listen_criteria_t criteria)
{
    egl_result_t result;
    egl_rfm69_reg_listen1_t regval;

    result = egl_rfm69_read_byte(rfm, EGL_RFM69_REG_LISTEN1, &regval.raw);
    EGL_RESULT_CHECK(result);

    regval.bitfield.listen_criteria = criteria;

    return egl_rfm69_write_byte(rfm, EGL_RFM69_REG_LISTEN1, regval.raw);
}

egl_result_t egl_rfm69_listen_criteria_get(egl_rfm69_t *rfm, egl_rfm69_listen_criteria_t *criteria)
{
    egl_result_t result;
    egl_rfm69_reg_listen1_t regval;

    result = egl_rfm69_read_byte(rfm, EGL_RFM69_REG_LISTEN1, &regval.raw);
    EGL_RESULT_CHECK(result);

    *criteria = regval.bitfield.listen_criteria;

    return result;
}

egl_result_t egl_rfm69_listen_rx_resolution_set(egl_rfm69_t *rfm, egl_rfm69_listen_resolution_t resolution)
{
    egl_result_t result;
    egl_rfm69_reg_listen1_t regval;

    result = egl_rfm69_read_byte(rfm, EGL_RFM69_REG_LISTEN1, &regval.raw);
    EGL_RESULT_CHECK(result);

    regval.bitfield.listen_resol_rx = resolution;

    return egl_rfm69_write_byte(rfm, EGL_RFM69_REG_LISTEN1, regval.raw);
}

egl_result_t egl_rfm69_listen_rx_resolution_get(egl_rfm69_t *rfm, egl_rfm69_listen_resolution_t *resolution)
{
    egl_result_t result;
    egl_rfm69_reg_listen1_t regval;

    result = egl_rfm69_read_byte(rfm, EGL_RFM69_REG_LISTEN1, &regval.raw);
    EGL_RESULT_CHECK(result);

    *resolution = regval.bitfield.listen_resol_rx;

    return result;
}

egl_result_t egl_rfm69_listen_idle_resolution_set(egl_rfm69_t *rfm, egl_rfm69_listen_resolution_t resolution)
{
    egl_result_t result;
    egl_rfm69_reg_listen1_t regval;

    result = egl_rfm69_read_byte(rfm, EGL_RFM69_REG_LISTEN1, &regval.raw);
    EGL_RESULT_CHECK(result);

    regval.bitfield.listen_resol_idle = resolution;

    return egl_rfm69_write_byte(rfm, EGL_RFM69_REG_LISTEN1, regval.raw);
}

egl_result_t egl_rfm69_listen_idle_resolution_get(egl_rfm69_t *rfm, egl_rfm69_listen_resolution_t *resolution)
{
    egl_result_t result;
    egl_rfm69_reg_listen1_t regval;

    result = egl_rfm69_read_byte(rfm, EGL_RFM69_REG_LISTEN1, &regval.raw);
    EGL_RESULT_CHECK(result);

    *resolution = regval.bitfield.listen_resol_idle;

    return result;
}

egl_result_t egl_rfm69_listen_idle_coef_set(egl_rfm69_t *rfm, uint8_t coef)
{
    return egl_rfm69_write_byte(rfm, EGL_RFM69_REG_LISTEN2, coef);
}

egl_result_t egl_rfm69_listen_idle_coef_get(egl_rfm69_t *rfm, uint8_t *coef)
{
    return egl_rfm69_read_byte(rfm, EGL_RFM69_REG_LISTEN2, coef);
}

egl_result_t egl_rfm69_listen_rx_coef_set(egl_rfm69_t *rfm, uint8_t coef)
{
    return egl_rfm69_write_byte(rfm, EGL_RFM69_REG_LISTEN3, coef);
}

egl_result_t egl_rfm69_listen_rx_coef_get(egl_rfm69_t *rfm, uint8_t *coef)
{
    return egl_rfm69_read_byte(rfm, EGL_RFM69_REG_LISTEN3, coef);
}

egl_result_t egl_rfm69_power_set(egl_rfm69_t *rfm, int8_t db)
{
    EGL_ASSERT_CHECK(db >= EGL_RFM69_MIN_POWER_DB &&
                     db <= EGL_RFM69_MAX_POWER_DB,
                     EGL_OUT_OF_BOUNDARY);

    egl_result_t result;
    egl_rfm69_reg_pa_level_t regval;

    result = egl_rfm69_read_byte(rfm, EGL_RFM69_REG_PA_LEVEL, &regval.raw);
    EGL_RESULT_CHECK(result);

    regval.bitfield.out_power = db - EGL_RFM69_MIN_POWER_DB;

    return egl_rfm69_write_byte(rfm, EGL_RFM69_REG_PA_LEVEL, regval.raw);
}

egl_result_t egl_rfm69_power_get(egl_rfm69_t *rfm, int8_t *db)
{
    egl_result_t result;
    egl_rfm69_reg_pa_level_t regval;

    result = egl_rfm69_read_byte(rfm, EGL_RFM69_REG_PA_LEVEL, &regval.raw);
    EGL_RESULT_CHECK(result);

    *db = regval.bitfield.out_power + EGL_RFM69_MIN_POWER_DB;

    return result;
}

egl_result_t egl_rfm69_pa0_set(egl_rfm69_t *rfm, bool state)
{
    egl_result_t result;
    egl_rfm69_reg_pa_level_t regval;

    result = egl_rfm69_read_byte(rfm, EGL_RFM69_REG_PA_LEVEL, &regval.raw);
    EGL_RESULT_CHECK(result);

    regval.bitfield.pa0_enable = state;

    return egl_rfm69_write_byte(rfm, EGL_RFM69_REG_PA_LEVEL, regval.raw);
}

egl_result_t egl_rfm69_pa0_get(egl_rfm69_t *rfm, bool *state)
{
    egl_result_t result;
    egl_rfm69_reg_pa_level_t regval;

    result = egl_rfm69_read_byte(rfm, EGL_RFM69_REG_PA_LEVEL, &regval.raw);
    EGL_RESULT_CHECK(result);

    *state = regval.bitfield.pa0_enable;

    return result;
}

egl_result_t egl_rfm69_pa1_set(egl_rfm69_t *rfm, bool state)
{
    egl_result_t result;
    egl_rfm69_reg_pa_level_t regval;

    result = egl_rfm69_read_byte(rfm, EGL_RFM69_REG_PA_LEVEL, &regval.raw);
    EGL_RESULT_CHECK(result);

    regval.bitfield.pa1_enable = state;

    return egl_rfm69_write_byte(rfm, EGL_RFM69_REG_PA_LEVEL, regval.raw);
}

egl_result_t egl_rfm69_pa1_get(egl_rfm69_t *rfm, bool *state)
{
    egl_result_t result;
    egl_rfm69_reg_pa_level_t regval;

    result = egl_rfm69_read_byte(rfm, EGL_RFM69_REG_PA_LEVEL, &regval.raw);
    EGL_RESULT_CHECK(result);

    *state = regval.bitfield.pa1_enable;

    return result;
}

egl_result_t egl_rfm69_pa2_set(egl_rfm69_t *rfm, bool state)
{
    egl_result_t result;
    egl_rfm69_reg_pa_level_t regval;

    result = egl_rfm69_read_byte(rfm, EGL_RFM69_REG_PA_LEVEL, &regval.raw);
    EGL_RESULT_CHECK(result);

    regval.bitfield.pa2_enable = state;

    return egl_rfm69_write_byte(rfm, EGL_RFM69_REG_PA_LEVEL, regval.raw);
}

egl_result_t egl_rfm69_pa2_get(egl_rfm69_t *rfm, bool *state)
{
    egl_result_t result;
    egl_rfm69_reg_pa_level_t regval;

    result = egl_rfm69_read_byte(rfm, EGL_RFM69_REG_PA_LEVEL, &regval.raw);
    EGL_RESULT_CHECK(result);

    *state = regval.bitfield.pa2_enable;

    return result;
}

egl_result_t egl_rfm69_power_ramp_set(egl_rfm69_t *rfm, egl_rfm69_power_ramp_t ramp)
{
    return egl_rfm69_write_byte(rfm, EGL_RFM69_REG_PA_RAMP, (uint8_t)ramp);
}

egl_result_t egl_rfm69_power_ramp_get(egl_rfm69_t *rfm, egl_rfm69_power_ramp_t *ramp)
{
    return egl_rfm69_read_byte(rfm, EGL_RFM69_REG_PA_RAMP, (uint8_t *)ramp);
}

egl_result_t egl_rfm69_ocp_trim_set(egl_rfm69_t *rfm, uint8_t ma)
{
    EGL_ASSERT_CHECK(ma >= EGL_RFM69_MIN_OCP_MA &&
        ma <= EGL_RFM69_MAX_OCP_MA,
        EGL_OUT_OF_BOUNDARY);

    egl_result_t result;
    egl_rfm69_reg_ocp_t regval;

    result = egl_rfm69_read_byte(rfm, EGL_RFM69_REG_OCP, &regval.raw);
    EGL_RESULT_CHECK(result);

    regval.bitfield.ocp_trim = (ma - EGL_RFM69_MIN_OCP_MA) / EGL_RFM69_OCP_STEP;

    return egl_rfm69_write_byte(rfm, EGL_RFM69_REG_OCP, regval.raw);
}

egl_result_t egl_rfm69_ocp_trim_get(egl_rfm69_t *rfm, uint8_t *ma)
{
    egl_result_t result;
    egl_rfm69_reg_ocp_t regval;

    result = egl_rfm69_read_byte(rfm, EGL_RFM69_REG_OCP, &regval.raw);
    EGL_RESULT_CHECK(result);

    *ma = EGL_RFM69_MIN_OCP_MA + EGL_RFM69_OCP_STEP * regval.bitfield.ocp_trim;

    return result;
}

egl_result_t egl_rfm69_ocp_state_set(egl_rfm69_t *rfm, bool state)
{
    egl_result_t result;
    egl_rfm69_reg_ocp_t regval;

    result = egl_rfm69_read_byte(rfm, EGL_RFM69_REG_OCP, &regval.raw);
    EGL_RESULT_CHECK(result);

    regval.bitfield.ocp_on = state;

    return egl_rfm69_write_byte(rfm, EGL_RFM69_REG_OCP, regval.raw);
}

egl_result_t egl_rfm69_ocp_state_get(egl_rfm69_t *rfm, bool *state)
{
    egl_result_t result;
    egl_rfm69_reg_ocp_t regval;

    result = egl_rfm69_read_byte(rfm, EGL_RFM69_REG_OCP, &regval.raw);
    EGL_RESULT_CHECK(result);

    *state = regval.bitfield.ocp_on;

    return result;
}

egl_result_t egl_rfm69_lna_select_gain_set(egl_rfm69_t *rfm, egl_rfm69_lna_gain_t gain)
{
    egl_result_t result;
    egl_rfm69_reg_lna_t regval;

    result = egl_rfm69_read_byte(rfm, EGL_RFM69_REG_LNA, &regval.raw);
    EGL_RESULT_CHECK(result);

    regval.bitfield.lna_gain_select = gain;

    return egl_rfm69_write_byte(rfm, EGL_RFM69_REG_LNA, regval.raw);
}

egl_result_t egl_rfm69_lna_select_gain_get(egl_rfm69_t *rfm, egl_rfm69_lna_gain_t *gain)
{
    egl_result_t result;
    egl_rfm69_reg_lna_t regval;

    result = egl_rfm69_read_byte(rfm, EGL_RFM69_REG_LNA, &regval.raw);
    EGL_RESULT_CHECK(result);

    *gain = regval.bitfield.lna_gain_select;

    return result;
}

egl_result_t egl_rfm69_lna_current_gain_get(egl_rfm69_t *rfm, egl_rfm69_lna_gain_t *gain)
{
    egl_result_t result;
    egl_rfm69_reg_lna_t regval;

    result = egl_rfm69_read_byte(rfm, EGL_RFM69_REG_LNA, &regval.raw);
    EGL_RESULT_CHECK(result);

    *gain = regval.bitfield.lna_current_gain;

    return result;
}

egl_result_t egl_rfm69_lna_zin_set(egl_rfm69_t *rfm, egl_rfm69_lna_zin_t zin)
{
    egl_result_t result;
    egl_rfm69_reg_lna_t regval;

    result = egl_rfm69_read_byte(rfm, EGL_RFM69_REG_LNA, &regval.raw);
    EGL_RESULT_CHECK(result);

    regval.bitfield.lna_zin = zin;

    return egl_rfm69_write_byte(rfm, EGL_RFM69_REG_LNA, regval.raw);
}

egl_result_t egl_rfm69_lna_zin_get(egl_rfm69_t *rfm, egl_rfm69_lna_zin_t *zin)
{
    egl_result_t result;
    egl_rfm69_reg_lna_t regval;

    result = egl_rfm69_read_byte(rfm, EGL_RFM69_REG_LNA, &regval.raw);
    EGL_RESULT_CHECK(result);

    *zin = regval.bitfield.lna_zin;

    return result;
}

egl_result_t egl_rfm69_rx_bw_exp_set(egl_rfm69_t *rfm, uint8_t exp)
{
    EGL_ASSERT_CHECK(exp < 8, EGL_OUT_OF_BOUNDARY);

    egl_result_t result;
    egl_rfm69_reg_bw_t regval;

    result = egl_rfm69_read_byte(rfm, EGL_RFM69_REG_RX_BW, &regval.raw);
    EGL_RESULT_CHECK(result);

    regval.bitfield.bw_exp = exp;

    return egl_rfm69_write_byte(rfm, EGL_RFM69_REG_RX_BW, regval.raw);
}

egl_result_t egl_rfm69_rx_bw_exp_get(egl_rfm69_t *rfm, uint8_t *exp)
{
    egl_result_t result;
    egl_rfm69_reg_bw_t regval;

    result = egl_rfm69_read_byte(rfm, EGL_RFM69_REG_RX_BW, &regval.raw);
    EGL_RESULT_CHECK(result);

    *exp = regval.bitfield.bw_exp;

    return result;
}

egl_result_t egl_rfm69_rx_bw_mant_set(egl_rfm69_t *rfm, egl_rfm69_bw_mant_t mant)
{
    egl_result_t result;
    egl_rfm69_reg_bw_t regval;

    result = egl_rfm69_read_byte(rfm, EGL_RFM69_REG_RX_BW, &regval.raw);
    EGL_RESULT_CHECK(result);

    regval.bitfield.bw_mant = mant;

    return egl_rfm69_write_byte(rfm, EGL_RFM69_REG_RX_BW, regval.raw);
}

egl_result_t egl_rfm69_rx_bw_mant_get(egl_rfm69_t *rfm, egl_rfm69_bw_mant_t *mant)
{
    egl_result_t result;
    egl_rfm69_reg_bw_t regval;

    result = egl_rfm69_read_byte(rfm, EGL_RFM69_REG_RX_BW, &regval.raw);
    EGL_RESULT_CHECK(result);

    *mant = regval.bitfield.bw_mant;

    return result;
}

egl_result_t egl_rfm69_rx_dcc_freq_set(egl_rfm69_t *rfm, uint8_t freq)
{
    EGL_ASSERT_CHECK(freq < 8, EGL_OUT_OF_BOUNDARY);

    egl_result_t result;
    egl_rfm69_reg_bw_t regval;

    result = egl_rfm69_read_byte(rfm, EGL_RFM69_REG_RX_BW, &regval.raw);
    EGL_RESULT_CHECK(result);

    regval.bitfield.dcc_freq = freq;

    return egl_rfm69_write_byte(rfm, EGL_RFM69_REG_RX_BW, regval.raw);
}

egl_result_t egl_rfm69_rx_dcc_freq_get(egl_rfm69_t *rfm, uint8_t *freq)
{
    egl_result_t result;
    egl_rfm69_reg_bw_t regval;

    result = egl_rfm69_read_byte(rfm, EGL_RFM69_REG_RX_BW, &regval.raw);
    EGL_RESULT_CHECK(result);

    *freq = regval.bitfield.dcc_freq;

    return result;
}

egl_result_t egl_rfm69_afc_bw_exp_set(egl_rfm69_t *rfm, uint8_t exp)
{
    EGL_ASSERT_CHECK(exp < 8, EGL_OUT_OF_BOUNDARY);

    egl_result_t result;
    egl_rfm69_reg_bw_t regval;

    result = egl_rfm69_read_byte(rfm, EGL_RFM69_REG_AFC_BW, &regval.raw);
    EGL_RESULT_CHECK(result);

    regval.bitfield.bw_exp = exp;

    return egl_rfm69_write_byte(rfm, EGL_RFM69_REG_AFC_BW, regval.raw);
}

egl_result_t egl_rfm69_afc_bw_exp_get(egl_rfm69_t *rfm, uint8_t *exp)
{
    egl_result_t result;
    egl_rfm69_reg_bw_t regval;

    result = egl_rfm69_read_byte(rfm, EGL_RFM69_REG_AFC_BW, &regval.raw);
    EGL_RESULT_CHECK(result);

    *exp = regval.bitfield.bw_exp;

    return result;
}

egl_result_t egl_rfm69_afc_bw_mant_set(egl_rfm69_t *rfm, egl_rfm69_bw_mant_t mant)
{
    egl_result_t result;
    egl_rfm69_reg_bw_t regval;

    result = egl_rfm69_read_byte(rfm, EGL_RFM69_REG_AFC_BW, &regval.raw);
    EGL_RESULT_CHECK(result);

    regval.bitfield.bw_mant = mant;

    return egl_rfm69_write_byte(rfm, EGL_RFM69_REG_AFC_BW, regval.raw);
}

egl_result_t egl_rfm69_afc_bw_mant_get(egl_rfm69_t *rfm, egl_rfm69_bw_mant_t *mant)
{
    egl_result_t result;
    egl_rfm69_reg_bw_t regval;

    result = egl_rfm69_read_byte(rfm, EGL_RFM69_REG_AFC_BW, &regval.raw);
    EGL_RESULT_CHECK(result);

    *mant = regval.bitfield.bw_mant;

    return result;
}

egl_result_t egl_rfm69_afc_dcc_freq_set(egl_rfm69_t *rfm, uint8_t freq)
{
    EGL_ASSERT_CHECK(freq < 8, EGL_OUT_OF_BOUNDARY);

    egl_result_t result;
    egl_rfm69_reg_bw_t regval;

    result = egl_rfm69_read_byte(rfm, EGL_RFM69_REG_AFC_BW, &regval.raw);
    EGL_RESULT_CHECK(result);

    regval.bitfield.dcc_freq = freq;

    return egl_rfm69_write_byte(rfm, EGL_RFM69_REG_AFC_BW, regval.raw);
}

egl_result_t egl_rfm69_afc_dcc_freq_get(egl_rfm69_t *rfm, uint8_t *freq)
{
    egl_result_t result;
    egl_rfm69_reg_bw_t regval;

    result = egl_rfm69_read_byte(rfm, EGL_RFM69_REG_AFC_BW, &regval.raw);
    EGL_RESULT_CHECK(result);

    *freq = regval.bitfield.dcc_freq;

    return result;
}

egl_result_t egl_rfm69_ook_peak_thresh_dec_set(egl_rfm69_t *rfm, egl_rfm69_ook_thresh_dec_t dec)
{
    egl_result_t result;
    egl_rfm69_reg_ook_peak_t regval;

    result = egl_rfm69_read_byte(rfm, EGL_RFM69_REG_OOK_PEAK, &regval.raw);
    EGL_RESULT_CHECK(result);

    regval.bitfield.ook_peak_thresh_dec = dec;

    return egl_rfm69_write_byte(rfm, EGL_RFM69_REG_OOK_PEAK, regval.raw);
}

egl_result_t egl_rfm69_ook_peak_thresh_dec_get(egl_rfm69_t *rfm, egl_rfm69_ook_thresh_dec_t *dec)
{
    egl_result_t result;
    egl_rfm69_reg_ook_peak_t regval;

    result = egl_rfm69_read_byte(rfm, EGL_RFM69_REG_OOK_PEAK, &regval.raw);
    EGL_RESULT_CHECK(result);

    *dec = regval.bitfield.ook_peak_thresh_dec;

    return result;
}

egl_result_t egl_rfm69_ook_peak_thresh_step_set(egl_rfm69_t *rfm, egl_rfm69_ook_thresh_step_t step)
{
    egl_result_t result;
    egl_rfm69_reg_ook_peak_t regval;

    result = egl_rfm69_read_byte(rfm, EGL_RFM69_REG_OOK_PEAK, &regval.raw);
    EGL_RESULT_CHECK(result);

    regval.bitfield.ook_peak_thresh_step = step;

    return egl_rfm69_write_byte(rfm, EGL_RFM69_REG_OOK_PEAK, regval.raw);
}

egl_result_t egl_rfm69_ook_peak_thresh_step_get(egl_rfm69_t *rfm, egl_rfm69_ook_thresh_step_t *step)
{
    egl_result_t result;
    egl_rfm69_reg_ook_peak_t regval;

    result = egl_rfm69_read_byte(rfm, EGL_RFM69_REG_OOK_PEAK, &regval.raw);
    EGL_RESULT_CHECK(result);

    *step = regval.bitfield.ook_peak_thresh_step;

    return result;
}

egl_result_t egl_rfm69_ook_thresh_type_set(egl_rfm69_t *rfm, egl_rfm69_ook_thresh_type_t type)
{
    egl_result_t result;
    egl_rfm69_reg_ook_peak_t regval;

    result = egl_rfm69_read_byte(rfm, EGL_RFM69_REG_OOK_PEAK, &regval.raw);
    EGL_RESULT_CHECK(result);

    regval.bitfield.ook_thresh_type = type;

    return egl_rfm69_write_byte(rfm, EGL_RFM69_REG_OOK_PEAK, regval.raw);
}

egl_result_t egl_rfm69_ook_thresh_type_get(egl_rfm69_t *rfm, egl_rfm69_ook_thresh_type_t *type)
{
    egl_result_t result;
    egl_rfm69_reg_ook_peak_t regval;

    result = egl_rfm69_read_byte(rfm, EGL_RFM69_REG_OOK_PEAK, &regval.raw);
    EGL_RESULT_CHECK(result);

    *type = regval.bitfield.ook_thresh_type;

    return result;
}

egl_result_t egl_rfm69_ook_thresh_avg_filt_set(egl_rfm69_t *rfm, egl_rfm69_ook_thresh_avg_filt_t filt)
{
    egl_result_t result;
    egl_rfm69_reg_ook_avg_t regval;

    result = egl_rfm69_read_byte(rfm, EGL_RFM69_REG_OOK_AVG, &regval.raw);
    EGL_RESULT_CHECK(result);

    regval.bitfield.ook_average_thresh_filt = filt;

    return egl_rfm69_write_byte(rfm, EGL_RFM69_REG_OOK_AVG, regval.raw);
}

egl_result_t egl_rfm69_ook_thresh_avg_filt_get(egl_rfm69_t *rfm, egl_rfm69_ook_thresh_avg_filt_t *filt)
{
    egl_result_t result;
    egl_rfm69_reg_ook_avg_t regval;

    result = egl_rfm69_read_byte(rfm, EGL_RFM69_REG_OOK_AVG, &regval.raw);
    EGL_RESULT_CHECK(result);

    *filt = regval.bitfield.ook_average_thresh_filt;

    return result;
}

egl_result_t egl_rfm69_ook_thresh_fixed_set(egl_rfm69_t *rfm, uint8_t db)
{
    return egl_rfm69_write_byte(rfm, EGL_RFM69_REG_OOK_FIX, db);
}

egl_result_t egl_rfm69_ook_thresh_fixed_get(egl_rfm69_t *rfm, uint8_t *db)
{
    return egl_rfm69_read_byte(rfm, EGL_RFM69_REG_OOK_FIX, db);
}

egl_result_t egl_rfm69_afc_start(egl_rfm69_t *rfm)
{
    egl_result_t result;
    egl_rfm69_reg_afc_fei_t regval;

    result = egl_rfm69_read_byte(rfm, EGL_RFM69_REG_AFC_FEI, &regval.raw);
    EGL_RESULT_CHECK(result);

    regval.bitfield.afc_start = true;

    return egl_rfm69_write_byte(rfm, EGL_RFM69_REG_AFC_FEI, regval.raw);
}

egl_result_t egl_rfm69_afc_clear(egl_rfm69_t *rfm)
{
    egl_result_t result;
    egl_rfm69_reg_afc_fei_t regval;

    result = egl_rfm69_read_byte(rfm, EGL_RFM69_REG_AFC_FEI, &regval.raw);
    EGL_RESULT_CHECK(result);

    regval.bitfield.afc_clear = true;

    return egl_rfm69_write_byte(rfm, EGL_RFM69_REG_AFC_FEI, regval.raw);
}

egl_result_t egl_rfm69_afc_auto_start_set(egl_rfm69_t *rfm, bool state)
{
    egl_result_t result;
    egl_rfm69_reg_afc_fei_t regval;

    result = egl_rfm69_read_byte(rfm, EGL_RFM69_REG_AFC_FEI, &regval.raw);
    EGL_RESULT_CHECK(result);

    regval.bitfield.afc_auto_on = state;

    return egl_rfm69_write_byte(rfm, EGL_RFM69_REG_AFC_FEI, regval.raw);
}

egl_result_t egl_rfm69_afc_auto_start_get(egl_rfm69_t *rfm, bool *state)
{
    egl_result_t result;
    egl_rfm69_reg_afc_fei_t regval;

    result = egl_rfm69_read_byte(rfm, EGL_RFM69_REG_AFC_FEI, &regval.raw);
    EGL_RESULT_CHECK(result);

    *state = regval.bitfield.afc_auto_on;

    return result;
}

egl_result_t egl_rfm69_afc_auto_clear_set(egl_rfm69_t *rfm, bool state)
{
    egl_result_t result;
    egl_rfm69_reg_afc_fei_t regval;

    result = egl_rfm69_read_byte(rfm, EGL_RFM69_REG_AFC_FEI, &regval.raw);
    EGL_RESULT_CHECK(result);

    regval.bitfield.afc_auto_clear_on = state;

    return egl_rfm69_write_byte(rfm, EGL_RFM69_REG_AFC_FEI, regval.raw);
}

egl_result_t egl_rfm69_afc_auto_clear_get(egl_rfm69_t *rfm, bool *state)
{
    egl_result_t result;
    egl_rfm69_reg_afc_fei_t regval;

    result = egl_rfm69_read_byte(rfm, EGL_RFM69_REG_AFC_FEI, &regval.raw);
    EGL_RESULT_CHECK(result);

    *state = regval.bitfield.afc_auto_clear_on;

    return result;
}

egl_result_t egl_rfm69_afc_state_get(egl_rfm69_t *rfm, bool *state)
{
    egl_result_t result;
    egl_rfm69_reg_afc_fei_t regval;

    result = egl_rfm69_read_byte(rfm, EGL_RFM69_REG_AFC_FEI, &regval.raw);
    EGL_RESULT_CHECK(result);

    *state = regval.bitfield.afc_done;

    return result;
}

egl_result_t egl_rfm69_fei_start(egl_rfm69_t *rfm)
{
    egl_result_t result;
    egl_rfm69_reg_afc_fei_t regval;

    result = egl_rfm69_read_byte(rfm, EGL_RFM69_REG_AFC_FEI, &regval.raw);
    EGL_RESULT_CHECK(result);

    regval.bitfield.fei_start = true;

    return egl_rfm69_write_byte(rfm, EGL_RFM69_REG_AFC_FEI, regval.raw);
}

egl_result_t egl_rfm69_fei_state_get(egl_rfm69_t *rfm, bool *state)
{
    egl_result_t result;
    egl_rfm69_reg_afc_fei_t regval;

    result = egl_rfm69_read_byte(rfm, EGL_RFM69_REG_AFC_FEI, &regval.raw);
    EGL_RESULT_CHECK(result);

    *state = regval.bitfield.fei_done;

    return result;
}

egl_result_t egl_rfm69_afc_get(egl_rfm69_t *rfm, int16_t *hz)
{
    egl_result_t result;
    uint16_t raw;

    result = egl_rfm69_read_burst(rfm, EGL_RFM69_REG_AFC_MSB, &raw, sizeof(raw));
    EGL_RESULT_CHECK(result);

    *hz = (int16_t)((((uint64_t)egl_swap16(raw)) * egl_clock_get(rfm->clock)) / EGL_RFM69_FSTEP_COEF);

    return result;
}

egl_result_t egl_rfm69_fei_get(egl_rfm69_t *rfm, int16_t *hz)
{
    egl_result_t result;
    uint16_t raw;

    result = egl_rfm69_read_burst(rfm, EGL_RFM69_REG_FEI_MSB, &raw, sizeof(raw));
    EGL_RESULT_CHECK(result);

    *hz = (int16_t)((((uint64_t)egl_swap16(raw)) * egl_clock_get(rfm->clock)) / EGL_RFM69_FSTEP_COEF);

    return result;
}

egl_result_t egl_rfm69_rssi_start(egl_rfm69_t *rfm)
{
    egl_result_t result;
    egl_rfm69_reg_rssi_config_t regval;

    result = egl_rfm69_read_byte(rfm, EGL_RFM69_REG_RSSI_CONFIG, &regval.raw);
    EGL_RESULT_CHECK(result);

    regval.bitfield.rssi_start = true;

    return egl_rfm69_write_byte(rfm, EGL_RFM69_REG_RSSI_CONFIG, regval.raw);
}

egl_result_t egl_rfm69_rssi_state_get(egl_rfm69_t *rfm, bool *state)
{
    egl_result_t result;
    egl_rfm69_reg_rssi_config_t regval;

    result = egl_rfm69_read_byte(rfm, EGL_RFM69_REG_RSSI_CONFIG, &regval.raw);
    EGL_RESULT_CHECK(result);

    *state = regval.bitfield.rssi_done;

    return result;
}

egl_result_t egl_rfm69_rssi_get(egl_rfm69_t *rfm, int8_t *db)
{
    return egl_rfm69_read_byte(rfm, EGL_RFM69_REG_RSSI_VALUE, (uint8_t *)db);
}

egl_result_t egl_rfm69_dio0_mode_set(egl_rfm69_t *rfm, egl_rfm69_dio_mode_t mode)
{
    egl_result_t result;
    egl_rfm69_reg_dio_map1_t regval;

    result = egl_rfm69_read_byte(rfm, EGL_RFM69_REG_DIO_MAP1, &regval.raw);
    EGL_RESULT_CHECK(result);

    regval.bitfield.dio0 = mode;

    return egl_rfm69_write_byte(rfm, EGL_RFM69_REG_DIO_MAP1, regval.raw);
}

egl_result_t egl_rfm69_dio0_mode_get(egl_rfm69_t *rfm, egl_rfm69_dio_mode_t *mode)
{
    egl_result_t result;
    egl_rfm69_reg_dio_map1_t regval;

    result = egl_rfm69_read_byte(rfm, EGL_RFM69_REG_DIO_MAP1, &regval.raw);
    EGL_RESULT_CHECK(result);

    *mode = regval.bitfield.dio0;

    return result;
}

egl_result_t egl_rfm69_dio1_mode_set(egl_rfm69_t *rfm, egl_rfm69_dio_mode_t mode)
{
    egl_result_t result;
    egl_rfm69_reg_dio_map1_t regval;

    result = egl_rfm69_read_byte(rfm, EGL_RFM69_REG_DIO_MAP1, &regval.raw);
    EGL_RESULT_CHECK(result);

    regval.bitfield.dio1 = mode;

    return egl_rfm69_write_byte(rfm, EGL_RFM69_REG_DIO_MAP1, regval.raw);
}

egl_result_t egl_rfm69_dio1_mode_get(egl_rfm69_t *rfm, egl_rfm69_dio_mode_t *mode)
{
    egl_result_t result;
    egl_rfm69_reg_dio_map1_t regval;

    result = egl_rfm69_read_byte(rfm, EGL_RFM69_REG_DIO_MAP1, &regval.raw);
    EGL_RESULT_CHECK(result);

    *mode = regval.bitfield.dio1;

    return result;
}

egl_result_t egl_rfm69_dio2_mode_set(egl_rfm69_t *rfm, egl_rfm69_dio_mode_t mode)
{
    egl_result_t result;
    egl_rfm69_reg_dio_map1_t regval;

    result = egl_rfm69_read_byte(rfm, EGL_RFM69_REG_DIO_MAP1, &regval.raw);
    EGL_RESULT_CHECK(result);

    regval.bitfield.dio2 = mode;

    return egl_rfm69_write_byte(rfm, EGL_RFM69_REG_DIO_MAP1, regval.raw);
}

egl_result_t egl_rfm69_dio2_mode_get(egl_rfm69_t *rfm, egl_rfm69_dio_mode_t *mode)
{
    egl_result_t result;
    egl_rfm69_reg_dio_map1_t regval;

    result = egl_rfm69_read_byte(rfm, EGL_RFM69_REG_DIO_MAP1, &regval.raw);
    EGL_RESULT_CHECK(result);

    *mode = regval.bitfield.dio2;

    return result;
}

egl_result_t egl_rfm69_dio3_mode_set(egl_rfm69_t *rfm, egl_rfm69_dio_mode_t mode)
{
    egl_result_t result;
    egl_rfm69_reg_dio_map1_t regval;

    result = egl_rfm69_read_byte(rfm, EGL_RFM69_REG_DIO_MAP1, &regval.raw);
    EGL_RESULT_CHECK(result);

    regval.bitfield.dio3 = mode;

    return egl_rfm69_write_byte(rfm, EGL_RFM69_REG_DIO_MAP1, regval.raw);
}

egl_result_t egl_rfm69_dio3_mode_get(egl_rfm69_t *rfm, egl_rfm69_dio_mode_t *mode)
{
    egl_result_t result;
    egl_rfm69_reg_dio_map1_t regval;

    result = egl_rfm69_read_byte(rfm, EGL_RFM69_REG_DIO_MAP1, &regval.raw);
    EGL_RESULT_CHECK(result);

    *mode = regval.bitfield.dio3;

    return result;
}

egl_result_t egl_rfm69_dio4_mode_set(egl_rfm69_t *rfm, egl_rfm69_dio_mode_t mode)
{
    egl_result_t result;
    egl_rfm69_reg_dio_map2_t regval;

    result = egl_rfm69_read_byte(rfm, EGL_RFM69_REG_DIO_MAP2, &regval.raw);
    EGL_RESULT_CHECK(result);

    regval.bitfield.dio4 = mode;

    return egl_rfm69_write_byte(rfm, EGL_RFM69_REG_DIO_MAP2, regval.raw);
}

egl_result_t egl_rfm69_dio4_mode_get(egl_rfm69_t *rfm, egl_rfm69_dio_mode_t *mode)
{
    egl_result_t result;
    egl_rfm69_reg_dio_map2_t regval;

    result = egl_rfm69_read_byte(rfm, EGL_RFM69_REG_DIO_MAP2, &regval.raw);
    EGL_RESULT_CHECK(result);

    *mode = regval.bitfield.dio4;

    return result;
}

egl_result_t egl_rfm69_dio5_mode_set(egl_rfm69_t *rfm, egl_rfm69_dio_mode_t mode)
{
    egl_result_t result;
    egl_rfm69_reg_dio_map2_t regval;

    result = egl_rfm69_read_byte(rfm, EGL_RFM69_REG_DIO_MAP2, &regval.raw);
    EGL_RESULT_CHECK(result);

    regval.bitfield.dio5 = mode;

    return egl_rfm69_write_byte(rfm, EGL_RFM69_REG_DIO_MAP2, regval.raw);
}

egl_result_t egl_rfm69_dio5_mode_get(egl_rfm69_t *rfm, egl_rfm69_dio_mode_t *mode)
{
    egl_result_t result;
    egl_rfm69_reg_dio_map2_t regval;

    result = egl_rfm69_read_byte(rfm, EGL_RFM69_REG_DIO_MAP2, &regval.raw);
    EGL_RESULT_CHECK(result);

    *mode = regval.bitfield.dio5;

    return result;
}

egl_result_t egl_rfm69_clk_out_set(egl_rfm69_t *rfm, egl_rfm69_clk_out_t out)
{
    egl_result_t result;
    egl_rfm69_reg_dio_map2_t regval;

    result = egl_rfm69_read_byte(rfm, EGL_RFM69_REG_DIO_MAP2, &regval.raw);
    EGL_RESULT_CHECK(result);

    regval.bitfield.clk_out = out;

    return egl_rfm69_write_byte(rfm, EGL_RFM69_REG_DIO_MAP2, regval.raw);
}

egl_result_t egl_rfm69_clk_out_get(egl_rfm69_t *rfm, egl_rfm69_clk_out_t *out)
{
    egl_result_t result;
    egl_rfm69_reg_dio_map2_t regval;

    result = egl_rfm69_read_byte(rfm, EGL_RFM69_REG_DIO_MAP2, &regval.raw);
    EGL_RESULT_CHECK(result);

    *out = regval.bitfield.clk_out;

    return result;
}

egl_result_t egl_rfm69_flags_get(egl_rfm69_t *rfm, egl_rfm69_irq_flags_t *flags)
{
    return egl_rfm69_read_burst(rfm, EGL_RFM69_REG_IRQ_FLAGS1, &flags->raw, sizeof(*flags));
}

egl_result_t egl_rfm69_rssi_thresh_set(egl_rfm69_t *rfm, int8_t db)
{
    return egl_rfm69_write_byte(rfm, EGL_RFM69_REG_RSSI_THRESH, (uint8_t)(-db * 2));
}

egl_result_t egl_rfm69_rssi_thresh_get(egl_rfm69_t *rfm, int8_t *db)
{
    egl_result_t result;
    uint8_t raw;

    result = egl_rfm69_read_byte(rfm, EGL_RFM69_REG_RSSI_THRESH, &raw);
    EGL_RESULT_CHECK(result);

    *db = -((int8_t)(raw / 2));

    return result;
}

egl_result_t egl_rfm69_timeout_rx_start_set(egl_rfm69_t *rfm, uint8_t tout)
{
    return egl_rfm69_write_byte(rfm, EGL_RFM69_REG_TIMEOUT1, tout);
}

egl_result_t egl_rfm69_timeout_rx_start_get(egl_rfm69_t *rfm, uint8_t *tout)
{
    return egl_rfm69_read_byte(rfm, EGL_RFM69_REG_TIMEOUT1, tout);
}

egl_result_t egl_rfm69_timeout_rssi_thresh_set(egl_rfm69_t *rfm, uint8_t tout)
{
    return egl_rfm69_write_byte(rfm, EGL_RFM69_REG_TIMEOUT2, tout);
}

egl_result_t egl_rfm69_timeout_rssi_thresh_get(egl_rfm69_t *rfm, uint8_t *tout)
{
    return egl_rfm69_read_byte(rfm, EGL_RFM69_REG_TIMEOUT2, tout);
}

egl_result_t egl_rfm69_preamble_set(egl_rfm69_t *rfm, uint16_t len)
{
    uint16_t regval = egl_swap16(len);
    return egl_rfm69_write_burst(rfm, EGL_RFM69_REG_PREAMBLE_MSB, (uint8_t *)&regval, sizeof(regval));
}

egl_result_t egl_rfm69_preamble_get(egl_rfm69_t *rfm, uint16_t *len)
{
    egl_result_t result;
    uint16_t regval;

    result = egl_rfm69_read_burst(rfm, EGL_RFM69_REG_PREAMBLE_MSB, &regval, sizeof(regval));
    EGL_RESULT_CHECK(result);

    *len = egl_swap16(regval);

    return result;
}

egl_result_t egl_rfm69_sync_tol_set(egl_rfm69_t *rfm, uint8_t tol)
{
    EGL_ASSERT_CHECK(tol < 8, EGL_OUT_OF_BOUNDARY);
    
    egl_result_t result;
    egl_rfm69_reg_sync_config_t regval;

    result = egl_rfm69_read_byte(rfm, EGL_RFM69_REG_SYNC_CONFIG, &regval.raw);
    EGL_RESULT_CHECK(result);

    regval.bitfield.sync_tol = tol;

    return egl_rfm69_write_byte(rfm, EGL_RFM69_REG_SYNC_CONFIG, regval.raw);
}

egl_result_t egl_rfm69_sync_tol_get(egl_rfm69_t *rfm, uint8_t *tol)
{
    egl_result_t result;
    egl_rfm69_reg_sync_config_t regval;

    result = egl_rfm69_read_byte(rfm, EGL_RFM69_REG_SYNC_CONFIG, &regval.raw);
    EGL_RESULT_CHECK(result);

    *tol = regval.bitfield.sync_tol;

    return result;
}

egl_result_t egl_rfm69_sync_size_set(egl_rfm69_t *rfm, uint8_t size)
{
    EGL_ASSERT_CHECK(size <= 8, EGL_OUT_OF_BOUNDARY);
    EGL_ASSERT_CHECK(size > 0, EGL_OUT_OF_BOUNDARY);

    egl_result_t result;
    egl_rfm69_reg_sync_config_t regval;

    result = egl_rfm69_read_byte(rfm, EGL_RFM69_REG_SYNC_CONFIG, &regval.raw);
    EGL_RESULT_CHECK(result);

    regval.bitfield.sync_size = size - 1;

    return egl_rfm69_write_byte(rfm, EGL_RFM69_REG_SYNC_CONFIG, regval.raw);
}

egl_result_t egl_rfm69_sync_size_get(egl_rfm69_t *rfm, uint8_t *size)
{
    egl_result_t result;
    egl_rfm69_reg_sync_config_t regval;

    result = egl_rfm69_read_byte(rfm, EGL_RFM69_REG_SYNC_CONFIG, &regval.raw);
    EGL_RESULT_CHECK(result);

    *size = regval.bitfield.sync_size + 1;

    return result;
}

egl_result_t egl_rfm69_fifo_fill_cond_set(egl_rfm69_t *rfm, egl_rfm69_fifo_fill_cont_t cond)
{
    egl_result_t result;
    egl_rfm69_reg_sync_config_t regval;

    result = egl_rfm69_read_byte(rfm, EGL_RFM69_REG_SYNC_CONFIG, &regval.raw);
    EGL_RESULT_CHECK(result);

    regval.bitfield.fifo_fill_condition = cond;

    return egl_rfm69_write_byte(rfm, EGL_RFM69_REG_SYNC_CONFIG, regval.raw);
}

egl_result_t egl_rfm69_fifo_fill_cond_get(egl_rfm69_t *rfm, egl_rfm69_fifo_fill_cont_t *cond)
{
    egl_result_t result;
    egl_rfm69_reg_sync_config_t regval;

    result = egl_rfm69_read_byte(rfm, EGL_RFM69_REG_SYNC_CONFIG, &regval.raw);
    EGL_RESULT_CHECK(result);

    *cond = regval.bitfield.fifo_fill_condition;

    return result;
}

egl_result_t egl_rfm69_sync_state_set(egl_rfm69_t *rfm, bool state)
{
    egl_result_t result;
    egl_rfm69_reg_sync_config_t regval;

    result = egl_rfm69_read_byte(rfm, EGL_RFM69_REG_SYNC_CONFIG, &regval.raw);
    EGL_RESULT_CHECK(result);

    regval.bitfield.sync_on = state;

    return egl_rfm69_write_byte(rfm, EGL_RFM69_REG_SYNC_CONFIG, regval.raw);
}

egl_result_t egl_rfm69_sync_state_get(egl_rfm69_t *rfm, bool *state)
{
    egl_result_t result;
    egl_rfm69_reg_sync_config_t regval;

    result = egl_rfm69_read_byte(rfm, EGL_RFM69_REG_SYNC_CONFIG, &regval.raw);
    EGL_RESULT_CHECK(result);

    *state = regval.bitfield.sync_on;

    return result;
}

egl_result_t egl_rfm69_sync_set(egl_rfm69_t *rfm, uint8_t *sync, uint8_t size)
{
    egl_result_t result;

    EGL_ASSERT_CHECK(sync != NULL, EGL_NULL_POINTER);

    result = egl_rfm69_sync_size_set(rfm, size);
    EGL_RESULT_CHECK(result);

    return egl_rfm69_write_burst(rfm, EGL_RFM69_REG_SYNC_VALUE1, sync, size);
}

egl_result_t egl_rfm69_sync_get(egl_rfm69_t *rfm, uint8_t *sync, uint8_t *size)
{
    egl_result_t result;

    result = egl_rfm69_sync_size_get(rfm, size);
    EGL_RESULT_CHECK(result);

    return egl_rfm69_read_burst(rfm, EGL_RFM69_REG_SYNC_VALUE1, sync, *size);
}

egl_result_t egl_rfm69_address_filtering_set(egl_rfm69_t *rfm, egl_rfm69_address_filtering_t filtering)
{
    egl_result_t result;
    egl_rfm69_reg_packet_config1_t regval;

    result = egl_rfm69_read_byte(rfm, EGL_RFM69_REG_PACKET_CONFIG1, &regval.raw);
    EGL_RESULT_CHECK(result);

    regval.bitfield.address_filtering = filtering;

    return egl_rfm69_write_byte(rfm, EGL_RFM69_REG_PACKET_CONFIG1, regval.raw);
}

egl_result_t egl_rfm69_address_filtering_get(egl_rfm69_t *rfm, egl_rfm69_address_filtering_t *filtering)
{
    egl_result_t result;
    egl_rfm69_reg_packet_config1_t regval;

    result = egl_rfm69_read_byte(rfm, EGL_RFM69_REG_PACKET_CONFIG1, &regval.raw);
    EGL_RESULT_CHECK(result);

    *filtering = regval.bitfield.address_filtering;

    return result;
}

egl_result_t egl_rfm69_crc_auto_clear_state_set(egl_rfm69_t *rfm, bool state)
{
    egl_result_t result;
    egl_rfm69_reg_packet_config1_t regval;

    result = egl_rfm69_read_byte(rfm, EGL_RFM69_REG_PACKET_CONFIG1, &regval.raw);
    EGL_RESULT_CHECK(result);

    regval.bitfield.crc_auto_clear_off = !state;

    return egl_rfm69_write_byte(rfm, EGL_RFM69_REG_PACKET_CONFIG1, regval.raw);
}

egl_result_t egl_rfm69_crc_auto_clear_state_get(egl_rfm69_t *rfm, bool *state)
{
    egl_result_t result;
    egl_rfm69_reg_packet_config1_t regval;

    result = egl_rfm69_read_byte(rfm, EGL_RFM69_REG_PACKET_CONFIG1, &regval.raw);
    EGL_RESULT_CHECK(result);

    *state = !regval.bitfield.crc_auto_clear_off;

    return result;
}

egl_result_t egl_rfm69_crc_check_state_set(egl_rfm69_t *rfm, bool state)
{
    egl_result_t result;
    egl_rfm69_reg_packet_config1_t regval;

    result = egl_rfm69_read_byte(rfm, EGL_RFM69_REG_PACKET_CONFIG1, &regval.raw);
    EGL_RESULT_CHECK(result);

    regval.bitfield.crc_on = state;

    return egl_rfm69_write_byte(rfm, EGL_RFM69_REG_PACKET_CONFIG1, regval.raw);
}

egl_result_t egl_rfm69_crc_check_state_get(egl_rfm69_t *rfm, bool *state)
{
    egl_result_t result;
    egl_rfm69_reg_packet_config1_t regval;

    result = egl_rfm69_read_byte(rfm, EGL_RFM69_REG_PACKET_CONFIG1, &regval.raw);
    EGL_RESULT_CHECK(result);

    *state = regval.bitfield.crc_on;

    return result;
}

egl_result_t egl_rfm69_dc_free_set(egl_rfm69_t *rfm, egl_rfm69_dc_free_t type)
{
    egl_result_t result;
    egl_rfm69_reg_packet_config1_t regval;

    result = egl_rfm69_read_byte(rfm, EGL_RFM69_REG_PACKET_CONFIG1, &regval.raw);
    EGL_RESULT_CHECK(result);

    regval.bitfield.dc_free = type;

    return egl_rfm69_write_byte(rfm, EGL_RFM69_REG_PACKET_CONFIG1, regval.raw);
}

egl_result_t egl_rfm69_dc_free_get(egl_rfm69_t *rfm, egl_rfm69_dc_free_t *type)
{
    egl_result_t result;
    egl_rfm69_reg_packet_config1_t regval;

    result = egl_rfm69_read_byte(rfm, EGL_RFM69_REG_PACKET_CONFIG1, &regval.raw);
    EGL_RESULT_CHECK(result);

    *type = regval.bitfield.dc_free;

    return result;
}

egl_result_t egl_rfm69_packet_format_set(egl_rfm69_t *rfm, egl_rfm69_packet_format_t format)
{
    egl_result_t result;
    egl_rfm69_reg_packet_config1_t regval;

    result = egl_rfm69_read_byte(rfm, EGL_RFM69_REG_PACKET_CONFIG1, &regval.raw);
    EGL_RESULT_CHECK(result);

    regval.bitfield.packet_format = format;

    return egl_rfm69_write_byte(rfm, EGL_RFM69_REG_PACKET_CONFIG1, regval.raw);
}

egl_result_t egl_rfm69_packet_format_get(egl_rfm69_t *rfm, egl_rfm69_packet_format_t *format)
{
    egl_result_t result;
    egl_rfm69_reg_packet_config1_t regval;

    result = egl_rfm69_read_byte(rfm, EGL_RFM69_REG_PACKET_CONFIG1, &regval.raw);
    EGL_RESULT_CHECK(result);

    *format = regval.bitfield.packet_format;

    return result;
}

egl_result_t egl_rfm69_packet_length_set(egl_rfm69_t *rfm, uint8_t len)
{
    return egl_rfm69_write_byte(rfm, EGL_RFM69_REG_PAYLOAD_LENGTH, len);
}

egl_result_t egl_rfm69_packet_length_get(egl_rfm69_t *rfm, uint8_t *len)
{
    return egl_rfm69_read_byte(rfm, EGL_RFM69_REG_PAYLOAD_LENGTH, len);
}

egl_result_t egl_rfm69_node_address_set(egl_rfm69_t *rfm, uint8_t addr)
{
    return egl_rfm69_write_byte(rfm, EGL_RFM69_REG_NODE_ADDRESS, addr);
}

egl_result_t egl_rfm69_node_address_get(egl_rfm69_t *rfm, uint8_t *addr)
{
    return egl_rfm69_read_byte(rfm, EGL_RFM69_REG_NODE_ADDRESS, addr);
}

egl_result_t egl_rfm69_broadcast_address_set(egl_rfm69_t *rfm, uint8_t addr)
{
    return egl_rfm69_write_byte(rfm, EGL_RFM69_REG_BROADCAST_ADDRESS, addr);
}

egl_result_t egl_rfm69_broadcast_address_get(egl_rfm69_t *rfm, uint8_t *addr)
{
    return egl_rfm69_read_byte(rfm, EGL_RFM69_REG_BROADCAST_ADDRESS, addr);
}

egl_result_t egl_rfm69_intermediate_mode_set(egl_rfm69_t *rfm, egl_rfm69_intermediate_mode_t mode)
{
    egl_result_t result;
    egl_rfm69_reg_auto_modes_t regval;

    result = egl_rfm69_read_byte(rfm, EGL_RFM69_REG_AUTO_MODES, &regval.raw);
    EGL_RESULT_CHECK(result);

    regval.bitfield.intermediate_mode = mode;

    return egl_rfm69_write_byte(rfm, EGL_RFM69_REG_AUTO_MODES, regval.raw);
}

egl_result_t egl_rfm69_intermediate_mode_get(egl_rfm69_t *rfm, egl_rfm69_intermediate_mode_t *mode)
{
    egl_result_t result;
    egl_rfm69_reg_auto_modes_t regval;

    result = egl_rfm69_read_byte(rfm, EGL_RFM69_REG_AUTO_MODES, &regval.raw);
    EGL_RESULT_CHECK(result);

    *mode = regval.bitfield.intermediate_mode;

    return result;
}

egl_result_t egl_rfm69_exit_condition_set(egl_rfm69_t *rfm, egl_rfm69_exit_condition_t cond)
{
    egl_result_t result;
    egl_rfm69_reg_auto_modes_t regval;

    result = egl_rfm69_read_byte(rfm, EGL_RFM69_REG_AUTO_MODES, &regval.raw);
    EGL_RESULT_CHECK(result);

    regval.bitfield.exit_condition = cond;

    return egl_rfm69_write_byte(rfm, EGL_RFM69_REG_AUTO_MODES, regval.raw);
}

egl_result_t egl_rfm69_exit_condition_get(egl_rfm69_t *rfm, egl_rfm69_exit_condition_t *cond)
{
    egl_result_t result;
    egl_rfm69_reg_auto_modes_t regval;

    result = egl_rfm69_read_byte(rfm, EGL_RFM69_REG_AUTO_MODES, &regval.raw);
    EGL_RESULT_CHECK(result);

    *cond = regval.bitfield.exit_condition;

    return result;
}

egl_result_t egl_rfm69_enter_condition_set(egl_rfm69_t *rfm, egl_rfm69_enter_condition_t cond)
{
    egl_result_t result;
    egl_rfm69_reg_auto_modes_t regval;

    result = egl_rfm69_read_byte(rfm, EGL_RFM69_REG_AUTO_MODES, &regval.raw);
    EGL_RESULT_CHECK(result);

    regval.bitfield.enter_condition = cond;

    return egl_rfm69_write_byte(rfm, EGL_RFM69_REG_AUTO_MODES, regval.raw);
}

egl_result_t egl_rfm69_enter_condition_get(egl_rfm69_t *rfm, egl_rfm69_enter_condition_t *cond)
{
    egl_result_t result;
    egl_rfm69_reg_auto_modes_t regval;

    result = egl_rfm69_read_byte(rfm, EGL_RFM69_REG_AUTO_MODES, &regval.raw);
    EGL_RESULT_CHECK(result);

    *cond = regval.bitfield.enter_condition;

    return result;
}

egl_result_t egl_rfm69_fifo_thresh_set(egl_rfm69_t *rfm, uint8_t thresh)
{
    EGL_ASSERT_CHECK(thresh <= EGL_RFM69_FIFO_SIZE, EGL_OUT_OF_BOUNDARY);

    egl_result_t result;
    egl_rfm69_reg_fifo_thresh_t regval;

    result = egl_rfm69_read_byte(rfm, EGL_RFM69_REG_FIFO_THRESH, &regval.raw);
    EGL_RESULT_CHECK(result);

    regval.bitfield.fifo_thresh = thresh;

    return egl_rfm69_write_byte(rfm, EGL_RFM69_REG_FIFO_THRESH, regval.raw);
}

egl_result_t egl_rfm69_fifo_thresh_get(egl_rfm69_t *rfm, uint8_t *thresh)
{
    egl_result_t result;
    egl_rfm69_reg_fifo_thresh_t regval;

    result = egl_rfm69_read_byte(rfm, EGL_RFM69_REG_FIFO_THRESH, &regval.raw);
    EGL_RESULT_CHECK(result);

    *thresh = regval.bitfield.fifo_thresh;

    return result;
}

egl_result_t egl_rfm69_tx_start_cond_set(egl_rfm69_t *rfm, egl_rfm69_tx_start_cond_t cond)
{
    egl_result_t result;
    egl_rfm69_reg_fifo_thresh_t regval;

    result = egl_rfm69_read_byte(rfm, EGL_RFM69_REG_FIFO_THRESH, &regval.raw);
    EGL_RESULT_CHECK(result);

    regval.bitfield.tx_start_condition = cond;

    return egl_rfm69_write_byte(rfm, EGL_RFM69_REG_FIFO_THRESH, regval.raw);
}

egl_result_t egl_rfm69_tx_start_cond_get(egl_rfm69_t *rfm, egl_rfm69_tx_start_cond_t *cond)
{
    egl_result_t result;
    egl_rfm69_reg_fifo_thresh_t regval;

    result = egl_rfm69_read_byte(rfm, EGL_RFM69_REG_FIFO_THRESH, &regval.raw);
    EGL_RESULT_CHECK(result);

    *cond = regval.bitfield.tx_start_condition;

    return result;
}

egl_result_t egl_rfm69_aes_state_set(egl_rfm69_t *rfm, bool state)
{
    egl_result_t result;
    egl_rfm69_reg_packet_config2_t regval;

    result = egl_rfm69_read_byte(rfm, EGL_RFM69_REG_PACKET_CONFIG2, &regval.raw);
    EGL_RESULT_CHECK(result);

    regval.bitfield.aes_on = state;

    return egl_rfm69_write_byte(rfm, EGL_RFM69_REG_PACKET_CONFIG2, regval.raw);
}

egl_result_t egl_rfm69_aes_state_get(egl_rfm69_t *rfm, bool *state)
{
    egl_result_t result;
    egl_rfm69_reg_packet_config2_t regval;

    result = egl_rfm69_read_byte(rfm, EGL_RFM69_REG_PACKET_CONFIG2, &regval.raw);
    EGL_RESULT_CHECK(result);

    *state = regval.bitfield.aes_on;

    return result;
}

egl_result_t egl_rfm69_auto_rx_restart_state_set(egl_rfm69_t *rfm, bool state)
{
    egl_result_t result;
    egl_rfm69_reg_packet_config2_t regval;

    result = egl_rfm69_read_byte(rfm, EGL_RFM69_REG_PACKET_CONFIG2, &regval.raw);
    EGL_RESULT_CHECK(result);

    regval.bitfield.auto_rx_restart_on = state;

    return egl_rfm69_write_byte(rfm, EGL_RFM69_REG_PACKET_CONFIG2, regval.raw);
}

egl_result_t egl_rfm69_auto_rx_restart_state_get(egl_rfm69_t *rfm, bool *state)
{
    egl_result_t result;
    egl_rfm69_reg_packet_config2_t regval;

    result = egl_rfm69_read_byte(rfm, EGL_RFM69_REG_PACKET_CONFIG2, &regval.raw);
    EGL_RESULT_CHECK(result);

    *state = regval.bitfield.auto_rx_restart_on;

    return result;
}

egl_result_t egl_rfm69_rx_restart(egl_rfm69_t *rfm)
{
    egl_result_t result;
    egl_rfm69_reg_packet_config2_t regval;

    result = egl_rfm69_read_byte(rfm, EGL_RFM69_REG_PACKET_CONFIG2, &regval.raw);
    EGL_RESULT_CHECK(result);

    regval.bitfield.restart_rx = true;

    return egl_rfm69_write_byte(rfm, EGL_RFM69_REG_PACKET_CONFIG2, regval.raw);
}

egl_result_t egl_rfm69_interpacket_delay_set(egl_rfm69_t *rfm, uint8_t delay)
{
    EGL_ASSERT_CHECK(delay <= EGL_RFM69_INTERPACKET_DELAY_MAX, EGL_OUT_OF_BOUNDARY);

    egl_result_t result;
    egl_rfm69_reg_packet_config2_t regval;

    result = egl_rfm69_read_byte(rfm, EGL_RFM69_REG_PACKET_CONFIG2, &regval.raw);
    EGL_RESULT_CHECK(result);

    regval.bitfield.interpacket_rx_delay = delay;

    return egl_rfm69_write_byte(rfm, EGL_RFM69_REG_PACKET_CONFIG2, regval.raw);
}

egl_result_t egl_rfm69_interpacket_delay_get(egl_rfm69_t *rfm, uint8_t *delay)
{
    egl_result_t result;
    egl_rfm69_reg_packet_config2_t regval;

    result = egl_rfm69_read_byte(rfm, EGL_RFM69_REG_PACKET_CONFIG2, &regval.raw);
    EGL_RESULT_CHECK(result);

    *delay = regval.bitfield.interpacket_rx_delay;

    return result;
}

egl_result_t egl_rfm69_aes_key_set(egl_rfm69_t *rfm, uint8_t *key, size_t size)
{
    EGL_ASSERT_CHECK(size == EGL_RFM69_AES_KEY_SIZE, EGL_INVALID_PARAM);
    EGL_ASSERT_CHECK(key != NULL, EGL_NULL_POINTER);

    return egl_rfm69_write_burst(rfm, EGL_RFM69_REG_AES_KEY1, key, size);
}

egl_result_t egl_rfm69_temp_meas_start(egl_rfm69_t *rfm)
{
    egl_result_t result;
    egl_rfm69_reg_temp1_t regval;

    result = egl_rfm69_read_byte(rfm, EGL_RFM69_REG_TEMP1, &regval.raw);
    EGL_RESULT_CHECK(result);

    regval.bitfield.temp_meas_start = true;

    return egl_rfm69_write_byte(rfm, EGL_RFM69_REG_TEMP1, regval.raw);
}

egl_result_t egl_rfm69_temp_meas_state_get(egl_rfm69_t *rfm, bool *state)
{
    egl_result_t result;
    egl_rfm69_reg_temp1_t regval;

    result = egl_rfm69_read_byte(rfm, EGL_RFM69_REG_TEMP1, &regval.raw);
    EGL_RESULT_CHECK(result);

    *state = regval.bitfield.temp_meas_running;

    return result;
}

egl_result_t egl_rfm69_temp_get(egl_rfm69_t *rfm, int8_t *temp)
{
    #define EGL_RFM69_TEMP_CONSTANT (166)

    egl_result_t result;
    uint8_t raw;

    result = egl_rfm69_read_byte(rfm, EGL_RFM69_REG_TEMP2, &raw);

    *temp = (int8_t)(EGL_RFM69_TEMP_CONSTANT - raw);

    return result;
}

egl_result_t egl_rfm69_sensitivity_mode_set(egl_rfm69_t *rfm, egl_rfm69_sensitivity_mode_t mode)
{
    return egl_rfm69_write_byte(rfm, EGL_RFM69_REG_TEST_LNA, (uint8_t)mode);
}

egl_result_t egl_rfm69_sensitivity_mode_get(egl_rfm69_t *rfm, egl_rfm69_sensitivity_mode_t *mode)
{
    return egl_rfm69_read_byte(rfm, EGL_RFM69_REG_TEST_LNA, (uint8_t *)mode);
}

egl_result_t egl_rfm69_pa1_mode_set(egl_rfm69_t *rfm, egl_rfm69_pa1_mode_t mode)
{
    return egl_rfm69_write_byte(rfm, EGL_RFM69_REG_TEST_PA1, (uint8_t)mode);
}

egl_result_t egl_rfm69_pa1_mode_get(egl_rfm69_t *rfm, egl_rfm69_pa1_mode_t *mode)
{
    return egl_rfm69_read_byte(rfm, EGL_RFM69_REG_TEST_PA1, (uint8_t *)mode);
}

egl_result_t egl_rfm69_pa2_mode_set(egl_rfm69_t *rfm, egl_rfm69_pa2_mode_t mode)
{
    return egl_rfm69_write_byte(rfm, EGL_RFM69_REG_TEST_PA2, (uint8_t)mode);
}

egl_result_t egl_rfm69_pa2_mode_get(egl_rfm69_t *rfm, egl_rfm69_pa2_mode_t *mode)
{
    return egl_rfm69_read_byte(rfm, EGL_RFM69_REG_TEST_PA2, (uint8_t *)mode);
}

egl_result_t egl_rfm69_dagc_mode_set(egl_rfm69_t *rfm, egl_rfm69_dagc_mode_t mode)
{
    return egl_rfm69_write_byte(rfm, EGL_RFM69_REG_TEST_DAGC, (uint8_t)mode);
}

egl_result_t egl_rfm69_dagc_mode_get(egl_rfm69_t *rfm, egl_rfm69_dagc_mode_t *mode)
{
    return egl_rfm69_read_byte(rfm, EGL_RFM69_REG_TEST_DAGC, (uint8_t *)mode);
}

egl_result_t egl_rfm69_afc_offset_set(egl_rfm69_t *rfm, uint32_t hz)
{
    uint8_t regval = hz / EGL_RFM69_AFC_OFFSET_COEF;
    return egl_rfm69_write_byte(rfm, EGL_RFM69_REG_TEST_AFC, regval);
}

egl_result_t egl_rfm69_afc_offset_get(egl_rfm69_t *rfm, uint32_t *hz)
{
    egl_result_t result;
    uint8_t regval;

    result = egl_rfm69_read_byte(rfm, EGL_RFM69_REG_TEST_AFC, &regval);
    EGL_RESULT_CHECK(result);

    *hz = regval * EGL_RFM69_AFC_OFFSET_COEF;

    return result;
}

egl_result_t egl_rfm69_version_get(egl_rfm69_t *rfm, uint8_t *version)
{
    return egl_rfm69_read_byte(rfm, EGL_RFM69_REG_VERSION, version);
}

egl_result_t egl_rfm69_rx_bandwidth_set(egl_rfm69_t *rfm, egl_rfm69_bandwidth_t bw)
{
    EGL_ASSERT_CHECK(bw < EGL_ARRAY_SIZE(egl_rfm69_bw_table), EGL_INVALID_PARAM);

    egl_result_t result;

    result = egl_rfm69_rx_bw_exp_set(rfm, egl_rfm69_bw_table[bw].exp);
    EGL_RESULT_CHECK(result);

    result = egl_rfm69_rx_bw_mant_set(rfm, egl_rfm69_bw_table[bw].mant);
    EGL_RESULT_CHECK(result);

    return result;
}

egl_result_t egl_rfm69_rx_bandwidth_get(egl_rfm69_t *rfm, egl_rfm69_bandwidth_t *bw)
{
    uint8_t exp;
    egl_rfm69_bw_mant_t mant;
    egl_result_t result;

    result = egl_rfm69_rx_bw_exp_get(rfm, &exp);
    EGL_RESULT_CHECK(result);

    result = egl_rfm69_rx_bw_mant_get(rfm, &mant);
    EGL_RESULT_CHECK(result);

    unsigned int index;
    for(index = 0; index < EGL_ARRAY_SIZE(egl_rfm69_bw_table); index++)
    {
        if(egl_rfm69_bw_table[index].exp == exp &&
           egl_rfm69_bw_table[index].mant == mant)
        {
            break;
        }
    }

    EGL_ASSERT_CHECK(index < EGL_ARRAY_SIZE(egl_rfm69_bw_table), EGL_INVALID_STATE);

    *bw = (egl_rfm69_bandwidth_t)index;

    return result;
}

egl_result_t egl_rfm69_afc_bandwidth_set(egl_rfm69_t *rfm, egl_rfm69_bandwidth_t bw)
{
    EGL_ASSERT_CHECK(bw < EGL_ARRAY_SIZE(egl_rfm69_bw_table), EGL_INVALID_PARAM);

    egl_result_t result;

    result = egl_rfm69_afc_bw_exp_set(rfm, egl_rfm69_bw_table[bw].exp);
    EGL_RESULT_CHECK(result);

    result = egl_rfm69_afc_bw_mant_set(rfm, egl_rfm69_bw_table[bw].mant);
    EGL_RESULT_CHECK(result);

    return result;
}

egl_result_t egl_rfm69_afc_bandwidth_get(egl_rfm69_t *rfm, egl_rfm69_bandwidth_t *bw)
{
    uint8_t exp;
    egl_rfm69_bw_mant_t mant;
    egl_result_t result;

    result = egl_rfm69_afc_bw_exp_get(rfm, &exp);
    EGL_RESULT_CHECK(result);

    result = egl_rfm69_afc_bw_mant_get(rfm, &mant);
    EGL_RESULT_CHECK(result);

    unsigned int index;
    for(index = 0; index < EGL_ARRAY_SIZE(egl_rfm69_bw_table); index++)
    {
        if(egl_rfm69_bw_table[index].exp == exp &&
           egl_rfm69_bw_table[index].mant == mant)
        {
            break;
        }
    }

    EGL_ASSERT_CHECK(index < EGL_ARRAY_SIZE(egl_rfm69_bw_table), EGL_INVALID_STATE);

    *bw = (egl_rfm69_bandwidth_t)index;

    return result;
}