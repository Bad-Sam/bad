// ============= Defaults =============
static bad_forceinline f32x4 f32x4_any()
{
    return _mm_undefined_ps();
}


static bad_forceinline f32x4 f32x4_zero()
{
    return _mm_setzero_ps();
}


static bad_forceinline f32x4 f32x4_half()
{
#if defined(__SSE2__)
    mask128 all1_mask = mask128_all1();
    mask128 half      = _mm_srli_epi32(_mm_slli_epi32(all1_mask, 26), 2);

    return _mm_castsi128_ps(half);
#else
    return _mm_set1_ps(.5f);
#endif
}


static bad_forceinline f32x4 f32x4_one()
{
#if defined(__SSE2__)
    mask128 all1_mask = mask128_all1();
    mask128 one       = _mm_srli_epi32(_mm_slli_epi32(all1_mask, 25), 2);

    return _mm_castsi128_ps(one);
#else
    return _mm_set1_ps(1.f);
#endif
}


static bad_forceinline f32x4 f32x4_two()
{
#if defined(__SSE2__)
    mask128 all1_mask = mask128_all1();
    mask128 two       = _mm_srli_epi32(_mm_slli_epi32(all1_mask, 31), 1);

    return _mm_castsi128_ps(two);
#else
    return _mm_set1_ps(2.f);
#endif   
}


// ========== Loads & stores ==========
static bad_forceinline f32x4 f32x4_load(const f32* mem_addr)
{
    bad_assert_sse_aligned(mem_addr);

#if defined(__SSE2__)
    return _mm_load_si128((__m128i*)mem_addr);
#else
    return _mm_load_ps(mem_addr);
#endif
}


static bad_forceinline f32x4 f32x4_loadu(const f32* mem_addr)
{
#if defined(__SSE2__)
    return _mm_loadu_si128((__m128i*)mem_addr);
#else
    return _mm_loadu_ps(mem_addr);
#endif
}


static bad_forceinline f32x4 f32x4_set(f32 a, f32 b, f32 c, f32 d)
{
    return _mm_set_ps(d, c, b, a);
}


static bad_forceinline f32x4 f32x4_set_all(f32 a)
{
    return _mm_set1_ps(a);
}


static bad_forceinline f32x4 f32x4_set_lower(f32 a)
{
    return _mm_set_ss(a);
}


static bad_forceinline void bad_veccall f32x4_store(f32* mem_addr, f32x4_vec0 a)
{
    bad_assert_sse_aligned(mem_addr);

#if defined(__SSE2__)
    return _mm_store_si128((__m128i*)mem_addr, a);
#else
    return _mm_store_ps(mem_addr, a);
#endif
}


static bad_forceinline void bad_veccall f32x4_storeu(f32* mem_addr, f32x4_vec0 a)
{
#if defined(__SSE2__)
    return _mm_storeu_si128((__m128i*)mem_addr, a);
#else
    return _mm_storeu_ps(mem_addr, a);
#endif
}


static bad_forceinline void bad_veccall f32x4_store_lower(f32* mem_addr, f32x4_vec0 a)
{
    mem_addr[0] = f32x4_get_0(a);
}


// ============== Getter ==============
static bad_forceinline f32 bad_veccall f32x4_get_0(f32x4_vec0 a)
{
    return _mm_cvtss_f32(a);
}


static bad_forceinline f32 bad_veccall f32x4_get_1(f32x4_vec0 a)
{
    return _mm_cvtss_f32(_mm_shuffle_ps(a, a, _MM_SHUFFLE(1, 1, 1, 1)));
}


static bad_forceinline f32 bad_veccall f32x4_get_2(f32x4_vec0 a)
{
    return _mm_cvtss_f32(_mm_shuffle_ps(a, a, _MM_SHUFFLE(2, 2, 2, 2)));
}


static bad_forceinline f32 bad_veccall f32x4_get_3(f32x4_vec0 a)
{
    return _mm_cvtss_f32(_mm_shuffle_ps(a, a, _MM_SHUFFLE(3, 3, 3, 3)));
}


static bad_forceinline f32 bad_veccall f32x4_get_i(f32x4_vec0 a, s32 idx)
{
#if defined(__AVX__)
    mask128 vidx     = _mm_cvtsi32_si128(idx);
    f32x4   shuffled = _mm_permutevar_ps(a, vidx);

    return _mm_cvtss_f32(shuffled);
#elif defined(__SSE3__)
    const s32 low4  = 0x03020100;
    const s32 step4 = 0x04040404;

    s32 selector = low4 + idx * step4;
    
    mask128 vidx     = _mm_cvtsi32_si128(selector);
    f32x4   shuffled = _mm_shuffle_epi8(_mm_castps_si128(a), vidx);

    return _mm_cvtss_f32(_mm_castsi128_ps(shuffled));
#else
    bad_align(16) f32 s[4];
    f32x4_store(s, a);

    return s[idx];
#endif
}


