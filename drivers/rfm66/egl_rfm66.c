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
}egl_rfm6_reg_pa_config_t;
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
    egl_rfm6_reg_pa_config_t regval;

    result = egl_rfm66_read_byte(rfm, EGL_RFM66_REG_PA_CONFIG, &regval.raw);
    EGL_RESULT_CHECK(result);

    regval.bitfield.pa_power = power;

    return egl_rfm66_write_byte(rfm, EGL_RFM66_REG_PA_CONFIG, regval.raw);
}

egl_result_t egl_rfm66_pa_power_get(egl_rfm66_t *rfm, uint8_t *power)
{
    egl_result_t result;
    egl_rfm6_reg_pa_config_t regval;

    result = egl_rfm66_read_byte(rfm, EGL_RFM66_REG_PA_CONFIG, &regval.raw);
    EGL_RESULT_CHECK(result);

    *power = regval.bitfield.pa_power;

    return result;
}

egl_result_t egl_rfm66_pa_select_set(egl_rfm66_t *rfm, egl_rfm66_pa_select_t select)
{
    egl_result_t result;
    egl_rfm6_reg_pa_config_t regval;

    result = egl_rfm66_read_byte(rfm, EGL_RFM66_REG_PA_CONFIG, &regval.raw);
    EGL_RESULT_CHECK(result);

    regval.bitfield.pa_select = select;

    return egl_rfm66_write_byte(rfm, EGL_RFM66_REG_PA_CONFIG, regval.raw);
}

egl_result_t egl_rfm66_pa_select_get(egl_rfm66_t *rfm, egl_rfm66_pa_select_t *select)
{
    egl_result_t result;
    egl_rfm6_reg_pa_config_t regval;

    result = egl_rfm66_read_byte(rfm, EGL_RFM66_REG_PA_CONFIG, &regval.raw);
    EGL_RESULT_CHECK(result);

    *select = regval.bitfield.pa_select;

    return result;
}