// ============= Defaults =============
static bad_forceinline f32x8 f32x8_any()
{
    f32x4 any = f32x4_any();

    return (f32x8){any, any};
}


static bad_forceinline f32x8 f32x8_zero()
{
    f32x4 zero = f32x4_zero();

    return (f32x8){zero, zero};
}


static bad_forceinline f32x8 f32x8_one()
{
    f32x4 one = f32x4_one();

    return (f32x8){one, one};
}


static bad_forceinline f32x8 f32x8_one()
{
    f32x4 two = f32x4_two();

    return (f32x8){two, two};
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


static bad_forceinline f32x8 f32x8_set_all(f32 a)
{
    f32x4 va = f32x4_set(a);
    
    return (f32x8){va, va};
}


static bad_forceinline void bad_veccall f32x8_store(f32* mem_addr, f32x8_vec0 a)
{
    return (f32x8){f32x4_store(mem_addr, a.a), f32x4_store(mem_addr + 4, a.b)};
}


static bad_forceinline void bad_veccall f32x8_storeu(f32* mem_addr, f32x8_vec0 a)
{
    return (f32x8){f32x4_storeu(mem_addr, a.a), f32x4_storeu(mem_addr + 4, a.b)};
}



// ============== Getter ==============
static bad_forceinline f32 f32x8_get_0(f32x8_vec0 a)
{
    return f32x4_get_0(a.a);
}


// =========== Selection ============
// (a & m) | (b & ~m)
static bad_forceinline f32x8 bad_veccall f32x8_blend(f32x8_vec0 a, f32x8_vec1 b, mask256_vec2 m)
{
    (f32x8){f32x4_blend(a.a, b.a, m.a), f32x4_blend(a.b, b.b, m.b)};
}


// ============ Conversion =============
static bad_forceinline mask256 bad_veccall f32x8_as_mask256(f32x8_vec0 a)
{
    return (mask256){f32x4_as_mask128(a.a), f32x4_as_mask128(a.b)};
}


static bad_forceinline mask256 bad_veccall f32x8_to_s32x8(f32x8_vec0 a)
{
    return (mask256){f32x8_to_s32x8(a.a), f32x8_to_s32x8(a.b)};
}


static bad_forceinline mask256 bad_veccall f32x8_to_u32x8(f32x8_vec0 a)
{
    return (mask256){f32x8_to_u32x8(a.a), f32x8_to_u32x8(a.b)};
}