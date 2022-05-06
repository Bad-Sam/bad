#ifndef BAD_SIMD_TYPES_H
#define BAD_SIMD_TYPES_H

#include <bad/bad.h>

#include "scalar_types.h"

// SIMD headers
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
#   if defined(_M_ARM64) || defined(__aarch64__) && defined(_MSC_VER)
#       include <arm64_neon.h>
#   else
#       include <arm_neon.h>
#   endif
#endif


BAD_NAMESPACE_START

// 4-way
#if defined(__SSE__)
    typedef __m128 f32x4;
#   if defined(__SSE2__)
        typedef __m128i mask128;
#   else
        typedef __m128  mask128;
#   endif
#elif defined(__ARM_NEON_FP)
    typedef float32x4_t f32x4;
    typedef uint32x4_t  mask128;
#else
    typedef union { f32 e[4]; struct { f32 x, y, z, w; }; } f32x4;
    typedef union { u32 e[4]; struct { u32 x, y, z, w; }; } mask128;
#endif

// 8-way
#if defined(__AVX__)
    typedef __m256  f32x8;
    typedef __m256i mask256;
#else
    typedef union { f32x4   e[2]; struct { f32x4   a; f32x4   b; }; } f32x8;
    typedef union { mask128 e[2]; struct { mask128 a; mask128 b; }; } mask256;
#endif


// Aliases for code clarity
typedef mask128 u32x4;
typedef mask128 s32x4;
typedef mask256 u32x8;
typedef mask256 s32x8;

BAD_NAMESPACE_END

#endif