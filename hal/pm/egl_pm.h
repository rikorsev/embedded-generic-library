/**
 * @file The module represents Power Manager for specific unit
 */

#ifndef EGL_PM_H
#define EGL_PM_H

#include <stdint.h>

#include "egl_result.h"

typedef struct
{
    egl_result_t (*init)(void);
    egl_result_t (*poweron)(void);
    egl_result_t (*mode_set)(uint32_t mode);
    egl_result_t (*sleep)(uint32_t delay);
    egl_result_t (*reset)(void);
    egl_result_t (*shutdown)(void);
    egl_result_t (*deinit)(void);
}egl_pm_t;

/**
 * @brief Init specific power unit
 *
 * @param pm - pointer to PM instance
 *
 * @return EGL_SUCCESS in case of successful initialization
 */
egl_result_t egl_pm_init(egl_pm_t *pm);

/**
 * @brief Power On specific unit
 *
 * @param pm - pointer to PM instance
 *
 * @return EGL_SUCCESS in case of successful poweron
 */
egl_result_t egl_pm_poweron(egl_pm_t *pm);

/**
 * @brief Set specific power profile to the unit
 * 
 * @param pm - pointer to pm instance
 * @param mode - profile id to apply
 *
 * @return EGL_SUCCESS in case if the profile applied successfuly
 */
egl_result_t egl_pm_mode_set(egl_pm_t *pm, uint32_t mode);

/**
 * @brief Sleep for specified amoutn of time
 *
 * @param pm - pointer to PM instance
 * @param delay - amount of time to sleep (ms)
 *
 * @return EGL_SUCCESS in case of successful delay
 */
egl_result_t egl_pm_sleep(egl_pm_t *pm, uint32_t delay);

/**
 * @brief Perform a unit reset
 *
 * @param plat - pointer to PM instance
 *
 * @return EGL_SUCCESS in case of successful reset
 */
egl_result_t egl_pm_reset(egl_pm_t *pm);

/**
 * @brief Perform a unit shutdown
 *
 * @param pm - pointer to PM instance
 *
 * @return EGL_SUCCESS in case of successful shutdown
 */
egl_result_t egl_pm_shutdown(egl_pm_t *pm);

/**
 * @brief Denit specific power unit
 *
 * @param pm - pointer to PM instance
 *
 * @return EGL_SUCCESS in case of successful deinitialization
 */
egl_result_t egl_pm_deinit(egl_pm_t *pm);

#endif