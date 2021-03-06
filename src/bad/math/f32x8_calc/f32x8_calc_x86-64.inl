// =========== Arithmetic ===========
static bad_forceinline f32x8 bad_veccall f32x8_add(f32x8 a, f32x8 b)
{
#if defined(__AVX__)
    return _mm256_add_ps(a, b);
#else
    return (f32x8){f32x4_add(a.a, b.a), f32x4_add(a.b, b.b)};
#endif
}


static bad_forceinline f32x8 bad_veccall f32x8_sub(f32x8 a, f32x8 b)
{
#if defined(__AVX__)
    return _mm256_sub_ps(a, b);
#else
    return (f32x8){f32x4_sub(a.a, b.a), f32x4_sub(a.b, b.b)};
#endif
}


static bad_forceinline f32x8 bad_veccall f32x8_mul(f32x8 a, f32x8 b)
{
#if defined(__AVX__)
    return _mm256_mul_ps(a, b);
#else
    return (f32x8){f32x4_mul(a.a, b.a), f32x4_mul(a.b, b.b)};
#endif
}


// NOTE: using _mm256_rcp_ps + _mm256_mul_ps brings significant imprecision
static bad_forceinline f32x8 bad_veccall f32x8_div(f32x8 a, f32x8 b)
{
#if defined(__AVX__)
    return _mm256_div_ps(a, b);
#else
    return (f32x8){f32x4_div(a.a, b.a), f32x4_div(a.b, b.b)};
#endif
}


// See Peter Cordes' very comprehensive explanation: https://stackoverflow.com/a/35270026/15315204
static bad_forceinline f32x8 bad_veccall f32x8_hadd(f32x8 a)
{
#if defined(__AVX__)
    // TODO: check whether _mm256_hadd_ps(a) is better here
    f32x4 low  = _mm256_castps256_ps128(a);
    f32x4 high = _mm256_extractf128_ps(a, 1);
          low  = _mm_add_ps(low, high);

    // TODO: manage the penalty for the AVX <--> SSE transition 
    f32x4 shuf = _mm_movehdup_ps(low);
    f32x4 sums = _mm_add_ps(low, shuf);
          shuf = _mm_movehl_ps(shuf, sums);
   
    return _mm256_set_m128(high, _mm_add_ss(sums, shuf));
#else
    f32x4 hadd = f32x4_add(f32x4_hadd4(a.a), f32x4_hadd4(a.b));

    return (f32x8){hadd, hadd};
#endif
}


static bad_forceinline f32 bad_veccall f32x8_sum(f32x8 a)
{
#if defined(__AVX__)
    f32x4 low  = _mm256_castps256_ps128(a);
    f32x4 high = _mm256_extractf128_ps(a, 1);
          low  = _mm_add_ps(low, high);

    // TODO: manage the penalty for the AVX <--> SSE transition 
    f32x4 shuf = _mm_movehdup_ps(low);
    f32x4 sums = _mm_add_ps(low, shuf);
          shuf = _mm_movehl_ps(shuf, sums);
   
    return _mm_cvtss_f32(_mm_add_ss(sums, shuf));
#else
    return f32x4_sum4(a.a) + f32x4_sum4(a.b);
#endif
}


// ====== Advanced arithmetic =======
static bad_forceinline f32x8 bad_veccall f32x8_rcp(f32x8 a)
{
#if defined(__AVX__)
    return _mm256_rcp_ps(a);
#else
    return (f32x8){f32x4_rcp(a.a), f32x4_rcp(a.b)};
#endif
}


static bad_forceinline f32x8 bad_veccall f32x8_sqrt(f32x8 a)
{
#if defined(__AVX__)
    return _mm256_sqrt_ps(a);
#else
    return (f32x8){f32x4_sqrt(a.a), f32x4_sqrt(a.b)};
#endif
}


static bad_forceinline f32x8 bad_veccall f32x8_rsqrt(f32x8 a)
{
#if defined(__AVX__)
    return _mm256_rsqrt_ps(a);
#else
    return (f32x8){f32x4_rsqrt(a.a), f32x4_rsqrt(a.b)};
#endif
}


