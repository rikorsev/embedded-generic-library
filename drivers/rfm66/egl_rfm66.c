#include "egl_rfm66.h"
#include "egl_log.h"
#include "egl_util.h"

#define EGL_RFM66_FSTEP_COEF                (524288U)

#pragma pack(push, 1)

typedef union
{
    uint8_t raw;
    struct
    {
        uint8_t mode : 3;
        uint8_t modulation_shaping : 2;
        uint8_t modulation_type : 2;
    }bitfield;
}egl_rfm66_reg_op_mode_t;

typedef union
{
    uint8_t raw;
    struct
    {
        uint8_t pa_power : 4;
        uint8_t reserved : 3;
        uint8_t pa_select : 1;
    }bitfield;
}egl_rfm66_reg_pa_config_t;

typedef union
{
    uint8_t raw;
    struct
    {
        uint8_t pa_ramp : 4;
        uint8_t low_pn_tx_pll_off : 1;
    }bitfield;
}egl_rfm66_reg_pa_ramp_t;

typedef union
{
    uint8_t raw;
    struct
    {
        uint8_t ocp_trim : 5;
        uint8_t ocp_on : 1;
    }bitfield;
}egl_rfm66_reg_ocp_t;

typedef union
{
    uint8_t raw;
    struct
    {
        uint8_t lna_boost : 2;
        uint8_t reserved : 3;
        uint8_t lna_gain : 3;
    }bitfield;
}egl_rfm66_reg_lna_t;

typedef union
{
    uint8_t raw;
    struct
    {
        uint8_t rx_trigger : 3;
        uint8_t agc_auto_on : 1;
        uint8_t afc_auto_on : 1;
        uint8_t restart_rx_with_pll_lock : 1;
        uint8_t restart_rx_wo_pll_lock : 1;
        uint8_t restart_rx_on_collision : 1;
    }bitfield;
}egl_rfm66_reg_rx_config_t;

typedef union
{
    uint8_t raw;
    struct
    {
        uint8_t rssi_smoothing : 3;
        uint8_t rssi_offset : 4;
        uint8_t rssi_offset_sign : 1;
    }bitfield;
}egl_rfm66_reg_rssi_config_t;

typedef union
{
    uint8_t raw;
    struct
    {
        uint8_t bw_exp : 3;
        uint8_t bw_mant : 2;
    }bitfield;
}egl_rfm66_reg_bw_t;

typedef union
{
    uint8_t raw;
    struct
    {
        uint8_t ook_peak_thresh_step : 3;
        uint8_t ook_thresh_type : 2;
        uint8_t bit_sync_on : 1;
    }bitfield;
}egl_rfm66_reg_ook_peak_t;

typedef union
{
    uint8_t raw;
    struct
    {
        uint8_t ook_average_thresh_filt : 2;
        uint8_t ook_average_offset : 2;
        uint8_t reserved : 1;
        uint8_t ook_peak_thresh_dec : 3;
    }bitfield;
}egl_rfm66_reg_ook_avg_t;
#pragma pack(pop)

static egl_result_t egl_rfm66_hw_init(egl_rfm66_t *rfm)
{
    egl_result_t result;

    result = egl_pm_init(rfm->pm);
    EGL_RESULT_CHECK(result);

    result = egl_itf_init(rfm->iface);
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

    result = egl_clock_init(rfm->clock, 0);
    EGL_RESULT_CHECK(result);

    return result;
}

egl_result_t egl_rfm66_init(egl_rfm66_t *rfm)
{
    egl_result_t result;

    result = egl_rfm66_hw_init(rfm);
    EGL_RESULT_CHECK(result);

    return result;
}

egl_result_t egl_rfm66_read_byte(egl_rfm66_t *rfm, uint8_t addr, uint8_t *value)
{
    egl_result_t result;
    size_t len = sizeof(*value);

    result = egl_itf_read_addr(rfm->iface, (uint32_t)addr, value, &len);
    EGL_RESULT_CHECK(result);
    EGL_ASSERT_CHECK(len == sizeof(*value), EGL_FAIL);

    return result;
}

egl_result_t egl_rfm66_write_byte(egl_rfm66_t *rfm, uint8_t addr, uint8_t value)
{
    egl_result_t result;
    size_t len = sizeof(value);

    result = egl_itf_write_addr(rfm->iface, (uint32_t)addr, &value, &len);
    EGL_RESULT_CHECK(result);
    EGL_ASSERT_CHECK(len == sizeof(value), EGL_FAIL);

    return result;
}

egl_result_t egl_rfm66_write_burst(egl_rfm66_t *rfm, uint8_t addr, void *data, size_t len)
{
    return egl_itf_write_addr(rfm->iface, (uint32_t)addr, data, &len);
}

egl_result_t egl_rfm66_read_burst(egl_rfm66_t *rfm, uint8_t addr, void *data, size_t len)
{
    return egl_itf_read_addr(rfm->iface, (uint32_t)addr, data, &len);
}

egl_result_t egl_rfm66_version_get(egl_rfm66_t *rfm, uint8_t *version)
{
    return egl_rfm66_read_byte(rfm, EGL_RFM66_REG_VERSION, version);
}

