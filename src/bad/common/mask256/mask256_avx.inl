static bad_forceinline mask256 mask256_load(const u32* mem_addr)
{
    bad_debug_check_aligned(mem_addr, f32x8);
    return _mm256_load_si256((__m256i*)mem_addr);
}


static bad_forceinline mask256 mask256_loadu(const u32* mem_addr)
{
    return _mm256_loadu_si256((__m256i*)mem_addr);
}


static bad_forceinline mask256 mask256_set(u32 a, u32 b, u32 c, u32 d,
                                           u32 e, u32 f, u32 g, u32 h)
{
    bad_align_to(mask256) const u32 mem_addr[8] = {a, b, c, d, e, f, g, h};

    return mask256_load(mem_addr);
}


static bad_forceinline mask256 mask256_set_all(u32 k)
{
    return _mm256_set1_epi32(k);
}


static bad_forceinline void mask256_store(u32* mem_addr, mask256 a)
{
    bad_debug_check_aligned(mem_addr, f32x8);
    
    _mm256_store_si256((__m256i*)mem_addr, a);
}


static bad_forceinline void mask256_storeu(u32* mem_addr, mask256 a)
{
    _mm256_storeu_si256((__m256i*)mem_addr, a);
}


static bad_forceinline mask256 mask256_zero()
{
    return _mm256_setzero_si256();
}


static bad_forceinline mask256 mask256_all1()
{
#if defined(__AVX2__)
#   if defined(_MSC_VER)
#       if defined(BAD_x86)
            __asm { vpcmpeqd ymm0, ymm0, ymm0 };
        #else
            mask256 v = _mm256_setzero_si256();
            return _mm256_cmpeq_epi32(v, v);
#       endif
#   else
        mask256 v;
        return _mm256_cmpeq_epi32(v, v);
#   endif
#else
#   if defined(_MSC_VER)
        mask256 v = _mm256_setzero_si256();
#   else
        mask256 v;
#   endif
    return _mm256_castps_si256(_mm256_cmp_ps(_mm256_castps_si256(v),
                                             _mm256_castps_si256(v),
                                             _CMP_EQ_OQ));
#endif
}


static bad_forceinline mask256 mask256_value32()
{
#if defined(__AVX2__)
    return _mm256_srli_epi32(mask256_all1(), 1);
#else
    return _mm256_set1_epi32(0x7FFFFFFF);
#endif
}


static bad_forceinline mask256 mask256_highbit32()
{
#if defined(__AVX2__)
    const mask256 mask = mask256_all1();
    return _mm256_slli_epi32(mask, 31);
#else
    return _mm256_set1_epi32(0x7FFFFFFF);
#endif
}


static bad_forceinline mask256 mask256_lowbit32()
{
#if defined(__AVX2__)
    const mask256 mask = mask256_all1();
    return _mm256_srli_epi32(mask, 31);
#else
    return _mm256_set1_epi32(0x00000001);
#endif
}


static bad_forceinline mask256 mask256_exponent32()
{
#if defined(__AVX2__)
    return _mm256_srli_epi32(_mm256_slli_epi32(mask256_all1(), 24), 1);
#else
    return _mm256_set1_epi32(0x7F80000);
#endif
}




// ======= Masking operations =======
static bad_forceinline mask256 bad_veccall mask256_keep_highbit32(mask256 a)
{
#if defined(__AVX2__)
    return _mm256_slli_epi32(_mm256_srli_epi32(a, 31), 31);
#else
    return mask256_and(a, mask256_highbit32());
#endif
}


static bad_forceinline mask256 bad_veccall mask256_keep_lowbit32(mask256 a)
{
#if defined(__AVX2__)
    return _mm256_srli_epi32(_mm256_slli_epi32(a, 31), 31);
#else
    return mask256_and(a, mask256_lowbit32());
#endif
}


static bad_forceinline mask256 bad_veccall mask256_shift_left32(mask256 a, s32 shift)
{
#if defined(__AVX2__)
    return _mm256_slli_epi32(a, shift);
#else
    mask128 store[2];
    _mm256_store_si256((mask256*)store, a);

    store[0] = mask128_shift_left32(store[0], shift);
    store[1] = mask128_shift_left32(store[1], shift);

    return _mm256_set_m128i(store[1], store[0]);
#endif
}


