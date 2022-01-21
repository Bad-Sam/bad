// ============= Defaults =============
static bad_forceinline f32x4 f32x4_any()
{
    return _mm_undefined_ps();
}


static bad_forceinline f32x4 f32x4_zero()
{
    return _mm_setzero_ps();
}


static bad_forceinline f32x4 f32x4_one()
{
#if defined(__SSE2__)
    const mask128 one = _mm_slli_epi32(_mm_srli_epi32(mask128_all1(), 25), 23);

    return _mm_castsi128_ps(one);
#else
    return _mm_set1_ps(1.f);
#endif
}


// ========== Loads & stores ==========
static bad_forceinline f32x4 f32x4_load(const f32* mem_addr)
{
    bad_assert_sse_aligned(mem_addr);

#if defined(__SSE2__)
    // NOTE: si128 version has a better throughput
    return _mm_load_si128((__m128i*)mem_addr);
#else
    return _mm_load_ps(mem_addr);
#endif
}


static bad_forceinline f32x4 f32x4_loadu(const f32* mem_addr)
{
#if defined(__SSE2__)
    // NOTE: si128 version has a better throughput
    return _mm_loadu_si128((__m128i*)mem_addr);
#else
    return _mm_loadu_ps(mem_addr);
#endif
}


static bad_forceinline f32x4 f32x4_set(const f32 a, const f32 b, const f32 c, const f32 d)
{
    return _mm_set_ps(d, c, b, a);
}


static bad_forceinline f32x4 f32x4_set1(const f32 a)
{
    return _mm_set1_ps(a);
}


static bad_forceinline void bad_veccall f32x4_store(f32* mem_addr, f32x4_vec0 a)
{
    bad_assert_sse_aligned(mem_addr);

#if defined(__SSE2__)
    // NOTE: si128 version has a better throughput
    return _mm_store_si128((__m128i*)mem_addr, a);
#else
    return _mm_store_ps(mem_addr, a);
#endif
}


static bad_forceinline void bad_veccall f32x4_storeu(f32* mem_addr, f32x4_vec0 a)
{
#if defined(__SSE2__)
    // NOTE: si128 version has a better throughput
    return _mm_storeu_si128((__m128i*)mem_addr, a);
#else
    return _mm_storeu_ps(mem_addr, a);
#endif
}


// =========== Arithmetic ===========
static bad_forceinline f32x4 bad_veccall f32x4_add(f32x4_vec0 a, f32x4_vec1 b)
{
    return _mm_add_ps(a, b);
}


static bad_forceinline f32x4 bad_veccall f32x4_sub(f32x4_vec0 a, f32x4_vec1 b)
{
    return _mm_sub_ps(a, b);
}


static bad_forceinline f32x4 bad_veccall f32x4_mul(f32x4_vec0 a, f32x4_vec1 b)
{
    return _mm_mul_ps(a, b);
}


static bad_forceinline f32x4 bad_veccall f32x4_div(f32x4_vec0 a, f32x4_vec1 b)
{
    return _mm_div_ps(a, b);
}


// See Peter Cordes' very comprehensive explanation: https://stackoverflow.com/a/35270026/15315204
static bad_forceinline f32 bad_veccall f32x4_hadd(f32x4_vec0 a)
{
#if defined(__SSE3__)
    f32x4 shuf = _mm_movehdup_ps(a);
    f32x4 sums = _mm_add_ps(a, shuf);
    shuf       = _mm_movehl_ps(shuf, sums);
    sums       = _mm_add_ss(sums, shuf);

    return _mm_cvtss_f32(sums);
#elif defined(__SSE__)
    f32x4 shuf = _mm_shuffle_ps(a, a, _MM_SHUFFLE(2, 3, 0, 1));
    f32x4 sums = _mm_add_ps(a, shuf);
    shuf       = _mm_movehl_ps(shuf, sums);
    sums       = _mm_add_ss(sums, shuf);

    return _mm_cvtss_f32(sums);
#endif
}


