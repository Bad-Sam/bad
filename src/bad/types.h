#ifndef BAD_TYPES_H
#define BAD_TYPES_H

#include <bad/bad.h>
#include <bad/detect/isa.h>
#include <bad/qualifiers.h>

// TODO: find an alternative
#include <stdint.h>

// TODO move to simd_header.h
#if defined(__FMA__) || defined(__AVX__)
#   include <immintrin.h>
#elif defined(__SSE4_2__)
#   include <nmmintrin.h>
#elif defined(__SSE4_1__)
#   include <smmintrin.h>
#elif defined(__SSSE3__)
#   include <tmmintrin.h>
#elif defined(__SSE2__)
#   include <emmintrin.h>
#elif defined(__SSE__)
#   include <xmmintrin.h>
#elif defined(__ARM_NEON) // Cortex-A and Cortex-R
#   if defined(BAD_ARM64) && defined(_MSC_VER)
#       include <arm64_neon.h>
#   else
#       include <arm_neon.h>
#   endif
#endif

// TODO: are Helium intrinsics worth supporting?
// For Cortex-M processors only (microcontrollers, IoT, embedded devices)
// #elif defined(__ARM_FEATURE_MVE)
// #    include <arm_mve.h>
// #endif

BAD_NAMESPACE_START

// ========== Scalar types ==========
// Integer types
typedef int8_t   s8;
typedef int16_t  s16;
typedef int32_t  s32;
typedef int64_t  s64;
typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

// Floating-point types
typedef float    f32;
typedef double   f64;


// ========== SIMD types ==========
#if defined(__SSE__)
    typedef __m128 f32x4;
#   if defined(__SSE2__)
        typedef __m128i mask128;
        typedef u32     mask_elem;
#   else
        typedef __m128  mask128;
        typedef f32     mask_elem;
#   endif

#   if defined(__AVX__)
        typedef __m256  f32x8;
        typedef __m256i mask256;
        typedef u32     mask_elem;
#   else
        typedef struct
        {
            __m128 a;
            __m128 b;
        } f32x8;

        typedef struct
        {
            mask128 a;
            mask128 b;
        } mask256;
#   endif
#elif defined(__ARM_NEON_FP)
    typedef float32x4_t f32x4;
    typedef uint32x4_t  mask128;
    typedef u32         mask_elem;

    typedef struct
    {
        float32x4_t a;
        float32x4_t b;
    } f32x8;

    typedef struct
    {
        uint32x4_t a;
        uint32x4_t b;
    } mask256;
#else
    typedef union
    {
        f32 e[4];
        struct
        {
            f32 x;
            f32 y;
            f32 z;
            f32 w;
        };
    } f32x4;

    typedef union
    {
        f32x4 e[2];
        struct
        {
            f32x4 a;
            f32x4 b;
        }
    } f32x8;

    typedef union
    {
        u32 e[4];
        struct
        {
            u32 x;
            u32 y;
            u32 z;
            u32 w;
        };
    } mask128;

    typedef struct
    {
        mask128 a;
        mask128 b;
    } mask256;

    typedef u32 mask_elem;
#endif

BAD_NAMESPACE_END

#endif