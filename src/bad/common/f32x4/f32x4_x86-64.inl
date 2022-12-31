// ============= Defaults =============
static bad_forceinline f32x4 f32x4_any()
{
    return _mm_undefined_ps();
}


static bad_forceinline f32x4 f32x4_zero()
{
    return mask128_as_f32x4(mask128_zero());
}


static bad_forceinline f32x4 f32x4_half()
{
    mask128 all1_mask = mask128_all1();
    mask128 half      = _mm_srli_epi32(_mm_slli_epi32(all1_mask, 26), 2);

    return _mm_castsi128_ps(half);
}


static bad_forceinline f32x4 f32x4_one()
{
    mask128 all1_mask = mask128_all1();
    mask128 one       = _mm_srli_epi32(_mm_slli_epi32(all1_mask, 25), 2);

    return _mm_castsi128_ps(one);
}


static bad_forceinline f32x4 f32x4_two()
{
    mask128 all1_mask = mask128_all1();
    mask128 two       = _mm_srli_epi32(_mm_slli_epi32(all1_mask, 31), 1);

    return _mm_castsi128_ps(two);
}


// ========== Loads & stores ==========
static bad_forceinline f32x4 f32x4_load(const f32* mem_addr)
{
    bad_debug_check_aligned(mem_addr, f32x4);

    return _mm_load_si128((__m128i*)mem_addr);
}


