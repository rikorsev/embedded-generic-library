#include "egl_rfm69.h"
#include "egl_log.h"
#include "egl_util.h"

#define EGL_RFM69_FSTEP_COEF                (524288U)
#define EGL_RFM69_MODE_MASK                 (0x1C)
#define EGL_RFM69_MODE_SHIFT                (2U)

typedef union __attribute__((packed, aligned(1)))
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

typedef union __attribute__((packed, aligned(1)))
{
    uint8_t raw;
    struct
    {
        uint8_t reserved    : 6;
        uint8_t calib_state : 1;
        uint8_t calib_start : 1;
    }bitfield;
}egl_rfm69_reg_osc1_t;

typedef union __attribute__((packed, aligned(1)))
{
    uint8_t raw;
    struct
    {
        uint8_t reserved : 5;
        uint8_t afc_low_beta_on : 1;
    }bitfield;
}egl_rfm69_reg_afc_ctrl_t;

typedef union __attribute__((packed, aligned(1)))
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

typedef union __attribute__((packed, aligned(1)))
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

typedef union __attribute__((packed, aligned(1)))
{
    uint8_t raw;
    struct
    {
        uint8_t ocp_trim : 4;
        uint8_t ocp_on : 1;
    }bitfield;
}egl_rfm69_reg_ocp_t;

typedef union __attribute__((packed, aligned(1)))
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

typedef union __attribute__((packed, aligned(1)))
{
    uint8_t raw;
    struct
    {
        uint8_t bw_exp : 3;
        uint8_t bw_mant : 2;
        uint8_t dcc_freq : 3;
    }bitfield;
}egl_rfm69_reg_bw_t;

typedef union __attribute__((packed, aligned(1)))
{
    uint8_t raw;
    struct
    {
        uint8_t ook_peak_thresh_dec : 3;
        uint8_t ook_peak_thresh_step : 3;
        uint8_t ook_thresh_type : 2;
    }bitfield;
}egl_rfm69_reg_ook_peak_t;

typedef union __attribute__((packed, aligned(1)))
{
    uint8_t raw;
    struct
    {
        uint8_t reserved : 6;
        uint8_t ook_average_thresh_filt : 2;
    }bitfield;
}egl_rfm69_reg_ook_avg_t;

typedef union __attribute__((packed, aligned(1)))
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
}egl_rfm69_reg_afc_fet_t;

typedef union __attribute__((packed, aligned(1)))
{
    uint8_t raw;
    struct
    {
        uint8_t rssi_start : 1;
        uint8_t rssi_done : 1;
    }bitfield;
}egl_rfm69_reg_rssi_config_t;

typedef union __attribute__((packed, aligned(1)))
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

typedef union __attribute__((packed, aligned(1)))
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

static egl_result_t egl_rfm69_hw_init(egl_rfm69_t *rfm)
{
    egl_result_t result;

    result = egl_pm_init(rfm->pm);
    if(result != EGL_SUCCESS)
    {
        EGL_LOG_ERROR("Fail to init rfm69 PM component. Result: %s", EGL_RESULT(result));
        return result;
    }

    result = egl_itf_init(rfm->iface);
    if(result != EGL_SUCCESS)
    {
        EGL_LOG_ERROR("Fail to init rfm69 iface component. Result: %s", EGL_RESULT(result));
        return result;
    }

    result = egl_pio_init(rfm->dio0);
    if(result != EGL_SUCCESS)
    {
        EGL_LOG_ERROR("Fail to init rfm69 DIO0 component. Result: %s", EGL_RESULT(result));
        return result;
    }

    result = egl_pio_init(rfm->dio1);
    if(result != EGL_SUCCESS)
    {
        EGL_LOG_ERROR("Fail to init rfm69 DIO1 component. Result: %s", EGL_RESULT(result));
        return result;
    }

    result = egl_pio_init(rfm->dio2);
    if(result != EGL_SUCCESS)
    {
        EGL_LOG_ERROR("Fail to init rfm69 DIO2 component. Result: %s", EGL_RESULT(result));
        return result;
    }

    result = egl_pio_init(rfm->dio3);
    if(result != EGL_SUCCESS)
    {
        EGL_LOG_ERROR("Fail to init rfm69 DIO3 component. Result: %s", EGL_RESULT(result));
        return result;
    }

    result = egl_pio_init(rfm->dio4);
    if(result != EGL_SUCCESS)
    {
        EGL_LOG_ERROR("Fail to init rfm69 DIO4 component. Result: %s", EGL_RESULT(result));
        return result;
    }

    result = egl_pio_init(rfm->dio5);
    if(result != EGL_SUCCESS)
    {
        EGL_LOG_ERROR("Fail to init rfm69 DIO5 component. Result: %s", EGL_RESULT(result));
        return result;
    }

    result = egl_pm_poweron(rfm->pm);
    if(result != EGL_SUCCESS)
    {
        EGL_LOG_ERROR("Fail to poweron rfm69. Result: %s", EGL_RESULT(result));
        return result;
    }

    result = egl_pm_reset(rfm->pm);
    if(result != EGL_SUCCESS)
    {
        EGL_LOG_ERROR("Fail to reset rfm69. Result: %s", EGL_RESULT(result));
        return result;
    }

    result = egl_clock_init(rfm->clock, 0);
    if(result != EGL_SUCCESS)
    {
        EGL_LOG_ERROR("Fail to init clock rfm69. Result: %s", EGL_RESULT(result));
        return result;
    }

    return result;
}

