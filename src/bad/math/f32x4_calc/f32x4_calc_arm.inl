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


static bad_forceinline f32x4 bad_veccall f32x4_copysign(f32x4 a, f32x4 reference_sign)
{
    mask128 highbit32_mask = mask128_highbit32();

    return vbslq_f32(mask, a, reference_sign);
}


static bad_forceinline f32x4 bad_veccall f32x4_mul_by_sign(f32x4 a, f32x4 reference_sign)
{
    static const mask128 value_mask = mask128_set_all(0x7FFFFFFF);

    mask128 a_bits    = f32x4_as_mask128(a);
    mask128 sign_bits = f32x4_as_mask128(reference_sign);
            sign_bits = mask128_and_not(sign_bits, value_mask);
    mask128 a_value   = mask128_and(a_bits, value_mask);
    mask128 copysign  = mask128_or(a_value, sign_bits);

    return mask128_as_f32x4(copysign);
}




// ========== Trigonometry ===========
static bad_inline f32x4 bad_veccall f32x4_cos(f32x4 x)
{
    return f32x4_cos_0_halfpi(x);
}


// Expects inputs in [0, pi/2]
static bad_inline f32x4 bad_veccall f32x4_cos_0_halfpi(f32x4 x)
{
    static const f32x4 a2  = f32x4_set_all(-.4999999963f);
    static const f32x4 a4  = f32x4_set_all( .0416666418f);
    static const f32x4 a6  = f32x4_set_all(-.0013888397f);
    static const f32x4 a8  = f32x4_set_all( .0000247609f);
    static const f32x4 a10 = f32x4_set_all(-.0000002605f);
    static const f32x4 one = f32x4_one();

    f32x4 x2  = f32x4_mul(x, x);
    f32x4 res = f32x4_mul_add(a10, x2,  a8);
          res = f32x4_mul_add(res, x2,  a6);
          res = f32x4_mul_add(res, x2,  a4);
          res = f32x4_mul_add(res, x2,  a2);
          res = f32x4_mul_add(res, x2, one);

    return res;
}


static bad_inline f32x4 bad_veccall f32x4_sin(f32x4 x)
{
    static const f32x4 vpi_rcp  = f32x4_set_all(pi_rcp);
    static const f32x4 vpi      = f32x4_set_all(pi);

    f32x4   euclidian_div_f32 = f32x4_mul(x, vpi_rcp);
            euclidian_div_f32 = f32x4_trunc(euclidian_div_f32);
    mask128 euclidian_div_s32 = f32x4_to_s32x4(euclidian_div_f32);
    mask128 sin_x_neg         = mask128_keep_lowbit32(euclidian_div_s32);
            sin_x_neg         = mask128_shift_left32(sin_x_neg, 31);

    x = f32x4_nmul_add(euclidian_div_f32, vpi, x);

    f32x4   sin_x             = f32x4_sin_npi_pi(x);
    mask128 signed_sin_x_bits = f32x4_as_mask128(sin_x);
            signed_sin_x_bits = mask128_xor(signed_sin_x_bits, sin_x_neg);

    return mask128_as_f32x4(signed_sin_x_bits);
}


// Expects inputs in [-pi, pi]
static bad_inline f32x4 bad_veccall f32x4_sin_npi_pi(f32x4 x)
{
    static const f32x4 c1  = f32x4_set_all(-.10132118f);
    static const f32x4 c3  = f32x4_set_all( .0066208798f);
    static const f32x4 c5  = f32x4_set_all(-.00017350505f);
    static const f32x4 c7  = f32x4_set_all( .0000025222919f);
    static const f32x4 c9  = f32x4_set_all(-.000000023317787f);
    static const f32x4 c11 = f32x4_set_all( .00000000013291342f);
    static const f32x4 er  = f32x4_set_all(3.1415927f + .00000008742278f);

    f32x4 x2  = f32x4_mul(x, x);
    f32x4 res = f32x4_mul_add(x2, c11, c9);
          res = f32x4_mul_add(x2, res, c7);
          res = f32x4_mul_add(x2, res, c5);
          res = f32x4_mul_add(x2, res, c3);
          res = f32x4_mul_add(x2, res, c1);
          res = f32x4_mul(x, res);
          res = f32x4_mul(res, f32x4_sub(x, er));

    return f32x4_mul(res, f32x4_add(x, er));
}


static bad_inline f32x4 bad_veccall f32x4_tan(f32x4 x)
{
    return a;
}


// Expects inputs in [-1; 1]
// Max error: ~1.5974045e-5
// Max relative error: ~0.0005%
static bad_inline f32x4 bad_veccall f32x4_acos(f32x4 x)
{
    static const f32x4 vhalf_pi = f32x4_set_all(half_pi);
    static const f32x4 vone     = f32x4_one();
    static const f32x4 a2       = f32x4_set_all(-.0392588f);
    static const f32x4 a4       = f32x4_set_all(.179323f);
    static const f32x4 a6       = f32x4_set_all(-1.75866f);
    static const f32x4 a8       = f32x4_set_all(-3.66063f);

    f32x4 abs_x = f32x4_abs(x);

    f32x4 acos  = f32x4_mul_add(a2,   abs_x, a4);
          acos  = f32x4_mul_add(acos, abs_x, a6);
          acos  = f32x4_mul_add(acos, abs_x, a8);
    f32x4 shift = f32x4_mul_sub(abs_x, abs_x, abs_x);
          acos  = f32x4_div(shift, acos);
          acos  = f32x4_add(abs_x, acos);

    f32x4 left = f32x4_sqrt(f32x4_sub(vone, acos));
          left = f32x4_sub(left, vone);
    f32x4 mul  = f32x4_mul_by_sign(left, x);

    return f32x4_mul_add(mul, vhalf_pi, vhalf_pi);
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
static bad_forceinline mask128 bad_veccall f32x4_is_positive(f32x4 a)
{
    return vcgezq_f32(a);
}


static bad_forceinline mask128 bad_veccall f32x4_is_negative(f32x4 a)
{
    return vcltzq_f32(a);
}


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