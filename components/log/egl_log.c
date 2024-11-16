#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

#include "egl_result.h"
#include "egl_log.h"

static const char *m_level_str[] =
{
    "DEBUG",
    "INFO",
    "WARN",
    "ERROR",
    "FAIL"
};

static egl_log_t *default_logger = NULL;

egl_result_t egl_log_init(egl_log_t *log, egl_interface_t *iface, egl_timer_t *timer)
{
    EGL_ASSERT_CHECK(log, EGL_ASSERT_FAIL);
    EGL_ASSERT_CHECK(iface, EGL_ASSERT_FAIL);

    log->iface = iface;
    log->timer = timer;

    return EGL_SUCCESS;
}

egl_result_t egl_log_default_set(egl_log_t *log)
{
    default_logger = log;
    return EGL_SUCCESS;
}

egl_log_t *egl_log_default_get()
{
    return default_logger;
}

egl_result_t egl_log(egl_log_t *log, egl_log_level_t lvl, char *module, char *format, ...)
{
    va_list arg;
    unsigned int offset = 0;
    int result;

    EGL_ASSERT_CHECK(log, EGL_ASSERT_FAIL);
    EGL_ASSERT_CHECK(format, EGL_ASSERT_FAIL);
    EGL_ASSERT_CHECK(lvl < EGL_LOG_LEVEL_LAST, EGL_ASSERT_FAIL);
    EGL_ASSERT_CHECK(log->iface, EGL_ASSERT_FAIL);

    if(log->timer)
    {
        result = snprintf(log->buff, sizeof(log->buff),"[%08u]",
                                            (unsigned int)egl_timer_get(log->timer));
        EGL_ASSERT_CHECK(result > 0, EGL_ASSERT_FAIL);
        offset += result;
    }

    result = snprintf(log->buff + offset, sizeof(log->buff) - offset, "[%s]", m_level_str[lvl]);
    EGL_ASSERT_CHECK(result > 0, EGL_ASSERT_FAIL);
    offset += result;

    if(module != NULL)
    {
        result = snprintf(log->buff + offset, sizeof(log->buff) - offset, "%s: ", module);
        EGL_ASSERT_CHECK(result > 0, EGL_ASSERT_FAIL);
        offset += result;
    }

    va_start(arg, format);
    result = vsnprintf(log->buff + offset, sizeof(log->buff) - offset, format, arg);
    EGL_ASSERT_CHECK(result > 0, EGL_ASSERT_FAIL);
    offset += result;
    va_end(arg);

    result = snprintf(log->buff + offset, sizeof(log->buff) - offset, "\r\n");
    EGL_ASSERT_CHECK(result > 0, EGL_ASSERT_FAIL);
    offset += result;

    return egl_itf_write(log->iface, log->buff, &offset);
}
