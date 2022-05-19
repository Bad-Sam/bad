#ifndef BAD_F32XN_H
#define BAD_F32XN_H

#include <bad/bad.h>

// f32xn is the widest available vector
#if defined(BAD_FORCE_WIDEST_VEC) || defined(BAD_FORCE_8WAY_VEC)
#   define f32xn_width 8u
#   include "f32x8.h"
#elif defined(BAD_FORCE_TINIEST_VEC) || defined(BAD_FORCE_4WAY_VEC)
#   define f32xn_width 4u
#   include "f32x4.h"
#else // By default, use the widest available SIMD intrinsics type
#   if defined(__AVX__)
#       define f32xn_width 8u
#       include "f32x8.h"
#   else
#       define f32xn_width 4u
#       include "f32x4.h"
#   endif
#endif


BAD_NAMESPACE_START

#if (f32xn_width == 8u)
    typedef f32x8 f32xn;

#   define f32xn_any         f32x8_any
#   define f32xn_zero        f32x8_zero
#   define f32xn_half        f32x8_half
#   define f32xn_one         f32x8_one
#   define f32xn_two         f32x8_two
#   define f32xn_load        f32x8_load
#   define f32xn_loadu       f32x8_loadu
#   define f32xn_set_all     f32x8_set_all
#   define f32xn_set_lower   f32x8_set_lower
#   define f32xn_store       f32x8_store
#   define f32xn_storeu      f32x8_storeu
#   define f32xn_store_lower f32x8_store_lower
#   define f32xn_blend       f32x8_blend
#   define f32xn_as_maskn    f32x8_as_mask256
#else
    typedef f32x4 f32xn;
    
#   define f32xn_any         f32x4_any
#   define f32xn_zero        f32x4_zero
#   define f32xn_half        f32x4_half
#   define f32xn_one         f32x4_one
#   define f32xn_two         f32x4_two
#   define f32xn_load        f32x4_load
#   define f32xn_loadu       f32x4_loadu
#   define f32xn_set_all     f32x4_set_all
#   define f32xn_set_lower   f32x4_set_lower
#   define f32xn_store       f32x4_store
#   define f32xn_storeu      f32x4_storeu
#   define f32xn_store_lower f32x4_store_lower
#   define f32xn_blend       f32x4_blend
#   define f32xn_as_maskn    f32x4_as_mask128
#endif

BAD_NAMESPACE_END

#endif