static bad_forceinline f32x8 bad_veccall f32x8_min(f32x8 a, f32x8 b)
{
#if defined(__AVX__)
    return _mm256_min_ps(a, b);
#else
    return (f32x8){f32x4_min(a.a, b.a), f32x4_min(a.b, b.b)};
#endif
}


static bad_forceinline f32x8 bad_veccall f32x8_max(f32x8 a, f32x8 b)
{
#if defined(__AVX__)
    return _mm256_max_ps(a, b);
#else
    return (f32x8){f32x4_max(a.a, b.a), f32x4_max(a.b, b.b)};
#endif
}


static bad_forceinline f32x8 bad_veccall f32x8_abs(f32x8 a)
{
#if defined(__AVX2__)
    // Shift out the sign bit, shift in zero instead
    mask256 a_mask = _mm256_castps_si256(a);

    return _mm256_castsi256_ps(_mm256_srli_epi32(_mm256_slli_epi32(a_mask, 1), 1));
#elif defined(__AVX__)
    return _mm256_and_ps(mask256_value32(), a);
#elif defined(__SSE2__)
    return (f32x8){f32x4_abs(a.a), f32x4_abs(a.b)};
#else
    const mask128 value32 = mask128_value32();
    
    return {_mm_and_ps(value32, a.a), _mm_and_ps(value32, a.b)};
#endif
}


static bad_forceinline f32x8 bad_veccall f32x8_sign(f32x8 a)
{
#if defined(__AVX2__)
    mask256       a_sign = _mm256_cmpeq_epi32(_mm256_castps_si256(a), _mm256_castps_si256(a));
    const mask256 one    = _mm256_slli_epi32(_mm256_srli_epi32(a_sign, 25), 23);
                  a_sign = _mm256_slli_epi32(_mm256_srli_epi32(_mm256_castps_si256(a), 31), 31);

    return _mm256_castsi256_ps(_mm256_or_si256(one, a_sign));
#elif defined(__AVX__)
    const f32x8   one    = _mm256_set1_ps(1.f);
    const mask256 a_sign = _mm256_and_ps(_mm256_castsi256_ps(_mm256_set1_epi32(0x7FFFFFFF)), a);

    return _mm256_or_ps(one, a_sign);
#elif defined(__SSE2__)
    // b_sign is all1
    mask128       b_sign = _mm_cmpeq_epi32(_mm_castps_si128(a.a), _mm_castps_si128(a.a));
    const mask128 one    = _mm_slli_epi32(_mm_srli_epi32(b_sign, 25), 23);
    mask128       a_sign = _mm_slli_epi32(_mm_srli_epi32(_mm_castps_si128(a.a), 31), 31);
                  b_sign = _mm_slli_epi32(_mm_srli_epi32(_mm_castps_si128(a.b), 31), 31);

    return (f32x8)
    {
        _mm_castsi128_ps(_mm_or_si128(one, a_sign)),
        _mm_castsi128_ps(_mm_or_si128(one, b_sign)),
    }
#else
    const f32x4 one       = f32x4_one();
    const f32x4 sign_mask = mask128_highbit32();

    return (f32x8)
    {
        _mm_and_ps(_mm_or_ps(sign_mask, a.a), one),
        _mm_and_ps(_mm_or_ps(sign_mask, a.b), one),
    }
#endif
}


static bad_forceinline f32x8 bad_veccall f32x8_neg(f32x8 a)
{
#if defined(__AVX2__)
    return _mm256_castsi256_ps(_mm256_xor_si256(mask256_highbit32(), _mm256_castps_si256(a)));
#elif defined(__AVX__)
    return _mm256_xor_ps(mask256_highbit32(), a);
#elif defined(__SSE2___)
    return (f32x8){f32x4_neg(a.a), f32x4_neg(a.b)};
#else
    const mask128 highbit32 = mask128_highbit32();
    return {_mm_xor_ps(highbit32, a.a), _mm_xor_ps(highbit32, a.b)};
#endif
}