egl_result_t egl_rfm69_init(egl_rfm69_t *rfm)
{
    egl_result_t result;

    result = egl_rfm69_hw_init(rfm);
    if(result != EGL_SUCCESS)
    {
        EGL_LOG_ERROR("Failt to init rfm69 hardware. Result: %s", EGL_RESULT(result));
        return result;
    }

    return result;
}

egl_result_t egl_rfm69_read_byte(egl_rfm69_t *rfm, uint8_t addr, uint8_t *value)
{
    egl_result_t result;
    size_t len = sizeof(*value);

    result = egl_itf_read_addr(rfm->iface, (uint32_t)addr, value, &len);
    EGL_RESULT_CHECK(result);
    EGL_ASSERT_CHECK(len == sizeof(*value), EGL_FAIL);

    return result;
}

egl_result_t egl_rfm69_write_byte(egl_rfm69_t *rfm, uint8_t addr, uint8_t value)
{
    egl_result_t result;
    size_t len = sizeof(value);

    result = egl_itf_write_addr(rfm->iface, (uint32_t)addr, &value, &len);
    EGL_RESULT_CHECK(result);
    EGL_ASSERT_CHECK(len == sizeof(value), EGL_FAIL);

    return result;
}

egl_result_t egl_rfm69_write_burst(egl_rfm69_t *rfm, uint8_t addr, void *data, size_t len)
{
    return egl_itf_write_addr(rfm->iface, (uint32_t)addr, data, &len);
}

egl_result_t egl_rfm69_read_burst(egl_rfm69_t *rfm, uint8_t addr, void *data, size_t len)
{
    return egl_itf_read_addr(rfm->iface, (uint32_t)addr, data, &len);
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
    uint8_t mode_val = ((uint8_t)mode << EGL_RFM69_MODE_SHIFT) & EGL_RFM69_MODE_MASK;
    return egl_rfm69_write_byte(rfm, EGL_RFM69_REG_MODE, mode_val);
}

egl_result_t egl_rfm69_mode_get(egl_rfm69_t *rfm, egl_rfm69_mode_t *mode)
{
    egl_result_t result;
    uint8_t mode_val;

    result = egl_rfm69_read_byte(rfm, EGL_RFM69_REG_MODE, &mode_val);
    EGL_RESULT_CHECK(result);

    *mode = (egl_rfm69_mode_t)((mode_val & EGL_RFM69_MODE_MASK) >> EGL_RFM69_MODE_SHIFT);

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
    *frequency |= freq_val[3];
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

egl_result_t egl_rfm69_ook_peak_thresh_dec_set(egl_rfm69_t *rfm, egl_rfm_ook_thresh_dec_t dec)
{
    egl_result_t result;
    egl_rfm69_reg_ook_peak_t regval;

    result = egl_rfm69_read_byte(rfm, EGL_RFM69_REG_OOK_PEAK, &regval.raw);
    EGL_RESULT_CHECK(result);

    regval.bitfield.ook_peak_thresh_dec = dec;

    return egl_rfm69_write_byte(rfm, EGL_RFM69_REG_OOK_PEAK, regval.raw);
}

egl_result_t egl_rfm69_ook_peak_thresh_dec_get(egl_rfm69_t *rfm, egl_rfm_ook_thresh_dec_t *dec)
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
    egl_rfm69_reg_afc_fet_t regval;

    result = egl_rfm69_read_byte(rfm, EGL_RFM69_REG_AFC_FEI, &regval.raw);
    EGL_RESULT_CHECK(result);

    regval.bitfield.afc_start = true;

    return egl_rfm69_write_byte(rfm, EGL_RFM69_REG_AFC_FEI, regval.raw);
}

