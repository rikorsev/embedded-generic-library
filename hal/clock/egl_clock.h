/**
 * @file The module represents any clock module
 */

#ifndef EGL_CLOCK_H
#define EGL_CLOCK_H

#include <stdint.h>
#include "egl_result.h"

typedef struct
{
    egl_result_t (*init)(uint32_t profile);
    uint32_t (*get)(void);
}egl_clock_t;

/**
 * @brief Initi clock unit
 *
 * @param clock - pointer to clock unit to init
 * @param profile - init profile id to apply
 * 
 * @return EGL_SUCCESS in case of successfull initialization
 */
egl_result_t egl_clock_init(egl_clock_t *clock, uint32_t profile);

/**
 * @brief Get frequency if the clock unit
 *
 * @param clock - pointer to clock to get frequency
 *
 * @return the clock unit frequency in Hz
 */
uint32_t egl_clock_get(egl_clock_t *clock);

#endif