egl_result_t egl_rfm66_mode_set(egl_rfm66_t *rfm, egl_rfm66_mode_t mode)
{
    egl_result_t result;
    egl_rfm66_reg_op_mode_t regval;

    result = egl_rfm66_read_byte(rfm, EGL_RFM66_REG_MODE, &regval.raw);
    EGL_RESULT_CHECK(result);

    regval.bitfield.mode = mode;

    return egl_rfm66_write_byte(rfm, EGL_RFM66_REG_MODE, regval.raw);
}

egl_result_t egl_rfm66_mode_get(egl_rfm66_t *rfm, egl_rfm66_mode_t *mode)
{
    egl_result_t result;
    egl_rfm66_reg_op_mode_t regval;

    result = egl_rfm66_read_byte(rfm, EGL_RFM66_REG_MODE, &regval.raw);
    EGL_RESULT_CHECK(result);

    *mode = regval.bitfield.mode;

    return result;
}

egl_result_t egl_rfm66_modulation_shaping_set(egl_rfm66_t *rfm, egl_rfm66_modulation_shaping_t modsh)
{
    egl_result_t result;
    egl_rfm66_reg_op_mode_t regval;

    result = egl_rfm66_read_byte(rfm, EGL_RFM66_REG_MODE, &regval.raw);
    EGL_RESULT_CHECK(result);

    regval.bitfield.modulation_shaping = modsh;

    return egl_rfm66_write_byte(rfm, EGL_RFM66_REG_MODE, regval.raw);
}

egl_result_t egl_rfm66_modulation_shaping_get(egl_rfm66_t *rfm, egl_rfm66_modulation_shaping_t *modsh)
{
    egl_result_t result;
    egl_rfm66_reg_op_mode_t regval;

    result = egl_rfm66_read_byte(rfm, EGL_RFM66_REG_MODE, &regval.raw);
    EGL_RESULT_CHECK(result);

    *modsh = regval.bitfield.modulation_shaping;

    return result;
}

egl_result_t egl_rfm66_modulation_type_set(egl_rfm66_t *rfm, egl_rfm66_modulation_type_t modtype)
{
    egl_result_t result;
    egl_rfm66_reg_op_mode_t regval;

    result = egl_rfm66_read_byte(rfm, EGL_RFM66_REG_MODE, &regval.raw);
    EGL_RESULT_CHECK(result);

    regval.bitfield.modulation_type = modtype;

    return egl_rfm66_write_byte(rfm, EGL_RFM66_REG_MODE, regval.raw);
}

egl_result_t egl_rfm66_modulation_type_get(egl_rfm66_t *rfm, egl_rfm66_modulation_type_t *modtype)
{
    egl_result_t result;
    egl_rfm66_reg_op_mode_t regval;

    result = egl_rfm66_read_byte(rfm, EGL_RFM66_REG_MODE, &regval.raw);
    EGL_RESULT_CHECK(result);

    *modtype = regval.bitfield.modulation_type;

    return result;
}

egl_result_t egl_rfm66_bitrate_set(egl_rfm66_t *rfm, uint32_t kbs)
{
    /* Calculate bitrate value */
    uint16_t raw = egl_swap16((uint16_t)(egl_clock_get(rfm->clock) / kbs));

    /* Write bautrate value */
    return egl_rfm66_write_burst(rfm, EGL_RFM66_REG_BITRATE_MSB, (uint8_t *)&raw, sizeof(raw));
}

egl_result_t egl_rfm66_bitrate_get(egl_rfm66_t *rfm, uint32_t *kbs)
{
    egl_result_t result;
    uint16_t raw;

    result = egl_rfm66_read_burst(rfm, EGL_RFM66_REG_BITRATE_MSB, &raw, sizeof(raw));
    EGL_RESULT_CHECK(result);

    /* Calculate bitrate in bits per second */
    *kbs = egl_clock_get(rfm->clock) / egl_swap16(raw);

    return result;
}

egl_result_t egl_rfm66_deviation_set(egl_rfm66_t *rfm, uint32_t hz)
{
    uint16_t raw;

    raw = egl_swap16((uint16_t)(((uint64_t)hz * EGL_RFM66_FSTEP_COEF) / egl_clock_get(rfm->clock)));

    return egl_rfm66_write_burst(rfm, EGL_RFM66_REG_DEVIATION_MSB, (uint8_t *)&raw, sizeof(raw));
}

egl_result_t egl_rfm66_deviation_get(egl_rfm66_t *rfm, uint32_t *hz)
{
    egl_result_t result;
    uint16_t raw;

    result = egl_rfm66_read_burst(rfm, EGL_RFM66_REG_DEVIATION_MSB, &raw, sizeof(raw));
    EGL_RESULT_CHECK(result);

    /* Calculate bitrate in bits per second */
    *hz = (uint32_t)(((uint64_t)egl_swap16(raw) * egl_clock_get(rfm->clock)) / EGL_RFM66_FSTEP_COEF);

    return result;
}

egl_result_t egl_rfm66_frequency_set(egl_rfm66_t *rfm, uint32_t hz)
{
    uint8_t raw[3];
    hz = (((uint64_t)hz * EGL_RFM66_FSTEP_COEF) / egl_clock_get(rfm->clock));

    raw[0] = hz >> 16 & 0xFF;
    raw[1] = hz >> 8 & 0xFF;
    raw[2] = hz & 0xFF;

    return egl_rfm66_write_burst(rfm, EGL_RFM66_REG_FREQUENCY_MSB, raw, sizeof(raw));
}

