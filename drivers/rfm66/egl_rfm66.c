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

typedef union
{
    uint8_t raw;
    struct
    {
        uint8_t afc_auto_clear_on : 1;
        uint8_t afc_clear : 1;
        uint8_t reserved : 2;
        uint8_t agc_start : 1;
    }bitfield;
}egl_rfm66_reg_afc_fei_t;

typedef union
{
    uint8_t raw;
    struct
    {
        uint8_t preamble_detector_tol : 5;
        uint8_t preamble_detector_size : 2;
        uint8_t preamble_detector_on : 1;
    }bitfield;
}egl_rfm66_reg_preamble_detect_t;

typedef union
{
    uint8_t raw;
    struct
    {
        uint8_t clk_out : 3;
        uint8_t rc_cal_start : 1;
    }bitfield;
}egl_rfm66_reg_osc_t;

typedef union
{
    uint8_t raw;
    struct
    {
        uint8_t sync_size : 3;
        uint8_t fifo_fill_condition : 1;
        uint8_t sync_on : 1;
        uint8_t preamble_polarity : 1;
        uint8_t auto_restart_rx_mode : 2;
    }bitfield;
}egl_rfm66_reg_sync_config_t;

typedef union
{
    uint8_t raw;
    struct
    {
        uint8_t crc_whitening_type : 1;
        uint8_t address_filtering : 2;
        uint8_t crc_auto_clear_off : 1;
        uint8_t crc_on : 1;
        uint8_t dc_free : 2;
        uint8_t packet_format : 1;
    }bitfield;
}egl_rfm66_reg_packet_config1_t;

typedef union
{
    uint8_t raw;
    struct
    {
        uint8_t payload_lenght : 3;
        uint8_t beacon_on : 1;
        uint8_t io_home_power_frame : 1;
        uint8_t io_home_on : 1;
        uint8_t data_mode : 1;
    }bitfield;
}egl_rfm66_reg_packet_config2_t;

typedef union
{
    uint8_t raw;
    struct
    {
        uint8_t fifo_threshold : 6;
        uint8_t reserved : 1;
        uint8_t tx_start_condition : 1;
    }bitfield;
}egl_rfm66_reg_fifo_thresh_t;

typedef union
{
    uint8_t raw;
    struct
    {
        uint8_t from_transmit : 1;
        uint8_t from_idle : 1;
        uint8_t low_power_selection : 1;
        uint8_t from_start : 2;
        uint8_t idle_mode : 1;
        uint8_t sequencer_stop : 1;
        uint8_t sequencer_start : 1;
    }bitfield;
}egl_rfm66_reg_seq_config1_t;

typedef union
{
    uint8_t raw;
    struct
    {
        uint8_t from_packet_received : 3;
        uint8_t from_rx_timeout : 2;
        uint8_t from_receive : 3;
    }bitfield;
}egl_rfm66_reg_seq_config2_t;

typedef union
{
    uint8_t raw;
    struct
    {
        uint8_t timer2_resolution : 2;
        uint8_t timer1_resolution : 2;
    }bitfield;
}egl_rfm66_reg_timer_resol_t;

typedef union
{
    uint8_t raw;
    struct
    {
        uint8_t temp_monitor_off : 1;
        uint8_t temp_threshold : 2;
        uint8_t temp_change : 1;
        uint8_t reserved : 1;
        uint8_t image_cal_running : 1;
        uint8_t image_cal_start : 1;
        uint8_t auto_image_cal_on : 1;
    }bitfield;
}egl_rfm66_reg_image_cal_t;

typedef union
{
    uint8_t raw;
    struct
    {
        uint8_t low_bat_trim : 3;
        uint8_t low_bat_on : 1;
    }bitfield;
}egl_rfm66_reg_low_bat_t;

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
}egl_rfm66_reg_dio_map1_t;

typedef union
{
    uint8_t raw;
    struct
    {
        uint8_t map_preamble_detect : 1;
        uint8_t reserved : 3;
        uint8_t dio5 : 2;
        uint8_t dio4 : 2;
    }bitfield;
}egl_rfm66_reg_dio_map2_t;

typedef union
{
    uint8_t raw;
    struct
    {
        uint8_t agc_step1 : 4;
    }bitfield;
}egl_rfm66_reg_agc_thresh1_t;

typedef union
{
    uint8_t raw;
    struct
    {
        uint8_t agc_step3 : 4;
        uint8_t agc_step2 : 4;
    }bitfield;
}egl_rfm66_reg_agc_thresh2_t;

typedef union
{
    uint8_t raw;
    struct
    {
        uint8_t agc_step5 : 4;
        uint8_t agc_step4 : 4;
    }bitfield;
}egl_rfm66_reg_agc_thresh3_t;

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

egl_result_t egl_rfm66_afc_clear(egl_rfm66_t *rfm)
{
    egl_result_t result;
    egl_rfm66_reg_afc_fei_t regval;

    result = egl_rfm66_read_byte(rfm, EGL_RFM66_REG_AFC_FEI, &regval.raw);
    EGL_RESULT_CHECK(result);

    regval.bitfield.afc_clear = true;

    return egl_rfm66_write_byte(rfm, EGL_RFM66_REG_AFC_FEI, regval.raw);
}

egl_result_t egl_rfm66_afc_auto_clear_set(egl_rfm66_t *rfm, bool state)
{
    egl_result_t result;
    egl_rfm66_reg_afc_fei_t regval;

    result = egl_rfm66_read_byte(rfm, EGL_RFM66_REG_AFC_FEI, &regval.raw);
    EGL_RESULT_CHECK(result);

    regval.bitfield.afc_auto_clear_on = state;

    return egl_rfm66_write_byte(rfm, EGL_RFM66_REG_AFC_FEI, regval.raw);
}

egl_result_t egl_rfm66_afc_auto_clear_get(egl_rfm66_t *rfm, bool *state)
{
    egl_result_t result;
    egl_rfm66_reg_afc_fei_t regval;

    result = egl_rfm66_read_byte(rfm, EGL_RFM66_REG_AFC_FEI, &regval.raw);
    EGL_RESULT_CHECK(result);

    *state = regval.bitfield.afc_auto_clear_on;

    return result;
}

egl_result_t egl_rfm66_agc_start(egl_rfm66_t *rfm)
{
    egl_result_t result;
    egl_rfm66_reg_afc_fei_t regval;

    result = egl_rfm66_read_byte(rfm, EGL_RFM66_REG_AFC_FEI, &regval.raw);
    EGL_RESULT_CHECK(result);

    regval.bitfield.agc_start = true;

    return egl_rfm66_write_byte(rfm, EGL_RFM66_REG_AFC_FEI, regval.raw);
}

egl_result_t egl_rfm66_afc_get(egl_rfm66_t *rfm, int16_t *hz)
{
    egl_result_t result;
    uint16_t raw;

    result = egl_rfm66_read_burst(rfm, EGL_RFM66_REG_AFC_MSB, &raw, sizeof(raw));
    EGL_RESULT_CHECK(result);

    *hz = (int16_t)((((uint64_t)egl_swap16(raw)) * egl_clock_get(rfm->clock)) / EGL_RFM66_FSTEP_COEF);

    return result;
}

egl_result_t egl_rfm66_fei_get(egl_rfm66_t *rfm, int16_t *hz)
{
    egl_result_t result;
    uint16_t raw;

    result = egl_rfm66_read_burst(rfm, EGL_RFM66_REG_FEI_MSB, &raw, sizeof(raw));
    EGL_RESULT_CHECK(result);

    *hz = (int16_t)((((uint64_t)egl_swap16(raw)) * egl_clock_get(rfm->clock)) / EGL_RFM66_FSTEP_COEF);

    return result;
}

egl_result_t egl_rfm66_preamble_detect_tol_set(egl_rfm66_t *rfm, uint8_t tol)
{
    EGL_ASSERT_CHECK(tol <= 31, EGL_OUT_OF_BOUNDARY);

    egl_result_t result;
    egl_rfm66_reg_preamble_detect_t regval;

    result = egl_rfm66_read_byte(rfm, EGL_RFM66_REG_PREAMBLE_DETECT, &regval.raw);
    EGL_RESULT_CHECK(result);

    regval.bitfield.preamble_detector_tol = tol;

    return egl_rfm66_write_byte(rfm, EGL_RFM66_REG_PREAMBLE_DETECT, regval.raw);
}

egl_result_t egl_rfm66_preamble_detect_tol_get(egl_rfm66_t *rfm, uint8_t *tol)
{
    egl_result_t result;
    egl_rfm66_reg_preamble_detect_t regval;

    result = egl_rfm66_read_byte(rfm, EGL_RFM66_REG_PREAMBLE_DETECT, &regval.raw);
    EGL_RESULT_CHECK(result);

    *tol = regval.bitfield.preamble_detector_tol;

    return result;
}