// ====== Advanced arithmetic =======
static bad_forceinline f32x4 bad_veccall f32x4_rcp(f32x4_vec0 a)
{
    return _mm_rcp_ps(a);
}


static bad_forceinline f32x4 bad_veccall f32x4_sqrt(f32x4_vec0 a)
{
    return _mm_sqrt_ps(a);
}


static bad_forceinline f32x4 bad_veccall f32x4_rsqrt(f32x4_vec0 a)
{
    return _mm_rsqrt_ps(a);
}


static bad_forceinline f32x4 bad_veccall f32x4_min(f32x4_vec0 a, f32x4_vec1 b)
{
    return _mm_min_ps(a, b);
}


static bad_forceinline f32x4 bad_veccall f32x4_max(f32x4_vec0 a, f32x4_vec1 b)
{
    return _mm_max_ps(a, b);
}


static bad_forceinline f32x4 bad_veccall f32x4_abs(f32x4_vec0 a)
{
#if defined(__SSE2__)
    // Shift out the sign bit, shift in zero instead
    return _mm_castsi128_ps(_mm_srli_epi32(_mm_slli_epi32(_mm_castps_si128(a), 1), 1));
#elif defined(__SSE__)
    return _mm_and_ps(mask128_value32(), a);
#endif
}


static bad_forceinline f32x4 bad_veccall f32x4_neg(f32x4_vec0 a)
{
#if defined(__SSE2__)
    // si128 version has a better throughput
    return _mm_castsi128_ps(_mm_xor_si128(mask128_highbit32(), _mm_castps_si128(a)));
#else
    return _mm_xor_ps(mask128_highbit32(), a);
#endif
}


static bad_forceinline f32x4 bad_veccall f32x4_mod(f32x4_vec0 a, f32x4_vec1 b)
{
    // NOTE: using _mm_rcp_ps + _mm_mul_ps brings significant imprecision
    const f32x4 a_div_b   = _mm_div_ps(a, b);
    const f32x4 truncated = f32x4_trunc(a_div_b);
    
    return _mm_sub_ps(a, _mm_mul_ps(truncated, b));
}


static bad_forceinline f32x4 bad_veccall f32x4_trunc(f32x4_vec0 a)
{
#if defined(__SSE4_1__)
    return _mm_round_ps(a, _MM_FROUND_TO_ZERO | _MM_FROUND_NO_EXC);
#elif defined(__SSE2__)
    return _mm_cvtepi32_ps(_mm_cvttps_epi32(a));
#elif defined(__SSE__)
    const __m64 low  = _mm_cvttps_pi32(a);
    const __m64 high = _mm_cvttps_pi32(_mm_shuffle_ps(a, a, _MM_SHUFFLE(0, 0, 3, 2)));

    return _mm_cvtpi32x2_ps(low, high);
#endif
}


static bad_forceinline f32x4 bad_veccall f32x4_round(f32x4_vec0 a)
{
#if defined(__SSE4_1__)
    return _mm_round_ps(a, _MM_FROUND_TO_NEAREST_INT | _MM_FROUND_NO_EXC);
#elif defined(__SSE2__)
    return _mm_cvtepi32_ps(_mm_cvtps_epi32(a));
#else
    const __m64 low  = _mm_cvtps_pi32(a);
    const __m64 high = _mm_cvtps_pi32(_mm_shuffle_ps(a, a, _MM_SHUFFLE(0, 0, 3, 2)));

    return _mm_cvtpi32x2_ps(low, high);
#endif
}


