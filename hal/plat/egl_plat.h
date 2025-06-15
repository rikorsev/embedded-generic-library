/**
 * @file The module represents platform specific functions
 */

#ifndef EGL_PLAT_H
#define EGL_PLAT_H

#include <stdint.h>

#include "egl_result.h"

typedef struct
{
    egl_result_t    (*init)(void);
    egl_result_t    (*boot)(unsigned int slot_idx);
    void            *(*info)(void);
    void            *(*slot_info)(unsigned int slot_idx);
    egl_result_t    (*deinit)(void);
}egl_platform_t;

/**
 * @brief General platform initialization
 *
 * @param plat - pointer to platform
 *
 * @return EGL_SUCCESS in case of successful deinitialization
 */
egl_result_t egl_plat_init(egl_platform_t *plat);

/**
 * @brief Deinitialize platform
 *
 * @param plat - pointer to platform instance
 *
 * @return EGL_SUCCESS in case of successful deinitialization
 */
egl_result_t egl_plat_deinit(egl_platform_t *plat);

/**
 * @brief Boot application from specific slot
 *
 * @param plat - pointer to platform instance
 * @param slot_idx - slot index to boot
 *
 * @return Usualli it shouldn't return from the function. If it returns, return value will carry
 *         some nrgative result
 */
egl_result_t egl_plat_boot(egl_platform_t *plat, unsigned int slot_idx);

/**
 * @brief Perform platform shutdown
 *
 * @param plat - pointer to platform instance
 *
 * @return Usualli it shouldn't return from the function. If it returns, return value will carry
 *         some nrgative result
 */
egl_result_t egl_plat_shutdown(egl_platform_t *plat);

/**
 * @brief Get application information
 *
 * @param plat - pointer to platform instance
 *
 * @return pointer to application information
 */
void *egl_plat_info(egl_platform_t *plat);

/**
 * @brief Get application information from specific slot
 *
 * @param plat - pointer to platform instance
 * @param slot_idx - index of slot to get information from
 *
 * @return pointer to application information from specific slot
 */
void *egl_plat_slot_info(egl_platform_t *plat, unsigned int slot_idx);

#endif