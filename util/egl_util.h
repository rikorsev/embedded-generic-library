#ifndef EGL_UTIL_H
#define EGL_UTIL_H

#define EGL_ARRAY_SIZE(array) (sizeof((array)) / sizeof((array[0])))

static inline uint16_t egl_swap16(uint16_t val)
{
    return ((val >> 8) & 0x00FF) | ((val << 8) & 0xFF00);
}

static inline uint32_t egl_swap32(uint32_t val)
{
    return ((val >> 24) & 0x000000FF) |
           ((val >> 8)  & 0x0000FF00) |
           ((val << 8)  & 0x00FF0000) |
           ((val << 24) & 0xFF000000);
}

#endif