/**
 * @file The module represents any clock module
 */

#ifndef EGL_CLOCK_H
#define EGL_CLOCK_H

#include <stdint.h>
#include "egl_result.h"

typedef struct
{
    egl_result_t (*init)(void);
    uint32_t (*get)(void);
    egl_result_t (*deinit)(void);
}egl_clock_t;

/**
 * @brief Initi clock unit
 *
 * @param clock - pointer to clock unit to init
 * 
 * @return EGL_SUCCESS in case of successfull initialization
 */
egl_result_t egl_clock_init(egl_clock_t *clock);

/**
 * @brief Get frequency if the clock unit
 *
 * @param clock - pointer to clock to get frequency
 *
 * @return the clock unit frequency in Hz
 */
uint32_t egl_clock_get(egl_clock_t *clock);

/**
 * @brief Deinit clock unit
 *
 * @param clock - pointer to clock unit to deinit
 *
 * @return EGL_SUCCESS in case of successfull deinitialization
 */
egl_result_t egl_clock_deinit(egl_clock_t *clock);

#endif