egl_result_t egl_rfm66_frequency_get(egl_rfm66_t *rfm, uint32_t *hz)
{
    egl_result_t result;
    uint8_t raw[3];

    result = egl_rfm66_read_burst(rfm, EGL_RFM66_REG_FREQUENCY_MSB, &raw, sizeof(raw));
    EGL_RESULT_CHECK(result);

    *hz = 0;
    *hz |= raw[0] << 16;
    *hz |= raw[1] << 8;
    *hz |= raw[3];
    *hz = ((uint64_t)(*hz) * egl_clock_get(rfm->clock)) / EGL_RFM66_FSTEP_COEF;

    return result;
}

egl_result_t egl_rfm66_pa_power_set(egl_rfm66_t *rfm, uint8_t power)
{
    EGL_ASSERT_CHECK(power <= EGL_RFM66_RAW_PA_POWER_MAX, EGL_OUT_OF_BOUNDARY);

    egl_result_t result;
    egl_rfm66_reg_pa_config_t regval;

    result = egl_rfm66_read_byte(rfm, EGL_RFM66_REG_PA_CONFIG, &regval.raw);
    EGL_RESULT_CHECK(result);

    regval.bitfield.pa_power = power;

    return egl_rfm66_write_byte(rfm, EGL_RFM66_REG_PA_CONFIG, regval.raw);
}

egl_result_t egl_rfm66_pa_power_get(egl_rfm66_t *rfm, uint8_t *power)
{
    egl_result_t result;
    egl_rfm66_reg_pa_config_t regval;

    result = egl_rfm66_read_byte(rfm, EGL_RFM66_REG_PA_CONFIG, &regval.raw);
    EGL_RESULT_CHECK(result);

    *power = regval.bitfield.pa_power;

    return result;
}

egl_result_t egl_rfm66_pa_select_set(egl_rfm66_t *rfm, egl_rfm66_pa_select_t select)
{
    egl_result_t result;
    egl_rfm66_reg_pa_config_t regval;

    result = egl_rfm66_read_byte(rfm, EGL_RFM66_REG_PA_CONFIG, &regval.raw);
    EGL_RESULT_CHECK(result);

    regval.bitfield.pa_select = select;

    return egl_rfm66_write_byte(rfm, EGL_RFM66_REG_PA_CONFIG, regval.raw);
}

egl_result_t egl_rfm66_pa_select_get(egl_rfm66_t *rfm, egl_rfm66_pa_select_t *select)
{
    egl_result_t result;
    egl_rfm66_reg_pa_config_t regval;

    result = egl_rfm66_read_byte(rfm, EGL_RFM66_REG_PA_CONFIG, &regval.raw);
    EGL_RESULT_CHECK(result);

    *select = regval.bitfield.pa_select;

    return result;
}

egl_result_t egl_rfm66_pa_ramp_set(egl_rfm66_t *rfm, egl_rfm66_power_ramp_t ramp)
{
    egl_result_t result;
    egl_rfm66_reg_pa_ramp_t regval;

    result = egl_rfm66_read_byte(rfm, EGL_RFM66_REG_PA_RAMP, &regval.raw);
    EGL_RESULT_CHECK(result);

    regval.bitfield.pa_ramp = ramp;

    return egl_rfm66_write_byte(rfm, EGL_RFM66_REG_PA_RAMP, regval.raw);
}

egl_result_t egl_rfm66_pa_ramp_get(egl_rfm66_t *rfm, egl_rfm66_power_ramp_t *ramp)
{
    egl_result_t result;
    egl_rfm66_reg_pa_ramp_t regval;

    result = egl_rfm66_read_byte(rfm, EGL_RFM66_REG_PA_RAMP, &regval.raw);
    EGL_RESULT_CHECK(result);

    *ramp = regval.bitfield.pa_ramp;

    return result;
}

egl_result_t egl_rfm66_low_pn_tx_state_set(egl_rfm66_t *rfm, bool state)
{
    egl_result_t result;
    egl_rfm66_reg_pa_ramp_t regval;

    result = egl_rfm66_read_byte(rfm, EGL_RFM66_REG_PA_RAMP, &regval.raw);
    EGL_RESULT_CHECK(result);

    regval.bitfield.low_pn_tx_pll_off = !state;

    return egl_rfm66_write_byte(rfm, EGL_RFM66_REG_PA_RAMP, regval.raw);
}

egl_result_t egl_rfm66_low_pn_tx_state_get(egl_rfm66_t *rfm, bool *state)
{
    egl_result_t result;
    egl_rfm66_reg_pa_ramp_t regval;

    result = egl_rfm66_read_byte(rfm, EGL_RFM66_REG_PA_RAMP, &regval.raw);
    EGL_RESULT_CHECK(result);

    *state = !regval.bitfield.low_pn_tx_pll_off;

    return result;
}

