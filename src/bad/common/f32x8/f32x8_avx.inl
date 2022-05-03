// ============= Defaults =============
static bad_forceinline f32x8 f32x8_any()
{
    return _mm256_undefined_ps();
}


static bad_forceinline f32x8 f32x8_zero()
{
    return _mm256_setzero_ps();
}


static bad_forceinline f32x8 f32x8_half()
{
#if defined(__AVX2__)
    mask256 all1_mask = mask256_all1();
    mask256 half      = _mm256_srli_epi32(_mm256_slli_epi32(all1_mask, 26), 2);

    return _mm256_castsi256_ps(half);
#else
    f32x4 half = f32x4_half();

    return _mm256_set_m128(half, half);
#endif
}


static bad_forceinline f32x8 f32x8_one()
{
#if defined(__AVX2__)
    mask256 all1_mask = mask256_all1();
    mask256 one       = _mm256_srli_epi32(_mm256_slli_epi32(all1_mask, 25), 2);

    return _mm256_castsi256_ps(one);
#else
    f32x4 one = f32x4_one();

    return _mm256_set_m128(one, one);
#endif
}


static bad_forceinline f32x8 f32x8_two()
{
 #if defined(__AVX2__)
    mask256 all1_mask = mask256_all1();
    mask256 two       = _mm256_srli_epi32(_mm256_slli_epi32(all1_mask, 31), 1);

    return _mm256_castsi256_ps(two);
#else
    f32x4 two = f32x4_two();

    return _mm256_set_m128(two, two);
#endif   
}


// ========== Loads & stores ==========
static bad_forceinline f32x8 f32x8_load(const f32* mem_addr)
{
    bad_assert_avx_aligned(mem_addr);

    return _mm256_castsi256_ps(_mm256_load_si256((__m256i*)mem_addr));
}


static bad_forceinline f32x8 f32x8_loadu(const f32* mem_addr)
{
    return _mm256_castsi256_ps(_mm256_loadu_si256((__m256i*)mem_addr));
}


static bad_forceinline f32x8 f32x8_set(f32 a, f32 b, f32 c, f32 d,
                                       f32 e, f32 f, f32 g, f32 h)
{
    return _mm256_set_ps(h, g, f, e, d, c, b, a);
}


static bad_forceinline f32x8 f32x8_set_all(f32 a)
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


// ============== Getter ==============
static bad_forceinline f32 bad_veccall f32x8_get_0(f32x8_vec0 a)
{
    return _mm256_cvtss_f32(a);
}


// =========== Selection ============
// (a & m) | (b & ~m)
static bad_forceinline f32x8 bad_veccall f32x8_blend(f32x8_vec0 a, f32x8_vec1 b, mask256_vec2 m)
{
    return _mm256_blendv_ps(b, a, _mm256_castsi256_ps(m));
}


// ============ Conversion =============
static bad_forceinline mask256 bad_veccall f32x8_as_mask256(f32x8_vec0 a)
{
    return _mm256_castps_si256(a);
}


static bad_forceinline mask256 bad_veccall f32x8_to_s32x8(f32x8_vec0 a)
{
#if defined(___SSE2__)
    return _mm256_cvtps_epi32(a);
#else
    bad_align(32) f32 store[8];
    bad_align(32) s32 load[8];

    f32x8_store(store, a);

    load[0] = (s32)store[0];
    load[1] = (s32)store[1];
    load[2] = (s32)store[2];
    load[3] = (s32)store[3];
    load[4] = (s32)store[4];
    load[5] = (s32)store[5];
    load[6] = (s32)store[6];
    load[7] = (s32)store[7];

    return mask256_load((mask_elem*)load);
#endif
}


static bad_forceinline mask256 bad_veccall f32x8_to_u32x8(f32x8_vec0 a)
{
    bad_align(32) f32 store[8];
    bad_align(32) u32 load[8];

    f32x8_store(store, a);

    load[0] = (u32)store[0];
    load[1] = (u32)store[1];
    load[2] = (u32)store[2];
    load[3] = (u32)store[3];
    load[4] = (u32)store[4];
    load[5] = (u32)store[5];
    load[6] = (u32)store[6];
    load[7] = (u32)store[7];

    return mask256_load((mask_elem*)load);
}