// ============= Defaults =============
static bad_forceinline f32x8 f32x8_any()
{
    return _mm256_undefined_ps();
}


static bad_forceinline f32x8 f32x8_zero()
{
    return _mm256_setzero_ps();
}


static bad_forceinline f32x8 f32x8_one()
{
    const mask256 one = _mm256_slli_epi32(_mm256_srli_epi32(mask256_all1(), 25), 23);

    return _mm256_castsi256_ps(one);
}


// ========== Loads & stores ==========
static bad_forceinline f32x8 f32x8_load(const f32* mem_addr)
{
    bad_assert_avx_aligned(mem_addr);

    // NOTE: si256 version has a better throughput
    return _mm256_load_si256((__m256i*)mem_addr);
}


static bad_forceinline f32x8 f32x8_loadu(const f32* mem_addr)
{
    // NOTE: si256 version has a better throughput
    return _mm256_loadu_si256((__m256i*)mem_addr);
}


static bad_forceinline f32x8 f32x8_set(f32 a, f32 b, f32 c, f32 d,
                                       f32 e, f32 f, f32 g, f32 h)
{
    return _mm256_set_ps(h, g, f, e, d, c, b, a);
}


static bad_forceinline f32x8 f32x8_set1(f32 a)
{
    return _mm256_set1_ps(a);
}


static bad_forceinline void bad_veccall f32x8_store(f32* mem_addr, f32x8_vec0 a)
{
    bad_assert_avx_aligned(mem_addr);

    // NOTE: si128 version has a better throughput
    return _mm256_store_si256((__m256i*)mem_addr, a);
}


static bad_forceinline void bad_veccall f32x8_storeu(f32* mem_addr, f32x8_vec0 a)
{
    // NOTE: si128 version has a better throughput
    return _mm256_storeu_si256((__m256i*)mem_addr, a);
}


// =========== Selection ============
// (a & m) | (b & ~m)
static bad_forceinline f32x8 bad_veccall f32x8_blend(f32x8_vec0 a, f32x8_vec1 b, mask256_vec2 m)
{
    return _mm256_blendv_ps(b, a, _mm256_castsi256_ps(m));
}


// ============ Conversion =============
static bad_forceinline mask256 bad_veccall f32x8_cast_mask256(f32x8_vec0 a)
{
    return _mm256_castps_si256(a);
}