egl_result_t egl_rfm69_afc_clear(egl_rfm69_t *rfm)
{
    egl_result_t result;
    egl_rfm69_reg_afc_fet_t regval;

    result = egl_rfm69_read_byte(rfm, EGL_RFM69_REG_AFC_FEI, &regval.raw);
    EGL_RESULT_CHECK(result);

    regval.bitfield.afc_clear = true;

    return egl_rfm69_write_byte(rfm, EGL_RFM69_REG_AFC_FEI, regval.raw);
}

egl_result_t egl_rfm69_afc_auto_start_set(egl_rfm69_t *rfm, bool state)
{
    egl_result_t result;
    egl_rfm69_reg_afc_fet_t regval;

    result = egl_rfm69_read_byte(rfm, EGL_RFM69_REG_AFC_FEI, &regval.raw);
    EGL_RESULT_CHECK(result);

    regval.bitfield.afc_auto_on = state;

    return egl_rfm69_write_byte(rfm, EGL_RFM69_REG_AFC_FEI, regval.raw);
}

egl_result_t egl_rfm69_afc_auto_start_get(egl_rfm69_t *rfm, bool *state)
{
    egl_result_t result;
    egl_rfm69_reg_afc_fet_t regval;

    result = egl_rfm69_read_byte(rfm, EGL_RFM69_REG_AFC_FEI, &regval.raw);
    EGL_RESULT_CHECK(result);

    *state = regval.bitfield.afc_auto_on;

    return result;
}

egl_result_t egl_rfm69_afc_auto_clear_set(egl_rfm69_t *rfm, bool state)
{
    egl_result_t result;
    egl_rfm69_reg_afc_fet_t regval;

    result = egl_rfm69_read_byte(rfm, EGL_RFM69_REG_AFC_FEI, &regval.raw);
    EGL_RESULT_CHECK(result);

    regval.bitfield.afc_auto_clear_on = state;

    return egl_rfm69_write_byte(rfm, EGL_RFM69_REG_AFC_FEI, regval.raw);
}

egl_result_t egl_rfm69_afc_auto_clear_get(egl_rfm69_t *rfm, bool *state)
{
    egl_result_t result;
    egl_rfm69_reg_afc_fet_t regval;

    result = egl_rfm69_read_byte(rfm, EGL_RFM69_REG_AFC_FEI, &regval.raw);
    EGL_RESULT_CHECK(result);

    *state = regval.bitfield.afc_auto_clear_on;

    return result;
}

egl_result_t egl_rfm69_afc_state_get(egl_rfm69_t *rfm, bool *state)
{
    egl_result_t result;
    egl_rfm69_reg_afc_fet_t regval;

    result = egl_rfm69_read_byte(rfm, EGL_RFM69_REG_AFC_FEI, &regval.raw);
    EGL_RESULT_CHECK(result);

    *state = regval.bitfield.afc_done;

    return result;
}

egl_result_t egl_rfm69_fei_start(egl_rfm69_t *rfm)
{
    egl_result_t result;
    egl_rfm69_reg_afc_fet_t regval;

    result = egl_rfm69_read_byte(rfm, EGL_RFM69_REG_AFC_FEI, &regval.raw);
    EGL_RESULT_CHECK(result);

    regval.bitfield.fei_start = true;

    return egl_rfm69_write_byte(rfm, EGL_RFM69_REG_AFC_FEI, regval.raw);
}

egl_result_t egl_rfm69_fei_state_get(egl_rfm69_t *rfm, bool *state)
{
    egl_result_t result;
    egl_rfm69_reg_afc_fet_t regval;

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
    return egl_rfm69_read_burst(rfm, EGL_RFM69_REG_IRQ_FALGS1, &flags->raw, sizeof(*flags));
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

