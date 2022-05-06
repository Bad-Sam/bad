// =========== Arithmetic ===========
static bad_forceinline f32x4 bad_veccall f32x4_add(f32x4 a, f32x4 b)
{
    return vaddq_f32(a, b);
}


static bad_forceinline f32x4 bad_veccall f32x4_sub(f32x4 a, f32x4 b)
{
    return vsubq_f32(a, b);
}


static bad_forceinline f32x4 bad_veccall f32x4_mul(f32x4 a, f32x4 b)
{
    return vmulq_f32(a, b);
}


static bad_forceinline f32x4 bad_veccall f32x4_div(f32x4 a, f32x4 b)
{
    return vdivq_f32(a, b);
}


static bad_forceinline f32x4 bad_veccall f32x4_hadd3(f32x4 a)
{
    f32x4 sum = vpaddq_f32(a, a);

    return vpaddq_f32(sum, vdupq_laneq_f32(a, 2));
}


static bad_forceinline f32x4 bad_veccall f32x4_hadd4(f32x4 a)
{
    f32x4 sum = vpaddq_f32(a, a);

    return vpaddq_f32(sum, sum);
}


static bad_forceinline f32 bad_veccall f32x4_sum3(f32x4 a)
{
    return f32x4_get_0(f32x4_hadd3(a));
}


static bad_forceinline f32 bad_veccall f32x4_sum4(f32x4 a)
{
    return vaddvq_f32(a);
}


// ====== Advanced arithmetic =======
static bad_forceinline f32x4 bad_veccall f32x4_rcp(f32x4 a)
{
    return vrecpeq_f32(a);
}


static bad_forceinline f32x4 bad_veccall f32x4_sqrt(f32x4 a)
{
    return vsqrtq_f32(a);
}


static bad_forceinline f32x4 bad_veccall f32x4_rsqrt(f32x4 a)
{
    return vrsqrteq_f32(a);
}


static bad_forceinline f32x4 bad_veccall f32x4_min(f32x4 a, f32x4 b)
{
    return vminq_f32(a, b);
}


static bad_forceinline f32x4 bad_veccall f32x4_max(f32x4 a, f32x4 b)
{
    return vmaxq_f32(a, b);
}


static bad_forceinline f32x4 bad_veccall f32x4_abs(f32x4 a)
{
    return vabsq_f32(a);
}


static bad_forceinline f32x4 bad_veccall f32x4_sign(f32x4 a)
{
    mask128 a_sign = vceqq_u32(vreinterpretq_u32_f32(a), vreinterpretq_u32_f32(a));
    mask128 one    = vshlq_n_u32(vshrq_n_u32(a_sign, 25), 23);
    
    a_sign = mask128_keep_highbit32(f32x4_as_mask128(a));

    return vreinterpretq_f32_u32(vorq_u32(one, a_sign));
}


static bad_forceinline f32x4 bad_veccall f32x4_neg(f32x4 a)
{
    return vnegq_f32(a);
}


static bad_forceinline f32x4 bad_veccall f32x4_frac(f32x4 a)
{
    return f32x4_sub(a, f32x4_trunc(a));
}


static bad_forceinline f32x4 bad_veccall f32x4_mod(f32x4 a, f32x4 b)
{
    // TODO: test vmulq_f32(a, vrecpeq_f32(b))
    f32x4 truncated = vdivq_f32(a, b);
          truncated = vrndq_f32(truncated);
    
    return vsubq_f32(a, vmulq_f32(truncated, b));
}


static bad_forceinline f32x4 bad_veccall f32x4_trunc(f32x4 a)
{
    return vrndq_f32(a);
}


static bad_forceinline f32x4 bad_veccall f32x4_round(f32x4 a)
{
    return vrndnq_f32(a);
}


static bad_forceinline f32x4 bad_veccall f32x4_floor(f32x4 a)
{
    return vrndmq_f32(a);
}


static bad_forceinline f32x4 bad_veccall f32x4_ceil(f32x4 a)
{
    return vrndpq_f32(a);
}


static bad_forceinline f32x4 bad_veccall f32x4_clamp(f32x4 a, f32x4 min, f32x4 max)
{
    return vminq_f32(vmax_f32(a, min), max);
}


static bad_forceinline f32x4 bad_veccall f32x4_lerp(f32x4 a, f32x4 b, f32x4 t)
{
    f32x4 one_min_t = f32x4_sub(f32x4_one(), t);

    return f32x4_add(f32x4_mul(a, one_min_t), f32x4_mul(b, t));
}


// ========== Trigonometry ===========
static bad_forceinline f32x4 bad_veccall f32x4_cos(f32x4 a)
{
    return a;
}