egl_result_t egl_rfm66_preamble_detect_size_set(egl_rfm66_t *rfm, egl_rfm66_preamble_detect_size_t size)
{
    egl_result_t result;
    egl_rfm66_reg_preamble_detect_t regval;

    result = egl_rfm66_read_byte(rfm, EGL_RFM66_REG_PREAMBLE_DETECT, &regval.raw);
    EGL_RESULT_CHECK(result);

    regval.bitfield.preamble_detector_size = size;

    return egl_rfm66_write_byte(rfm, EGL_RFM66_REG_PREAMBLE_DETECT, regval.raw);
}

egl_result_t egl_rfm66_preamble_detect_size_get(egl_rfm66_t *rfm, egl_rfm66_preamble_detect_size_t *size)
{
    egl_result_t result;
    egl_rfm66_reg_preamble_detect_t regval;

    result = egl_rfm66_read_byte(rfm, EGL_RFM66_REG_PREAMBLE_DETECT, &regval.raw);
    EGL_RESULT_CHECK(result);

    *size = regval.bitfield.preamble_detector_size;

    return result;
}

egl_result_t egl_rfm66_preamble_detect_state_set(egl_rfm66_t *rfm, bool state)
{
    egl_result_t result;
    egl_rfm66_reg_preamble_detect_t regval;

    result = egl_rfm66_read_byte(rfm, EGL_RFM66_REG_PREAMBLE_DETECT, &regval.raw);
    EGL_RESULT_CHECK(result);

    regval.bitfield.preamble_detector_on = state;

    return egl_rfm66_write_byte(rfm, EGL_RFM66_REG_PREAMBLE_DETECT, regval.raw);
}

egl_result_t egl_rfm66_preamble_detect_state_get(egl_rfm66_t *rfm, bool *state)
{
    egl_result_t result;
    egl_rfm66_reg_preamble_detect_t regval;

    result = egl_rfm66_read_byte(rfm, EGL_RFM66_REG_PREAMBLE_DETECT, &regval.raw);
    EGL_RESULT_CHECK(result);

    *state = regval.bitfield.preamble_detector_on;

    return result;
}

egl_result_t egl_rfm66_timeout_rx_rssi_set(egl_rfm66_t *rfm, uint8_t timeout)
{
    return egl_rfm66_write_byte(rfm, EGL_RFM66_REG_RX_TIMEOUT1, timeout);
}

egl_result_t egl_rfm66_timeout_rx_rssi_get(egl_rfm66_t *rfm, uint8_t *timeout)
{
    return egl_rfm66_read_byte(rfm, EGL_RFM66_REG_RX_TIMEOUT1, timeout);
}

egl_result_t egl_rfm66_timeout_rx_preamble_set(egl_rfm66_t *rfm, uint8_t timeout)
{
    return egl_rfm66_write_byte(rfm, EGL_RFM66_REG_RX_TIMEOUT2, timeout);
}

egl_result_t egl_rfm66_timeout_rx_preamble_get(egl_rfm66_t *rfm, uint8_t *timeout)
{
    return egl_rfm66_read_byte(rfm, EGL_RFM66_REG_RX_TIMEOUT2, timeout);
}

egl_result_t egl_rfm66_timeout_rx_signal_sync_set(egl_rfm66_t *rfm, uint8_t timeout)
{
    return egl_rfm66_write_byte(rfm, EGL_RFM66_REG_RX_TIMEOUT3, timeout);
}

egl_result_t egl_rfm66_timeout_rx_signal_sync_get(egl_rfm66_t *rfm, uint8_t *timeout)
{
    return egl_rfm66_read_byte(rfm, EGL_RFM66_REG_RX_TIMEOUT3, timeout);
}

egl_result_t egl_rfm66_timeout_rx_delay_set(egl_rfm66_t *rfm, uint8_t delay)
{
    return egl_rfm66_write_byte(rfm, EGL_RFM66_REG_RX_DELAY, delay);
}

egl_result_t egl_rfm66_timeout_rx_delay_get(egl_rfm66_t *rfm, uint8_t *delay)
{
    return egl_rfm66_read_byte(rfm, EGL_RFM66_REG_RX_DELAY, delay);
}

egl_result_t egl_rfm66_clk_out_set(egl_rfm66_t *rfm, egl_rfm66_clk_out_t out)
{
    egl_result_t result;
    egl_rfm66_reg_osc_t regval;

    result = egl_rfm66_read_byte(rfm, EGL_RFM66_REG_OSC, &regval.raw);
    EGL_RESULT_CHECK(result);

    regval.bitfield.clk_out = out;

    return egl_rfm66_write_byte(rfm, EGL_RFM66_REG_OSC, regval.raw);
}

egl_result_t egl_rfm66_clk_out_get(egl_rfm66_t *rfm, egl_rfm66_clk_out_t *out)
{
    egl_result_t result;
    egl_rfm66_reg_osc_t regval;

    result = egl_rfm66_read_byte(rfm, EGL_RFM66_REG_OSC, &regval.raw);
    EGL_RESULT_CHECK(result);

    *out = regval.bitfield.clk_out;

    return result;
}

egl_result_t egl_rfm66_rc_calibration_start(egl_rfm66_t *rfm)
{
    egl_result_t result;
    egl_rfm66_reg_osc_t regval;

    result = egl_rfm66_read_byte(rfm, EGL_RFM66_REG_OSC, &regval.raw);
    EGL_RESULT_CHECK(result);

    regval.bitfield.rc_cal_start = true;

    return egl_rfm66_write_byte(rfm, EGL_RFM66_REG_OSC, regval.raw);
}

egl_result_t egl_rfm66_preamble_set(egl_rfm66_t *rfm, uint16_t bytes)
{
    return egl_rfm66_write_burst(rfm, EGL_RFM66_REG_PREAMBLE_MSB, &bytes, sizeof(bytes));
}

egl_result_t egl_rfm66_preamble_get(egl_rfm66_t *rfm, uint16_t *bytes)
{
    return egl_rfm66_read_burst(rfm, EGL_RFM66_REG_PREAMBLE_MSB, bytes, sizeof(*bytes));
}

egl_result_t egl_rfm66_sync_size_set(egl_rfm66_t *rfm, uint8_t size)
{
    EGL_ASSERT_CHECK(size <= EGL_RFM66_SYNC_MAX_SIZE, EGL_OUT_OF_BOUNDARY);
    EGL_ASSERT_CHECK(size > 0, EGL_OUT_OF_BOUNDARY);

    egl_result_t result;
    egl_rfm66_reg_sync_config_t regval;

    result = egl_rfm66_read_byte(rfm, EGL_RFM66_REG_SYNC_CONFIG, &regval.raw);
    EGL_RESULT_CHECK(result);

    regval.bitfield.sync_size = size - 1;

    return egl_rfm66_write_byte(rfm, EGL_RFM66_REG_SYNC_CONFIG, regval.raw);
}

egl_result_t egl_rfm66_sync_size_get(egl_rfm66_t *rfm, uint8_t *size)
{
    egl_result_t result;
    egl_rfm66_reg_sync_config_t regval;

    result = egl_rfm66_read_byte(rfm, EGL_RFM66_REG_SYNC_CONFIG, &regval.raw);
    EGL_RESULT_CHECK(result);

    *size = regval.bitfield.sync_size + 1;

    return result;
}

egl_result_t egl_rfm66_fifo_fill_cond_set(egl_rfm66_t *rfm, egl_rfm66_fifo_fill_cond_t cond)
{
    egl_result_t result;
    egl_rfm66_reg_sync_config_t regval;

    result = egl_rfm66_read_byte(rfm, EGL_RFM66_REG_SYNC_CONFIG, &regval.raw);
    EGL_RESULT_CHECK(result);

    regval.bitfield.fifo_fill_condition = cond;

    return egl_rfm66_write_byte(rfm, EGL_RFM66_REG_SYNC_CONFIG, regval.raw);
}

egl_result_t egl_rfm66_fifo_fill_cond_get(egl_rfm66_t *rfm, egl_rfm66_fifo_fill_cond_t *cond)
{
    egl_result_t result;
    egl_rfm66_reg_sync_config_t regval;

    result = egl_rfm66_read_byte(rfm, EGL_RFM66_REG_SYNC_CONFIG, &regval.raw);
    EGL_RESULT_CHECK(result);

    *cond = regval.bitfield.fifo_fill_condition;

    return result;
}

