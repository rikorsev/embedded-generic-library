#include "egl_rfm69.h"
#include "egl_log.h"
#include "egl_util.h"

#define EGL_MODULE_NAME "egl_rfm69"

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
}egl_rfm_reg_osc1_t;

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

egl_result_t egl_rfm_rc_calib_start(egl_rfm69_t *rfm)
{
    egl_rfm_reg_osc1_t regval;

    regval.bitfield.calib_start = true;

    return egl_rfm69_write_byte(rfm, EGL_RFM69_REG_OSC1, regval.raw);
}

egl_result_t egl_rfm_rc_calib_state_get(egl_rfm69_t *rfm, egl_rfm69_rc_calib_state_t *state)
{
    egl_result_t result;
    egl_rfm_reg_osc1_t regval;

    result = egl_rfm69_read_byte(rfm, EGL_RFM69_REG_OSC1, &regval.raw);
    EGL_RESULT_CHECK(result);

    *state = regval.bitfield.calib_state;

    return result;
}