static bad_forceinline f32x8 bad_veccall f32x8_frac(f32x8 a)
{
    return f32x8_sub(a, f32x8_trunc(a));
}


static bad_forceinline f32x8 bad_veccall f32x8_mod(f32x8 a, f32x8 b)
{
#if defined(__AVX__)
    const f32x8 a_div_b = _mm256_div_ps(a, b);
    const f32x8 trunc   = f32x8_trunc(a_div_b);
    
    return f32x8_nmul_add(trunc, b, a);
#else
    return (f32x8){f32x4_mod(a, b), f32x4_mod(a, b)};
#endif
}


static bad_forceinline f32x8 bad_veccall f32x8_trunc(f32x8 a)
{
#if defined(__AVX__)
    return _mm256_round_ps(a, _MM_FROUND_TO_ZERO | _MM_FROUND_NO_EXC);
#else
    return (f32x8){f32x4_trunc(a.a), f32x4_trunc(a.b)};
#endif
}


static bad_forceinline f32x8 bad_veccall f32x8_round(f32x8 a)
{
#if defined(__AVX__)
    return _mm256_round_ps(a, _MM_FROUND_TO_NEAREST_INT | _MM_FROUND_NO_EXC);
#else
    return (f32x8){f32x4_round(a.a), f32x4_round(a.b)};
#endif
}


static bad_forceinline f32x8 bad_veccall f32x8_floor(f32x8 a)
{
#if defined(__AVX__)
    return _mm256_floor_ps(a);
#else
    return (f32x8){f32x4_floor(a.a), f32x4_floor(a.b)};
#endif
}


static bad_forceinline f32x8 bad_veccall f32x8_ceil(f32x8 a)
{
#if defined(__AVX__)
    return _mm256_ceil_ps(a);
#else
    return (f32x8){f32x4_ceil(a.a), f32x4_ceil(a.b)};
#endif
}


static bad_forceinline f32x8 bad_veccall f32x8_clamp(f32x8 a, f32x8 min, f32x8 max)
{
#if defined(__AVX__)
    return _mm256_min_ps(_mm256_max_ps(a, min), max);
#else
    return (f32x8){f32x4_clamp(a.a, b.a, max.a), f32x4_clamp(a.b, b.b, max.b)};
#endif
}


static bad_forceinline f32x8 bad_veccall f32x8_lerp(f32x8 a, f32x8 b, f32x8 t)
{
    const f32x8 vone = f32x8_one();

#if defined(__AVX__)
    f32x8 one_min_t = f32x8_sub(vone, t);

    return f32x8_add(f32x8_mul(one_min_t, a), f32x8_mul(t, b));
#else
    return (f32x8)
    {
        f32x4_add(f32x4_mul(f32x4_sub(vone, t.a), a.a), f32x4_mul(t.a, b.a)),
        f32x4_add(f32x4_mul(f32x4_sub(vone, t.b), a.b), f32x4_mul(t.b, b.b))
    };
#endif
}


static bad_forceinline f32x8 bad_veccall f32x8_copysign(f32x8 a, f32x8 reference_sign)
{
    const mask256 value_mask = mask256_set_all(0x7FFFFFFF);

    mask256 a_bits    = f32x8_as_mask256(a);
    mask256 sign_bits = f32x8_as_mask256(reference_sign);
            sign_bits = mask256_and_not(sign_bits, value_mask);
    mask256 a_value   = mask256_and(a_bits, value_mask);
    mask256 copysign  = mask256_or(a_value, sign_bits);

    return mask256_as_f32x8(copysign);
}


static bad_forceinline f32x8 bad_veccall f32x8_mul_by_sign(f32x8 a, f32x8 reference_sign)
{
    mask256 a_bits    = f32x8_as_mask256(a);
    mask256 sign_bits = f32x8_as_mask256(reference_sign);
            sign_bits = mask256_keep_highbit32(sign_bits);

    mask256 mul_by_sign_bits = mask256_xor(a_bits, sign_bits);

    return mask256_as_f32x8(mul_by_sign_bits);
}


