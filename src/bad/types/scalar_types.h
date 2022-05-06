#ifndef BAD_SCALAR_TYPES_H
#define BAD_SCALAR_TYPES_H

#include <bad/bad.h>

// TODO: find an alternative
#include <stdint.h>

BAD_NAMESPACE_START

typedef int8_t   s8;
typedef int16_t  s16;
typedef int32_t  s32;
typedef int64_t  s64;
typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
typedef float    f32;

#if defined(__SSE__) && !defined(__SSE2__)
    typedef f32 mask_elem;
#else
    typedef u32 mask_elem;
#endif

BAD_NAMESPACE_END

#endif