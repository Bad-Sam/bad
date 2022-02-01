// =========== Arithmetic ===========
static bad_forceinline f32x8 bad_veccall f32x8_add(f32x8_vec0 a, f32x8_vec1 b)
{
#if defined(__AVX__)
    return _mm256_add_ps(a, b);
#else
    return (f32x8){f32x4_add(a.a, b.a), f32x4_add(a.b, b.b)};
#endif
}


static bad_forceinline f32x8 bad_veccall f32x8_sub(f32x8_vec0 a, f32x8_vec1 b)
{
#if defined(__AVX__)
    return _mm256_sub_ps(a, b);
#else
    return (f32x8){f32x4_sub(a.a, b.a), f32x4_sub(a.b, b.b)};
#endif
}


static bad_forceinline f32x8 bad_veccall f32x8_mul(f32x8_vec0 a, f32x8_vec1 b)
{
#if defined(__AVX__)
    return _mm256_mul_ps(a, b);
#else
    return (f32x8){f32x4_mul(a.a, b.a), f32x4_mul(a.b, b.b)};
#endif
}


// NOTE: using _mm256_rcp_ps + _mm256_mul_ps brings significant imprecision
static bad_forceinline f32x8 bad_veccall f32x8_div(f32x8_vec0 a, f32x8_vec1 b)
{
#if defined(__AVX__)
    return _mm256_div_ps(a, b);
#else
    return (f32x8){f32x4_div(a.a, b.a), f32x4_div(a.b, b.b)};
#endif
}


// See Peter Cordes' very comprehensive explaination: https://stackoverflow.com/a/35270026/15315204
static bad_forceinline f32 bad_veccall f32x8_hadd(f32x8_vec0 a)
{
#if defined(__AVX__)
    f32x4 low   = _mm256_castps256_ps128(v);
    f32x4 high  = _mm256_extractf128_ps(v, 1);
    low         = _mm_add_ps(low, high);

    // TODO: isn't there a penalty for the AVX <--> SSE transition?
    //       If so, find an alternative 
    f32x4 shuf = _mm_movehdup_ps(low);
    f32x4 sums = _mm_add_ps(low, shuf);
    shuf       = _mm_movehl_ps(shuf, sums);
    sums       = _mm_add_ss(sums, shuf);

    return _mm_cvtss_f32(sums);
#else
    return (f32x8){f32x4_hadd(a.a), f32x4_hadd(a.b)};
#endif
}


// ====== Advanced arithmetic =======
static bad_forceinline f32x8 bad_veccall f32x8_rcp(f32x8_vec0 a)
{
#if defined(__AVX__)
    return _mm256_rcp_ps(a);
#else
    return (f32x8){f32x4_rcp(a.a), f32x4_rcp(a.b)};
#endif
}


static bad_forceinline f32x8 bad_veccall f32x8_sqrt(f32x8_vec0 a)
{
#if defined(__AVX__)
    return _mm256_sqrt_ps(a);
#else
    return (f32x8){f32x4_sqrt(a.a), f32x4_sqrt(a.b)};
#endif
}


static bad_forceinline f32x8 bad_veccall f32x8_rsqrt(f32x8_vec0 a)
{
#if defined(__AVX__)
    return _mm256_rsqrt_ps(a);
#else
    return (f32x8){f32x4_rsqrt(a.a), f32x4_rsqrt(a.b)};
#endif
}


static bad_forceinline f32x8 bad_veccall f32x8_min(f32x8_vec0 a, f32x8_vec1 b)
{
#if defined(__AVX__)
    return _mm256_min_ps(a, b);
#else
    return (f32x8){f32x4_min(a.a, b.a), f32x4_min(a.b, b.b)};
#endif
}


static bad_forceinline f32x8 bad_veccall f32x8_max(f32x8_vec0 a, f32x8_vec1 b)
{
#if defined(__AVX__)
    return _mm256_max_ps(a, b);
#else
    return (f32x8){f32x4_max(a.a, b.a), f32x4_max(a.b, b.b)};
#endif
}


