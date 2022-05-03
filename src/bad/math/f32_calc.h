#ifndef BAD_F32_CALC_H
#define BAD_F32_CALC_H

#include <bad/types.h>
#include <bad/detect/builtin.h>
#include <bad/common/f32.h>
#include <bad/common/u32.h>
#include <bad/math/constants.h>

// TODO: ARM's Neon
#if defined(__SSE__)
#   include <bad/math/f32x4_calc.h>
#endif

BAD_NAMESPACE_START

/* =========== Arithmetic =========== */
static bad_forceinline f32 f32_add(f32 a, f32 b);
static bad_forceinline f32 f32_sub(f32 a, f32 b);
static bad_forceinline f32 f32_mul(f32 a, f32 b);
static bad_forceinline f32 f32_div(f32 a, f32 b);


/* ====== Advanced arithmetic ======= */
static bad_forceinline f32 f32_rcp(f32 a);
static bad_forceinline f32 f32_sqrt(f32 a);
static bad_forceinline f32 f32_rsqrt(f32 a);
static bad_forceinline f32 f32_min(f32 a, f32 b);
static bad_forceinline f32 f32_max(f32 a, f32 b);
static bad_forceinline f32 f32_abs(f32 a);
static bad_forceinline f32 f32_sign(f32 a);
static bad_forceinline f32 f32_neg(f32 a);
static bad_forceinline f32 f32_frac(f32 a);
static bad_forceinline f32 f32_mod(f32 a, f32 b);
static bad_forceinline f32 f32_trunc(f32 a);
static bad_forceinline f32 f32_round(f32 a);
static bad_forceinline f32 f32_floor(f32 a);
static bad_forceinline f32 f32_ceil(f32 a);
static bad_forceinline f32 f32_clamp(f32 a, f32 min, f32 max);
static bad_forceinline f32 f32_lerp(f32 a, f32 b, f32 t);


/* ========== Trigonometry =========== */
static bad_forceinline f32 f32_cos(f32 a);
static bad_forceinline f32 f32_sin(f32 a);
static bad_forceinline f32 f32_tan(f32 a);

static bad_forceinline f32 f32_cos_0_halfpi(f32 a);
static bad_forceinline f32 f32_sin_npi_pi(f32 a);


/* ======== Fused operations ======== */
static bad_forceinline f32 f32_mul_add(f32 a, f32 b, f32 c);
static bad_forceinline f32 f32_mul_sub(f32 a, f32 b, f32 c);
static bad_forceinline f32 f32_nmul_add(f32 a, f32 b, f32 c);
static bad_forceinline f32 f32_nmul_sub(f32 a, f32 b, f32 c);


/* ============ Comparison ============ */
static bad_forceinline u32 f32_neq(f32 a, f32 b);
static bad_forceinline u32 f32_eq(f32 a, f32 b);
static bad_forceinline u32 f32_ge(f32 a, f32 b);
static bad_forceinline u32 f32_gt(f32 a, f32 b);
static bad_forceinline u32 f32_le(f32 a, f32 b);
static bad_forceinline u32 f32_lt(f32 a, f32 b);


/* ======= Tests ======== */
static bad_forceinline u32 f32_is_nan(f32 a);
static bad_forceinline u32 f32_is_infinite(f32 a);
static bad_forceinline u32 f32_is_finite(f32 a);


#include "f32_calc.inl"

BAD_NAMESPACE_END

#endif