// ========== Trigonometry ===========
// TODO(review): try to find an approximation proper to cos? Or keep it as is?
static bad_inline f32x8 bad_veccall f32x8_cos(f32x8 x)
{
    const f32x8 vhalf_pi = f32x8_set_all(half_pi);

    f32x8 shifted_x = f32x8_add(x, vhalf_pi);
    
    return f32x8_sin(shifted_x);
}


// Expects inputs in [0, pi/2]
static bad_inline f32x8 bad_veccall f32x8_cos_0_halfpi(f32x8 x)
{
    const f32x8 a2  = f32x8_set_all(-.4999999963f);
    const f32x8 a4  = f32x8_set_all( .0416666418f);
    const f32x8 a6  = f32x8_set_all(-.0013888397f);
    const f32x8 a8  = f32x8_set_all( .0000247609f);
    const f32x8 a10 = f32x8_set_all(-.0000002605f);
    const f32x8 one = f32x8_one();

    f32x8 x2  = f32x8_mul(x, x);
    f32x8 res = f32x8_mul_add(a10, x2,  a8);
          res = f32x8_mul_add(res, x2,  a6);
          res = f32x8_mul_add(res, x2,  a4);
          res = f32x8_mul_add(res, x2,  a2);
          res = f32x8_mul_add(res, x2, one);

    return res;
}


// Expects values in [-pi, pi]
static bad_inline f32x8 bad_veccall f32x8_sin(f32x8 x)
{
    const f32x8 vpi_rcp  = f32x8_set_all(pi_rcp);
    const f32x8 vpi      = f32x8_set_all(pi);

    f32x8   euclidian_div_f32 = f32x8_mul(x, vpi_rcp);
            euclidian_div_f32 = f32x8_trunc(euclidian_div_f32);
    mask256 euclidian_div_s32 = f32x8_to_s32x8(euclidian_div_f32);
    mask256 sin_x_neg         = mask256_keep_lowbit32(euclidian_div_s32);
            sin_x_neg         = mask256_shift_left32(sin_x_neg, 31);

    x = f32x8_nmul_add(euclidian_div_f32, vpi, x);

    f32x8   sin_x             = f32x8_sin_npi_pi(x);
    mask256 signed_sin_x_bits = f32x8_as_mask256(sin_x);
            signed_sin_x_bits = mask256_xor(signed_sin_x_bits, sin_x_neg);

    return mask256_as_f32x8(signed_sin_x_bits);
}


// Expects inputs in [-pi, pi]
static bad_inline f32x8 bad_veccall f32x8_sin_npi_pi(f32x8 x)
{
    const f32x8 c1  = f32x8_set_all(-.10132118f),
                       c3  = f32x8_set_all( .0066208798f),
                       c5  = f32x8_set_all(-.00017350505f),
                       c7  = f32x8_set_all( .0000025222919f),
                       c9  = f32x8_set_all(-.000000023317787f),
                       c11 = f32x8_set_all( .00000000013291342f),
                       er  = f32x8_set_all(3.1415927f + .00000008742278f);

    f32x8 x2  = f32x8_mul(x, x);
    f32x8 res = f32x8_mul_add(x2, c11, c9);
          res = f32x8_mul_add(x2, res, c7);
          res = f32x8_mul_add(x2, res, c5);
          res = f32x8_mul_add(x2, res, c3);
          res = f32x8_mul_add(x2, res, c1);
          res = f32x8_mul(x, res);
          res = f32x8_mul(res, f32x8_sub(x, er));

    return f32x8_mul(res, f32x8_add(x, er));
}


static bad_inline f32x8 bad_veccall f32x8_tan(f32x8 a)
{
    // TODO
    return a;
}


