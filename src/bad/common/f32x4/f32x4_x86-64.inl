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


static bad_forceinline f32x4 f32x4_set(f32 a, f32 b, f32 c, f32 d)
{
    return _mm_set_ps(d, c, b, a);
}


static bad_forceinline f32x4 f32x4_set1(f32 a)
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


// =========== Selection ============
// (a & m) | (b & ~m)
static bad_forceinline f32x4 bad_veccall f32x4_blend(f32x4_vec0 a, f32x4_vec1 b, mask128_vec2 m)
{
#if defined(__SSE4_1__)
    return _mm_blendv_ps(b, a, _mm_castsi128_ps(m));
#else
    const mask128 a_mask = f32x4_cast_mask128(a);
    const mask128 b_mask = f32x4_cast_mask128(b);
    
    return mask128_or(mask128_and(a_mask, b_mask), mask128_and_not(b_mask, m));
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