egl_result_t egl_rfm66_sync_state_set(egl_rfm66_t *rfm, bool state)
{
    egl_result_t result;
    egl_rfm66_reg_sync_config_t regval;

    result = egl_rfm66_read_byte(rfm, EGL_RFM66_REG_SYNC_CONFIG, &regval.raw);
    EGL_RESULT_CHECK(result);

    regval.bitfield.sync_on = state;

    return egl_rfm66_write_byte(rfm, EGL_RFM66_REG_SYNC_CONFIG, regval.raw);
}

egl_result_t egl_rfm66_sync_state_get(egl_rfm66_t *rfm, bool *state)
{
    egl_result_t result;
    egl_rfm66_reg_sync_config_t regval;

    result = egl_rfm66_read_byte(rfm, EGL_RFM66_REG_SYNC_CONFIG, &regval.raw);
    EGL_RESULT_CHECK(result);

    *state = regval.bitfield.sync_on;

    return result;
}

egl_result_t egl_rfm66_preamble_polarity_set(egl_rfm66_t *rfm, egl_rfm66_preamble_pol_t polarity)
{
    egl_result_t result;
    egl_rfm66_reg_sync_config_t regval;

    result = egl_rfm66_read_byte(rfm, EGL_RFM66_REG_SYNC_CONFIG, &regval.raw);
    EGL_RESULT_CHECK(result);

    regval.bitfield.preamble_polarity = polarity;

    return egl_rfm66_write_byte(rfm, EGL_RFM66_REG_SYNC_CONFIG, regval.raw);
}

egl_result_t egl_rfm66_preamble_polarity_get(egl_rfm66_t *rfm, egl_rfm66_preamble_pol_t *polarity)
{
    egl_result_t result;
    egl_rfm66_reg_sync_config_t regval;

    result = egl_rfm66_read_byte(rfm, EGL_RFM66_REG_SYNC_CONFIG, &regval.raw);
    EGL_RESULT_CHECK(result);

    *polarity = regval.bitfield.preamble_polarity;

    return result;
}

egl_result_t egl_rfm66_auto_restart_rx_mode_set(egl_rfm66_t *rfm, egl_rfm66_auto_restart_rx_mode_t mode)
{
    egl_result_t result;
    egl_rfm66_reg_sync_config_t regval;

    result = egl_rfm66_read_byte(rfm, EGL_RFM66_REG_SYNC_CONFIG, &regval.raw);
    EGL_RESULT_CHECK(result);

    regval.bitfield.auto_restart_rx_mode = mode;

    return egl_rfm66_write_byte(rfm, EGL_RFM66_REG_SYNC_CONFIG, regval.raw);
}

egl_result_t egl_rfm66_auto_restart_rx_mode_get(egl_rfm66_t *rfm, egl_rfm66_auto_restart_rx_mode_t *mode)
{
    egl_result_t result;
    egl_rfm66_reg_sync_config_t regval;

    result = egl_rfm66_read_byte(rfm, EGL_RFM66_REG_SYNC_CONFIG, &regval.raw);
    EGL_RESULT_CHECK(result);

    *mode = regval.bitfield.auto_restart_rx_mode;

    return result;
}

egl_result_t egl_rfm66_sync_set(egl_rfm66_t *rfm, uint8_t *sync, uint8_t size)
{
    egl_result_t result;

    EGL_ASSERT_CHECK(sync != NULL, EGL_NULL_POINTER);

    result = egl_rfm66_sync_size_set(rfm, size);
    EGL_RESULT_CHECK(result);

    return egl_rfm66_write_burst(rfm, EGL_RFM66_REG_SYNC_VALUE1, sync, size);
}

egl_result_t egl_rfm66_sync_get(egl_rfm66_t *rfm, uint8_t *sync, uint8_t *size)
{
    egl_result_t result;

    result = egl_rfm66_sync_size_get(rfm, size);
    EGL_RESULT_CHECK(result);

    return egl_rfm66_read_burst(rfm, EGL_RFM66_REG_SYNC_VALUE1, sync, *size);
}

egl_result_t egl_rfm66_crc_whitening_type_set(egl_rfm66_t *rfm, egl_rfm66_crc_whitening_t whitening)
{
    egl_result_t result;
    egl_rfm66_reg_packet_config1_t regval;

    result = egl_rfm66_read_byte(rfm, EGL_RFM66_REG_PACKET_CONFIG1, &regval.raw);
    EGL_RESULT_CHECK(result);

    regval.bitfield.crc_whitening_type = whitening;

    return egl_rfm66_write_byte(rfm, EGL_RFM66_REG_PACKET_CONFIG1, regval.raw);
}

egl_result_t egl_rfm66_crc_whitening_type_get(egl_rfm66_t *rfm, egl_rfm66_crc_whitening_t *whitening)
{
    egl_result_t result;
    egl_rfm66_reg_packet_config1_t regval;

    result = egl_rfm66_read_byte(rfm, EGL_RFM66_REG_PACKET_CONFIG1, &regval.raw);
    EGL_RESULT_CHECK(result);

    *whitening = regval.bitfield.crc_whitening_type;

    return result;
}

egl_result_t egl_rfm66_address_filtering_set(egl_rfm66_t *rfm, egl_rfm66_address_filtering_t filteing)
{
    egl_result_t result;
    egl_rfm66_reg_packet_config1_t regval;

    result = egl_rfm66_read_byte(rfm, EGL_RFM66_REG_PACKET_CONFIG1, &regval.raw);
    EGL_RESULT_CHECK(result);

    regval.bitfield.address_filtering = filteing;

    return egl_rfm66_write_byte(rfm, EGL_RFM66_REG_PACKET_CONFIG1, regval.raw);
}

egl_result_t egl_rfm66_address_filtering_get(egl_rfm66_t *rfm, egl_rfm66_address_filtering_t *filteing)
{
    egl_result_t result;
    egl_rfm66_reg_packet_config1_t regval;

    result = egl_rfm66_read_byte(rfm, EGL_RFM66_REG_PACKET_CONFIG1, &regval.raw);
    EGL_RESULT_CHECK(result);

    *filteing = regval.bitfield.address_filtering;

    return result;
}

egl_result_t egl_rfm66_crc_autoclear_state_set(egl_rfm66_t *rfm, bool state)
{
    egl_result_t result;
    egl_rfm66_reg_packet_config1_t regval;

    result = egl_rfm66_read_byte(rfm, EGL_RFM66_REG_PACKET_CONFIG1, &regval.raw);
    EGL_RESULT_CHECK(result);

    regval.bitfield.crc_auto_clear_off = !state;

    return egl_rfm66_write_byte(rfm, EGL_RFM66_REG_PACKET_CONFIG1, regval.raw);
}

egl_result_t egl_rfm66_crc_autoclear_state_get(egl_rfm66_t *rfm, bool *state)
{
    egl_result_t result;
    egl_rfm66_reg_packet_config1_t regval;

    result = egl_rfm66_read_byte(rfm, EGL_RFM66_REG_PACKET_CONFIG1, &regval.raw);
    EGL_RESULT_CHECK(result);

    *state = !regval.bitfield.crc_auto_clear_off;

    return result;
}

egl_result_t egl_rfm66_crc_state_set(egl_rfm66_t *rfm, bool state)
{
    egl_result_t result;
    egl_rfm66_reg_packet_config1_t regval;

    result = egl_rfm66_read_byte(rfm, EGL_RFM66_REG_PACKET_CONFIG1, &regval.raw);
    EGL_RESULT_CHECK(result);

    regval.bitfield.crc_on = state;

    return egl_rfm66_write_byte(rfm, EGL_RFM66_REG_PACKET_CONFIG1, regval.raw);
}

egl_result_t egl_rfm66_crc_state_get(egl_rfm66_t *rfm, bool *state)
{
    egl_result_t result;
    egl_rfm66_reg_packet_config1_t regval;

    result = egl_rfm66_read_byte(rfm, EGL_RFM66_REG_PACKET_CONFIG1, &regval.raw);
    EGL_RESULT_CHECK(result);

    *state = regval.bitfield.crc_on;

    return result;
}

egl_result_t egl_rfm66_dc_free_set(egl_rfm66_t *rfm, egl_rfm66_dc_free_t type)
{
    egl_result_t result;
    egl_rfm66_reg_packet_config1_t regval;

    result = egl_rfm66_read_byte(rfm, EGL_RFM66_REG_PACKET_CONFIG1, &regval.raw);
    EGL_RESULT_CHECK(result);

    regval.bitfield.dc_free = type;

    return egl_rfm66_write_byte(rfm, EGL_RFM66_REG_PACKET_CONFIG1, regval.raw);
}

