#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

#include "egl_result.h"
#include "egl_log.h"

#if CONFIG_EGL_LOG_COLOR_ENABLED
#define RESET   "\x1b[0m"
#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define WHITE   "\x1b[37m"
#define BOLD    "\x1b[1m"
#else
#define RESET
#define RED
#define GREEN
#define YELLOW
#define BLUE
#define WHITE
#define BOLD
#endif

static const char *m_level_str[] =
{
    BLUE   "DEBUG" WHITE,
    GREEN  "INFO"  WHITE,
    YELLOW "WARN"  WHITE,
    RED    "ERROR" WHITE,
    RED    "FAIL"  WHITE
};

egl_result_t egl_log_init(egl_log_t *log)
{
    EGL_ASSERT_CHECK(log, EGL_ASSERT_FAIL);
    EGL_ASSERT_CHECK(log->iface, EGL_ASSERT_FAIL);

    egl_result_t result;

    result = egl_iface_init(log->iface);
    EGL_RESULT_CHECK(result);

    if(log->timer)
    {
        result = egl_timer_init(log->timer);
        EGL_RESULT_CHECK(result);
    }

    return result;
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
        result = snprintf(log->buff, sizeof(log->buff), BOLD "[%08u]",
                                            (unsigned int)egl_timer_get(log->timer));
        EGL_ASSERT_CHECK(result > 0, EGL_ASSERT_FAIL);
        offset += result;
    }

    result = snprintf(log->buff + offset, sizeof(log->buff) - offset, BOLD "[%s]", m_level_str[lvl]);
    EGL_ASSERT_CHECK(result > 0, EGL_ASSERT_FAIL);
    offset += result;

    result = snprintf(log->buff + offset, sizeof(log->buff) - offset, "%s: " RESET, module);
    EGL_ASSERT_CHECK(result > 0, EGL_ASSERT_FAIL);
    offset += result;

    va_start(arg, format);
    result = vsnprintf(log->buff + offset, sizeof(log->buff) - offset, format, arg);
    EGL_ASSERT_CHECK(result > 0, EGL_ASSERT_FAIL);
    offset += result;
    va_end(arg);

    result = snprintf(log->buff + offset, sizeof(log->buff) - offset, "\r\n");
    EGL_ASSERT_CHECK(result > 0, EGL_ASSERT_FAIL);
    offset += result;

    return egl_iface_write(log->iface, log->buff, &offset);
}

egl_result_t egl_log_buff(egl_log_t *log, egl_log_level_t lvl, char *name, uint8_t *buff, size_t len, size_t row)
{
    EGL_ASSERT_CHECK(log, EGL_NULL_POINTER);
    EGL_ASSERT_CHECK(buff, EGL_NULL_POINTER);
    EGL_ASSERT_CHECK(name, EGL_NULL_POINTER);

    egl_result_t result;
    char formatted[row * 3 + 1]; // 2 hex digits + space + null terminator

    result = egl_log(log, lvl, name, "Size(%u):", (unsigned int)len);
    EGL_RESULT_CHECK(result);

    for(size_t i = 0; i < len; i += row)
    {
        memset(formatted, 0, sizeof(formatted));

        for(size_t j = 0; j < row; j++)
        {
            snprintf(formatted + j * 3, sizeof(formatted) - j * 3, "%02x ", buff[i + j]);
        }

        result = egl_log(log, lvl, name, "%s", formatted);
        EGL_RESULT_CHECK(result);
    }

    return EGL_SUCCESS;
}

egl_result_t egl_log_deinit(egl_log_t *log)
{
    EGL_ASSERT_CHECK(log, EGL_ASSERT_FAIL);
    EGL_ASSERT_CHECK(log->iface, EGL_ASSERT_FAIL);

    egl_result_t result;

    result = egl_iface_deinit(log->iface);
    EGL_RESULT_CHECK(result);

    if(log->timer)
    {
        result = egl_timer_deinit(log->timer);
        EGL_RESULT_CHECK(result);
    }

    return result;
}
