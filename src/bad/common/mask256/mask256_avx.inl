static bad_forceinline mask256 mask256_load(const mask_elem* mem_addr)
{
    return _mm256_load_si256((__m256i*)mem_addr);
}


static bad_forceinline mask256 mask256_loadu(const mask_elem* mem_addr)
{
    return _mm256_loadu_si256((__m256i*)mem_addr);
}


static bad_forceinline mask256 mask256_set(mask_elem a, mask_elem b,
                                           mask_elem c, mask_elem d,
                                           mask_elem e, mask_elem f,
                                           mask_elem g, mask_elem h)
{
    return _mm256_set_epi32(a, b, c, d, e, f, g, h);
}


static bad_forceinline mask256 mask256_set1(mask_elem k)
{
    return _mm256_set1_epi32(k);
}


static bad_forceinline void mask256_store(mask_elem* mem_addr, mask256_vec0 a)
{
    bad_assert_avx_aligned(mask_elem);
    
    _mm256_store_si256((__m256i*)mem_addr, a);
}


static bad_forceinline void mask256_storeu(mask_elem* mem_addr, mask256_vec0 a)
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


// ========== Comparison ==========
static bad_forceinline mask256 mask256_eq(mask256_vec0 a, mask256_vec1 b)
{
#if defined(__AVX2__)
    return _mm256_cmpeq_epi32(a, b);
#else
    return _mm256_cmp_ps(_mm256_castps_si256(a), _mm256_castps_si256(b), _CMP_EQ_OQ);
#endif
}


static bad_forceinline mask256 mask256_neq(mask256_vec0 a, mask256_vec1 b)
{
    return _mm256_cmp_ps(_mm256_castsi256_ps(a), _mm256_castsi256_ps(b), _CMP_NEQ_OQ);
}


// ============= Logical ==============
static bad_forceinline mask256 bad_veccall mask256_and(mask256_vec0 a, mask256_vec1 b)
{
#if defined(__AVX2__)
    return _mm256_and_si256(a, b);
#else
    return _mm256_and_ps(_mm256_castsi256_ps(a), _mm256_castsi256_ps(b));
#endif
}


static bad_forceinline mask256 bad_veccall mask256_and_not(mask256_vec0 a, mask256_vec1 b)
{
#if defined(__AVX2__)
    return _mm256_andnot_si256(b, a);
#else
    return _mm256_andnot_ps(_mm256_castsi256_ps(b), _mm256_castsi256_ps(a));
#endif
}


static bad_forceinline mask256 bad_veccall mask256_or(mask256_vec0 a, mask256_vec1 b)
{
#if defined(__AVX2__)
    return _mm256_or_si256(a, b);
#else
    return _mm256_or_ps(_mm256_castsi256_ps(a), _mm256_castsi256_ps(b));
#endif
}


static bad_forceinline mask256 bad_veccall mask256_xor(mask256_vec0 a, mask256_vec1 b)
{
#if defined(__AVX2__)
    return _mm256_xor_si256(a, b);
#else
    return _mm256_xor_ps(_mm256_castps_si256(a), _mm256_castps_si256(b));
#endif
}


static bad_forceinline mask256 bad_veccall mask256_not(mask256_vec0 a)
{
#if defined(__AVX2__)
    return _mm256_xor_si256(a, _mm256_cmpeq_epi32(a, a));
#else
    return _mm256_xor_ps(a, _mm256_cmp_ps(a, a, _CMP_EQ_OQ));
#endif  
}


// ============ Conversion =============
static bad_forceinline f32x8 bad_veccall mask256_cast_f32x8(mask256_vec0 a)
{
    return _mm256_castsi256_ps(a);
}