egl_result_t egl_rfm66_ocp_trim_set(egl_rfm66_t *rfm, uint8_t ma)
{
#define EGL_RFM66_OCP_TRIM_THRESH_1_MA (120U)
#define EGL_RFM66_OCP_TRIM_THRESH_2_MA (240U)
#define EGL_RFM66_OCP_TRIM_RAW_MAX     (0x1F)

    egl_result_t result;
    egl_rfm66_reg_ocp_t regval;
    uint8_t ocp_trim_raw;

    result = egl_rfm66_read_byte(rfm, EGL_RFM66_REG_OCP, &regval.raw);
    EGL_RESULT_CHECK(result);

    if(ma <=  EGL_RFM66_OCP_TRIM_THRESH_1_MA)
    {
        ocp_trim_raw = (ma - 45) / 5;
    }
    else if(ma <= EGL_RFM66_OCP_TRIM_THRESH_2_MA)
    {
        ocp_trim_raw = (ma + 30) / 10;
    }
    else
    {
        ocp_trim_raw = EGL_RFM66_OCP_TRIM_RAW_MAX;
    }

    regval.bitfield.ocp_trim = ocp_trim_raw;

    return egl_rfm66_write_byte(rfm, EGL_RFM66_REG_OCP, regval.raw);
}

egl_result_t egl_rfm66_ocp_trim_get(egl_rfm66_t *rfm, uint8_t *ma)
{
#define EGL_RFM66_OCP_TRIM_RAW_THRESH_1 (15U)
#define EGL_RFM66_OCP_TRIM_RAW_THRESH_2 (27U)
#define EGL_RFM66_OCP_TRIM_MAX_MA       (240U)

    egl_result_t result;
    egl_rfm66_reg_ocp_t regval;

    result = egl_rfm66_read_byte(rfm, EGL_RFM66_REG_OCP, &regval.raw);
    EGL_RESULT_CHECK(result);

    if(regval.bitfield.ocp_trim <= EGL_RFM66_OCP_TRIM_RAW_THRESH_1)
    {
        *ma = (regval.bitfield.ocp_trim * 5) + 45;
    }
    else if(regval.bitfield.ocp_trim <= EGL_RFM66_OCP_TRIM_RAW_THRESH_2)
    {
        *ma = (regval.bitfield.ocp_trim * 10) - 30;
    }
    else
    {
        *ma = EGL_RFM66_OCP_TRIM_MAX_MA;
    }

    return result;
}

egl_result_t egl_rfm66_ocp_state_set(egl_rfm66_t *rfm, bool state)
{
    egl_result_t result;
    egl_rfm66_reg_ocp_t regval;

    result = egl_rfm66_read_byte(rfm, EGL_RFM66_REG_OCP, &regval.raw);
    EGL_RESULT_CHECK(result);

    regval.bitfield.ocp_on = state;

    return egl_rfm66_write_byte(rfm, EGL_RFM66_REG_OCP, regval.raw);
}

egl_result_t egl_rfm66_ocp_state_get(egl_rfm66_t *rfm, bool *state)
{
    egl_result_t result;
    egl_rfm66_reg_ocp_t regval;

    result = egl_rfm66_read_byte(rfm, EGL_RFM66_REG_OCP, &regval.raw);
    EGL_RESULT_CHECK(result);

    *state = regval.bitfield.ocp_on;

    return result;
}

egl_result_t egl_rfm66_lna_boost_state_set(egl_rfm66_t *rfm, egl_rfm66_lna_boost_t state)
{
    egl_result_t result;
    egl_rfm66_reg_lna_t regval;

    result = egl_rfm66_read_byte(rfm, EGL_RFM66_REG_LNA, &regval.raw);
    EGL_RESULT_CHECK(result);

    regval.bitfield.lna_boost = state;

    return egl_rfm66_write_byte(rfm, EGL_RFM66_REG_LNA, regval.raw);
}

egl_result_t egl_rfm66_lna_boost_state_get(egl_rfm66_t *rfm, egl_rfm66_lna_boost_t *state)
{
    egl_result_t result;
    egl_rfm66_reg_lna_t regval;

    result = egl_rfm66_read_byte(rfm, EGL_RFM66_REG_LNA, &regval.raw);
    EGL_RESULT_CHECK(result);

    *state = regval.bitfield.lna_boost;

    return result;
}

egl_result_t egl_rfm66_lna_gain_set(egl_rfm66_t *rfm, egl_rfm66_lna_gain_t gain)
{
    egl_result_t result;
    egl_rfm66_reg_lna_t regval;

    result = egl_rfm66_read_byte(rfm, EGL_RFM66_REG_LNA, &regval.raw);
    EGL_RESULT_CHECK(result);

    regval.bitfield.lna_gain = gain;

    return egl_rfm66_write_byte(rfm, EGL_RFM66_REG_LNA, regval.raw);
}

egl_result_t egl_rfm66_lna_gain_get(egl_rfm66_t *rfm, egl_rfm66_lna_gain_t *gain)
{
    egl_result_t result;
    egl_rfm66_reg_lna_t regval;

    result = egl_rfm66_read_byte(rfm, EGL_RFM66_REG_LNA, &regval.raw);
    EGL_RESULT_CHECK(result);

    *gain = regval.bitfield.lna_gain;

    return result;
}

egl_result_t egl_rfm66_rx_trigger_set(egl_rfm66_t *rfm, egl_rfm66_rx_trigger_t trigger)
{
    egl_result_t result;
    egl_rfm66_reg_rx_config_t regval;

    result = egl_rfm66_read_byte(rfm, EGL_RFM66_REG_RX_CONFIG, &regval.raw);
    EGL_RESULT_CHECK(result);

    regval.bitfield.rx_trigger = trigger;

    return egl_rfm66_write_byte(rfm, EGL_RFM66_REG_RX_CONFIG, regval.raw);
}

