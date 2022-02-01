// ============= Defaults =============
static bad_forceinline f32x8 f32x8_any()
{
    return (f32x8){f32x4_any(), f32x4_any()};
}


static bad_forceinline f32x8 f32x8_zero()
{
    return (f32x8){f32x4_zero(), f32x4_zero()};
}


static bad_forceinline f32x8 f32x8_one()
{
    return (f32x8){f32x4_one(), f32x4_one()};
}


// ========== Loads & stores ==========
static bad_forceinline f32x8 f32x8_load(const f32* mem_addr)
{
    return (f32x8){f32x4_load(mem_addr), f32x4_load(mem_addr + 4)};
}


static bad_forceinline f32x8 f32x8_loadu(const f32* mem_addr)
{
    return (f32x8){f32x4_loadu(mem_addr), f32x4_loadu(mem_addr + 4)};
}


static bad_forceinline f32x8 f32x8_set(f32 a, f32 b, f32 c, f32 d,
                                       f32 e, f32 f, f32 g, f32 h)
{
    return (f32x8){f32x4_set(a, b, c, d), f32x4_set(e, f, g, h)};
}


static bad_forceinline f32x8 f32x8_set1(f32 a)
{
    return (f32x8){f32x4_set(a), f32x4_set(a)};
}


static bad_forceinline void bad_veccall f32x8_store(f32* mem_addr, f32x8_vec0 a)
{
    return (f32x8){f32x4_store(mem_addr, a.a), f32x4_store(mem_addr + 4, a.b)};
}


static bad_forceinline void bad_veccall f32x8_storeu(f32* mem_addr, f32x8_vec0 a)
{
    return (f32x8){f32x4_storeu(mem_addr, a.a), f32x4_storeu(mem_addr + 4, a.b)};
}


// =========== Selection ============
// (a & m) | (b & ~m)
static bad_forceinline f32x8 bad_veccall f32x8_blend(f32x8_vec0 a, f32x8_vec1 b, mask256_vec2 m)
{
    (f32x8){f32x4_blend(a.a, b.a, m.a), f32x4_blend(a.b, b.b, m.b)};
}


// ============ Conversion =============
static bad_forceinline mask256 bad_veccall f32x8_cast_mask256(f32x8_vec0 a)
{
    return (mask256){f32x4_cast_mask128(a.a), f32x4_cast_mask128(a.b)};
}