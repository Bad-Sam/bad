#ifndef BAD_F32X4_CALC_H
#define BAD_F32X4_CALC_H

#include <bad/bad.h>
#include <bad/qualifiers.h>
#include <bad/args.h>

#include <bad/types.h>
#include <bad/common/f32x4.h>
#include <bad/common/mask128.h>

BAD_NAMESPACE_START

// =========== Arithmetic ===========
static bad_forceinline f32x4 bad_veccall f32x4_add(f32x4_vec0 a, f32x4_vec1 b);
static bad_forceinline f32x4 bad_veccall f32x4_sub(f32x4_vec0 a, f32x4_vec1 b);
static bad_forceinline f32x4 bad_veccall f32x4_mul(f32x4_vec0 a, f32x4_vec1 b);
static bad_forceinline f32x4 bad_veccall f32x4_div(f32x4_vec0 a, f32x4_vec1 b);
static bad_forceinline f32   bad_veccall f32x4_hadd(f32x4_vec0 a);


// ====== Advanced arithmetic =======
static bad_forceinline f32x4 bad_veccall f32x4_rcp(f32x4_vec0 a);
static bad_forceinline f32x4 bad_veccall f32x4_sqrt(f32x4_vec0 a);
static bad_forceinline f32x4 bad_veccall f32x4_rsqrt(f32x4_vec0 a);
static bad_forceinline f32x4 bad_veccall f32x4_min(f32x4_vec0 a, f32x4_vec1 b);
static bad_forceinline f32x4 bad_veccall f32x4_max(f32x4_vec0 a, f32x4_vec1 b);

// TODO: power, exponential, log, 
static bad_forceinline f32x4 bad_veccall f32x4_abs(f32x4_vec0 a);
static bad_forceinline f32x4 bad_veccall f32x4_neg(f32x4_vec0 a);
static bad_forceinline f32x4 bad_veccall f32x4_mod(f32x4_vec0 a, f32x4_vec1 b);
static bad_forceinline f32x4 bad_veccall f32x4_trunc(f32x4_vec0 a);
static bad_forceinline f32x4 bad_veccall f32x4_round(f32x4_vec0 a);
static bad_forceinline f32x4 bad_veccall f32x4_floor(f32x4_vec0 a);
static bad_forceinline f32x4 bad_veccall f32x4_ceil(f32x4_vec0 a);
static bad_forceinline f32x4 bad_veccall f32x4_clamp(f32x4_vec0 a, f32x4_vec1 min, f32x4_vec2 max);

static bad_forceinline f32x4 bad_veccall f32x4_mul_add(f32x4_vec0 a, f32x4_vec1 b, f32x4_vec2 c);
static bad_forceinline f32x4 bad_veccall f32x4_mul_sub(f32x4_vec0 a, f32x4_vec1 b, f32x4_vec2 c);
static bad_forceinline f32x4 bad_veccall f32x4_nmul_add(f32x4_vec0 a, f32x4_vec1 b, f32x4_vec2 c);
static bad_forceinline f32x4 bad_veccall f32x4_nmul_sub(f32x4_vec0 a, f32x4_vec1 b, f32x4_vec2 c);


// ============ Comparison ============
static bad_forceinline mask128 bad_veccall f32x4_neq(f32x4_vec0 a, f32x4_vec1 b);
static bad_forceinline mask128 bad_veccall f32x4_eq(f32x4_vec0 a, f32x4_vec1 b);
static bad_forceinline mask128 bad_veccall f32x4_ge(f32x4_vec0 a, f32x4_vec1 b);
static bad_forceinline mask128 bad_veccall f32x4_gt(f32x4_vec0 a, f32x4_vec1 b);
static bad_forceinline mask128 bad_veccall f32x4_le(f32x4_vec0 a, f32x4_vec1 b);
static bad_forceinline mask128 bad_veccall f32x4_lt(f32x4_vec0 a, f32x4_vec1 b);


// ======= Selection & tests ========
static bad_forceinline mask128 bad_veccall f32x4_is_nan(f32x4_vec0 a);
static bad_forceinline mask128 bad_veccall f32x4_is_infinite(f32x4_vec0 a);
static bad_forceinline mask128 bad_veccall f32x4_is_finite(f32x4_vec0 a);

#if defined(__SSE__)
#   include "f32x4_calc/f32x4_calc_x86-64.inl"
#elif defined(__ARM_NEON_FP)
#   include "f32x4_calc/f32x4_calc_arm.inl"
#else
#   include "f32x4_calc/f32x4_calc_no_simd.inl"
#endif

BAD_NAMESPACE_END

#endif