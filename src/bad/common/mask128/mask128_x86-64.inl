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


static bad_forceinline mask128 mask128_set(mask_elem a, mask_elem b, mask_elem c, mask_elem d)
{
    bad_align(16) const mask_elem elem[4] = {a, b, c, d};

    return mask128_load(elem);
}


static bad_forceinline mask128 mask128_set_all(mask_elem k)
{
    bad_align(16) const mask_elem elem[4] = {k, k, k, k};

    return mask128_load(elem);
}


static bad_forceinline void mask128_store(mask_elem* mem_addr, mask128 a)
{
#if defined(__SSE2__)
    _mm_store_si128((__m128i*)mem_addr, a);
#else
    _mm_store_ps(mem_addr, a);
#endif
}


static bad_forceinline void mask128_storeu(mask_elem* mem_addr, mask128 a)
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
// MSVC seems to always generate movdqa (or more) instead of the desired pcmpeqd
#if defined(_MSC_VER)
#   if defined(BAD_x86)
        mask128 v = _mm_undefined_ps();
        return _mm_cmpeq_ps(v, v);
#   else
#       if defined(__SSE2__)
            mask128 v = _mm_undefined_si128();
            return _mm_cmpeq_epi32(v, v);
#       else
            mask128 v = _mm_undefined_ps();
            return _mm_cmpeq_ps(v, v);
#       endif
#   endif
#else
    mask128 v;
#   if defined(__SSE2__)
        return _mm_cmpeq_epi32(v, v);
#   else
        return _mm_cmpeq_ps(v, v);
#   endif
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


// ======= Masking operations =======
static bad_forceinline mask128 bad_veccall mask128_keep_highbit32(mask128 a)
{
#if defined(__SSE2__)
    return _mm_slli_epi32(_mm_srli_epi32(a, 31), 31);
#else
    return mask128_and(a, mask128_highbit32());
#endif
}


static bad_forceinline mask128 bad_veccall mask128_keep_lowbit32(mask128 a)
{
#if defined(__SSE2__)
    return _mm_srli_epi32(_mm_slli_epi32(a, 31), 31);
#else
    return mask128_and(a, mask128_lowbit32());
#endif
}


static bad_forceinline mask128 bad_veccall mask128_shift_left32(mask128 a, s32 shift)
{
#if defined(__SSE2__)
    return _mm_slli_epi32(a, shift);
#else
    bad_align(16) f32 s[4];
    mask128_store(s, a);

    s[0] <<= shift;
    s[1] <<= shift;
    s[2] <<= shift;
    s[3] <<= shift;

    return mask128_load(s);
#endif
}


static bad_forceinline mask128 bad_veccall mask128_shift_right32(mask128 a, s32 shift)
{
#if defined(__SSE2__)
    return _mm_srli_epi32(a, shift);
#else
    bad_align(16) f32 s[4];
    mask128_store(s, a);

    s[0] >>= shift;
    s[1] >>= shift;
    s[2] >>= shift;
    s[3] >>= shift;

    return mask128_load(s);
#endif
}




// ============== Getters =============
static bad_forceinline mask_elem bad_veccall mask128_get_0(mask128 a)
{
#if defined(__SSE2__)
    f32 first = _mm_cvtss_f32(mask128_as_f32x4(a));

    return *(mask_elem*)&first;
#else
    return _mm_cvtss_f32(a);
#endif
}


static bad_forceinline mask_elem bad_veccall mask128_get_1(mask128 a)
{
#if defined(__SSE2__)
    mask128 shuf   = _mm_shuffle_epi32(a, _MM_SHUFFLE(1, 1, 1, 1));
    f32     second = _mm_cvtss_f32(shuf);

    return *(u32*)&second;
#else
    mask128 shuf = _mm_shuffle_ps(a, a, _MM_SHUFFLE(1, 1, 1, 1));

    return _mm_cvtss_f32(shuf);
#endif
}


static bad_forceinline mask_elem bad_veccall mask128_get_2(mask128 a)
{
#if defined(__SSE2__)
    mask128 shuf   = _mm_shuffle_epi32(a, _MM_SHUFFLE(2, 2, 2, 2));
    f32     second = _mm_cvtss_f32(shuf);

    return *(u32*)&second;
#else
    mask128 shuf = _mm_shuffle_ps(a, a, _MM_SHUFFLE(2, 2, 2, 2));

    return _mm_cvtss_f32(shuf);
#endif
}