egl_result_t egl_rfm66_dc_free_get(egl_rfm66_t *rfm, egl_rfm66_dc_free_t *type)
{
    egl_result_t result;
    egl_rfm66_reg_packet_config1_t regval;

    result = egl_rfm66_read_byte(rfm, EGL_RFM66_REG_PACKET_CONFIG1, &regval.raw);
    EGL_RESULT_CHECK(result);

    *type = regval.bitfield.dc_free;

    return result;
}

egl_result_t egl_rfm66_packet_format_set(egl_rfm66_t *rfm, egl_rfm66_packet_format_t format)
{
    egl_result_t result;
    egl_rfm66_reg_packet_config1_t regval;

    result = egl_rfm66_read_byte(rfm, EGL_RFM66_REG_PACKET_CONFIG1, &regval.raw);
    EGL_RESULT_CHECK(result);

    regval.bitfield.packet_format = format;

    return egl_rfm66_write_byte(rfm, EGL_RFM66_REG_PACKET_CONFIG1, regval.raw);
}

egl_result_t egl_rfm66_packet_format_get(egl_rfm66_t *rfm, egl_rfm66_packet_format_t *format)
{
    egl_result_t result;
    egl_rfm66_reg_packet_config1_t regval;

    result = egl_rfm66_read_byte(rfm, EGL_RFM66_REG_PACKET_CONFIG1, &regval.raw);
    EGL_RESULT_CHECK(result);

    *format = regval.bitfield.packet_format;

    return result;
}

egl_result_t egl_rfm66_packet_length_set(egl_rfm66_t *rfm, uint16_t length)
{
    EGL_ASSERT_CHECK(length < 1024, EGL_OUT_OF_BOUNDARY);

    egl_result_t result;
    egl_rfm66_reg_packet_config2_t regval;

    uint8_t lsb = (uint8_t)length;
    uint8_t msb = (uint8_t)(length >> 8 & 0xFF);

    result = egl_rfm66_write_byte(rfm, EGL_RFM66_REG_PACKET_LENGTH, lsb);
    EGL_RESULT_CHECK(result);

    result = egl_rfm66_read_byte(rfm, EGL_RFM66_REG_PACKET_CONFIG2, &regval.raw);
    EGL_RESULT_CHECK(result);

    regval.bitfield.payload_lenght = msb;

    return egl_rfm66_write_byte(rfm, EGL_RFM66_REG_PACKET_CONFIG2, regval.raw);
}

egl_result_t egl_rfm66_packet_length_get(egl_rfm66_t *rfm, uint16_t *length)
{
    uint8_t lsb;
    egl_result_t result;
    egl_rfm66_reg_packet_config2_t regval;

    result = egl_rfm66_read_byte(rfm, EGL_RFM66_REG_PACKET_LENGTH, &lsb);
    EGL_RESULT_CHECK(result);

    result = egl_rfm66_read_byte(rfm, EGL_RFM66_REG_PACKET_CONFIG2, &regval.raw);
    EGL_RESULT_CHECK(result);

    *length = regval.bitfield.payload_lenght << 8 | lsb;

    return result;
}

egl_result_t egl_rfm66_beacon_mode_set(egl_rfm66_t *rfm, bool state)
{
    egl_result_t result;
    egl_rfm66_reg_packet_config2_t regval;

    result = egl_rfm66_read_byte(rfm, EGL_RFM66_REG_PACKET_CONFIG2, &regval.raw);
    EGL_RESULT_CHECK(result);

    regval.bitfield.beacon_on = state;

    return egl_rfm66_write_byte(rfm, EGL_RFM66_REG_PACKET_CONFIG2, regval.raw);
}

egl_result_t egl_rfm66_beacon_mode_get(egl_rfm66_t *rfm, bool *state)
{
    egl_result_t result;
    egl_rfm66_reg_packet_config2_t regval;

    result = egl_rfm66_read_byte(rfm, EGL_RFM66_REG_PACKET_CONFIG2, &regval.raw);
    EGL_RESULT_CHECK(result);

    *state = regval.bitfield.beacon_on;

    return result;
}

egl_result_t egl_rfm66_io_home_power_frame_state_set(egl_rfm66_t *rfm, bool state)
{
    egl_result_t result;
    egl_rfm66_reg_packet_config2_t regval;

    result = egl_rfm66_read_byte(rfm, EGL_RFM66_REG_PACKET_CONFIG2, &regval.raw);
    EGL_RESULT_CHECK(result);

    regval.bitfield.io_home_power_frame = state;

    return egl_rfm66_write_byte(rfm, EGL_RFM66_REG_PACKET_CONFIG2, regval.raw);
}

egl_result_t egl_rfm66_io_home_power_frame_state_get(egl_rfm66_t *rfm, bool *state)
{
    egl_result_t result;
    egl_rfm66_reg_packet_config2_t regval;

    result = egl_rfm66_read_byte(rfm, EGL_RFM66_REG_PACKET_CONFIG2, &regval.raw);
    EGL_RESULT_CHECK(result);

    *state = regval.bitfield.io_home_power_frame;

    return result;
}

egl_result_t egl_rfm66_io_home_state_set(egl_rfm66_t *rfm, bool state)
{
    egl_result_t result;
    egl_rfm66_reg_packet_config2_t regval;

    result = egl_rfm66_read_byte(rfm, EGL_RFM66_REG_PACKET_CONFIG2, &regval.raw);
    EGL_RESULT_CHECK(result);

    regval.bitfield.io_home_on = state;

    return egl_rfm66_write_byte(rfm, EGL_RFM66_REG_PACKET_CONFIG2, regval.raw);
}

egl_result_t egl_rfm66_io_home_state_get(egl_rfm66_t *rfm, bool *state)
{
    egl_result_t result;
    egl_rfm66_reg_packet_config2_t regval;

    result = egl_rfm66_read_byte(rfm, EGL_RFM66_REG_PACKET_CONFIG2, &regval.raw);
    EGL_RESULT_CHECK(result);

    *state = regval.bitfield.io_home_on;

    return result;
}

egl_result_t egl_rfm66_data_mode_set(egl_rfm66_t *rfm, egl_rfm66_data_mode_t mode)
{
    egl_result_t result;
    egl_rfm66_reg_packet_config2_t regval;

    result = egl_rfm66_read_byte(rfm, EGL_RFM66_REG_PACKET_CONFIG2, &regval.raw);
    EGL_RESULT_CHECK(result);

    regval.bitfield.data_mode = mode;

    return egl_rfm66_write_byte(rfm, EGL_RFM66_REG_PACKET_CONFIG2, regval.raw);
}

egl_result_t egl_rfm66_data_mode_get(egl_rfm66_t *rfm, egl_rfm66_data_mode_t *mode)
{
    egl_result_t result;
    egl_rfm66_reg_packet_config2_t regval;

    result = egl_rfm66_read_byte(rfm, EGL_RFM66_REG_PACKET_CONFIG2, &regval.raw);
    EGL_RESULT_CHECK(result);

    *mode = regval.bitfield.data_mode;

    return result;
}

egl_result_t egl_rfm66_node_address_set(egl_rfm66_t *rfm, uint8_t address)
{
    return egl_rfm66_write_byte(rfm, EGL_RFM66_REG_MODE_ADRS, address);
}

egl_result_t egl_rfm66_node_address_get(egl_rfm66_t *rfm, uint8_t *address)
{
    return egl_rfm66_read_byte(rfm, EGL_RFM66_REG_MODE_ADRS, address);
}

egl_result_t egl_rfm66_broadcast_address_set(egl_rfm66_t *rfm, uint8_t address)
{
    return egl_rfm66_write_byte(rfm, EGL_RFM66_REG_BROADCAST_ADRS, address);
}

egl_result_t egl_rfm66_broadcast_address_get(egl_rfm66_t *rfm, uint8_t *address)
{
    return egl_rfm66_read_byte(rfm, EGL_RFM66_REG_BROADCAST_ADRS, address);
}

egl_result_t egl_rfm66_fifo_thresh_set(egl_rfm66_t *rfm, uint8_t thresh)
{
    EGL_ASSERT_CHECK(thresh < 32, EGL_OUT_OF_BOUNDARY)

    egl_result_t result;
    egl_rfm66_reg_fifo_thresh_t regval;

    result = egl_rfm66_read_byte(rfm, EGL_RFM66_REG_FIFO_THRESH, &regval.raw);
    EGL_RESULT_CHECK(result);

    regval.bitfield.fifo_threshold = thresh;

    return egl_rfm66_write_byte(rfm, EGL_RFM66_REG_FIFO_THRESH, regval.raw);
}