// Expects inputs in [-1; 1]
// Max error: ~1.5974045e-5
// Max relative error: ~0.0005%
static bad_inline f32x8 bad_veccall f32x8_acos(f32x8 x)
{
    const f32x8 vhalf_pi = f32x8_set_all(half_pi);
    const f32x8 vone     = f32x8_one();
    const f32x8 a2       = f32x8_set_all(-.0392588f);
    const f32x8 a4       = f32x8_set_all(.179323f);
    const f32x8 a6       = f32x8_set_all(-1.75866f);
    const f32x8 a8       = f32x8_set_all(-3.66063f);

    f32x8 abs_x = f32x8_abs(x);

    f32x8 acos  = f32x8_mul_add(a2,   abs_x, a4);
          acos  = f32x8_mul_add(acos, abs_x, a6);
          acos  = f32x8_mul_add(acos, abs_x, a8);
    f32x8 shift = f32x8_mul_sub(abs_x, abs_x, abs_x);
          acos  = f32x8_div(shift, acos);
          acos  = f32x8_add(abs_x, acos);

    f32x8 left = f32x8_sqrt(f32x8_sub(vone, acos));
          left = f32x8_sub(left, vone);
    f32x8 mul  = f32x8_mul_by_sign(left, x);

    return f32x8_mul_add(mul, vhalf_pi, vhalf_pi);
}


// ======== Fused operations ========
// a * b + c
static bad_forceinline f32x8 bad_veccall f32x8_mul_add(f32x8 a, f32x8 b, f32x8 c)
{
#if defined(__AVX__)
    return _mm256_fmadd_ps(a, b, c);
#else
    return (f32x8){f32x4_mul_add(a.a, b.a, c.a), f32x4_mul_add(a.b, b.b, c.b)};
#endif
}


// a * b - c
static bad_forceinline f32x8 bad_veccall f32x8_mul_sub(f32x8 a, f32x8 b, f32x8 c)
{
#if defined(__AVX__)
    return _mm256_fmsub_ps(a, b, c);
#else
    return (f32x8){f32x4_mul_sub(a.a, b.a, c.a), f32x4_mul_sub(a.b, b.b, c.b)};
#endif
}


// -a * b + c
static bad_forceinline f32x8 bad_veccall f32x8_nmul_add(f32x8 a, f32x8 b, f32x8 c)
{
#if defined(__AVX__)
    return _mm256_fnmadd_ps(a, b, c);
#else
    return (f32x8){f32x4_nmul_add(a.a, b.a, c.a), f32x4_nmul_add(a.b, b.b, c.b)};
#endif
}


// -a * b - c
static bad_forceinline f32x8 bad_veccall f32x8_nmul_sub(f32x8 a, f32x8 b, f32x8 c)
{
#if defined(__AVX__)
    return _mm256_fnmsub_ps(a, b, c);
#else
    return (f32x8){f32x4_nmul_sub(a.a, b.a, c.a), f32x4_nmul_sub(a.b, b.b, c.b)};
#endif
}


// ============ Comparison ============
static bad_forceinline mask256 bad_veccall f32x8_neq(f32x8 a, f32x8 b)
{
#if defined(__AVX__)
    return _mm256_castps_si256(_mm256_cmp_ps(a, b, _CMP_NEQ_UQ));
#else
    return (f32x8){f32x4_neq(a.a, b.a), f32x4_neq(a.b, b.b)};
#endif
}


static bad_forceinline mask256 bad_veccall f32x8_eq(f32x8 a, f32x8 b)
{
#if defined(__AVX__)
    return _mm256_castps_si256(_mm256_cmp_ps(a, b, _CMP_EQ_OQ));
#else
    return (f32x8){f32x4_eq(a.a, b.a), f32x4_eq(a.b, b.b)};
#endif
}


static bad_forceinline mask256 bad_veccall f32x8_ge(f32x8 a, f32x8 b)
{
#if defined(__AVX__)
    return _mm256_castps_si256(_mm256_cmp_ps(a, b, _CMP_GE_OQ));
#else
    return (f32x8){f32x4_ge(a.a, b.a), f32x4_ge(a.b, b.b)};
#endif
}


static bad_forceinline mask256 bad_veccall f32x8_gt(f32x8 a, f32x8 b)
{
#if defined(__AVX__)
    return _mm256_castps_si256(_mm256_cmp_ps(a, b, _CMP_GT_OQ));
#else
    return (f32x8){f32x4_gt(a.a, b.a), f32x4_gt(a.b, b.b)};
#endif
}


