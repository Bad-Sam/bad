#ifndef BAD_MATH_ARGS_H
#define BAD_MATH_ARGS_H

#include <bad/qualifiers.h>
#include <bad/detect/isa.h>
#include <bad/detect/os.h>

#include "types.h"

#if defined(BAD_x86)
    // Under x86 architectures, Windows or Linux, up to 3 __m128 can be passed in registers
#   define f32x4_vec0 const f32x4
#   define f32x4_vec1 const f32x4
#   define f32x4_vec2 const f32x4
#   define f32x4_vec3 const f32x4&
#   define mask128_vec0 const mask128
#   define mask128_vec1 const mask128
#   define mask128_vec2 const mask128
#   define mask128_vec3 const mask128&
#elif defined(BAD_x64)
#   if defined(BAD_WINDOWS)
        // With __vectorcall, up to 6 __m128 can passed in registers
#       if defined(BAD_VECTORCALL_AVAILABLE)
#           define f32x4_vec0 const f32x4
#           define f32x4_vec1 const f32x4
#           define f32x4_vec2 const f32x4
#           define f32x4_vec3 const f32x4
#           define mask128_vec0 const mask128
#           define mask128_vec1 const mask128
#           define mask128_vec2 const mask128
#           define mask128_vec3 const mask128
        // Without __vectorcall, all __m128 are passed by pointer/reference
#       else // TODO: adapt to C, pointers and restrict
#           define f32x4_vec0 const f32x4&
#           define f32x4_vec1 const f32x4&
#           define f32x4_vec2 const f32x4&
#           define f32x4_vec3 const f32x4&
#           define mask128_vec0 const mask128&
#           define mask128_vec1 const mask128&
#           define mask128_vec2 const mask128&
#           define mask128_vec3 const mask128&
#       endif
    // Under x64 Linux, up to 8 __m128 can be passed in registers
#   elif defined(BAD_LINUX)
#       define f32x4_vec0 const f32x4
#       define f32x4_vec1 const f32x4
#       define f32x4_vec2 const f32x4
#       define f32x4_vec3 const f32x4
#       define mask128_vec0 const mask128
#       define mask128_vec1 const mask128
#       define mask128_vec2 const mask128
#       define mask128_vec3 const mask128
#   endif
#elif defined(BAD_ARM32) || defined(BAD_ARM64)
    // Under ARM32, up to 32 floats can be passed in registers
    // Under ARM64, up to 64 floats can be passed in registers
#   define f32x4_vec0 const f32x4
#   define f32x4_vec1 const f32x4
#   define f32x4_vec2 const f32x4
#   define f32x4_vec3 const f32x4
#   define mask128_vec0 const mask128
#   define mask128_vec1 const mask128
#   define mask128_vec2 const mask128
#   define mask128_vec3 const mask128
#endif

#define vec4_vec0 f32x4_vec0
#define vec4_vec1 f32x4_vec1
#define vec4_vec2 f32x4_vec2
#define vec4_vec3 f32x4_vec3

#endif