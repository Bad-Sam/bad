#ifndef BAD_F32XN_CALC_H
#define BAD_F32XN_CALC_H

#include <bad/common/f32xn.h>

#if (f32xn_width == 8u)
#   include "f32x8_calc.h"
#   define f32xn_add          f32x8_add
#   define f32xn_sub          f32x8_sub
#   define f32xn_mul          f32x8_mul
#   define f32xn_div          f32x8_div

#   define f32xn_rcp          f32x8_rcp
#   define f32xn_sqrt         f32x8_sqrt
#   define f32xn_rsqrt        f32x8_rsqrt
#   define f32xn_min          f32x8_min
#   define f32xn_max          f32x8_max
#   define f32xn_abs          f32x8_abs
#   define f32xn_sign         f32x8_sign
#   define f32xn_neg          f32x8_neg
#   define f32xn_frac         f32x8_frac
#   define f32xn_mod          f32x8_mod
#   define f32xn_trunc        f32x8_trunc
#   define f32xn_round        f32x8_round
#   define f32xn_floor        f32x8_floor
#   define f32xn_ceil         f32x8_ceil
#   define f32xn_clamp        f32x8_clamp
#   define f32xn_lerp         f32x8_lerp
#   define f32xn_copysign     f32x8_copysign
#   define f32xn_mul_by_sign  f32x8_mul_by_sign

#   define f32xn_cos          f32x8_cos
#   define f32xn_cos_0_halfpi f32x8_cos_0_halfpi
#   define f32xn_sin          f32x8_sin
#   define f32xn_sin_npi_pi   f32x8_sin_npi_pi
#   define f32xn_tan          f32x8_tan
#   define f32xn_acos         f32x8_acos

#   define f32xn_mul_add      f32x8_mul_add
#   define f32xn_mul_sub      f32x8_mul_sub
#   define f32xn_nmul_add     f32x8_nmul_add
#   define f32xn_nmul_sub     f32x8_nmul_sub

#   define f32xn_neq          f32x8_neq
#   define f32xn_eq           f32x8_eq
#   define f32xn_ge           f32x8_ge
#   define f32xn_gt           f32x8_gt
#   define f32xn_le           f32x8_le
#   define f32xn_lt           f32x8_lt

#   define f32xn_is_positive  f32x8_is_positive
#   define f32xn_is_negative  f32x8_is_negative
#   define f32xn_is_nan       f32x8_is_nan
#   define f32xn_is_infinite  f32x8_is_infinite
#   define f32xn_is_finite    f32x8_is_finite
#else
#   include "f32x4_calc.h"
#   define f32xn_add          f32x4_add
#   define f32xn_sub          f32x4_sub
#   define f32xn_mul          f32x4_mul
#   define f32xn_div          f32x4_div

#   define f32xn_rcp          f32x4_rcp
#   define f32xn_sqrt         f32x4_sqrt
#   define f32xn_rsqrt        f32x4_rsqrt
#   define f32xn_min          f32x4_min
#   define f32xn_max          f32x4_max
#   define f32xn_abs          f32x4_abs
#   define f32xn_sign         f32x4_sign
#   define f32xn_neg          f32x4_neg
#   define f32xn_frac         f32x4_frac
#   define f32xn_mod          f32x4_mod
#   define f32xn_trunc        f32x4_trunc
#   define f32xn_round        f32x4_round
#   define f32xn_floor        f32x4_floor
#   define f32xn_ceil         f32x4_ceil
#   define f32xn_clamp        f32x4_clamp
#   define f32xn_lerp         f32x4_lerp
#   define f32xn_copysign     f32x4_copysign
#   define f32xn_mul_by_sign  f32x4_mul_by_sign

#   define f32xn_cos          f32x4_cos
#   define f32xn_cos_0_halfpi f32x4_cos_0_halfpi
#   define f32xn_sin          f32x4_sin
#   define f32xn_sin_npi_pi   f32x4_sin_npi_pi
#   define f32xn_tan          f32x4_tan
#   define f32xn_acos         f32x4_acos

#   define f32xn_mul_add      f32x4_mul_add
#   define f32xn_mul_sub      f32x4_mul_sub
#   define f32xn_nmul_add     f32x4_nmul_add
#   define f32xn_nmul_sub     f32x4_nmul_sub

#   define f32xn_neq          f32x4_neq
#   define f32xn_eq           f32x4_eq
#   define f32xn_ge           f32x4_ge
#   define f32xn_gt           f32x4_gt
#   define f32xn_le           f32x4_le
#   define f32xn_lt           f32x4_lt

#   define f32xn_is_positive  f32x4_is_positive
#   define f32xn_is_negative  f32x4_is_negative
#   define f32xn_is_nan       f32x4_is_nan
#   define f32xn_is_infinite  f32x4_is_infinite
#   define f32xn_is_finite    f32x4_is_finite
#endif

#endif