egl_result_t egl_rfm66_rx_trigger_get(egl_rfm66_t *rfm, egl_rfm66_rx_trigger_t *trigger)
{
    egl_result_t result;
    egl_rfm66_reg_rx_config_t regval;

    result = egl_rfm66_read_byte(rfm, EGL_RFM66_REG_RX_CONFIG, &regval.raw);
    EGL_RESULT_CHECK(result);

    *trigger = regval.bitfield.rx_trigger;

    return result;
}

egl_result_t egl_rfm66_auto_agc_state_set(egl_rfm66_t *rfm, bool state)
{
    egl_result_t result;
    egl_rfm66_reg_rx_config_t regval;

    result = egl_rfm66_read_byte(rfm, EGL_RFM66_REG_RX_CONFIG, &regval.raw);
    EGL_RESULT_CHECK(result);

    regval.bitfield.agc_auto_on = state;

    return egl_rfm66_write_byte(rfm, EGL_RFM66_REG_RX_CONFIG, regval.raw);
}

egl_result_t egl_rfm66_auto_agc_state_get(egl_rfm66_t *rfm, bool *state)
{
    egl_result_t result;
    egl_rfm66_reg_rx_config_t regval;

    result = egl_rfm66_read_byte(rfm, EGL_RFM66_REG_RX_CONFIG, &regval.raw);
    EGL_RESULT_CHECK(result);

    *state = regval.bitfield.agc_auto_on;

    return result;
}

egl_result_t egl_rfm66_auto_afc_state_set(egl_rfm66_t *rfm, bool state)
{
    egl_result_t result;
    egl_rfm66_reg_rx_config_t regval;

    result = egl_rfm66_read_byte(rfm, EGL_RFM66_REG_RX_CONFIG, &regval.raw);
    EGL_RESULT_CHECK(result);

    regval.bitfield.afc_auto_on = state;

    return egl_rfm66_write_byte(rfm, EGL_RFM66_REG_RX_CONFIG, regval.raw);
}

egl_result_t egl_rfm66_auto_afc_state_get(egl_rfm66_t *rfm, bool *state)
{
    egl_result_t result;
    egl_rfm66_reg_rx_config_t regval;

    result = egl_rfm66_read_byte(rfm, EGL_RFM66_REG_RX_CONFIG, &regval.raw);
    EGL_RESULT_CHECK(result);

    *state = regval.bitfield.afc_auto_on;

    return result;
}

egl_result_t egl_rfm66_restart_rx_with_pll_lock_state_set(egl_rfm66_t *rfm, bool state)
{
    egl_result_t result;
    egl_rfm66_reg_rx_config_t regval;

    result = egl_rfm66_read_byte(rfm, EGL_RFM66_REG_RX_CONFIG, &regval.raw);
    EGL_RESULT_CHECK(result);

    regval.bitfield.restart_rx_with_pll_lock = true;

    return egl_rfm66_write_byte(rfm, EGL_RFM66_REG_RX_CONFIG, regval.raw);
}

egl_result_t egl_rfm66_restart_rx_with_pll_lock_state_get(egl_rfm66_t *rfm, bool *state)
{
    egl_result_t result;
    egl_rfm66_reg_rx_config_t regval;

    result = egl_rfm66_read_byte(rfm, EGL_RFM66_REG_RX_CONFIG, &regval.raw);
    EGL_RESULT_CHECK(result);

    *state = regval.bitfield.restart_rx_with_pll_lock;

    return result;
}

egl_result_t egl_rfm66_restart_rx_wo_pll_lock_state_set(egl_rfm66_t *rfm, bool state)
{
    egl_result_t result;
    egl_rfm66_reg_rx_config_t regval;

    result = egl_rfm66_read_byte(rfm, EGL_RFM66_REG_RX_CONFIG, &regval.raw);
    EGL_RESULT_CHECK(result);

    regval.bitfield.restart_rx_wo_pll_lock = state;

    return egl_rfm66_write_byte(rfm, EGL_RFM66_REG_RX_CONFIG, regval.raw);
}

egl_result_t egl_rfm66_restart_rx_wo_pll_lock_state_get(egl_rfm66_t *rfm, bool *state)
{
    egl_result_t result;
    egl_rfm66_reg_rx_config_t regval;

    result = egl_rfm66_read_byte(rfm, EGL_RFM66_REG_RX_CONFIG, &regval.raw);
    EGL_RESULT_CHECK(result);

    *state = regval.bitfield.restart_rx_wo_pll_lock;

    return result;
}

egl_result_t egl_rfm66_restart_rx_on_collision_state_set(egl_rfm66_t *rfm, bool state)
{
    egl_result_t result;
    egl_rfm66_reg_rx_config_t regval;

    result = egl_rfm66_read_byte(rfm, EGL_RFM66_REG_RX_CONFIG, &regval.raw);
    EGL_RESULT_CHECK(result);

    regval.bitfield.restart_rx_on_collision = state;

    return egl_rfm66_write_byte(rfm, EGL_RFM66_REG_RX_CONFIG, regval.raw);
}

