#ifndef BAD_SCALAR_TYPES_H
#define BAD_SCALAR_TYPES_H

#include <bad/bad.h>
#include <bad/detect/os.h>

#if !defined(BAD_WINDOWS)
#   include <stdint.h>
#endif

BAD_NAMESPACE_START

#if defined(BAD_WINDOWS)
    typedef __int8   s8;
    typedef __int16  s16;
    typedef __int32  s32;
    typedef __int64  s64;
    typedef unsigned __int8  u8;
    typedef unsigned __int16 u16;
    typedef unsigned __int32 u32;
    typedef unsigned __int64 u64;
#else
    typedef int8_t   s8;
    typedef int16_t  s16;
    typedef int32_t  s32;
    typedef int64_t  s64;
    typedef uint8_t  u8;
    typedef uint16_t u16;
    typedef uint32_t u32;
    typedef uint64_t u64;
#endif

typedef float    f32;

#if defined(__SSE__) && !defined(__SSE2__)
    typedef f32 mask_elem;
#else
    typedef u32 mask_elem;
#endif

BAD_NAMESPACE_END

#endif