static bad_forceinline mask256 bad_veccall mask256_shift_right32(mask256 a, s32 shift)
{
#if defined(__AVX2__)
    return _mm256_srli_epi32(a, shift);
#else
    mask128 store[2];
    _mm256_store_si256((mask256*)store, a);

    store[0] = mask128_shift_right32(store[0], shift);
    store[1] = mask128_shift_right32(store[1], shift);
    
    return _mm256_set_m128i(store[1], store[0]);
#endif
}




// ========== Comparison ==========
static bad_forceinline mask256 mask256_eq(mask256 a, mask256 b)
{
#if defined(__AVX2__)
    return _mm256_cmpeq_epi32(a, b);
#else
    mask128 store[2];
    _mm256_store_si256((mask256*)store, a);

    store[0] = mask128_eq(store[0], shift);
    store[1] = mask128_eq(store[1], shift);
    
    return _mm256_set_m128i(store[1], store[0]);
#endif
}


static bad_forceinline mask256 mask256_neq(mask256 a, mask256 b)
{
#if defined(__AVX2__)
    return _mm256_xor_si256(_mm256_cmpeq_epi32(a, b), _mm256_cmpeq_epi32(a, a));
#else
    mask128 store[2];
    _mm256_store_si256((mask256*)store, a);

    store[0] = mask128_neq(store[0], shift);
    store[1] = mask128_neq(store[1], shift);
    
    return _mm256_set_m128i(store[1], store[0]);
#endif
}


static bad_forceinline mask256 mask256_gt(mask256 a, mask256 b)
{
#if defined(__AVX2__)
    return _mm256_cmpgt_epi32(a, b);
#else
    mask128 store[2];
    _mm256_store_si256((mask256*)store, a);

    store[0] = mask128_gt(store[0], shift);
    store[1] = mask128_gt(store[1], shift);
    
    return _mm256_set_m128i(store[1], store[0]);
#endif
}


// ============= Logical ==============
static bad_forceinline mask256 bad_veccall mask256_and(mask256 a, mask256 b)
{
#if defined(__AVX2__)
    return _mm256_and_si256(a, b);
#else
    return _mm256_and_ps(_mm256_castsi256_ps(a), _mm256_castsi256_ps(b));
#endif
}


static bad_forceinline mask256 bad_veccall mask256_and_not(mask256 a, mask256 b)
{
#if defined(__AVX2__)
    return _mm256_andnot_si256(b, a);
#else
    return _mm256_andnot_ps(_mm256_castsi256_ps(b), _mm256_castsi256_ps(a));
#endif
}


static bad_forceinline mask256 bad_veccall mask256_or(mask256 a, mask256 b)
{
#if defined(__AVX2__)
    return _mm256_or_si256(a, b);
#else
    return _mm256_or_ps(_mm256_castsi256_ps(a), _mm256_castsi256_ps(b));
#endif
}


static bad_forceinline mask256 bad_veccall mask256_xor(mask256 a, mask256 b)
{
#if defined(__AVX2__)
    return _mm256_xor_si256(a, b);
#else
    return _mm256_xor_ps(_mm256_castps_si256(a), _mm256_castps_si256(b));
#endif
}


static bad_forceinline mask256 bad_veccall mask256_not(mask256 a)
{
#if defined(__AVX2__)
    return _mm256_xor_si256(a, _mm256_cmpeq_epi32(a, a));
#else
    return _mm256_xor_ps(a, _mm256_cmp_ps(a, a, _CMP_EQ_OQ));
#endif  
}


// ============ Conversion =============
static bad_forceinline f32x8 bad_veccall mask256_as_f32x8(mask256 a)
{
    return _mm256_castsi256_ps(a);
}


static bad_forceinline f32x8 bad_veccall mask256_u32x8_to_f32x8(mask256 a)
{
    bad_align_to(mask256) s32 store[8];
    bad_align_to(f32x8) f32 load[8];

    mask256_store((mask_elem*)store, a);

    load[0] = (f32)*(u32*)(store + 0);
    load[1] = (f32)*(u32*)(store + 1);
    load[2] = (f32)*(u32*)(store + 2);
    load[3] = (f32)*(u32*)(store + 3);
    load[4] = (f32)*(u32*)(store + 4);
    load[5] = (f32)*(u32*)(store + 5);
    load[6] = (f32)*(u32*)(store + 6);
    load[7] = (f32)*(u32*)(store + 7);

    mask256 res = _mm256_load_si256((const mask256*)load);

    return _mm256_castsi256_ps(res);
}


static bad_forceinline f32x8 bad_veccall mask256_s32x8_to_f32x8(mask256 a)
{
    return _mm256_cvtepi32_ps(a);
}