egl_result_t egl_rfm66_restart_rx_on_collision_state_get(egl_rfm66_t *rfm, bool *state)
{
    egl_result_t result;
    egl_rfm66_reg_rx_config_t regval;

    result = egl_rfm66_read_byte(rfm, EGL_RFM66_REG_RX_CONFIG, &regval.raw);
    EGL_RESULT_CHECK(result);

    *state = regval.bitfield.restart_rx_on_collision;

    return result;
}

egl_result_t egl_rfm66_rssi_offset_set(egl_rfm66_t *rfm, int8_t offset)
{
#define EGL_RFM66_RSSI_OFFSET_MIN           (-16)
#define EGL_RFM66_RSSI_OFFSET_MAX           (15)
#define EGL_RFM66_RSSI_OFFSET_MASK          (0x07)
#define EGL_RFM66_RSSI_OFFSET_SHIFT         (3)

    egl_result_t result;
    egl_rfm66_reg_rssi_config_t regval;

    EGL_ASSERT_CHECK(offset >= EGL_RFM66_RSSI_OFFSET_MIN &&
                     offset <= EGL_RFM66_RSSI_OFFSET_MAX,
                     EGL_OUT_OF_BOUNDARY);

    result = egl_rfm66_read_byte(rfm, EGL_RFM66_REG_RSSI_CONFIG, &regval.raw);
    EGL_RESULT_CHECK(result);

    regval.raw &= EGL_RFM66_RSSI_OFFSET_MASK;
    regval.raw |= offset << EGL_RFM66_RSSI_OFFSET_SHIFT;

    return egl_rfm66_write_byte(rfm, EGL_RFM66_REG_RSSI_CONFIG, regval.raw);
}

egl_result_t egl_rfm66_rssi_offset_get(egl_rfm66_t *rfm, int8_t *offset)
{
#define EGL_RFM66_RSSI_OFFSET_SHIFT         (3)

    egl_result_t result;
    egl_rfm66_reg_rssi_config_t regval;

    result = egl_rfm66_read_byte(rfm, EGL_RFM66_REG_RSSI_CONFIG, &regval.raw);
    EGL_RESULT_CHECK(result);

    *offset = (int8_t)regval.raw >> EGL_RFM66_RSSI_OFFSET_SHIFT;

    return result;
}

egl_result_t egl_rfm66_rssi_smoothing_set(egl_rfm66_t *rfm, egl_rfm66_rssi_smoothing_t smoothing)
{
    egl_result_t result;
    egl_rfm66_reg_rssi_config_t regval;

    result = egl_rfm66_read_byte(rfm, EGL_RFM66_REG_RSSI_CONFIG, &regval.raw);
    EGL_RESULT_CHECK(result);

    regval.bitfield.rssi_smoothing = smoothing;

    return egl_rfm66_write_byte(rfm, EGL_RFM66_REG_RSSI_CONFIG, regval.raw);
}

egl_result_t egl_rfm66_rssi_smoothing_get(egl_rfm66_t *rfm, egl_rfm66_rssi_smoothing_t *smoothing)
{
    egl_result_t result;
    egl_rfm66_reg_rssi_config_t regval;

    result = egl_rfm66_read_byte(rfm, EGL_RFM66_REG_RSSI_CONFIG, &regval.raw);
    EGL_RESULT_CHECK(result);

    *smoothing = regval.bitfield.rssi_smoothing;

    return result;
}

egl_result_t egl_rfm66_rssi_collision_set(egl_rfm66_t *rfm, uint8_t collision)
{
    return egl_rfm66_write_byte(rfm, EGL_RFM66_REG_RSSI_COLLISION, collision);
}

egl_result_t egl_rfm66_rssi_collision_get(egl_rfm66_t *rfm, uint8_t *collision)
{
    return egl_rfm66_read_byte(rfm, EGL_RFM66_REG_RSSI_COLLISION, collision);
}

egl_result_t egl_rfm66_rssi_threshold_set(egl_rfm66_t *rfm, int8_t threshold)
{
    EGL_ASSERT_CHECK(threshold < 0, EGL_OUT_OF_BOUNDARY);

    return egl_rfm66_write_byte(rfm, EGL_RFM66_REG_RSSI_THRESHOLD, (uint8_t)(threshold * (-2)));
}

egl_result_t egl_rfm66_rssi_threshold_get(egl_rfm66_t *rfm, int8_t *threshold)
{
    uint8_t raw;
    egl_result_t result;

    result = egl_rfm66_read_byte(rfm, EGL_RFM66_REG_RSSI_THRESHOLD, &raw);
    EGL_RESULT_CHECK(result);

    *threshold = -(raw / 2);

    return result;
}

egl_result_t egl_rfm66_rssi_get(egl_rfm66_t *rfm, int8_t *rssi)
{
    uint8_t raw;
    egl_result_t result;

    result = egl_rfm66_read_byte(rfm, EGL_RFM66_REG_RSSI_VALUE, &raw);
    EGL_RESULT_CHECK(result);

    *rssi = -raw;

    return result;
}

egl_result_t egl_rfm66_rx_bw_exp_set(egl_rfm66_t *rfm, uint8_t exp)
{
    EGL_ASSERT_CHECK(exp < 8, EGL_OUT_OF_BOUNDARY);

    egl_result_t result;
    egl_rfm66_reg_bw_t regval;

    result = egl_rfm66_read_byte(rfm, EGL_RFM66_REG_RX_BW, &regval.raw);
    EGL_RESULT_CHECK(result);

    regval.bitfield.bw_exp = exp;

    return egl_rfm66_write_byte(rfm, EGL_RFM66_REG_RX_BW, regval.raw);
}