static bad_forceinline f32x4 bad_veccall f32x4_floor(f32x4_vec0 a)
{
#if defined(__SSE4_2__)
    return _mm_floor_ps(a);
#elif defined(__SSE4_1__)
    return _mm_round_ps(a, _MM_FROUND_TO_NEG_INF | _MM_FROUND_NO_EXC);
#elif defined(__SSE2__)
    const f32x4 truncated  = _mm_cvtepi32_ps(_mm_cvttps_epi32(a));
    const f32x4 is_greater = _mm_cmpgt_ps(truncated, a);
    const f32x4 decrement  = _mm_and_si128(is_greater, f32x4_one());

    return _mm_sub_ps(truncated, decrement);
#else
    const __m64 low        = _mm_cvttps_pi32(a);
    const __m64 high       = _mm_cvttps_pi32(_mm_shuffle_ps(a, a, _MM_SHUFFLE(0, 0, 3, 2)));
    const f32x4 truncated  = _mm_cvtpi32x2_ps(low, high);
    const f32x4 is_greater = _mm_cmpgt_ps(truncated, a);
    const f32x4 decrement  = _mm_and_ps(is_greater, f32x4_one());

    return _mm_sub_ps(truncated, decrement);
#endif
}


static bad_forceinline f32x4 bad_veccall f32x4_ceil(f32x4_vec0 a)
{
#if defined(__SSE4_2__)
    return _mm_ceil_ps(a);
#elif defined(__SSE4_1__)
    return _mm_round_ps(a, _MM_FROUND_TO_POS_INF | _MM_FROUND_NO_EXC);
#elif defined(__SSE2__)
    const f32x4 truncated    = _mm_cvtepi32_ps(_mm_cvttps_epi32(a));
    const f32x4 is_less_than = _mm_cmplt_ps(truncated, a);
    const f32x4 increment    = _mm_and_si128(is_less_than, f32x4_one());

    return _mm_add_ps(truncated, increment);
#else
    const __m64 low          = _mm_cvttps_pi32(a);
    const __m64 high         = _mm_cvttps_pi32(_mm_shuffle_ps(a, a, _MM_SHUFFLE(0, 0, 3, 2)));
    const f32x4 truncated    = _mm_cvtpi32x2_ps(low, high);
    const f32x4 is_less_than = _mm_cmplt_ps(truncated, a);
    const f32x4 increment    = _mm_and_ps(is_less_than, f32x4_one());

    return _mm_add_ps(truncated, increment);
#endif
}


static bad_forceinline f32x4 bad_veccall f32x4_clamp(f32x4_vec0 a, f32x4_vec1 min, f32x4_vec2 max)
{
    return _mm_min_ps(_mm_max_ps(a, min), max);
}


// a * b + c
static bad_forceinline f32x4 bad_veccall f32x4_mul_add(f32x4_vec0 a, f32x4_vec1 b, f32x4_vec2 c)
{
#if defined(__FMA__)
    return _mm_fmadd_ps(a, b, c);
#else
    return _mm_add_ps(_mm_mul_ps(a, b), c);
#endif
}


// a * b - c
static bad_forceinline f32x4 bad_veccall f32x4_mul_sub(f32x4_vec0 a, f32x4_vec1 b, f32x4_vec2 c)
{
#if defined(__FMA__)
    return _mm_fmsub_ps(a, b, c);
#else
    return _mm_sub_ps(_mm_mul_ps(a, b), c);
#endif
}


// -a * b + c
static bad_forceinline f32x4 bad_veccall f32x4_nmul_add(f32x4_vec0 a, f32x4_vec1 b, f32x4_vec2 c)
{
#if defined(__FMA__)
    return _mm_fnmadd_ps(a, b, c);
#else
    return f32x4_neg(f32x4_mul_sub(a, b, c));
#endif
}


// -a * b - c
static bad_forceinline f32x4 bad_veccall f32x4_nmul_sub(f32x4_vec0 a, f32x4_vec1 b, f32x4_vec2 c)
{
#if defined(__FMA__)
    return _mm_fnmsub_ps(a, b, c);
#else
    return f32x4_neg(f32x4_mul_add(a, b, c));
#endif
}


// ============ Comparison ============
static bad_forceinline mask128 bad_veccall f32x4_neq(f32x4_vec0 a, f32x4_vec1 b)
{
    return f32x4_cast_mask128(_mm_cmpneq_ps(a, b));
}