static bad_forceinline f32x8 bad_veccall f32x8_abs(f32x8_vec0 a)
{
#if defined(__AVX2__)
    // Shift out the sign bit, shift in zero instead
    const mask256 a_mask = _mm256_castps_si256(a);
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


static bad_forceinline f32x8 bad_veccall f32x8_neg(f32x8_vec0 a)
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


static bad_forceinline f32x8 bad_veccall f32x8_mod(f32x8_vec0 a, f32x8_vec1 b)
{
#if defined(__AVX__)
    const f32x8 a_div_b = _mm256_div_ps(a, b);
    const f32x8 trunc   = f32x8_trunc(a_div_b);
    
    return _mm256_sub_ps(a, _mm256_mul_ps(trunc, b));
#else
    return (f32x8){f32x4_mod(a, b), f32x4_mod(a, b)};
#endif
}


static bad_forceinline f32x8 bad_veccall f32x8_trunc(f32x8_vec0 a)
{
#if defined(__AVX__)
    _mm256_round_ps(a, _MM_FROUND_TO_ZERO | _MM_FROUND_NO_EXC);
#else
    return (f32x8){f32x4_trunc(a.a), f32x4_trunc(a.b)};
#endif
}


static bad_forceinline f32x8 bad_veccall f32x8_round(f32x8_vec0 a)
{
#if defined(__AVX__)
    return _mm256_round_ps(a, _MM_FROUND_TO_NEAREST_INT | _MM_FROUND_NO_EXC);
#else
    return (f32x8){f32x4_round(a.a), f32x4_round(a.b)};
#endif
}


static bad_forceinline f32x8 bad_veccall f32x8_floor(f32x8_vec0 a)
{
#if defined(__AVX__)
    return _mm256_floor_ps(a);
#else
    return (f32x8){f32x4_floor(a.a), f32x4_floor(a.b)};
#endif
}


static bad_forceinline f32x8 bad_veccall f32x8_ceil(f32x8_vec0 a)
{
#if defined(__AVX__)
    return _mm256_ceil_pss(a);
#else
    return (f32x8){f32x4_ceil(a.a), f32x4_ceil(a.b)};
#endif
}


static bad_forceinline f32x8 bad_veccall f32x8_clamp(f32x8_vec0 a, f32x8_vec1 min, f32x8_vec2 max)
{
#if defined(__AVX__)
    return _mm256_min_ps(_mm256_max_ps(a, min), max);
#else
    return (f32x8){f32x4_clamp(a.a, b.a, max.a), f32x4_clamp(a.b, b.b, max.b)};
#endif
}


// a * b + c
static bad_forceinline f32x8 bad_veccall f32x8_mul_add(f32x8_vec0 a, f32x8_vec1 b, f32x8_vec2 c)
{
#if defined(__AVX__)
    return _mm256_fmadd_ps(a, b, c);
#else
    return (f32x8){f32x4_mul_add(a.a, b.a, c.a), f32x4_mul_add(a.b, b.b, c.b)};
#endif
}


// a * b - c
static bad_forceinline f32x8 bad_veccall f32x8_mul_sub(f32x8_vec0 a, f32x8_vec1 b, f32x8_vec2 c)
{
#if defined(__AVX__)
    return _mm256_fmsub_ps(a, b, c);
#else
    return (f32x8){f32x4_mul_sub(a.a, b.a, c.a), f32x4_mul_sub(a.b, b.b, c.b)};
#endif
}


// -a * b + c
static bad_forceinline f32x8 bad_veccall f32x8_nmul_add(f32x8_vec0 a, f32x8_vec1 b, f32x8_vec2 c)
{
#if defined(__AVX__)
    return _mm256_fnmadd_ps(a, b, c);
#else
    return (f32x8){f32x4_nmul_add(a.a, b.a, c.a), f32x4_nmul_add(a.b, b.b, c.b)};
#endif
}


// -a * b - c
static bad_forceinline f32x8 bad_veccall f32x8_nmul_sub(f32x8_vec0 a, f32x8_vec1 b, f32x8_vec2 c)
{
#if defined(__AVX__)
    return _mm256_fnmsub_ps(a, b, c);
#else
    return (f32x8){f32x4_nmul_sub(a.a, b.a, c.a), f32x4_nmul_sub(a.b, b.b, c.b)};
#endif
}


// ============ Comparison ============
static bad_forceinline mask256 bad_veccall f32x8_neq(f32x8_vec0 a, f32x8_vec1 b)
{
#if defined(__AVX__)
    return _mm256_castps_si256(_mm256_cmp_ps(a, b, _CMP_NEQ_OQ));
#else
    return (f32x8){f32x4_neq(a.a, b.a), f32x4_neq(a.b, b.b)};
#endif
}


static bad_forceinline mask256 bad_veccall f32x8_eq(f32x8_vec0 a, f32x8_vec1 b)
{
#if defined(__AVX__)
    return _mm256_castps_si256(_mm256_cmp_ps(a, b, _CMP_EQ_OQ));
#else
    return (f32x8){f32x4_eq(a.a, b.a), f32x4_eq(a.b, b.b)};
#endif
}


static bad_forceinline mask256 bad_veccall f32x8_ge(f32x8_vec0 a, f32x8_vec1 b)
{
#if defined(__AVX__)
    return _mm256_castps_si256(_mm256_cmp_ps(a, b, _CMP_GE_OQ));
#else
    return (f32x8){f32x4_ge(a.a, b.a), f32x4_ge(a.b, b.b)};
#endif
}


static bad_forceinline mask256 bad_veccall f32x8_gt(f32x8_vec0 a, f32x8_vec1 b)
{
#if defined(__AVX__)
    return _mm256_castps_si256(_mm256_cmp_ps(a, b, _CMP_GT_OQ));
#else
    return (f32x8){f32x4_gt(a.a, b.a), f32x4_gt(a.b, b.b)};
#endif
}


static bad_forceinline mask256 bad_veccall f32x8_le(f32x8_vec0 a, f32x8_vec1 b)
{
#if defined(__AVX__)
    return _mm256_castps_si256(_mm256_cmp_ps(a, b, _CMP_LE_OQ));
#else
    return (f32x8){f32x4_le(a.a, b.a), f32x4_le(a.b, b.b)};
#endif
}


static bad_forceinline mask256 bad_veccall f32x8_lt(f32x8_vec0 a, f32x8_vec1 b)
{
#if defined(__AVX__)
    return _mm256_castps_si256(_mm256_cmp_ps(a, b, _CMP_LT_OQ));
#else
    return (f32x8){f32x4_lt(a.a, b.a), f32x4_lt(a.b, b.b)};
#endif
}



// ============= Tests ==============
static bad_forceinline mask256 bad_veccall f32x8_is_nan(f32x8_vec0 a)
{
#if defined(__AVX__)
    return f32x8_neq(a, a);
#else
    return (f32x8){f32x4_is_nan(a.a), f32x4_is_nan(a.b)};
#endif
}


static bad_forceinline mask256 bad_veccall f32x8_is_infinite(f32x8_vec0 a)
{
#if defined(__AVX2__)
    const mask256 all1_mask = mask256_all1();
    const mask256 inf_mask  = _mm256_srli_epi32(_mm256_slli_epi32(all1_mask, 24), 1);
    mask256 a_abs           = _mm256_srli_epi32(all1_mask, 1);
    a_abs                   = _mm256_and_si256(a_abs, _mm256_castps_si256(a));

    return _mm256_cmpeq_epi32(a_abs, inf_mask, _CMP_EQ_OQ);
#else
#   if defined(__SSE2__)
    mask128 a_abs          = mask128_all1();
    const mask128 inf_mask = _mm_srli_epi32(_mm_slli_epi32(a_abs, 24), 1);
    a_abs                  = _mm_srli_epi32(a_abs, 1);

    return (f32x8)
    {
        _mm_cmpeq_epi32(mask128_and(a_abs, _mm_castps_si128(a.a)), inf_mask),
        _mm_cmpeq_epi32(mask128_and(a_abs, _mm_castps_si128(a.b)), inf_mask)
    };
#   else
    const mask128 value_mask = mask128_value32();
    const mask128 inf_mask   = mask128_exponent32();

    return (f32x8)
    {
        _mm_cmpeq_ps(_mm_and_ps(value_mask, a.a), inf_mask),
        _mm_cmpeq_ps(_mm_and_ps(value_mask, a.b), inf_mask)
    };
#   endif
#endif
}


static bad_forceinline mask256 bad_veccall f32x8_is_finite(f32x8_vec0 a)
{
#if defined(__AVX__)
    // a is finite if its exponent is not all 1
    const mask256 exp_mask = mask256_exponent32();
    return mask256_eq(mask256_and(f32x8_cast_mask256(a), exp_mask), exp_mask);
#else
    const mask128 exp_mask = mask128_exponent32();

    return (f32x8)
    {
        mask128_eq(mask128_and(f32x4_cast_mask128(a.a), exp_mask), exp_mask),
        mask128_eq(mask128_and(f32x4_cast_mask128(a.b), exp_mask), exp_mask),
    };
#endif
}