egl_result_t egl_rfm66_rx_bw_exp_get(egl_rfm66_t *rfm, uint8_t *exp)
{
    egl_result_t result;
    egl_rfm66_reg_bw_t regval;

    result = egl_rfm66_read_byte(rfm, EGL_RFM66_REG_RX_BW, &regval.raw);
    EGL_RESULT_CHECK(result);

    *exp = regval.bitfield.bw_exp;

    return result;
}

egl_result_t egl_rfm66_rx_bw_mant_set(egl_rfm66_t *rfm, egl_rfm66_bw_mant_t mant)
{
    egl_result_t result;
    egl_rfm66_reg_bw_t regval;

    result = egl_rfm66_read_byte(rfm, EGL_RFM66_REG_RX_BW, &regval.raw);
    EGL_RESULT_CHECK(result);

    regval.bitfield.bw_mant = mant;

    return egl_rfm66_write_byte(rfm, EGL_RFM66_REG_RX_BW, regval.raw);
}

egl_result_t egl_rfm66_rx_bw_mant_get(egl_rfm66_t *rfm, egl_rfm66_bw_mant_t *mant)
{
    egl_result_t result;
    egl_rfm66_reg_bw_t regval;

    result = egl_rfm66_read_byte(rfm, EGL_RFM66_REG_RX_BW, &regval.raw);
    EGL_RESULT_CHECK(result);

    *mant = regval.bitfield.bw_mant;

    return result;
}

egl_result_t egl_rfm66_afc_bw_exp_set(egl_rfm66_t *rfm, uint8_t exp)
{
    EGL_ASSERT_CHECK(exp < 8, EGL_OUT_OF_BOUNDARY);

    egl_result_t result;
    egl_rfm66_reg_bw_t regval;

    result = egl_rfm66_read_byte(rfm, EGL_RFM66_REG_AFC_BW, &regval.raw);
    EGL_RESULT_CHECK(result);

    regval.bitfield.bw_exp = exp;

    return egl_rfm66_write_byte(rfm, EGL_RFM66_REG_AFC_BW, regval.raw);
}

egl_result_t egl_rfm66_afc_bw_exp_get(egl_rfm66_t *rfm, uint8_t *exp)
{
    egl_result_t result;
    egl_rfm66_reg_bw_t regval;

    result = egl_rfm66_read_byte(rfm, EGL_RFM66_REG_AFC_BW, &regval.raw);
    EGL_RESULT_CHECK(result);

    *exp = regval.bitfield.bw_exp;

    return result;
}

egl_result_t egl_rfm66_afc_bw_mant_set(egl_rfm66_t *rfm, egl_rfm66_bw_mant_t mant)
{
    egl_result_t result;
    egl_rfm66_reg_bw_t regval;

    result = egl_rfm66_read_byte(rfm, EGL_RFM66_REG_AFC_BW, &regval.raw);
    EGL_RESULT_CHECK(result);

    regval.bitfield.bw_mant = mant;

    return egl_rfm66_write_byte(rfm, EGL_RFM66_REG_AFC_BW, regval.raw);
}

egl_result_t egl_rfm66_afc_bw_mant_get(egl_rfm66_t *rfm, egl_rfm66_bw_mant_t *mant)
{
    egl_result_t result;
    egl_rfm66_reg_bw_t regval;

    result = egl_rfm66_read_byte(rfm, EGL_RFM66_REG_AFC_BW, &regval.raw);
    EGL_RESULT_CHECK(result);

    *mant = regval.bitfield.bw_mant;

    return result;
}

egl_result_t egl_rfm66_ook_peak_thresh_step_set(egl_rfm66_t *rfm, egl_rfm66_ook_thresh_step_t step)
{
    egl_result_t result;
    egl_rfm66_reg_ook_peak_t regval;

    result = egl_rfm66_read_byte(rfm, EGL_RFM66_REG_OOK_PEAK, &regval.raw);
    EGL_RESULT_CHECK(result);

    regval.bitfield.ook_peak_thresh_step = step;

    return egl_rfm66_write_byte(rfm, EGL_RFM66_REG_OOK_PEAK, regval.raw);
}

egl_result_t egl_rfm66_ook_peak_thresh_step_get(egl_rfm66_t *rfm, egl_rfm66_ook_thresh_step_t *step)
{
    egl_result_t result;
    egl_rfm66_reg_ook_peak_t regval;

    result = egl_rfm66_read_byte(rfm, EGL_RFM66_REG_OOK_PEAK, &regval.raw);
    EGL_RESULT_CHECK(result);

    *step = regval.bitfield.ook_peak_thresh_step;

    return result;
}

egl_result_t egl_rfm66_ook_thresh_type_set(egl_rfm66_t *rfm, egl_rfm66_ook_thresh_type_t type)
{
    egl_result_t result;
    egl_rfm66_reg_ook_peak_t regval;

    result = egl_rfm66_read_byte(rfm, EGL_RFM66_REG_OOK_PEAK, &regval.raw);
    EGL_RESULT_CHECK(result);

    regval.bitfield.ook_thresh_type = type;

    return egl_rfm66_write_byte(rfm, EGL_RFM66_REG_OOK_PEAK, regval.raw);
}