egl_result_t egl_rfm66_fifo_thresh_get(egl_rfm66_t *rfm, uint8_t *thresh)
{
    egl_result_t result;
    egl_rfm66_reg_fifo_thresh_t regval;

    result = egl_rfm66_read_byte(rfm, EGL_RFM66_REG_FIFO_THRESH, &regval.raw);
    EGL_RESULT_CHECK(result);

    *thresh = regval.bitfield.fifo_threshold;

    return result;
}

egl_result_t egl_rfm66_tx_start_condition_set(egl_rfm66_t *rfm, egl_rfm66_tx_start_condition_t cond)
{
    egl_result_t result;
    egl_rfm66_reg_fifo_thresh_t regval;

    result = egl_rfm66_read_byte(rfm, EGL_RFM66_REG_FIFO_THRESH, &regval.raw);
    EGL_RESULT_CHECK(result);

    regval.bitfield.tx_start_condition = cond;

    return egl_rfm66_write_byte(rfm, EGL_RFM66_REG_FIFO_THRESH, regval.raw);
}

egl_result_t egl_rfm66_tx_start_condition_get(egl_rfm66_t *rfm, egl_rfm66_tx_start_condition_t *cond)
{
    egl_result_t result;
    egl_rfm66_reg_fifo_thresh_t regval;

    result = egl_rfm66_read_byte(rfm, EGL_RFM66_REG_FIFO_THRESH, &regval.raw);
    EGL_RESULT_CHECK(result);

    *cond = regval.bitfield.tx_start_condition;

    return result;
}

egl_result_t egl_rfm66_from_transmit_set(egl_rfm66_t *rfm, egl_rfm66_from_transmit_t to)
{
    egl_result_t result;
    egl_rfm66_reg_seq_config1_t regval;

    result = egl_rfm66_read_byte(rfm, EGL_RFM66_REG_SEQ_CONFIG1, &regval.raw);
    EGL_RESULT_CHECK(result);

    regval.bitfield.from_transmit = to;

    return egl_rfm66_write_byte(rfm, EGL_RFM66_REG_SEQ_CONFIG1, regval.raw);
}

egl_result_t egl_rfm66_from_transmit_get(egl_rfm66_t *rfm, egl_rfm66_from_transmit_t *to)
{
    egl_result_t result;
    egl_rfm66_reg_seq_config1_t regval;

    result = egl_rfm66_read_byte(rfm, EGL_RFM66_REG_SEQ_CONFIG1, &regval.raw);
    EGL_RESULT_CHECK(result);

    *to = regval.bitfield.from_transmit;

    return result;
}

egl_result_t egl_rfm66_from_idle_set(egl_rfm66_t *rfm, egl_rfm66_from_idle_t to)
{
    egl_result_t result;
    egl_rfm66_reg_seq_config1_t regval;

    result = egl_rfm66_read_byte(rfm, EGL_RFM66_REG_SEQ_CONFIG1, &regval.raw);
    EGL_RESULT_CHECK(result);

    regval.bitfield.from_idle = to;

    return egl_rfm66_write_byte(rfm, EGL_RFM66_REG_SEQ_CONFIG1, regval.raw);
}

egl_result_t egl_rfm66_from_idle_get(egl_rfm66_t *rfm, egl_rfm66_from_idle_t *to)
{
    egl_result_t result;
    egl_rfm66_reg_seq_config1_t regval;

    result = egl_rfm66_read_byte(rfm, EGL_RFM66_REG_SEQ_CONFIG1, &regval.raw);
    EGL_RESULT_CHECK(result);

    *to = regval.bitfield.from_idle;

    return result;
}

egl_result_t egl_rfm66_low_power_selection_set(egl_rfm66_t *rfm, egl_rfm66_low_power_selection_t selection)
{
    egl_result_t result;
    egl_rfm66_reg_seq_config1_t regval;

    result = egl_rfm66_read_byte(rfm, EGL_RFM66_REG_SEQ_CONFIG1, &regval.raw);
    EGL_RESULT_CHECK(result);

    regval.bitfield.low_power_selection = selection;

    return egl_rfm66_write_byte(rfm, EGL_RFM66_REG_SEQ_CONFIG1, regval.raw);
}

egl_result_t egl_rfm66_low_power_selection_get(egl_rfm66_t *rfm, egl_rfm66_low_power_selection_t *selection)
{
    egl_result_t result;
    egl_rfm66_reg_seq_config1_t regval;

    result = egl_rfm66_read_byte(rfm, EGL_RFM66_REG_SEQ_CONFIG1, &regval.raw);
    EGL_RESULT_CHECK(result);

    *selection = regval.bitfield.low_power_selection;

    return result;
}

egl_result_t egl_rfm66_from_start_set(egl_rfm66_t *rfm, egl_rfm66_from_start_t to)
{
    egl_result_t result;
    egl_rfm66_reg_seq_config1_t regval;

    result = egl_rfm66_read_byte(rfm, EGL_RFM66_REG_SEQ_CONFIG1, &regval.raw);
    EGL_RESULT_CHECK(result);

    regval.bitfield.from_start = to;

    return egl_rfm66_write_byte(rfm, EGL_RFM66_REG_SEQ_CONFIG1, regval.raw);
}

egl_result_t egl_rfm66_from_start_get(egl_rfm66_t *rfm, egl_rfm66_from_start_t *to)
{
    egl_result_t result;
    egl_rfm66_reg_seq_config1_t regval;

    result = egl_rfm66_read_byte(rfm, EGL_RFM66_REG_SEQ_CONFIG1, &regval.raw);
    EGL_RESULT_CHECK(result);

    *to = regval.bitfield.from_start;

    return result;
}

egl_result_t egl_rfm66_idle_mode_set(egl_rfm66_t *rfm, egl_rfm66_idle_mode_t mode)
{
    egl_result_t result;
    egl_rfm66_reg_seq_config1_t regval;

    result = egl_rfm66_read_byte(rfm, EGL_RFM66_REG_SEQ_CONFIG1, &regval.raw);
    EGL_RESULT_CHECK(result);

    regval.bitfield.idle_mode = mode;

    return egl_rfm66_write_byte(rfm, EGL_RFM66_REG_SEQ_CONFIG1, regval.raw);
}

egl_result_t egl_rfm66_idle_mode_get(egl_rfm66_t *rfm, egl_rfm66_idle_mode_t *mode)
{
    egl_result_t result;
    egl_rfm66_reg_seq_config1_t regval;

    result = egl_rfm66_read_byte(rfm, EGL_RFM66_REG_SEQ_CONFIG1, &regval.raw);
    EGL_RESULT_CHECK(result);

    *mode = regval.bitfield.idle_mode;

    return result;
}

egl_result_t egl_rfm66_sequencer_start(egl_rfm66_t *rfm)
{
    egl_result_t result;
    egl_rfm66_reg_seq_config1_t regval;

    result = egl_rfm66_read_byte(rfm, EGL_RFM66_REG_SEQ_CONFIG1, &regval.raw);
    EGL_RESULT_CHECK(result);

    regval.bitfield.sequencer_start = true;

    return egl_rfm66_write_byte(rfm, EGL_RFM66_REG_SEQ_CONFIG1, regval.raw);
}

egl_result_t egl_rfm66_sequencer_stop(egl_rfm66_t *rfm)
{
    egl_result_t result;
    egl_rfm66_reg_seq_config1_t regval;

    result = egl_rfm66_read_byte(rfm, EGL_RFM66_REG_SEQ_CONFIG1, &regval.raw);
    EGL_RESULT_CHECK(result);

    regval.bitfield.sequencer_stop = true;

    return egl_rfm66_write_byte(rfm, EGL_RFM66_REG_SEQ_CONFIG1, regval.raw);
}

egl_result_t egl_rfm66_from_packet_received_set(egl_rfm66_t *rfm, egl_rfm66_from_packet_received_t to)
{
    egl_result_t result;
    egl_rfm66_reg_seq_config2_t regval;

    result = egl_rfm66_read_byte(rfm, EGL_RFM66_REG_SEQ_CONFIG2, &regval.raw);
    EGL_RESULT_CHECK(result);

    regval.bitfield.from_packet_received = to;

    return egl_rfm66_write_byte(rfm, EGL_RFM66_REG_SEQ_CONFIG2, regval.raw);
}

egl_result_t egl_rfm66_from_packet_received_get(egl_rfm66_t *rfm, egl_rfm66_from_packet_received_t *to)
{
    egl_result_t result;
    egl_rfm66_reg_seq_config2_t regval;

    result = egl_rfm66_read_byte(rfm, EGL_RFM66_REG_SEQ_CONFIG2, &regval.raw);
    EGL_RESULT_CHECK(result);

    *to = regval.bitfield.from_packet_received;

    return result;
}