static bad_forceinline mask_elem bad_veccall mask128_get_3(mask128 a)
{
#if defined(__SSE2__)
    mask128 shuf   = _mm_shuffle_epi32(a, _MM_SHUFFLE(3, 3, 3, 3));
    f32     second = _mm_cvtss_f32(shuf);

    return *(u32*)&second;
#else
    mask128 shuf = _mm_shuffle_ps(a, a, _MM_SHUFFLE(3, 3, 3, 3));

    return _mm_cvtss_f32(shuf);
#endif
}


// ========== Comparison ==========
static bad_forceinline mask128 mask128_eq(mask128 a, mask128 b)
{
#if defined(__SSE2__)
    return _mm_cmpeq_epi32(a, b);
#else
    // TODO: could we use MMX instrinsics to simplify this?
    const mask128 a_nans = _mm_cmpunord_ps(a, a);
    const mask128 b_nans = _mm_cmpunord_ps(b, b);
    const mask128 nans   = _mm_and_ps(a_nans, b_nans);
    
    return _mm_or_ps(_mm_cmpeq_ps(a, b), nans);
#endif
}


static bad_forceinline mask128 mask128_neq(mask128 a, mask128 b)
{
#if defined(__SSE2__)
    const mask128 eq = _mm_cmpeq_epi32(a, b);
    return _mm_xor_si128(eq, _mm_cmpeq_epi32(a, a));
#else
    const mask128 a_ord = _mm_cmpord_ps(a, a);
    const mask128 b_ord = _mm_cmpord_ps(b, b);
    const mask128 ord   = _mm_or_ps(a_ord, b_ord);

    return _mm_and_ps(_mm_cmpneq_ps(a, b), ord);
#endif
}


// ============= Logical ==============
static bad_forceinline mask128 bad_veccall mask128_and(mask128 a, mask128 b)
{
#if defined(__SSE2__)
    return _mm_and_si128(a, b);
#else
    return _mm_and_ps(a, b);
#endif
}


static bad_forceinline mask128 bad_veccall mask128_and_not(mask128 a, mask128 b)
{
#if defined(__SSE2__)
    return _mm_andnot_si128(b, a);
#else
    return _mm_andnot_ps(b, a);
#endif
}


static bad_forceinline mask128 bad_veccall mask128_or(mask128 a, mask128 b)
{
#if defined(__SSE2__)
    return _mm_or_si128(a, b);
#else
    return _mm_or_ps(a, b);
#endif
}


static bad_forceinline mask128 bad_veccall mask128_xor(mask128 a, mask128 b)
{
#if defined(__SSE2__)
    return _mm_xor_si128(a, b);
#else
    return _mm_xor_ps(a, b);
#endif
}


static bad_forceinline mask128 bad_veccall mask128_not(mask128 a)
{
#if defined(__SSE2__)
    return _mm_xor_si128(a, _mm_cmpeq_epi32(a, a));
#else
    return _mm_xor_ps(a, _mm_cmpeq_ps(a, a));
#endif
}


// ============ Conversion =============
static bad_forceinline f32x4 bad_veccall mask128_as_f32x4(mask128 a)
{
#if defined(__SSE2__)
    return _mm_castsi128_ps(a);
#else
    return a;
#endif
}


static bad_forceinline f32x4 bad_veccall mask128_u32x4_to_f32x4(mask128 a)
{
    bad_align(16) s32 store[4];
    bad_align(16) f32 load[4];

    mask128_store((mask_elem*)store, a);

    load[0] = (f32)*(u32*)(store + 0);
    load[1] = (f32)*(u32*)(store + 1);
    load[2] = (f32)*(u32*)(store + 2);
    load[3] = (f32)*(u32*)(store + 3);

    return _mm_load_ps(load);
}


static bad_forceinline f32x4 bad_veccall mask128_s32x4_to_f32x4(mask128 a)
{
#if defined(__SSE2__)
    return _mm_cvtepi32_ps(a);
#else
    bad_align(16) s32 store[4];
    bad_align(16) f32 load[4];

    mask128_store((mask_elem*)store, a);

    load[0] = (f32)store[0];
    load[1] = (f32)store[1];
    load[2] = (f32)store[2];
    load[3] = (f32)store[3];

    return _mm_load_ps(load);
#endif
}

