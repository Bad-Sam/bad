// =========== Arithmetic ===========
static bad_forceinline f32x4 bad_veccall f32x4_add(f32x4_vec0 a, f32x4_vec1 b)
{
    return vaddq_f32(a, b);
}


static bad_forceinline f32x4 bad_veccall f32x4_sub(f32x4_vec0 a, f32x4_vec1 b)
{
    return vsubq_f32(a, b);
}


static bad_forceinline f32x4 bad_veccall f32x4_mul(f32x4_vec0 a, f32x4_vec1 b)
{
    return vmulq_f32(a, b);
}


static bad_forceinline f32x4 bad_veccall f32x4_div(f32x4_vec0 a, f32x4_vec1 b)
{
    return vdivq_f32(a, b);
}


static bad_forceinline f32 bad_veccall f32x4_hadd(f32x4_vec0 a)
{
    return vaddvq_f32(a);
}


// ====== Advanced arithmetic =======
static bad_forceinline f32x4 bad_veccall f32x4_rcp(f32x4_vec0 a)
{
    return vrecpeq_f32(a);
}


static bad_forceinline f32x4 bad_veccall f32x4_sqrt(f32x4_vec0 a)
{
    return vsqrtq_f32(a);
}


static bad_forceinline f32x4 bad_veccall f32x4_rsqrt(f32x4_vec0 a)
{
    return vrsqrteq_f32(a);
}


static bad_forceinline f32x4 bad_veccall f32x4_min(f32x4_vec0 a, f32x4_vec1 b)
{
    return vminq_f32(a, b);
}


static bad_forceinline f32x4 bad_veccall f32x4_max(f32x4_vec0 a, f32x4_vec1 b)
{
    return vmaxq_f32(a, b);
}


static bad_forceinline f32x4 bad_veccall f32x4_abs(f32x4_vec0 a)
{
    return vabsq_f32(a);
}


static bad_forceinline f32x4 bad_veccall f32x4_sign(f32x4_vec0 a)
{
          mask128 a_sign = vceqq_u32(vreinterpretq_u32_f32(a), vreinterpretq_u32_f32(a));
    const mask128 one    = vshlq_n_u32(vshrq_n_u32(a_sign, 25), 23);
                  a_sign = vshlq_n_u32(vshrq_n_u32(vreinterpretq_u32_f32(a), 31), 31);

    return vreinterpretq_f32_u32(vorq_u32(one, a_sign));
}


static bad_forceinline f32x4 bad_veccall f32x4_neg(f32x4_vec0 a)
{
    return vnegq_f32(a);
}


static bad_forceinline f32x4 bad_veccall f32x4_mod(f32x4_vec0 a, f32x4_vec1 b)
{
    // TODO: test
    // const f32x4 a_div_b   = vdivq_f32(a, b);
    const f32x4 a_div_b   = vmulq_f32(a, vrecpeq_f32(b));
    const f32x4 truncated = vrndq_f32(a_div_b);
    
    return vsubq_f32(a, vmulq_f32(truncated, b));
}


static bad_forceinline f32x4 bad_veccall f32x4_trunc(f32x4_vec0 a)
{
    return vrndq_f32(a);
}


static bad_forceinline f32x4 bad_veccall f32x4_round(f32x4_vec0 a)
{
    return vrndnq_f32(a);
}


static bad_forceinline f32x4 bad_veccall f32x4_floor(f32x4_vec0 a)
{
    return vrndmq_f32(a);
}


static bad_forceinline f32x4 bad_veccall f32x4_ceil(f32x4_vec0 a)
{
    return vrndpq_f32(a);
}


static bad_forceinline f32x4 bad_veccall f32x4_clamp(f32x4_vec0 a, f32x4_vec1 min, f32x4_vec2 max)
{
    return vminq_f32(vmax_f32(a, min), max);
}

// a * b + c
static bad_forceinline f32x4 bad_veccall f32x4_mul_add(f32x4_vec0 a, f32x4_vec1 b, f32x4_vec2 c)
{
#if defined(__ARM_FEATURE_FMA)
    return vfmaq_f32(c, a, b);
#else
    return vmlaq_f32(c, a, b);
#endif
}

// a * b - c
static bad_forceinline f32x4 bad_veccall f32x4_mul_sub(f32x4_vec0 a, f32x4_vec1 b, f32x4_vec2 c)
{
#if defined(__ARM_FEATURE_FMA)
    return vnegq_f32(vfmsq_f32(c, a, b));
#else
    return vnegq_f32(vmlsq_f32(c, a, b));
#endif
}

// -a * b + c
static bad_forceinline f32x4 bad_veccall f32x4_nmul_add(f32x4_vec0 a, f32x4_vec1 b, f32x4_vec2 c)
{
#if defined(__ARM_FEATURE_FMA)
    return vfmsq_f32(c, a, b);
#else
    return vmlsq_f32(c, a, b);
#endif
}

// -a * b - c
static bad_forceinline f32x4 bad_veccall f32x4_nmul_sub(f32x4_vec0 a, f32x4_vec1 b, f32x4_vec2 c)
{
#if defined(__ARM_FEATURE_FMA)
    return vnegq_f32(vfmaq_f32(c, a, b));
#else
    return vnegq_f32(vmlaq_f32(c, a, b));
#endif
}


// ============ Comparison ============
static bad_forceinline mask128 bad_veccall f32x4_neq(f32x4_vec0 a, f32x4_vec1 b)
{
    return vmvnq_u32(vceqq_f32(a, b));
}


static bad_forceinline mask128 bad_veccall f32x4_eq(f32x4_vec0 a, f32x4_vec1 b)
{
    return vceqq_f32(a, b);
}


static bad_forceinline mask128 bad_veccall f32x4_ge(f32x4_vec0 a, f32x4_vec1 b)
{
    return vcgeq_f32(a, b);
}


static bad_forceinline mask128 bad_veccall f32x4_gt(f32x4_vec0 a, f32x4_vec1 b)
{
    return vcgtq_f32(a, b);
}


static bad_forceinline mask128 bad_veccall f32x4_le(f32x4_vec0 a, f32x4_vec1 b)
{
    return vcleq_f32(a, b);
}


static bad_forceinline mask128 bad_veccall f32x4_lt(f32x4_vec0 a, f32x4_vec1 b)
{
    return vcltq_f32(a, b);
}



// ======= Selection & tests ========
static bad_forceinline mask128 bad_veccall f32x4_is_nan(f32x4_vec0 a)
{
    // nan is the only value for which a == a returns false
    return f32x4_neq(a, a);
}


static bad_forceinline mask128 bad_veccall f32x4_is_infinite(f32x4_vec0 a)
{
    // +inf is 0x7F800000, -inf is 0xFF800000
    const mask128 all1_mask  = mask128_all1();
    const mask128 value_mask = vshrq_n_u32(all1_mask, 1);
    const mask128 inf_mask   = vshrq_n_u32(vshlq_n_u32(all1_mask, 24), 1);

    return vceqq_f32(vandq_u32(value_mask, vreinterpretq_u32_f32(a)), inf_mask);
}


static bad_forceinline mask128 bad_veccall f32x4_is_finite(f32x4_vec0 a)
{
    const mask128 exp = mask128_exponent32();
    return vmvnq_u32(vceqq_f32(vandq_u32(vreinterpretq_u32_f32(a), exp), exp));
}