egl_result_t egl_rfm66_ook_thresh_type_get(egl_rfm66_t *rfm, egl_rfm66_ook_thresh_type_t *type)
{
    egl_result_t result;
    egl_rfm66_reg_ook_peak_t regval;

    result = egl_rfm66_read_byte(rfm, EGL_RFM66_REG_OOK_PEAK, &regval.raw);
    EGL_RESULT_CHECK(result);

    *type = regval.bitfield.ook_thresh_type;

    return result;
}

egl_result_t egl_rfm66_bit_sync_state_set(egl_rfm66_t *rfm, bool state)
{
    egl_result_t result;
    egl_rfm66_reg_ook_peak_t regval;

    result = egl_rfm66_read_byte(rfm, EGL_RFM66_REG_OOK_PEAK, &regval.raw);
    EGL_RESULT_CHECK(result);

    regval.bitfield.bit_sync_on = state;

    return egl_rfm66_write_byte(rfm, EGL_RFM66_REG_OOK_PEAK, regval.raw);
}

egl_result_t egl_rfm66_bit_sync_state_get(egl_rfm66_t *rfm, bool *state)
{
    egl_result_t result;
    egl_rfm66_reg_ook_peak_t regval;

    result = egl_rfm66_read_byte(rfm, EGL_RFM66_REG_OOK_PEAK, &regval.raw);
    EGL_RESULT_CHECK(result);

    *state = regval.bitfield.bit_sync_on;

    return result;
}

egl_result_t egl_rfm66_ook_thresh_fixed_set(egl_rfm66_t *rfm, uint8_t thresh)
{
    return egl_rfm66_write_byte(rfm, EGL_RFM66_REG_OOK_FIX, thresh);
}

egl_result_t egl_rfm66_ook_thresh_fixed_get(egl_rfm66_t *rfm, uint8_t *thresh)
{
    return egl_rfm66_read_byte(rfm, EGL_RFM66_REG_OOK_FIX, thresh);
}

egl_result_t egl_rfm66_ook_thresh_avg_filt_set(egl_rfm66_t *rfm, egl_rfm66_ook_thresh_avg_filt_t filt)
{
    egl_result_t result;
    egl_rfm66_reg_ook_avg_t regval;

    result = egl_rfm66_read_byte(rfm, EGL_RFM66_REG_OOK_AVG, &regval.raw);
    EGL_RESULT_CHECK(result);

    regval.bitfield.ook_average_thresh_filt = filt;

    return egl_rfm66_write_byte(rfm, EGL_RFM66_REG_OOK_AVG, regval.raw);
}

egl_result_t egl_rfm66_ook_thresh_avg_filt_get(egl_rfm66_t *rfm, egl_rfm66_ook_thresh_avg_filt_t *filt)
{
    egl_result_t result;
    egl_rfm66_reg_ook_avg_t regval;

    result = egl_rfm66_read_byte(rfm, EGL_RFM66_REG_OOK_AVG, &regval.raw);
    EGL_RESULT_CHECK(result);

    *filt = regval.bitfield.ook_average_thresh_filt;

    return result;
}

egl_result_t egl_rfm66_ook_peak_thresh_dec_set(egl_rfm66_t *rfm, egl_rfm66_ook_thresh_dec_t dec)
{
    egl_result_t result;
    egl_rfm66_reg_ook_avg_t regval;

    result = egl_rfm66_read_byte(rfm, EGL_RFM66_REG_OOK_AVG, &regval.raw);
    EGL_RESULT_CHECK(result);

    regval.bitfield.ook_peak_thresh_dec = dec;

    return egl_rfm66_write_byte(rfm, EGL_RFM66_REG_OOK_AVG, regval.raw);
}

egl_result_t egl_rfm66_ook_peak_thresh_dec_get(egl_rfm66_t *rfm, egl_rfm66_ook_thresh_dec_t *dec)
{
    egl_result_t result;
    egl_rfm66_reg_ook_avg_t regval;

    result = egl_rfm66_read_byte(rfm, EGL_RFM66_REG_OOK_AVG, &regval.raw);
    EGL_RESULT_CHECK(result);

    *dec = regval.bitfield.ook_peak_thresh_dec;

    return result;
}

egl_result_t egl_rfm66_ook_avg_offset_set(egl_rfm66_t *rfm, egl_rfm66_ook_avg_offset_t offset)
{
    egl_result_t result;
    egl_rfm66_reg_ook_avg_t regval;

    result = egl_rfm66_read_byte(rfm, EGL_RFM66_REG_OOK_AVG, &regval.raw);
    EGL_RESULT_CHECK(result);

    regval.bitfield.ook_average_offset = offset;

    return egl_rfm66_write_byte(rfm, EGL_RFM66_REG_OOK_AVG, regval.raw);
}

egl_result_t egl_rfm66_ook_avg_offset_get(egl_rfm66_t *rfm, egl_rfm66_ook_avg_offset_t *offset)
{
    egl_result_t result;
    egl_rfm66_reg_ook_avg_t regval;

    result = egl_rfm66_read_byte(rfm, EGL_RFM66_REG_OOK_AVG, &regval.raw);
    EGL_RESULT_CHECK(result);

    *offset = regval.bitfield.ook_average_offset;

    return result;
}