egl_result_t egl_rfm66_from_rx_timeout_set(egl_rfm66_t *rfm, egl_rfm66_from_rx_timeout_t to)
{
    egl_result_t result;
    egl_rfm66_reg_seq_config2_t regval;

    result = egl_rfm66_read_byte(rfm, EGL_RFM66_REG_SEQ_CONFIG2, &regval.raw);
    EGL_RESULT_CHECK(result);

    regval.bitfield.from_rx_timeout = to;

    return egl_rfm66_write_byte(rfm, EGL_RFM66_REG_SEQ_CONFIG2, regval.raw);
}

egl_result_t egl_rfm66_from_rx_timeout_get(egl_rfm66_t *rfm, egl_rfm66_from_rx_timeout_t *to)
{
    egl_result_t result;
    egl_rfm66_reg_seq_config2_t regval;

    result = egl_rfm66_read_byte(rfm, EGL_RFM66_REG_SEQ_CONFIG2, &regval.raw);
    EGL_RESULT_CHECK(result);

    *to = regval.bitfield.from_rx_timeout;

    return result;
}

egl_result_t egl_rfm66_from_receive_set(egl_rfm66_t *rfm, egl_rfm66_from_receive_t to)
{
    egl_result_t result;
    egl_rfm66_reg_seq_config2_t regval;

    result = egl_rfm66_read_byte(rfm, EGL_RFM66_REG_SEQ_CONFIG2, &regval.raw);
    EGL_RESULT_CHECK(result);

    regval.bitfield.from_receive = to;

    return egl_rfm66_write_byte(rfm, EGL_RFM66_REG_SEQ_CONFIG2, regval.raw);
}

egl_result_t egl_rfm66_from_receive_get(egl_rfm66_t *rfm, egl_rfm66_from_receive_t *to)
{
    egl_result_t result;
    egl_rfm66_reg_seq_config2_t regval;

    result = egl_rfm66_read_byte(rfm, EGL_RFM66_REG_SEQ_CONFIG2, &regval.raw);
    EGL_RESULT_CHECK(result);

    *to = regval.bitfield.from_receive;

    return result;
}

egl_result_t egl_rfm66_timer1_resolution_set(egl_rfm66_t *rfm, egl_rfm66_timer_resolution_t resolution)
{
    egl_result_t result;
    egl_rfm66_reg_timer_resol_t regval;

    result = egl_rfm66_read_byte(rfm, EGL_RFM66_REG_TIMER_RESOL, &regval.raw);
    EGL_RESULT_CHECK(result);

    regval.bitfield.timer1_resolution = resolution;

    return egl_rfm66_write_byte(rfm, EGL_RFM66_REG_TIMER_RESOL, regval.raw);
}

egl_result_t egl_rfm66_timer1_resolution_get(egl_rfm66_t *rfm, egl_rfm66_timer_resolution_t *resolution)
{
    egl_result_t result;
    egl_rfm66_reg_timer_resol_t regval;

    result = egl_rfm66_read_byte(rfm, EGL_RFM66_REG_TIMER_RESOL, &regval.raw);
    EGL_RESULT_CHECK(result);

    *resolution = regval.bitfield.timer1_resolution;

    return result;
}

egl_result_t egl_rfm66_timer2_resolution_set(egl_rfm66_t *rfm, egl_rfm66_timer_resolution_t resolution)
{
    egl_result_t result;
    egl_rfm66_reg_timer_resol_t regval;

    result = egl_rfm66_read_byte(rfm, EGL_RFM66_REG_TIMER_RESOL, &regval.raw);
    EGL_RESULT_CHECK(result);

    regval.bitfield.timer2_resolution = resolution;

    return egl_rfm66_write_byte(rfm, EGL_RFM66_REG_TIMER_RESOL, regval.raw);
}

egl_result_t egl_rfm66_timer2_resolution_get(egl_rfm66_t *rfm, egl_rfm66_timer_resolution_t *resolution)
{
    egl_result_t result;
    egl_rfm66_reg_timer_resol_t regval;

    result = egl_rfm66_read_byte(rfm, EGL_RFM66_REG_TIMER_RESOL, &regval.raw);
    EGL_RESULT_CHECK(result);

    *resolution = regval.bitfield.timer2_resolution;

    return result;
}

egl_result_t egl_rfm66_timer1_coef_set(egl_rfm66_t *rfm, uint8_t coef)
{
    return egl_rfm66_write_byte(rfm, EGL_RFM66_REG_TIMER1_COEF, coef);
}

egl_result_t egl_rfm66_timer1_coef_get(egl_rfm66_t *rfm, uint8_t *coef)
{
    return egl_rfm66_read_byte(rfm, EGL_RFM66_REG_TIMER1_COEF, coef);
}

egl_result_t egl_rfm66_timer2_coef_set(egl_rfm66_t *rfm, uint8_t coef)
{
    return egl_rfm66_write_byte(rfm, EGL_RFM66_REG_TIMER2_COEF, coef);
}

egl_result_t egl_rfm66_timer2_coef_get(egl_rfm66_t *rfm, uint8_t *coef)
{
    return egl_rfm66_read_byte(rfm, EGL_RFM66_REG_TIMER2_COEF, coef);
}

egl_result_t egl_rfm66_temp_monitor_state_set(egl_rfm66_t *rfm, bool state)
{
    egl_result_t result;
    egl_rfm66_reg_image_cal_t regval;

    result = egl_rfm66_read_byte(rfm, EGL_RFM66_REG_IMAGE_CAL, &regval.raw);
    EGL_RESULT_CHECK(result);

    regval.bitfield.temp_monitor_off = !state;

    return egl_rfm66_write_byte(rfm, EGL_RFM66_REG_IMAGE_CAL, regval.raw);
}

egl_result_t egl_rfm66_temp_monitor_state_get(egl_rfm66_t *rfm, bool *state)
{
    egl_result_t result;
    egl_rfm66_reg_image_cal_t regval;

    result = egl_rfm66_read_byte(rfm, EGL_RFM66_REG_IMAGE_CAL, &regval.raw);
    EGL_RESULT_CHECK(result);

    *state = !regval.bitfield.temp_monitor_off;

    return result;
}

egl_result_t egl_rfm66_temp_threshold_set(egl_rfm66_t *rfm, egl_rfm66_temp_threshold_t threshold)
{
    egl_result_t result;
    egl_rfm66_reg_image_cal_t regval;

    result = egl_rfm66_read_byte(rfm, EGL_RFM66_REG_IMAGE_CAL, &regval.raw);
    EGL_RESULT_CHECK(result);

    regval.bitfield.temp_threshold = threshold;

    return egl_rfm66_write_byte(rfm, EGL_RFM66_REG_IMAGE_CAL, regval.raw);
}

egl_result_t egl_rfm66_temp_threshold_get(egl_rfm66_t *rfm, egl_rfm66_temp_threshold_t *threshold)
{
    egl_result_t result;
    egl_rfm66_reg_image_cal_t regval;

    result = egl_rfm66_read_byte(rfm, EGL_RFM66_REG_IMAGE_CAL, &regval.raw);
    EGL_RESULT_CHECK(result);

    *threshold = regval.bitfield.temp_threshold;

    return result;
}

egl_result_t egl_rfm66_temp_change_set(egl_rfm66_t *rfm, egl_rfm66_temp_change_t change)
{
    egl_result_t result;
    egl_rfm66_reg_image_cal_t regval;

    result = egl_rfm66_read_byte(rfm, EGL_RFM66_REG_IMAGE_CAL, &regval.raw);
    EGL_RESULT_CHECK(result);

    regval.bitfield.temp_change = change;

    return egl_rfm66_write_byte(rfm, EGL_RFM66_REG_IMAGE_CAL, regval.raw);
}

egl_result_t egl_rfm66_temp_change_get(egl_rfm66_t *rfm, egl_rfm66_temp_change_t *change)
{
    egl_result_t result;
    egl_rfm66_reg_image_cal_t regval;

    result = egl_rfm66_read_byte(rfm, EGL_RFM66_REG_IMAGE_CAL, &regval.raw);
    EGL_RESULT_CHECK(result);

    *change = regval.bitfield.temp_change;

    return result;
}

egl_result_t egl_rfm66_image_cal_start(egl_rfm66_t *rfm)
{
    egl_result_t result;
    egl_rfm66_reg_image_cal_t regval;

    result = egl_rfm66_read_byte(rfm, EGL_RFM66_REG_IMAGE_CAL, &regval.raw);
    EGL_RESULT_CHECK(result);

    regval.bitfield.image_cal_start = true;

    return egl_rfm66_write_byte(rfm, EGL_RFM66_REG_IMAGE_CAL, regval.raw);
}

