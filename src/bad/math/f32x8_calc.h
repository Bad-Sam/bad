#ifndef BAD_F32X8_CALC_H
#define BAD_F32X8_CALC_H

#include <bad/common/f32x8.h>
#include <bad/common/mask256.h>
#include <bad/math/constants.h>

BAD_NAMESPACE_START

/* =========== Arithmetic =========== */
static bad_forceinline f32x8 bad_veccall f32x8_add(f32x8 a, f32x8 b);
static bad_forceinline f32x8 bad_veccall f32x8_sub(f32x8 a, f32x8 b);
static bad_forceinline f32x8 bad_veccall f32x8_mul(f32x8 a, f32x8 b);
static bad_forceinline f32x8 bad_veccall f32x8_div(f32x8 a, f32x8 b);
static bad_forceinline f32x8 bad_veccall f32x8_hadd(f32x8 a);
static bad_forceinline f32   bad_veccall f32x8_sum(f32x8 a);


/* ====== Advanced arithmetic ======= */
static bad_forceinline f32x8 bad_veccall f32x8_rcp(f32x8 a);
static bad_forceinline f32x8 bad_veccall f32x8_sqrt(f32x8 a);
static bad_forceinline f32x8 bad_veccall f32x8_rsqrt(f32x8 a);
static bad_forceinline f32x8 bad_veccall f32x8_min(f32x8 a, f32x8 b);
static bad_forceinline f32x8 bad_veccall f32x8_max(f32x8 a, f32x8 b);
static bad_forceinline f32x8 bad_veccall f32x8_abs(f32x8 a);
static bad_forceinline f32x8 bad_veccall f32x8_sign(f32x8 a);
static bad_forceinline f32x8 bad_veccall f32x8_neg(f32x8 a);
static bad_forceinline f32x8 bad_veccall f32x8_frac(f32x8 a);
static bad_forceinline f32x8 bad_veccall f32x8_mod(f32x8 a, f32x8 b);
static bad_forceinline f32x8 bad_veccall f32x8_trunc(f32x8 a);
static bad_forceinline f32x8 bad_veccall f32x8_round(f32x8 a);
static bad_forceinline f32x8 bad_veccall f32x8_floor(f32x8 a);
static bad_forceinline f32x8 bad_veccall f32x8_ceil(f32x8 a);
static bad_forceinline f32x8 bad_veccall f32x8_clamp(f32x8 a, f32x8 min, f32x8 max);
static bad_forceinline f32x8 bad_veccall f32x8_lerp(f32x8 a, f32x8 b, f32x8 t);
static bad_forceinline f32x8 bad_veccall f32x8_copysign(f32x8 a, f32x8 reference_sign);
static bad_forceinline f32x8 bad_veccall f32x8_mul_by_sign(f32x8 a, f32x8 reference_sign);

/* ========== Trigonometry =========== */
static bad_inline f32x8 bad_veccall f32x8_cos(f32x8 a);
static bad_inline f32x8 bad_veccall f32x8_cos_0_halfpi(f32x8 a);
static bad_inline f32x8 bad_veccall f32x8_sin(f32x8 a);
static bad_inline f32x8 bad_veccall f32x8_sin_npi_pi(f32x8 a);
static bad_inline f32x8 bad_veccall f32x8_tan(f32x8 a);
static bad_inline f32x8 bad_veccall f32x8_acos(f32x8 a);



/* ======== Fused operations ======== */
static bad_forceinline f32x8 bad_veccall f32x8_mul_add(f32x8 a, f32x8 b, f32x8 c);
static bad_forceinline f32x8 bad_veccall f32x8_mul_sub(f32x8 a, f32x8 b, f32x8 c);
static bad_forceinline f32x8 bad_veccall f32x8_nmul_add(f32x8 a, f32x8 b, f32x8 c);
static bad_forceinline f32x8 bad_veccall f32x8_nmul_sub(f32x8 a, f32x8 b, f32x8 c);


/* ============ Comparison ============ */
static bad_forceinline mask256 bad_veccall f32x8_neq(f32x8 a, f32x8 b);
static bad_forceinline mask256 bad_veccall f32x8_eq(f32x8 a, f32x8 b);
static bad_forceinline mask256 bad_veccall f32x8_ge(f32x8 a, f32x8 b);
static bad_forceinline mask256 bad_veccall f32x8_gt(f32x8 a, f32x8 b);
static bad_forceinline mask256 bad_veccall f32x8_le(f32x8 a, f32x8 b);
static bad_forceinline mask256 bad_veccall f32x8_lt(f32x8 a, f32x8 b);


/* ======= Tests ======== */
static bad_forceinline mask256 bad_veccall f32x8_is_positive(f32x8 a);
static bad_forceinline mask256 bad_veccall f32x8_is_negative(f32x8 a);
static bad_forceinline mask256 bad_veccall f32x8_is_nan(f32x8 a);
static bad_forceinline mask256 bad_veccall f32x8_is_infinite(f32x8 a);
static bad_forceinline mask256 bad_veccall f32x8_is_finite(f32x8 a);


#include "f32x8_calc/f32x8_calc_x86-64.inl"

BAD_NAMESPACE_END

#endif