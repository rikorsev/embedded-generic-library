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

#if CONFIG_EGL_RESULT_ERROR_HOOK_ENABLED
static egl_result_error_hook_t *egl_result_error_hook = NULL;
#endif

void egl_result_error_hook_set(egl_result_error_hook_t *hook)
{
#if CONFIG_EGL_RESULT_ERROR_HOOK_ENABLED
    egl_result_error_hook = hook;
#endif
}

egl_result_error_hook_t *egl_result_error_hook_get(void)
{
#if CONFIG_EGL_RESULT_ERROR_HOOK_ENABLED
    return egl_result_error_hook;
#else
    return NULL;
#endif
}

egl_result_t egl_result_error_hook_call(egl_result_t result, char *file, unsigned int line)
{
#if CONFIG_EGL_RESULT_ERROR_HOOK_ENABLED
    if(egl_result_error_hook != NULL && egl_result_error_hook->func != NULL)
    {
        return egl_result_error_hook->func(result, file, line, egl_result_error_hook->ctx);
    }
#endif
    return result;
}

const char *egl_result_str_get(egl_result_t result)
{
    assert(result < EGL_LAST);

    return egl_result_str[result];
}