egl_result_t egl_rfm66_image_cal_state_get(egl_rfm66_t *rfm, bool *state)
{
    egl_result_t result;
    egl_rfm66_reg_image_cal_t regval;

    result = egl_rfm66_read_byte(rfm, EGL_RFM66_REG_IMAGE_CAL, &regval.raw);
    EGL_RESULT_CHECK(result);

    *state = regval.bitfield.image_cal_running;

    return result;
}

egl_result_t egl_rfm66_auto_image_cal_state_set(egl_rfm66_t *rfm, bool state)
{
    egl_result_t result;
    egl_rfm66_reg_image_cal_t regval;

    result = egl_rfm66_read_byte(rfm, EGL_RFM66_REG_IMAGE_CAL, &regval.raw);
    EGL_RESULT_CHECK(result);

    regval.bitfield.auto_image_cal_on = state;

    return egl_rfm66_write_byte(rfm, EGL_RFM66_REG_IMAGE_CAL, regval.raw);
}

egl_result_t egl_rfm66_auto_image_cal_state_get(egl_rfm66_t *rfm, bool *state)
{
    egl_result_t result;
    egl_rfm66_reg_image_cal_t regval;

    result = egl_rfm66_read_byte(rfm, EGL_RFM66_REG_IMAGE_CAL, &regval.raw);
    EGL_RESULT_CHECK(result);

    *state = regval.bitfield.auto_image_cal_on;

    return result;
}

egl_result_t egl_rfm66_temp_get(egl_rfm66_t *rfm, int8_t *temp)
{
    uint8_t raw;
    egl_result_t result;

    result = egl_rfm66_read_byte(rfm, EGL_RFM66_REG_TEMP, &raw);
    EGL_RESULT_CHECK(result);

    *temp = -(int8_t)raw;

    return result;
}

egl_result_t egl_rfm66_low_bat_trim_set(egl_rfm66_t *rfm, egl_rfm66_low_bat_trim_t trim)
{
    egl_result_t result;
    egl_rfm66_reg_low_bat_t regval;

    result = egl_rfm66_read_byte(rfm, EGL_RFM66_REG_LOW_BAT, &regval.raw);
    EGL_RESULT_CHECK(result);

    regval.bitfield.low_bat_trim = trim;

    return egl_rfm66_write_byte(rfm, EGL_RFM66_REG_LOW_BAT, regval.raw);
}

egl_result_t egl_rfm66_low_bat_trim_get(egl_rfm66_t *rfm, egl_rfm66_low_bat_trim_t *trim)
{
    egl_result_t result;
    egl_rfm66_reg_low_bat_t regval;

    result = egl_rfm66_read_byte(rfm, EGL_RFM66_REG_LOW_BAT, &regval.raw);
    EGL_RESULT_CHECK(result);

    *trim = regval.bitfield.low_bat_trim;

    return result;
}

egl_result_t egl_rfm66_low_bat_state_set(egl_rfm66_t *rfm, bool state)
{
    egl_result_t result;
    egl_rfm66_reg_low_bat_t regval;

    result = egl_rfm66_read_byte(rfm, EGL_RFM66_REG_LOW_BAT, &regval.raw);
    EGL_RESULT_CHECK(result);

    regval.bitfield.low_bat_on = state;

    return egl_rfm66_write_byte(rfm, EGL_RFM66_REG_LOW_BAT, regval.raw);
}

egl_result_t egl_rfm66_low_bat_state_get(egl_rfm66_t *rfm, bool *state)
{
    egl_result_t result;
    egl_rfm66_reg_low_bat_t regval;

    result = egl_rfm66_read_byte(rfm, EGL_RFM66_REG_LOW_BAT, &regval.raw);
    EGL_RESULT_CHECK(result);

    *state = regval.bitfield.low_bat_on;

    return result;
}

egl_result_t egl_rfm66_flags_get(egl_rfm66_t *rfm, egl_rfm66_irq_flags_t *flags)
{
    return egl_rfm66_read_burst(rfm, EGL_RFM66_REG_IRQ_FLAGS1, &flags->raw, sizeof(*flags));
}

egl_result_t egl_rfm66_dio0_mode_set(egl_rfm66_t *rfm, egl_rfm66_dio_mode_t mode)
{
    egl_result_t result;
    egl_rfm66_reg_dio_map1_t regval;

    result = egl_rfm66_read_byte(rfm, EGL_RFM66_REG_DIO_MAP1, &regval.raw);
    EGL_RESULT_CHECK(result);

    regval.bitfield.dio0 = mode;

    return egl_rfm66_write_byte(rfm, EGL_RFM66_REG_DIO_MAP1, regval.raw);
}

egl_result_t egl_rfm66_dio0_mode_get(egl_rfm66_t *rfm, egl_rfm66_dio_mode_t *mode)
{
    egl_result_t result;
    egl_rfm66_reg_dio_map1_t regval;

    result = egl_rfm66_read_byte(rfm, EGL_RFM66_REG_DIO_MAP1, &regval.raw);
    EGL_RESULT_CHECK(result);

    *mode = regval.bitfield.dio0;

    return result;
}

egl_result_t egl_rfm66_dio1_mode_set(egl_rfm66_t *rfm, egl_rfm66_dio_mode_t mode)
{
    egl_result_t result;
    egl_rfm66_reg_dio_map1_t regval;

    result = egl_rfm66_read_byte(rfm, EGL_RFM66_REG_DIO_MAP1, &regval.raw);
    EGL_RESULT_CHECK(result);

    regval.bitfield.dio1 = mode;

    return egl_rfm66_write_byte(rfm, EGL_RFM66_REG_DIO_MAP1, regval.raw);
}

egl_result_t egl_rfm66_dio1_mode_get(egl_rfm66_t *rfm, egl_rfm66_dio_mode_t *mode)
{
    egl_result_t result;
    egl_rfm66_reg_dio_map1_t regval;

    result = egl_rfm66_read_byte(rfm, EGL_RFM66_REG_DIO_MAP1, &regval.raw);
    EGL_RESULT_CHECK(result);

    *mode = regval.bitfield.dio1;

    return result;
}

egl_result_t egl_rfm66_dio2_mode_set(egl_rfm66_t *rfm, egl_rfm66_dio_mode_t mode)
{
    egl_result_t result;
    egl_rfm66_reg_dio_map1_t regval;

    result = egl_rfm66_read_byte(rfm, EGL_RFM66_REG_DIO_MAP1, &regval.raw);
    EGL_RESULT_CHECK(result);

    regval.bitfield.dio2 = mode;

    return egl_rfm66_write_byte(rfm, EGL_RFM66_REG_DIO_MAP1, regval.raw);
}

egl_result_t egl_rfm66_dio2_mode_get(egl_rfm66_t *rfm, egl_rfm66_dio_mode_t *mode)
{
    egl_result_t result;
    egl_rfm66_reg_dio_map1_t regval;

    result = egl_rfm66_read_byte(rfm, EGL_RFM66_REG_DIO_MAP1, &regval.raw);
    EGL_RESULT_CHECK(result);

    *mode = regval.bitfield.dio2;

    return result;
}

egl_result_t egl_rfm66_dio3_mode_set(egl_rfm66_t *rfm, egl_rfm66_dio_mode_t mode)
{
    egl_result_t result;
    egl_rfm66_reg_dio_map1_t regval;

    result = egl_rfm66_read_byte(rfm, EGL_RFM66_REG_DIO_MAP1, &regval.raw);
    EGL_RESULT_CHECK(result);

    regval.bitfield.dio3 = mode;

    return egl_rfm66_write_byte(rfm, EGL_RFM66_REG_DIO_MAP1, regval.raw);
}

egl_result_t egl_rfm66_dio3_mode_get(egl_rfm66_t *rfm, egl_rfm66_dio_mode_t *mode)
{
    egl_result_t result;
    egl_rfm66_reg_dio_map1_t regval;

    result = egl_rfm66_read_byte(rfm, EGL_RFM66_REG_DIO_MAP1, &regval.raw);
    EGL_RESULT_CHECK(result);

    *mode = regval.bitfield.dio3;

    return result;
}

egl_result_t egl_rfm66_dio4_mode_set(egl_rfm66_t *rfm, egl_rfm66_dio_mode_t mode)
{
    egl_result_t result;
    egl_rfm66_reg_dio_map2_t regval;

    result = egl_rfm66_read_byte(rfm, EGL_RFM66_REG_DIO_MAP2, &regval.raw);
    EGL_RESULT_CHECK(result);

    regval.bitfield.dio4 = mode;

    return egl_rfm66_write_byte(rfm, EGL_RFM66_REG_DIO_MAP2, regval.raw);
}

