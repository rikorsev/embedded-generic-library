/**
 * @file The module provides logging macroses
 */

#ifndef EGL_LOG_H
#define EGL_LOG_H

#include "egl_timer.h"
#include "egl_interface.h"

typedef enum
{
    EGL_LOG_LEVEL_DEBUG,
    EGL_LOG_LEVEL_INFO,
    EGL_LOG_LEVEL_WARN,
    EGL_LOG_LEVEL_ERROR,
    EGL_LOG_LEVEL_FAIL,
    EGL_LOG_LEVEL_LAST
}egl_log_level_t;

typedef struct
{
    egl_interface_t   *iface;
    egl_timer_t       *timer;
    char              buff[CONFIG_EGL_LOG_BUFF_SIZE];
}egl_log_t;

#if CONFIG_EGL_LOG_ENABLED
#define EGL_LOG_DEBUG(fmt, ...) egl_log(egl_log_default_get(), EGL_LOG_LEVEL_DEBUG, __FILENAME__, fmt, ##__VA_ARGS__)
#define EGL_LOG_INFO(fmt, ...)  egl_log(egl_log_default_get(), EGL_LOG_LEVEL_INFO,  __FILENAME__, fmt, ##__VA_ARGS__)
#define EGL_LOG_WARN(fmt, ...)  egl_log(egl_log_default_get(), EGL_LOG_LEVEL_WARN,  __FILENAME__, fmt, ##__VA_ARGS__)
#define EGL_LOG_ERROR(fmt, ...) egl_log(egl_log_default_get(), EGL_LOG_LEVEL_ERROR, __FILENAME__, fmt, ##__VA_ARGS__)
#define EGL_LOG_FAIL(fmt, ...)  egl_log(egl_log_default_get(), EGL_LOG_LEVEL_FAIL,  __FILENAME__, fmt, ##__VA_ARGS__)

/**
 * @brief init log module
 *
 * @param log   - pointer to log module
 * @param iface - pointer to serial interface that will be used to log the data
 * @param timer - pointer to timer that will provide timestamps
 *
 * @return EGL_SUCCESS in case of siccessfull initialization
 */
egl_result_t egl_log_init(egl_log_t *log, egl_interface_t *iface, egl_timer_t *timer);

/**
 * @brief Finction to log specific message
 *
 * Usually the function is not used directly. It is triggered through corresponding macroses
 * Like: EGL_LOG_INFO, EGL_LOG_ERROR etc
 *
 * @param log    - pointer to the log instance
 * @param lvl    - log level of the message like EGL_LOG_LEVEL_DEBUG, EGL_LOG_LEVEL_INFO etc
 * @param module - pointer to module name from which log function has called
 * @param format - pointer to format stirng
 * @param args   - variable number of arguments
 *
 * @return EGL_SUCCESS in case if the message has been logged successfully
 */
egl_result_t egl_log(egl_log_t *log, egl_log_level_t lvl, char *module, char *format, ...);

/**
 * @brief Set default logger
 *
 * Default logger is used by log marcoses to choosw through which logger data should be passsed
 *
 * @param log - pointer to default logger to set
 *
 * @return EGL_SUCCESS in case if the logger has been set successfully
 */
egl_result_t egl_log_default_set(egl_log_t *log);

/**
 * @brief Get default logger
 *
 * @return pointer to default logger
 */
egl_log_t *egl_log_default_get(void);
#else
#define EGL_LOG_DEBUG(fmt, ...)
#define EGL_LOG_INFO(fmt, ...)
#define EFL_LOG_WARN(fmt, ...)
#define EGL_LOG_ERROR(fmt, ...)
#define EGL_LOG_FAIL(fmt, ...)

egl_result_t egl_log_init(egl_log_t *log, egl_interface_t *iface) { return EGL_SUCCESS; }
egl_result_t egl_log(egl_log_t *log, egl_log_level_t lvl, char *module, char *format, ...) { return EGL_SUCCESS; }
egl_result_t egl_log_default_set(egl_log_t *log) { return EGL_SUCCESS; }
egl_log_t   *egl_log_default_get(void) { return EGL_SUCCESS; }
#endif

#endif /* EGL_LOG_H */
