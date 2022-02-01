// ============= Defaults =============
static bad_forceinline f32x4 f32x4_any()
{
    f32x4 any;

    return any;
}


static bad_forceinline f32x4 f32x4_zero()
{
    return f32x4_set1(.0f);
}


static bad_forceinline f32x4 f32x4_one()
{
    return f32x4_set1(1.f);
}


// ========== Load & store ==========
static bad_forceinline f32x4 f32x4_load(const f32* mem_addr)
{
    return f32x4_set(mem_addr[0], mem_addr[1], mem_addr[2], mem_addr[3]);
}


static bad_forceinline f32x4 f32x4_loadu(const f32* mem_addr)
{
    return f32x4_load(mem_addr);
}


static bad_forceinline f32x4 f32x4_set(f32 x, f32 y, f32 z, f32 w)
{
    f32x4 v;

    v.x = x;
    v.y = y;
    v.z = z;
    v.w = w;

    return v;
}


static bad_forceinline f32x4 f32x4_set1(f32 k)
{
    return f32x4_set(k, k, k, k);
}


static bad_forceinline void f32x4_store(f32* mem_addr, f32x4_vec0 a)
{
    mem_addr[0] = a.x;
    mem_addr[1] = a.y;
    mem_addr[2] = a.z;
    mem_addr[3] = a.w;
}


static bad_forceinline void f32x4_storeu(f32* mem_addr, f32x4_vec0 a)
{
    return f32x4_store(mem_addr, a);
}


// ======= Selection & swizzling ========
static bad_forceinline f32x4 f32x4_blend(f32x4_vec0 a, f32x4_vec1 b, mask128_vec2 m)
{
    const mask128 a_mask = f32x4_cast_mask128(a);
    const mask128 b_mask = f32x4_cast_mask128(b);
    const mask128 res    = mask128_or(mask128_and(a_mask, m), mask128_and_not(b_mask, m));
    
    return mask128_cast_f32x4(res);
}


// ============ Conversion =============
static bad_forceinline mask128 bad_veccall f32x4_cast_mask128(f32x4_vec0 a)
{
    mask128 res;

    res.x = *(u32*)&a.x;
    res.y = *(u32*)&a.y;
    res.z = *(u32*)&a.z;
    res.w = *(u32*)&a.w;

    return res;
}