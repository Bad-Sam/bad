#ifndef BAD_MATH_ARGS_H
#define BAD_MATH_ARGS_H

#include <bad/qualifiers.h>
#include <bad/detect/isa.h>
#include <bad/detect/os.h>

#include "types.h"

#if defined(BAD_x86)
    // Under x86 architectures, Windows or Linux, up to 3 SIMD variables can be passed in registers
#   define f32x4_vec0 f32x4
#   define f32x4_vec1 f32x4
#   define f32x4_vec2 f32x4
#   define f32x4_vec3 const f32x4&
#   if defined(__AVX__)
#       define f32x8_vec0 f32x8
#       define f32x8_vec1 f32x8
#       define f32x8_vec2 f32x8
#       define f32x8_vec3 const f32x8&
#   else // No AVX means f32x8 is made of 2 __m128
#       define f32x8_vec0 f32x8
#       define f32x8_vec1 const f32x8&
#       define f32x8_vec2 const f32x8&
#       define f32x8_vec3 const f32x8&
#   endif
#   define mask128_vec0 mask128
#   define mask128_vec1 mask128
#   define mask128_vec2 mask128
#   define mask128_vec3 const mask128&
#   if defined(__AVX__)
#       define mask256_vec0 mask256
#       define mask256_vec1 mask256
#       define mask256_vec2 mask256
#       define mask256_vec3 const mask256&
#   else
#       define mask256_vec0 mask256
#       define mask256_vec1 const mask256&
#       define mask256_vec2 const mask256&
#       define mask256_vec3 const mask256&
#   endif
#elif defined(BAD_x64)
#   if defined(BAD_WINDOWS)
        // With __vectorcall, up to 6 SIMD variables can passed in registers
#       if defined(BAD_VECTORCALL_AVAILABLE)
#           define f32x4_vec0 f32x4
#           define f32x4_vec1 f32x4
#           define f32x4_vec2 f32x4
#           define f32x4_vec3 f32x4
#           define f32x8_vec0 f32x8
#           define f32x8_vec1 f32x8
#           define f32x8_vec2 f32x8
#           define f32x8_vec3 f32x8
#           define mask128_vec0 mask128
#           define mask128_vec1 mask128
#           define mask128_vec2 mask128
#           define mask128_vec3 mask128
#           define mask256_vec0 mask256
#           define mask256_vec1 mask256
#           define mask256_vec2 mask256
#           define mask256_vec3 mask256
        // Without __vectorcall, all SIMD variables are passed by pointer/reference
#       else // TODO: adapt to C, pointers and restrict
#           define f32x4_vec0 const f32x4&
#           define f32x4_vec1 const f32x4&
#           define f32x4_vec2 const f32x4&
#           define f32x4_vec3 const f32x4&
#           define f32x8_vec0 const f32x8&
#           define f32x8_vec1 const f32x8&
#           define f32x8_vec2 const f32x8&
#           define f32x8_vec3 const f32x8&
#           define mask128_vec0 const mask128&
#           define mask128_vec1 const mask128&
#           define mask128_vec2 const mask128&
#           define mask128_vec3 const mask128&
#           define mask256_vec0 const mask256&
#           define mask256_vec1 const mask256&
#           define mask256_vec2 const mask256&
#           define mask256_vec3 const mask256&
#       endif
    // Under x64 Linux, up to 8 vector variables can be passed in registers
#   elif defined(BAD_LINUX)
#       define f32x4_vec0 f32x4
#       define f32x4_vec1 f32x4
#       define f32x4_vec2 f32x4
#       define f32x4_vec3 f32x4
#       define f32x8_vec0 f32x8
#       define f32x8_vec1 f32x8
#       define f32x8_vec2 f32x8
#       define f32x8_vec3 f32x8
#       define mask128_vec0 mask128
#       define mask128_vec1 mask128
#       define mask128_vec2 mask128
#       define mask128_vec3 mask128
#       define mask256_vec0 mask256
#       define mask256_vec1 mask256
#       define mask256_vec2 mask256
#       define mask256_vec3 mask256
#   endif
#elif defined(BAD_ARM32) || defined(BAD_ARM64)
    // Under ARM32, up to 8 vector variables can be passed in registers (= 8 float32x4_t)
    // Under ARM64, up to 16 vector variables can be passed in registers (= 16 float32x4_t)
#   define f32x4_vec0 f32x4
#   define f32x4_vec1 f32x4
#   define f32x4_vec2 f32x4
#   define f32x4_vec3 f32x4
#   define f32x8_vec0 f32x8
#   define f32x8_vec1 f32x8
#   define f32x8_vec2 f32x8
#   define f32x8_vec3 f32x8
#   define mask128_vec0 mask128
#   define mask128_vec1 mask128
#   define mask128_vec2 mask128
#   define mask128_vec3 mask128
#   define mask256_vec0 mask256
#   define mask256_vec1 mask256
#   define mask256_vec2 mask256
#   define mask256_vec3 mask256
#endif

// f32xn
#if defined(__AVX__)
#   define f32xn_vec0 f32x8_vec0
#   define f32xn_vec1 f32x8_vec1
#   define f32xn_vec2 f32x8_vec2
#   define f32xn_vec3 f32x8_vec3
#   define maskn_vec0 mask256_vec0
#   define maskn_vec1 mask256_vec1
#   define maskn_vec2 mask256_vec2
#   define maskn_vec3 mask256_vec3
#else
#   define f32xn_vec0 f32x4_vec0
#   define f32xn_vec1 f32x4_vec1
#   define f32xn_vec2 f32x4_vec2
#   define f32xn_vec3 f32x4_vec3
#   define maskn_vec0 mask128_vec0
#   define maskn_vec1 mask128_vec1
#   define maskn_vec2 mask128_vec2
#   define maskn_vec3 mask128_vec3
#endif

#define vec4_vec0 f32x4_vec0
#define vec4_vec1 f32x4_vec1
#define vec4_vec2 f32x4_vec2
#define vec4_vec3 f32x4_vec3

#endif