/**
 * @file The module represents platform specific functions
 */

#ifndef EGL_PLAT_H
#define EGL_PLAT_H

#include <stdint.h>

#include "egl_result.h"

#pragma pack(push, 4)

typedef struct
{
    uint8_t major;
    uint8_t minor;
    uint8_t revision;
    char sufix[CONFIG_EGL_PLAT_INFO_VERSION_SUFIX_BUFF_SIZE];
}egl_plat_version_t;

typedef struct
{
    char branch[CONFIG_EGL_PLAT_INFO_GIT_BRANCH_SUFIX_BUFF_SIZE];
    char commit[CONFIG_EGL_PLAT_INFO_GIT_HASH_SUFIX_BUFF_SIZE];
}egl_git_t;

typedef struct
{
    uint32_t magic;
    uint32_t size;
    uint32_t checksum;
    char name[CONFIG_EGL_PLAT_INFO_NAME_BUFF_SIZE];
    char buildtime[CONFIG_EGL_PLAT_INFO_BUILDTIME_BUFF_SIZE];
    egl_plat_version_t version;
    egl_git_t git;
    uint32_t boot_number;
}egl_plat_info_t;

typedef struct
{
    egl_result_t    (*init)(void);
    egl_result_t    (*sleep)(uint32_t delay);
    egl_result_t    (*boot)(unsigned int slot_idx);
    egl_result_t    (*reboot)(void);
    egl_result_t    (*shutdown)(void);
    egl_plat_info_t *(*info)(void);
    egl_plat_info_t *(*slot_info)(unsigned int slot_idx);
    uint32_t        (*clock)(void);
}egl_platform_t;

#pragma pack(pop)

/**
 * @brief General platform initialization
 *
 * @param plat - pointer to platform
 *
 * @return EGL_SUCCESS in case of successful deinitialization
 */
egl_result_t egl_plat_init(egl_platform_t *plat);

/**
 * @brief Sleep for specified amoutn of time
 *
 * @param plat - pointer to platform instance
 * @param delay - amount of time to sleep (ms)
 */
egl_result_t egl_plat_sleep(egl_platform_t *plat, uint32_t delay);

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
 * @brief Perform platform reboot
 *
 * @param plat - pointer to platform instance
 *
 * @return Usualli it shouldn't return from the function. If it returns, return value will carry
 *         some nrgative result
 */
egl_result_t egl_plat_reboot(egl_platform_t *plat);

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
egl_plat_info_t *egl_plat_info(egl_platform_t *plat);

/**
 * @brief Get application information from specific slot
 *
 * @param plat - pointer to platform instance
 * @param slot_idx - index of slot to get information from
 *
 * @return pointer to application information from specific slot
 */
egl_plat_info_t *egl_plat_slot_info(egl_platform_t *plat, unsigned int slot_idx);

/**
 * @brief Get platform clock frequency
 *
 * @param plat - pointer to platform instance
 *
 * @return Clock frequency in Hz
 */
uint32_t egl_plat_clock(egl_platform_t *plat);

#endif