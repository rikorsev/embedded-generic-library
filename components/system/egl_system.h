#ifndef EGL_SYSTEM_H
#define EGL_SYSTEM_H

#include "egl_result.h"
#include "egl_log.h"
#include "egl_clock.h"
#include "egl_pm.h"
#include "egl_timer.h"
#include "egl_plat.h"

#define SYSPLAT egl_sys_plat_get()
#define SYSLOG egl_sys_log_get()
#define SYSCLOCK egl_sys_clock_get()
#define SYSPM egl_sys_pm_get()
#define SYSTIMER egl_sys_timer_get()

typedef struct
{
    egl_platform_t *plat;
    egl_log_t *syslog;
    egl_clock_t *sysclock;
    egl_pm_t *syspm;
    egl_timer_t *systimer;
}egl_system_t;

egl_result_t   egl_system_init(egl_system_t *system);
egl_platform_t *egl_sys_plat_get(void);
egl_log_t      *egl_sys_log_get(void);
egl_clock_t    *egl_sys_clock_get(void);
egl_pm_t       *egl_sys_pm_get(void);
egl_timer_t    *egl_sys_timer_get(void);
egl_result_t   egl_sys_delay(uint32_t ms);
egl_result_t   egl_system_deinit(void);

#endif