static bad_forceinline f32x4 f32x4_loadu(const f32* mem_addr)
{
    return _mm_loadu_si128((__m128i*)mem_addr);
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


static bad_forceinline void bad_veccall f32x4_store(f32* mem_addr, f32x4 a)
{
    bad_debug_check_aligned(mem_addr, f32x4);

    return _mm_store_si128((__m128i*)mem_addr, a);
}


static bad_forceinline void bad_veccall f32x4_storeu(f32* mem_addr, f32x4 a)
{
    return _mm_storeu_si128((__m128i*)mem_addr, a);
}


static bad_forceinline void bad_veccall f32x4_store_lower(f32* mem_addr, f32x4 a)
{
    mem_addr[0] = f32x4_get_0(a);
}


// ============== Getter ==============
// Let the compiler do the work
static bad_forceinline f32 bad_veccall f32x4_get_0(f32x4 a)
{
    return *(f32*)&a;
}


static bad_forceinline f32 bad_veccall f32x4_get_1(f32x4 a)
{
    return *((f32*)&a + 1u);
}


static bad_forceinline f32 bad_veccall f32x4_get_2(f32x4 a)
{
    return *((f32*)&a + 2u);
}


static bad_forceinline f32 bad_veccall f32x4_get_3(f32x4 a)
{
    return *((f32*)&a + 3u);
}


static bad_forceinline f32 bad_veccall f32x4_get_i(f32x4 a, u32 idx)
{
    return *((f32*)&a + idx);
}


// ============== Setters =============
static bad_forceinline f32x4 bad_veccall f32x4_copy_0(f32x4 a, f32x4 origin)
{
#if defined(__SSE4_1__)
    return _mm_blend_ps(a, origin, 0b0001);
#else
    return _mm_move_ss(a, origin);
#endif
}


static bad_forceinline f32x4 bad_veccall f32x4_copy_1(f32x4 a, f32x4 origin)
{
#if defined(__SSE4_1__)
    return _mm_blend_ps(a, origin, 0b0010);
#else
    origin = _mm_move_ss(origin, a);

    return _mm_shuffle_ps(origin, a, _MM_SHUFFLE(3, 2, 1, 0));
#endif
}


static bad_forceinline f32x4 bad_veccall f32x4_copy_2(f32x4 a, f32x4 origin)
{
#if defined(__SSE4_1__)
    return _mm_blend_ps(a, origin, 0b0100);
#else
    origin = _mm_shuffle_ps(origin, a, _MM_SHUFFLE(3, 3, 2, 2));
    
    return _mm_shuffle_ps(a, origin, _MM_SHUFFLE(2, 0, 1, 0));
#endif
}


static bad_forceinline f32x4 bad_veccall f32x4_copy_3(f32x4 a, f32x4 origin)
{
#if defined(__SSE4_1__)
    return _mm_blend_ps(a, origin, 0b1000);
#else
    origin = _mm_shuffle_ps(origin, a, _MM_SHUFFLE(2, 2, 3, 3));

    return _mm_shuffle_ps(a, origin, _MM_SHUFFLE(1, 3, 1, 0));
#endif
}


static bad_forceinline f32x4 bad_veccall f32x4_set_0(f32x4 a, f32 value)
{
    return f32x4_copy_0(a, _mm_set_ss(value));
}


static bad_forceinline f32x4 bad_veccall f32x4_set_1(f32x4 a, f32 value)
{
    return f32x4_copy_1(a, f32x4_set_all(value));
}


static bad_forceinline f32x4 bad_veccall f32x4_set_2(f32x4 a, f32 value)
{
    return f32x4_copy_2(a, f32x4_set_all(value));
}


static bad_forceinline f32x4 bad_veccall f32x4_set_3(f32x4 a, f32 value)
{
    return f32x4_copy_3(a, f32x4_set_all(value));
}


// ==== Vector element broadcast =====
static bad_forceinline f32x4 bad_veccall f32x4_dup_0(f32x4 a)
{
#if defined(__AVX__)
    return _mm_permute_ps(a, 0b00000000);
#else
    return _mm_shuffle_ps(a, a, _MM_SHUFFLE(0, 0, 0, 0));
#endif
}


static bad_forceinline f32x4 bad_veccall f32x4_dup_1(f32x4 a)
{
#if defined(__AVX__)
    return _mm_permute_ps(a, 0b01010101);
#else
    return _mm_shuffle_ps(a, a, _MM_SHUFFLE(1, 1, 1, 1));
#endif
}


static bad_forceinline f32x4 bad_veccall f32x4_dup_2(f32x4 a)
{
#if defined(__AVX__)
    return _mm_permute_ps(a, 0b10101010);
#else
    return _mm_shuffle_ps(a, a, _MM_SHUFFLE(2, 2, 2, 2));
#endif
}


static bad_forceinline f32x4 bad_veccall f32x4_dup_3(f32x4 a)
{
#if defined(__AVX__)
    return _mm_permute_ps(a, 0b11111111);
#else
    return _mm_shuffle_ps(a, a, _MM_SHUFFLE(3, 3, 3, 3));
#endif
}


// =========== Selection ============
// (a & m) | (b & ~m)
static bad_forceinline f32x4 bad_veccall f32x4_blend(f32x4 a, f32x4 b, mask128 m)
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
static bad_forceinline mask128 bad_veccall f32x4_as_mask128(f32x4 a)
{
#if defined(__SSE2__)
    return _mm_castps_si128(a);
#else
    return a;
#endif
}

static bad_forceinline mask128 bad_veccall f32x4_to_s32x4(f32x4 a)
{
#if defined(___SSE2__)
    return _mm_cvtps_epi32(a);
#else
    bad_align_to(f32x4) f32 store[4];
    bad_align_to(mask128) s32 load[4];

    f32x4_store(store, a);

    load[0] = (s32)store[0];
    load[1] = (s32)store[1];
    load[2] = (s32)store[2];
    load[3] = (s32)store[3];

    return mask128_load((mask_elem*)load);
#endif
}


static bad_forceinline mask128 bad_veccall f32x4_to_u32x4(f32x4 a)
{
    bad_align_to(f32x4) f32 store[4];
    bad_align_to(mask128) s32 load[4];

    f32x4_store(store, a);

    load[0] = (u32)store[0];
    load[1] = (u32)store[1];
    load[2] = (u32)store[2];
    load[3] = (u32)store[3];

    return mask128_load((mask_elem*)load);
}
