#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>

#include "egl_result.h"
#include "egl_pio.h"

egl_result_t egl_pio_init(egl_pio_t *pio)
{
    EGL_ASSERT_CHECK(pio, EGL_ASSERT_FAIL);
    EGL_ASSERT_CHECK(pio->init, EGL_NOT_SUPPORTED);

    return pio->init();
}

egl_result_t egl_pio_set(egl_pio_t *pio, bool state)
{
    EGL_ASSERT_CHECK(pio, EGL_ASSERT_FAIL);
    EGL_ASSERT_CHECK(pio->set, EGL_NOT_SUPPORTED);

    return pio->set(state);
}

egl_result_t egl_pio_get(egl_pio_t *pio, bool *state)
{
    EGL_ASSERT_CHECK(pio, EGL_ASSERT_FAIL);
    EGL_ASSERT_CHECK(pio->get, EGL_NOT_SUPPORTED);

    return pio->get(state);
}

egl_result_t egl_pio_toggle(egl_pio_t *pio)
{
    EGL_ASSERT_CHECK(pio, EGL_ASSERT_FAIL);

    bool state;

    egl_result_t result = egl_pio_get(pio, &state);
    EGL_RESULT_CHECK(result);

    if(state)
    {
        result = egl_pio_set(pio, false);
        EGL_RESULT_CHECK(result);
    }
    else
    {
        result = egl_pio_set(pio, true);
        EGL_RESULT_CHECK(result);
    }

    return result;
}

egl_result_t egl_pio_callback_set(egl_pio_t *pio, egl_pio_callback_t callback)
{
    EGL_ASSERT_CHECK(pio, EGL_ASSERT_FAIL);

    pio->callback = callback;

    return EGL_SUCCESS;
}

egl_result_t egl_pio_deinit(egl_pio_t *pio)
{
    EGL_ASSERT_CHECK(pio, EGL_ASSERT_FAIL);
    EGL_ASSERT_CHECK(pio->deinit, EGL_NOT_SUPPORTED);

    return pio->deinit();
}
