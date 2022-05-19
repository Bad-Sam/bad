#ifndef BAD_MASKN_H
#define BAD_MASKN_H

#include <bad/bad.h>

// maskn is the widest available vector
#if defined(BAD_FORCE_WIDEST_VEC) || defined(BAD_FORCE_8WAY_VEC)
#   define maskn_width 8u
#   include "mask256.h"
#elif defined(BAD_FORCE_TINIEST_VEC) || defined(BAD_FORCE_4WAY_VEC)
#   define maskn_width 4u
#   include "mask128.h"
#else // By default, use the widest available SIMD intrinsics type
#   if defined(__AVX__)
#       define maskn_width 8u
#       include "mask256.h"
#   else
#       define maskn_width 4u
#       include "mask128.h"
#   endif
#endif

BAD_NAMESPACE_START

#if (maskn_width == 8u) 
    typedef mask256 maskn;

#   define maskn_load           mask256_load
#   define maskn_loadu          mask256_loadu
#   define maskn_set_all        mask256_set_all
#   define maskn_store          mask256_store
#   define maskn_storeu         mask256_storeu

#   define maskn_zero           mask256_zero
#   define maskn_all1           mask256_all1
#   define maskn_value32        mask256_value32
#   define maskn_highbit32      mask256_highbit32
#   define maskn_lowbit32       mask256_lowbit32
#   define maskn_exponent32     mask256_exponent32

#   define maskn_keep_highbit32 mask256_keep_highbit32
#   define maskn_keep_lowbit32  mask256_keep_lowbit32
#   define maskn_shift_left32   mask256_shift_left32
#   define maskn_shift_right32  mask256_shift_right32

#   define maskn_eq             mask256_eq
#   define maskn_neq            mask256_neq
#   define maskn_gt             mask256_gt

#   define maskn_and            mask256_and
#   define maskn_and_not        mask256_and_not
#   define maskn_or             mask256_or
#   define maskn_xor            mask256_xor
#   define maskn_not            mask256_not

#   define maskn_as_f32xn       mask256_as_f32x8
#else
    typedef mask128 maskn;

#   define maskn_load           mask128_load
#   define maskn_loadu          mask128_loadu
#   define maskn_set_all        mask128_set_all
#   define maskn_store          mask128_store
#   define maskn_storeu         mask128_storeu

#   define maskn_zero           mask128_zero
#   define maskn_all1           mask128_all1
#   define maskn_value32        mask128_value32
#   define maskn_highbit32      mask128_highbit32
#   define maskn_lowbit32       mask128_lowbit32
#   define maskn_exponent32     mask128_exponent32

#   define maskn_keep_highbit32 mask128_keep_highbit32
#   define maskn_keep_lowbit32  mask128_keep_lowbit32
#   define maskn_shift_left32   mask128_shift_left32
#   define maskn_shift_right32  mask128_shift_right32

#   define maskn_eq             mask128_eq
#   define maskn_neq            mask128_neq
#   define maskn_gt             mask128_gt

#   define maskn_and            mask128_and
#   define maskn_and_not        mask128_and_not
#   define maskn_or             mask128_or
#   define maskn_xor            mask128_xor
#   define maskn_not            mask128_not

#   define maskn_as_f32xn       mask128_as_f32x8

#endif

BAD_NAMESPACE_END

#endif