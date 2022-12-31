#ifndef BAD_F32X4_CALC_H
#define BAD_F32X4_CALC_H

#include <bad/common/f32x4.h>
#include <bad/common/mask128.h>
#include <bad/math/constants.h>

#if !defined(__SSE__) && !defined(__ARM_NEON_FP)
#   include "f32_calc.h"
#endif

BAD_NAMESPACE_START

// =========== Arithmetic ===========
static bad_forceinline f32x4 bad_veccall f32x4_add(f32x4 a, f32x4 b);
static bad_forceinline f32x4 bad_veccall f32x4_sub(f32x4 a, f32x4 b);
static bad_forceinline f32x4 bad_veccall f32x4_mul(f32x4 a, f32x4 b);
static bad_forceinline f32x4 bad_veccall f32x4_div(f32x4 a, f32x4 b);
static bad_forceinline f32x4 bad_veccall f32x4_hadd3(f32x4 a);
static bad_forceinline f32x4 bad_veccall f32x4_hadd4(f32x4 a);
static bad_forceinline f32   bad_veccall f32x4_sum3(f32x4 a);
static bad_forceinline f32   bad_veccall f32x4_sum4(f32x4 a);


// ====== Advanced arithmetic =======
static bad_forceinline f32x4 bad_veccall f32x4_rcp(f32x4 a);
static bad_forceinline f32x4 bad_veccall f32x4_sqrt(f32x4 a);
static bad_forceinline f32x4 bad_veccall f32x4_rsqrt(f32x4 a);
static bad_forceinline f32x4 bad_veccall f32x4_min(f32x4 a, f32x4 b);
static bad_forceinline f32x4 bad_veccall f32x4_max(f32x4 a, f32x4 b);
static bad_forceinline f32x4 bad_veccall f32x4_abs(f32x4 a);
static bad_forceinline f32x4 bad_veccall f32x4_sign(f32x4 a);
static bad_forceinline f32x4 bad_veccall f32x4_neg(f32x4 a);
static bad_forceinline f32x4 bad_veccall f32x4_frac(f32x4 a);
static bad_forceinline f32x4 bad_veccall f32x4_mod(f32x4 a, f32x4 b);
static bad_forceinline f32x4 bad_veccall f32x4_trunc(f32x4 a);
static bad_forceinline f32x4 bad_veccall f32x4_round(f32x4 a);
static bad_forceinline f32x4 bad_veccall f32x4_floor(f32x4 a);
static bad_forceinline f32x4 bad_veccall f32x4_ceil(f32x4 a);
static bad_forceinline f32x4 bad_veccall f32x4_clamp(f32x4 a, f32x4 min, f32x4 max);
static bad_forceinline f32x4 bad_veccall f32x4_lerp(f32x4 a, f32x4 b, f32x4 t);
static bad_forceinline f32x4 bad_veccall f32x4_copysign(f32x4 a, f32x4 reference_sign);
static bad_forceinline f32x4 bad_veccall f32x4_mul_by_sign(f32x4 a, f32x4 reference_sign);


// ========== Trigonometry ===========
static bad_inline f32x4 bad_veccall f32x4_cos(f32x4 x);
static bad_inline f32x4 bad_veccall f32x4_cos_0_halfpi(f32x4 x);
static bad_inline f32x4 bad_veccall f32x4_sin(f32x4 x);
static bad_inline f32x4 bad_veccall f32x4_sin_npi_pi(f32x4 x);
static bad_inline f32x4 bad_veccall f32x4_tan(f32x4 x);
static bad_inline f32x4 bad_veccall f32x4_acos(f32x4 x);



// ======== Fused operations ========
static bad_forceinline f32x4 bad_veccall f32x4_mul_add(f32x4 a, f32x4 b, f32x4 c);
static bad_forceinline f32x4 bad_veccall f32x4_mul_sub(f32x4 a, f32x4 b, f32x4 c);
static bad_forceinline f32x4 bad_veccall f32x4_nmul_add(f32x4 a, f32x4 b, f32x4 c);
static bad_forceinline f32x4 bad_veccall f32x4_nmul_sub(f32x4 a, f32x4 b, f32x4 c);


// ============ Comparison ============
static bad_forceinline mask128 bad_veccall f32x4_neq(f32x4 a, f32x4 b);
static bad_forceinline mask128 bad_veccall f32x4_eq(f32x4 a, f32x4 b);
static bad_forceinline mask128 bad_veccall f32x4_ge(f32x4 a, f32x4 b);
static bad_forceinline mask128 bad_veccall f32x4_gt(f32x4 a, f32x4 b);
static bad_forceinline mask128 bad_veccall f32x4_le(f32x4 a, f32x4 b);
static bad_forceinline mask128 bad_veccall f32x4_lt(f32x4 a, f32x4 b);


// ======= Tests ========
static bad_forceinline mask128 bad_veccall f32x4_is_positive(f32x4 a);
static bad_forceinline mask128 bad_veccall f32x4_is_negative(f32x4 a);
static bad_forceinline mask128 bad_veccall f32x4_is_nan(f32x4 a);
static bad_forceinline mask128 bad_veccall f32x4_is_infinite(f32x4 a);
static bad_forceinline mask128 bad_veccall f32x4_is_finite(f32x4 a);


#include "f32x4_calc/f32x4_calc_x86-64.inl"

BAD_NAMESPACE_END

#endif