static bad_forceinline mask128 bad_veccall f32x4_eq(f32x4_vec0 a, f32x4_vec1 b)
{
    return f32x4_cast_mask128(_mm_cmpeq_ps(a, b));
}


static bad_forceinline mask128 bad_veccall f32x4_ge(f32x4_vec0 a, f32x4_vec1 b)
{
    return f32x4_cast_mask128(_mm_cmpge_ps(a, b));
}


static bad_forceinline mask128 bad_veccall f32x4_gt(f32x4_vec0 a, f32x4_vec1 b)
{
    return f32x4_cast_mask128(_mm_cmpgt_ps(a, b));
}


static bad_forceinline mask128 bad_veccall f32x4_le(f32x4_vec0 a, f32x4_vec1 b)
{
    return f32x4_cast_mask128(_mm_cmple_ps(a, b));
}


static bad_forceinline mask128 bad_veccall f32x4_lt(f32x4_vec0 a, f32x4_vec1 b)
{
    return f32x4_cast_mask128(_mm_cmplt_ps(a, b));
}


// ======= Selection & tests ========
// (a & m) | (b & ~m)
static bad_forceinline f32x4 bad_veccall f32x4_blend(f32x4_vec0 a, f32x4_vec1 b, mask128_vec2 m)
{
#if defined(__SSE4_1__)
    return _mm_blendv_ps(b, a, _mm_castsi128_ps(m));
#elif defined(__SSE2__)
    return _mm_or_si128(_mm_and_si128(a, m), _mm_andnot_si128(m, b));

    // NOTE: would that be better?
    // // ((a ^ b) & m) ^ b
    // return _mm_xor_si128(b, _mm_and_si128(m, _mm_xor_si128(a, b)));
#else
    return _mm_or_ps(_mm_and_ps(a, m), _mm_andnot_ps(m, b));
#endif
}


static bad_forceinline mask128 bad_veccall f32x4_is_nan(f32x4_vec0 a)
{
    // nan is the only value for which a == a returns false
    // NOTE: I have not found any faster implementation
    //       (_mm_cmpneq_epi32 only exists with AVX512F + AVX512VL)
    return f32x4_neq(a, a);
}


static bad_forceinline mask128 bad_veccall f32x4_is_infinite(f32x4_vec0 a)
{
    // +inf is 0x7F800000, -inf is 0xFF800000
#if defined(__SSE2__)
    const mask128 all1_mask  = mask128_all1();
    const mask128 value_mask = _mm_srli_epi32(all1_mask, 1);
    const mask128 inf_mask   = _mm_srli_epi32(_mm_slli_epi32(all1_mask, 24), 1);

    return _mm_cmpeq_epi32(mask128_and(value_mask, _mm_castps_si128(a)), inf_mask);
#else
    const mask128 value    = mask128_value32();
    const mask128 inf_mask = _mm_set1_ps(inf);
    return _mm_cmpeq_ps(_mm_and_ps(value, a), inf_mask);
#endif
}


static bad_forceinline mask128 bad_veccall f32x4_is_finite(f32x4_vec0 a)
{
    // a is finite if its exponent is not all 1
#if defined(__SSE2__)
    // NOTE: There is no _mm_cmpneq_epi32 SSE2 intrinsics.  I have not found any faster implementation
    const mask128 exp = mask128_exponent32();
    return _mm_castsi128_ps(_mm_cmpneq_ps(_mm_and_si128(_mm_castps_si128(a), exp), exp));
#else
    const mask128 exp = mask128_exponent32();
    return _mm_cmpneq_ps(_mm_and_ps(a, exp), exp);
#endif
}


// ============ Conversion =============
static bad_forceinline mask128 bad_veccall f32x4_cast_mask128(f32x4_vec0 a)
{
#if defined(__SSE2__)
    return _mm_castps_si128(a);
#else
    return a;
#endif
}