static bad_forceinline mask128 mask128_load(const mask_elem* mem_addr)
{
#if defined(__SSE2__)
    return _mm_load_si128((__m128i*)mem_addr);
#else
    return _mm_load_ps(mem_addr);
#endif
}


static bad_forceinline mask128 mask128_loadu(const mask_elem* mem_addr)
{
#if defined(__SSE2__)
    return _mm_loadu_si128((__m128i*)mem_addr);
#else
    return _mm_loadu_ps(mem_addr);
#endif
}


static bad_forceinline mask128 mask128_set(const mask_elem a, const mask_elem b,
                                           const mask_elem c, const mask_elem d)
{
    bad_align(16) const mask_elem e[4] = {a, b, c, d};
    return mask128_load(e);
}


static bad_forceinline mask128 mask128_set1(const mask_elem k)
{
    bad_align(16) const mask_elem e[4] = {k, k, k, k};
    return mask128_load(e);
}


static bad_forceinline void mask128_store(mask_elem* const mem_addr, mask128_vec0 a)
{
#if defined(__SSE2__)
    _mm_store_si128((__m128i*)mem_addr, a);
#else
    _mm_store_ps(mem_addr, a);
#endif
}


static bad_forceinline void mask128_storeu(mask_elem* const mem_addr, mask128_vec0 a)
{
#if defined(__SSE2__)
    _mm_storeu_si128((__m128i*)mem_addr, a);
#else
    _mm_storeu_ps(mem_addr, a);
#endif
}


static bad_forceinline mask128 mask128_zero()
{
#if defined(__SSE2__)
    return _mm_setzero_si128();
#else
    return _mm_setzero_ps();
#endif
}


static bad_forceinline mask128 mask128_all1()
{
// MSVC seems to always generate movdqa (or more) instead of the desired vpcmpeqd
#if defined(_MSC_VER)
#   if defined(BAD_x86)
#       if defined(__SSE2__)
            mask128 v;
            __asm { vpcmpeqd xmm0, xmm0, xmm0 };
#       else
            return _mm_set1_ps(0xFFFFFFFF);
#       endif
#   else
#       if defined(__SSE2__)
            mask128 v = _mm_setzero_si128();
            return _mm_cmpeq_epi32(v, v);
#       else
            mask128 v = _mm_setzero_ps();
            return _mm_cmpeq_ps(v, v);
#       endif
#   endif
#else
    mask128 v;
    return _mm_cmpeq_epi32(v, v);
#endif
}


static bad_forceinline mask128 mask128_value32()
{
#if defined(__SSE2__)
    return _mm_srli_epi32(mask128_all1(), 1);
#else
    const u32 value32 = 0x7FFFFFFF;
    return _mm_set1_ps(*(f32*)value32);
#endif
}


static bad_forceinline mask128 mask128_highbit32()
{
#if defined(__SSE2__)
    const mask128 mask = mask128_all1();
    return _mm_slli_epi32(mask, 31);
#else
    const u32 highbit32 = 0x7FFFFFFF;
    return _mm_set1_ps(*(f32*)highbit32);
#endif
}


static bad_forceinline mask128 mask128_lowbit32()
{
#if defined(__SSE2__)
    const mask128 mask = mask128_all1();
    return _mm_srli_epi32(mask, 31);
#else
    const u32 lowbit32 = 0x00000001;
    return _mm_set1_ps(*(f32*)lowbit32);
#endif
}


static bad_forceinline mask128 mask128_exponent32()
{
#if defined(__SSE2__)
    return _mm_srli_epi32(_mm_slli_epi32(mask128_all1(), 24), 1);
#else
    const u32 exponent32_bits = 0x7F80000;
    return _mm_set1_ps(*(f32*)exponent32_bits);
#endif
}


// ========== Comparison ==========
static bad_forceinline mask128 mask128_eq(mask128_vec0 a, mask128_vec1 b)
{
#if defined(__SSE2__)
    return _mm_cmpeq_epi32(a, b);
#else
    return _mm_cmpeq_ps(a, b);
#endif
}


static bad_forceinline mask128 mask128_neq(mask128_vec0 a, mask128_vec1 b)
{
    return _mm_cmpneq_ps(mask128_cast_f32x4(a), mask128_cast_f32x4(b));
}


// ============= Logical ==============
static bad_forceinline mask128 bad_veccall mask128_and(mask128_vec0 a, mask128_vec1 b)
{
#if defined(__SSE2__)
    return _mm_and_si128(a, b);
#else
    return _mm_and_ps(a, b);
#endif
}


static bad_forceinline mask128 bad_veccall mask128_and_not(mask128_vec0 a, mask128_vec1 b)
{
#if defined(__SSE2__)
    return _mm_andnot_si128(b, a);
#else
    return _mm_andnot_ps(b, a);
#endif
}


static bad_forceinline mask128 bad_veccall mask128_or(mask128_vec0 a, mask128_vec1 b)
{
#if defined(__SSE2__)
    return _mm_or_si128(a, b);
#else
    return _mm_or_ps(a, b);
#endif
}


static bad_forceinline mask128 bad_veccall mask128_xor(mask128_vec0 a, mask128_vec1 b)
{
#if defined(__SSE2__)
    return _mm_xor_si128(a, b);
#else
    return _mm_xor_ps(a, b);
#endif
}


// ============ Conversion =============
static bad_forceinline f32x4 bad_veccall mask128_cast_f32x4(mask128_vec0 a)
{
#if defined(__SSE2__)
    return _mm_castsi128_ps(a);
#else
    return a;
#endif
}