static bad_forceinline mask256 bad_veccall f32x8_le(f32x8 a, f32x8 b)
{
#if defined(__AVX__)
    return _mm256_castps_si256(_mm256_cmp_ps(a, b, _CMP_LE_OQ));
#else
    return (f32x8){f32x4_le(a.a, b.a), f32x4_le(a.b, b.b)};
#endif
}


static bad_forceinline mask256 bad_veccall f32x8_lt(f32x8 a, f32x8 b)
{
#if defined(__AVX__)
    return _mm256_castps_si256(_mm256_cmp_ps(a, b, _CMP_LT_OQ));
#else
    return (f32x8){f32x4_lt(a.a, b.a), f32x4_lt(a.b, b.b)};
#endif
}



// ============= Tests ==============
static bad_forceinline mask256 bad_veccall f32x8_is_positive(f32x8 a)
{
#if defined(__AVX2__)
    mask256 a_mask    = f32x8_as_mask256(a);
    mask256 sign_only = mask256_shift_right32(a_mask, 31);
    mask256 zero_mask = mask256_zero();

    return _mm256_cmpeq_epi32(sign_only, zero_mask);
#else
    f32x8 vzero = f32x8_zero();
    
    return f32x8_ge(a, vzero);
#endif
}


static bad_forceinline mask256 bad_veccall f32x8_is_negative(f32x8 a)
{
#if defined(__AVX2__)
    mask256 a_mask    = f32x8_as_mask256(a);
    mask256 zero_mask = mask256_zero();

    return _mm256_cmpgt_epi32(a_mask, zero_mask);
#else
    f32x8 vzero = f32x8_zero();
    
    return f32x8_neq(a_mask, vzero);
#endif
}


static bad_forceinline mask256 bad_veccall f32x8_is_nan(f32x8 a)
{
#if defined(__AVX__)
    return f32x8_neq(a, a);
#else
    return (f32x8){f32x4_is_nan(a.a), f32x4_is_nan(a.b)};
#endif
}


static bad_forceinline mask256 bad_veccall f32x8_is_infinite(f32x8 a)
{
#if defined(__AVX2__)
    mask256 a_abs    = mask256_all1();
    mask256 inf_mask = _mm256_srli_epi32(_mm256_slli_epi32(a_abs, 24), 1);
            a_abs    = _mm256_srli_epi32(a_abs, 1);
            a_abs    = _mm256_and_si256(a_abs, _mm256_castps_si256(a));

    return _mm256_cmpeq_epi32(a_abs, inf_mask);
#elif defined(__SSE2__)
    mask128 a_abs    = mask128_all1();
    mask128 inf_mask = _mm_srli_epi32(_mm_slli_epi32(a_abs, 24), 1);
            a_abs    = _mm_srli_epi32(a_abs, 1);

    return (f32x8)
    {
        _mm_cmpeq_epi32(mask128_and(a_abs, _mm_castps_si128(a.a)), inf_mask),
        _mm_cmpeq_epi32(mask128_and(a_abs, _mm_castps_si128(a.b)), inf_mask)
    };
#else
    mask128 value_mask = mask128_value32();
    mask128 inf_mask   = mask128_exponent32();

    return (f32x8)
    {
        _mm_cmpeq_ps(_mm_and_ps(value_mask, a.a), inf_mask),
        _mm_cmpeq_ps(_mm_and_ps(value_mask, a.b), inf_mask)
    };
#endif
}


static bad_forceinline mask256 bad_veccall f32x8_is_finite(f32x8 a)
{
#if defined(__AVX__)
    // a is finite if its exponent is not all 1
    mask256 exp_mask = mask256_exponent32();
    return mask256_neq(mask256_and(f32x8_as_mask256(a), exp_mask), exp_mask);
#else
    mask128 exp_mask = mask128_exponent32();

    return (f32x8)
    {
        mask128_neq(mask128_and(f32x4_as_mask128(a.a), exp_mask), exp_mask),
        mask128_neq(mask128_and(f32x4_as_mask128(a.b), exp_mask), exp_mask),
    };
#endif
}