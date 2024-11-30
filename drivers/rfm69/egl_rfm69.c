#include "egl_rfm69.h"
#include "egl_log.h"
#include "egl_util.h"

#define EGL_MODULE_NAME "egl_rfm69"

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
    return egl_rfm69_write_burst(rfm, EGL_RFM69_REG_BITRATE_LSB, (uint8_t *)&bitrate_val, sizeof(bitrate_val));
}

egl_result_t egl_rfm69_bitrate_get(egl_rfm69_t *rfm, uint32_t *bitrate)
{
    egl_result_t result;
    uint16_t bitrate_val;

    result = egl_rfm69_read_burst(rfm, EGL_RFM69_REG_BITRATE_LSB, &bitrate_val, sizeof(bitrate_val));
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
    uint8_t regval;

    result = egl_rfm69_read_byte(rfm, EGL_RFM69_REG_DATA_MODUL, &regval);
    EGL_RESULT_CHECK(result);

    regval &= ~EGL_RFM69_MODULATION_SHAPING_MASK;
    regval |= (uint8_t)modsh;

    return egl_rfm69_write_byte(rfm, EGL_RFM69_REG_DATA_MODUL, regval);
}

egl_result_t egl_rfm69_modulation_shaping_get(egl_rfm69_t *rfm, egl_rfm69_modulation_shaping_t *modsh)
{
    egl_result_t result;
    uint8_t regval;

    result = egl_rfm69_read_byte(rfm, EGL_RFM69_REG_DATA_MODUL, &regval);
    EGL_RESULT_CHECK(result);

    *modsh = (egl_rfm69_modulation_shaping_t)(regval & EGL_RFM69_MODULATION_SHAPING_MASK);

    return result;
}

egl_result_t egl_rfm69_modulation_type_set(egl_rfm69_t *rfm, egl_rfm69_modulation_type_t modtype)
{
    egl_result_t result;
    uint8_t regval;

    result = egl_rfm69_read_byte(rfm, EGL_RFM69_REG_DATA_MODUL, &regval);
    EGL_RESULT_CHECK(result);

    regval &= ~EGL_RFM69_MODULATION_TYPE_MASK;
    regval |= ((uint8_t)modtype) << EGL_RFM69_MODULATION_TYPE_SHIFT;

    return egl_rfm69_write_byte(rfm, EGL_RFM69_REG_DATA_MODUL, regval);
}

egl_result_t egl_rfm69_modulation_type_get(egl_rfm69_t *rfm, egl_rfm69_modulation_type_t *modtype)
{
    egl_result_t result;
    uint8_t regval;

    result = egl_rfm69_read_byte(rfm, EGL_RFM69_REG_DATA_MODUL, &regval);
    EGL_RESULT_CHECK(result);

    *modtype = (egl_rfm69_modulation_type_t)((regval & EGL_RFM69_MODULATION_TYPE_MASK) >>
                                                       EGL_RFM69_MODULATION_TYPE_SHIFT);

    return result;
}

egl_result_t egl_rfm69_data_mode_set(egl_rfm69_t *rfm, egl_rfm69_data_mode_t mode)
{
    egl_result_t result;
    uint8_t regval;

    result = egl_rfm69_read_byte(rfm, EGL_RFM69_REG_DATA_MODUL, &regval);
    EGL_RESULT_CHECK(result);

    regval &= ~EGL_RFM69_DATA_MODE_MASK;
    regval |= ((uint8_t)mode) << EGL_RFM69_DATA_MODE_SHIFT;

    return egl_rfm69_write_byte(rfm, EGL_RFM69_REG_DATA_MODUL, regval);
}

egl_result_t egl_rfm69_data_mode_get(egl_rfm69_t *rfm, egl_rfm69_data_mode_t *mode)
{
    egl_result_t result;
    uint8_t regval;

    result = egl_rfm69_read_byte(rfm, EGL_RFM69_REG_DATA_MODUL, &regval);
    EGL_RESULT_CHECK(result);

    *mode = (egl_rfm69_data_mode_t)((regval & EGL_RFM69_DATA_MODE_MASK) >>
                                              EGL_RFM69_DATA_MODE_SHIFT);

    return result;
}