static bad_forceinline f32x4 bad_veccall f32x4_sin(f32x4 a)
{
    // Based on Chebyshev polynomials
    static const f32x4 c0     = f32x4_set_all(-.10132118f),
                       c1     = f32x4_set_all(.0066208798f),
                       c2     = f32x4_set_all(-.00017350505f),
                       c3     = f32x4_set_all(.0000025222919f),
                       c4     = f32x4_set_all(-.000000023317787f),
                       c5     = f32x4_set_all(.00000000013291342f),
                       pi     = f32x4_set_all(3.1415927f),
                       inv_pi = f32x4_set_all(.31830988f),
                       err    = f32x4_set_all(3.1415927f + .00000008742278f);

    static const mask128 odd_mask = mask128_set_all(1);

    { // Bring angles to [-pi, pi] to reach the 4 ULP precision goal
        // TODO: Bring to [0, 2pi] and subtract pi?
        f32x4   a_inv_pi  = f32x4_mul(a, inv_pi);
        mask128 a_floored = vcvtq_s32_f32(f32x4_floor(a_inv_pi));
        mask128 a_int     = mask128_and(a_floored, odd_mask);
                a_int     = vaddq_s32(a_floored, a_int);
                a         = f32x4_sub(a, f32x4_mul(vcvtq_f32_s32(a_int), pi));
    }

    f32x4 a2 = f32x4_mul(a, a);

    // Using Horner's method for polynomial evaluation
    f32x4 res = f32x4_mul_add(a2, c5,  c4);
    res       = f32x4_mul_add(a2, res, c3);
    res       = f32x4_mul_add(a2, res, c2);
    res       = f32x4_mul_add(a2, res, c1);
    res       = f32x4_mul_add(a2, res, c0);
    res       = f32x4_mul(a, res);
    res       = f32x4_mul(res, f32x4_sub(a, err));

    return f32x4_mul(res, f32x4_add(a, err));
}


static bad_forceinline f32x4 bad_veccall f32x4_tan(f32x4 a)
{
    return a;
}


// ======== Fused operations ========
// a * b + c
static bad_forceinline f32x4 bad_veccall f32x4_mul_add(f32x4 a, f32x4 b, f32x4 c)
{
#if defined(__ARM_FEATURE_FMA)
    return vfmaq_f32(c, a, b);
#else
    return vmlaq_f32(c, a, b);
#endif
}

// a * b - c
static bad_forceinline f32x4 bad_veccall f32x4_mul_sub(f32x4 a, f32x4 b, f32x4 c)
{
#if defined(__ARM_FEATURE_FMA)
    return vnegq_f32(vfmsq_f32(c, a, b));
#else
    return vnegq_f32(vmlsq_f32(c, a, b));
#endif
}

// -a * b + c
static bad_forceinline f32x4 bad_veccall f32x4_nmul_add(f32x4 a, f32x4 b, f32x4 c)
{
#if defined(__ARM_FEATURE_FMA)
    return vfmsq_f32(c, a, b);
#else
    return vmlsq_f32(c, a, b);
#endif
}

// -a * b - c
static bad_forceinline f32x4 bad_veccall f32x4_nmul_sub(f32x4 a, f32x4 b, f32x4 c)
{
#if defined(__ARM_FEATURE_FMA)
    return vnegq_f32(vfmaq_f32(c, a, b));
#else
    return vnegq_f32(vmlaq_f32(c, a, b));
#endif
}


// ============ Comparison ============
static bad_forceinline mask128 bad_veccall f32x4_neq(f32x4 a, f32x4 b)
{
    return vmvnq_u32(vceqq_f32(a, b));
}


static bad_forceinline mask128 bad_veccall f32x4_eq(f32x4 a, f32x4 b)
{
    return vceqq_f32(a, b);
}


static bad_forceinline mask128 bad_veccall f32x4_ge(f32x4 a, f32x4 b)
{
    return vcgeq_f32(a, b);
}


static bad_forceinline mask128 bad_veccall f32x4_gt(f32x4 a, f32x4 b)
{
    return vcgtq_f32(a, b);
}


static bad_forceinline mask128 bad_veccall f32x4_le(f32x4 a, f32x4 b)
{
    return vcleq_f32(a, b);
}


static bad_forceinline mask128 bad_veccall f32x4_lt(f32x4 a, f32x4 b)
{
    return vcltq_f32(a, b);
}



// ======= Selection & tests ========
static bad_forceinline mask128 bad_veccall f32x4_is_nan(f32x4 a)
{
    // nan is the only value for which a == a returns false
    return f32x4_neq(a, a);
}


static bad_forceinline mask128 bad_veccall f32x4_is_infinite(f32x4 a)
{
    // +inf is 0x7F800000, -inf is 0xFF800000
    mask128 all1_mask  = mask128_all1();
    mask128 value_mask = vshrq_n_u32(all1_mask, 1);
    mask128 inf_mask   = vshrq_n_u32(vshlq_n_u32(all1_mask, 24), 1);

    return vceqq_f32(vandq_u32(value_mask, vreinterpretq_u32_f32(a)), inf_mask);
}


static bad_forceinline mask128 bad_veccall f32x4_is_finite(f32x4 a)
{
    mask128 exp = mask128_exponent32();

    return vmvnq_u32(vceqq_f32(vandq_u32(vreinterpretq_u32_f32(a), exp), exp));
}