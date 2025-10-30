#include <assert.h>
#include <stdlib.h>

#include "egl_result.h"

static const char *egl_result_str[] =
{
    "EGL_SUCCESS",
    "EGL_SET",
    "EGL_UNKNOWN",
    "EGL_FAIL",
    "EGL_PROCESS",
    "EGL_NOT_SUPPORTED",
    "EGL_OUT_OF_BOUNDARY",
    "EGL_INVALID_PARAM",
    "EGL_INVALID_STATE",
    "EGL_ASSERT_FAIL",
    "EGL_TIMEOUT"
};

#if CONFIG_EGL_RESULT_ERROR_HANDLER_ENABLED
static egl_result_error_handler_t *egl_result_error_handler = NULL;
#endif

void egl_result_error_handler_set(egl_result_error_handler_t *handler)
{
#if CONFIG_EGL_RESULT_ERROR_HANDLER_ENABLED
    egl_result_error_handler = handler;
#endif
}

egl_result_error_handler_t *egl_result_error_handler_get(void)
{
#if CONFIG_EGL_RESULT_ERROR_HANDLER_ENABLED
    return egl_result_error_handler;
#else
    return NULL;
#endif
}

egl_result_t egl_result_error_handler_call(egl_result_t result, char *file, unsigned int line)
{
#if CONFIG_EGL_RESULT_ERROR_HANDLER_ENABLED
    if(egl_result_error_handler != NULL && egl_result_error_handler->func != NULL)
    {
        return egl_result_error_handler->func(result, file, line, egl_result_error_handler->ctx);
    }
#endif
    return result;
}

const char *egl_result_str_get(egl_result_t result)
{
    assert(result < EGL_LAST);

    return egl_result_str[result];
}