egl_result_t egl_rfm66_dio4_mode_get(egl_rfm66_t *rfm, egl_rfm66_dio_mode_t *mode)
{
    egl_result_t result;
    egl_rfm66_reg_dio_map2_t regval;

    result = egl_rfm66_read_byte(rfm, EGL_RFM66_REG_DIO_MAP2, &regval.raw);
    EGL_RESULT_CHECK(result);

    *mode = regval.bitfield.dio4;

    return result;
}

egl_result_t egl_rfm66_dio5_mode_set(egl_rfm66_t *rfm, egl_rfm66_dio_mode_t mode)
{
    egl_result_t result;
    egl_rfm66_reg_dio_map2_t regval;

    result = egl_rfm66_read_byte(rfm, EGL_RFM66_REG_DIO_MAP2, &regval.raw);
    EGL_RESULT_CHECK(result);

    regval.bitfield.dio5 = mode;

    return egl_rfm66_write_byte(rfm, EGL_RFM66_REG_DIO_MAP2, regval.raw);
}

egl_result_t egl_rfm66_dio5_mode_get(egl_rfm66_t *rfm, egl_rfm66_dio_mode_t *mode)
{
    egl_result_t result;
    egl_rfm66_reg_dio_map2_t regval;

    result = egl_rfm66_read_byte(rfm, EGL_RFM66_REG_DIO_MAP2, &regval.raw);
    EGL_RESULT_CHECK(result);

    *mode = regval.bitfield.dio5;

    return result;
}

egl_result_t egl_rfm66_map_preamble_detect_set(egl_rfm66_t *rfm, egl_rfm66_map_preamble_detect_t map)
{
    egl_result_t result;
    egl_rfm66_reg_dio_map2_t regval;

    result = egl_rfm66_read_byte(rfm, EGL_RFM66_REG_DIO_MAP2, &regval.raw);
    EGL_RESULT_CHECK(result);

    regval.bitfield.map_preamble_detect = map;

    return egl_rfm66_write_byte(rfm, EGL_RFM66_REG_DIO_MAP2, regval.raw);
}

egl_result_t egl_rfm66_map_preamble_detect_get(egl_rfm66_t *rfm, egl_rfm66_map_preamble_detect_t *map)
{
    egl_result_t result;
    egl_rfm66_reg_dio_map2_t regval;

    result = egl_rfm66_read_byte(rfm, EGL_RFM66_REG_DIO_MAP2, &regval.raw);
    EGL_RESULT_CHECK(result);

    *map = regval.bitfield.map_preamble_detect;

    return result;
}

egl_result_t egl_rfm66_agc_reference_level_set(egl_rfm66_t *rfm, uint8_t level)
{
    EGL_ASSERT_CHECK(level < 64, EGL_OUT_OF_BOUNDARY);

    return egl_rfm66_write_byte(rfm, EGL_RFM66_REG_AGC_REF, level);
}

egl_result_t egl_rfm66_agc_reference_level_get(egl_rfm66_t *rfm, uint8_t *level)
{
    return egl_rfm66_read_byte(rfm, EGL_RFM66_REG_AGC_REF, level);
}

egl_result_t egl_rfm66_agc_step1_set(egl_rfm66_t *rfm, uint8_t step)
{
    EGL_ASSERT_CHECK(step < 16, EGL_OUT_OF_BOUNDARY);

    egl_result_t result;
    egl_rfm66_reg_agc_thresh1_t regval;

    result = egl_rfm66_read_byte(rfm, EGL_RFM66_REG_AGC_THRESH1, &regval.raw);
    EGL_RESULT_CHECK(result);

    regval.bitfield.agc_step1 = step;

    return egl_rfm66_write_byte(rfm, EGL_RFM66_REG_AGC_THRESH1, step);
}

egl_result_t egl_rfm66_agc_step1_get(egl_rfm66_t *rfm, uint8_t *step)
{
    egl_result_t result;
    egl_rfm66_reg_agc_thresh1_t regval;

    result = egl_rfm66_read_byte(rfm, EGL_RFM66_REG_AGC_THRESH1, &regval.raw);
    EGL_RESULT_CHECK(result);

    *step = regval.bitfield.agc_step1;

    return result;
}

egl_result_t egl_rfm66_agc_step2_set(egl_rfm66_t *rfm, uint8_t step)
{
    EGL_ASSERT_CHECK(step < 16, EGL_OUT_OF_BOUNDARY);

    egl_result_t result;
    egl_rfm66_reg_agc_thresh2_t regval;

    result = egl_rfm66_read_byte(rfm, EGL_RFM66_REG_AGC_THRESH2, &regval.raw);
    EGL_RESULT_CHECK(result);

    regval.bitfield.agc_step2 = step;

    return egl_rfm66_write_byte(rfm, EGL_RFM66_REG_AGC_THRESH2, regval.raw);
}

egl_result_t egl_rfm66_agc_step2_get(egl_rfm66_t *rfm, uint8_t *step)
{
    egl_result_t result;
    egl_rfm66_reg_agc_thresh2_t regval;

    result = egl_rfm66_read_byte(rfm, EGL_RFM66_REG_AGC_THRESH2, &regval.raw);
    EGL_RESULT_CHECK(result);

    *step = regval.bitfield.agc_step2;

    return result;
}

egl_result_t egl_rfm66_agc_step3_set(egl_rfm66_t *rfm, uint8_t step)
{
    EGL_ASSERT_CHECK(step < 16, EGL_OUT_OF_BOUNDARY);

    egl_result_t result;
    egl_rfm66_reg_agc_thresh2_t regval;

    result = egl_rfm66_read_byte(rfm, EGL_RFM66_REG_AGC_THRESH2, &regval.raw);
    EGL_RESULT_CHECK(result);

    regval.bitfield.agc_step3 = step;

    return egl_rfm66_write_byte(rfm, EGL_RFM66_REG_AGC_THRESH2, regval.raw);
}

egl_result_t egl_rfm66_agc_step3_get(egl_rfm66_t *rfm, uint8_t *step)
{
    egl_result_t result;
    egl_rfm66_reg_agc_thresh2_t regval;

    result = egl_rfm66_read_byte(rfm, EGL_RFM66_REG_AGC_THRESH2, &regval.raw);
    EGL_RESULT_CHECK(result);

    *step = regval.bitfield.agc_step3;

    return result;
}

egl_result_t egl_rfm66_agc_step4_set(egl_rfm66_t *rfm, uint8_t step)
{
    EGL_ASSERT_CHECK(step < 16, EGL_OUT_OF_BOUNDARY);

    egl_result_t result;
    egl_rfm66_reg_agc_thresh3_t regval;

    result = egl_rfm66_read_byte(rfm, EGL_RFM66_REG_AGC_THRESH3, &regval.raw);
    EGL_RESULT_CHECK(result);

    regval.bitfield.agc_step4 = step;

    return egl_rfm66_write_byte(rfm, EGL_RFM66_REG_AGC_THRESH3, regval.raw);
}

egl_result_t egl_rfm66_agc_step4_get(egl_rfm66_t *rfm, uint8_t *step)
{
    egl_result_t result;
    egl_rfm66_reg_agc_thresh3_t regval;

    result = egl_rfm66_read_byte(rfm, EGL_RFM66_REG_AGC_THRESH3, &regval.raw);
    EGL_RESULT_CHECK(result);

    *step = regval.bitfield.agc_step4;

    return result;
}

egl_result_t egl_rfm66_agc_step5_set(egl_rfm66_t *rfm, uint8_t step)
{
    EGL_ASSERT_CHECK(step < 16, EGL_OUT_OF_BOUNDARY);

    egl_result_t result;
    egl_rfm66_reg_agc_thresh3_t regval;

    result = egl_rfm66_read_byte(rfm, EGL_RFM66_REG_AGC_THRESH3, &regval.raw);
    EGL_RESULT_CHECK(result);

    regval.bitfield.agc_step5 = step;

    return egl_rfm66_write_byte(rfm, EGL_RFM66_REG_AGC_THRESH3, regval.raw);
}

egl_result_t egl_rfm66_agc_step5_get(egl_rfm66_t *rfm, uint8_t *step)
{
    egl_result_t result;
    egl_rfm66_reg_agc_thresh3_t regval;

    result = egl_rfm66_read_byte(rfm, EGL_RFM66_REG_AGC_THRESH3, &regval.raw);
    EGL_RESULT_CHECK(result);

    *step = regval.bitfield.agc_step5;

    return result;
}