// ============== Setters =============
static bad_forceinline f32x4 bad_veccall f32x4_copy_0(f32x4_vec0 a, f32x4 origin)
{
#if defined(__SSE4_1__)
    return _mm_blend_ps(a, origin, 0b0001);
#else
    return _mm_move_ss(a, origin);
#endif
}


static bad_forceinline f32x4 bad_veccall f32x4_copy_1(f32x4_vec0 a, f32x4 origin)
{
#if defined(__SSE4_1__)
    return _mm_blend_ps(a, origin, 0b0010);
#else
    origin = _mm_move_ss(origin, a);

    return _mm_shuffle_ps(origin, a, _MM_SHUFFLE(3, 2, 1, 0));
#endif
}


static bad_forceinline f32x4 bad_veccall f32x4_copy_2(f32x4_vec0 a, f32x4 origin)
{
#if defined(__SSE4_1__)
    return _mm_blend_ps(a, origin, 0b0100);
#else
    origin = _mm_shuffle_ps(origin, a, _MM_SHUFFLE(3, 3, 2, 2));
    
    return _mm_shuffle_ps(a, origin, _MM_SHUFFLE(2, 0, 1, 0));
#endif
}


static bad_forceinline f32x4 bad_veccall f32x4_copy_3(f32x4_vec0 a, f32x4 origin)
{
#if defined(__SSE4_1__)
    return _mm_blend_ps(a, origin, 0b1000);
#else
    origin = _mm_shuffle_ps(origin, a, _MM_SHUFFLE(2, 2, 3, 3));

    return _mm_shuffle_ps(a, origin, _MM_SHUFFLE(1, 3, 1, 0));
#endif
}


static bad_forceinline f32x4 bad_veccall f32x4_set_0(f32x4_vec0 a, f32 value)
{
    return f32x4_copy_0(a, _mm_set_ss(value));
}


static bad_forceinline f32x4 bad_veccall f32x4_set_1(f32x4_vec0 a, f32 value)
{
    return f32x4_copy_1(a, f32x4_set_all(value));
}


static bad_forceinline f32x4 bad_veccall f32x4_set_2(f32x4_vec0 a, f32 value)
{
    return f32x4_copy_2(a, f32x4_set_all(value));
}


static bad_forceinline f32x4 bad_veccall f32x4_set_3(f32x4_vec0 a, f32 value)
{
    return f32x4_copy_3(a, f32x4_set_all(value));
}


// ==== Vector element broadcast =====
static bad_forceinline f32x4 bad_veccall f32x4_broadcast_0(f32x4_vec0 a)
{
    // vbroadcastss xmm, xmm doesn't seem to have an intrinsics
    return _mm_shuffle_ps(a, a, _MM_SHUFFLE(0, 0, 0, 0));
}


static bad_forceinline f32x4 bad_veccall f32x4_broadcast_1(f32x4_vec0 a)
{
    return _mm_shuffle_ps(a, a, _MM_SHUFFLE(1, 1, 1, 1));
}


static bad_forceinline f32x4 bad_veccall f32x4_broadcast_2(f32x4_vec0 a)
{
    return _mm_shuffle_ps(a, a, _MM_SHUFFLE(2, 2, 2, 2));
}


static bad_forceinline f32x4 bad_veccall f32x4_broadcast_3(f32x4_vec0 a)
{
    return _mm_shuffle_ps(a, a, _MM_SHUFFLE(3, 3, 3, 3));
}


// =========== Selection ============
// (a & m) | (b & ~m)
static bad_forceinline f32x4 bad_veccall f32x4_blend(f32x4_vec0 a, f32x4_vec1 b, mask128_vec2 m)
{
#if defined(__SSE4_1__)
    return _mm_blendv_ps(b, a, _mm_castsi128_ps(m));
#else
    const mask128 a_mask = f32x4_as_mask128(a);
    const mask128 b_mask = f32x4_as_mask128(b);
    
    return mask128_or(mask128_and(a_mask, b_mask), mask128_and_not(b_mask, m));
#endif
}


// ============ Cast and conversion =============
static bad_forceinline mask128 bad_veccall f32x4_as_mask128(f32x4_vec0 a)
{
#if defined(__SSE2__)
    return _mm_castps_si128(a);
#else
    return a;
#endif
}

static bad_forceinline mask128 bad_veccall f32x4_to_s32x4(f32x4_vec0 a)
{
#if defined(___SSE2__)
    return _mm_cvtps_epi32(a);
#else
    bad_align(16) f32 store[4];
    bad_align(16) s32 load[4];

    f32x4_store(store, a);

    load[0] = (s32)store[0];
    load[1] = (s32)store[1];
    load[2] = (s32)store[2];
    load[3] = (s32)store[3];

    return mask128_load((mask_elem*)load);
#endif
}


static bad_forceinline mask128 bad_veccall f32x4_to_u32x4(f32x4_vec0 a)
{
    bad_align(16) f32 store[4];
    bad_align(16) u32 load[4];

    f32x4_store(store, a);

    load[0] = (u32)store[0];
    load[1] = (u32)store[1];
    load[2] = (u32)store[2];
    load[3] = (u32)store[3];

    return mask128_load((mask_elem*)load);
}