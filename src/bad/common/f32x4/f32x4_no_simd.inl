// ============= Defaults =============
static bad_forceinline f32x4 f32x4_any()
{
    f32x4 any;

    return any;
}


static bad_forceinline f32x4 f32x4_zero()
{
    return f32x4_set_all(.0f);
}


static bad_forceinline f32x4 f32x4_half()
{
    return f32x4_set_all(.5f);
}


static bad_forceinline f32x4 f32x4_one()
{
    return f32x4_set_all(1.f);
}


static bad_forceinline f32x4 f32x4_two()
{
    return f32x4_set_all(2.f);
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

    v.e[0] = x;
    v.e[1] = y;
    v.e[2] = z;
    v.e[3] = w;

    return v;
}


static bad_forceinline f32x4 f32x4_set_all(f32 a)
{
    return f32x4_set(a, a, a, a);
}


static bad_forceinline f32x4 f32x4_set_lower(f32 a)
{
    f32x4 res;

    res.e[0] = a;

    return res;
}


static bad_forceinline void f32x4_store(f32* mem_addr, f32x4_vec0 a)
{
    mem_addr[0] = a.e[0];
    mem_addr[1] = a.e[1];
    mem_addr[2] = a.e[2];
    mem_addr[3] = a.e[3];
}


static bad_forceinline void f32x4_storeu(f32* mem_addr, f32x4_vec0 a)
{
    return f32x4_store(mem_addr, a);
}


static bad_forceinline void bad_veccall f32x4_store_lower(f32* mem_addr, f32x4_vec0 a)
{
    mem_addr[0] = f32x4_get_0(a);
}


// ============== Getter ==============
static bad_forceinline f32 f32x4_get_0(f32x4_vec0 a)
{
    return a.e[0];
}


static bad_forceinline f32 f32x4_get_1(f32x4_vec0 a)
{
    return a.e[1];
}

static bad_forceinline f32 f32x4_get_2(f32x4_vec0 a)
{
    return a.e[2];
}


static bad_forceinline f32 f32x4_get_3(f32x4_vec0 a)
{
    return a.e[3];
}

static bad_forceinline f32 f32x4_get_i(f32x4_vec0 a, s32 i)
{
    return a.e[i];
}


static bad_forceinline f32 f32x4_get_f32(f32x4_vec0 a, s32 i)
{
    return a.e[i];
}


// ============== Setters =============
static bad_forceinline f32x4 f32x4_copy_0(f32x4_vec0 a, f32x4 origin)
{
    return (f32x4){origin.e[0], a.e[1], a.e[2], a.e[3]};
}


static bad_forceinline f32x4 f32x4_copy_1(f32x4_vec0 a, f32x4 origin)
{
    return (f32x4){a.e[0], origin.e[1], a.e[2], a.e[3]};
}


static bad_forceinline f32x4 f32x4_copy_2(f32x4_vec0 a, f32x4 origin)
{
    return (f32x4){a.e[0], a.e[1], origin.e[2], a.e[3]};
}


static bad_forceinline f32x4 f32x4_copy_3(f32x4_vec0 a, f32x4 origin)
{
    return (f32x4){a.e[0], a.e[1], a.e[2], origin.e[3]};
}


static bad_forceinline f32x4 f32x4_set_0(f32x4_vec0 a, f32 value)
{
    return (f32x4){value, a.e[1], a.e[2], a.e[3]}
}


static bad_forceinline f32x4 f32x4_set_1(f32x4_vec0 a, f32 value)
{
    return (f32x4){a.e[0], value, a.e[2], a.e[3]};
}


static bad_forceinline f32x4 f32x4_set_2(f32x4_vec0 a, f32 value)
{
    return (f32x4){a.e[0], a.e[1], value, a.e[3]};
}


static bad_forceinline f32x4 f32x4_set_3(f32x4_vec0 a, f32 value)
{
    return (f32x4){a.e[0], a.e[1], a.e[2], value};
}


// ===== Vector element broadcast =====
static bad_forceinline f32x4 f32x4_broadcast_0(f32x4_vec0 a)
{
    return (f32x4){a.e[0], a.e[0], a.e[0], a.e[0]};
}


static bad_forceinline f32x4 f32x4_broadcast_1(f32x4_vec0 a)
{
    return (f32x4){a.e[1], a.e[1], a.e[1], a.e[1]};
}


static bad_forceinline f32x4 f32x4_broadcast_2(f32x4_vec0 a)
{
    return (f32x4){a.e[2], a.e[2], a.e[2], a.e[2]};
}


static bad_forceinline f32x4 f32x4_broadcast_3(f32x4_vec0 a)
{
    return (f32x4){a.e[3], a.e[3], a.e[3], a.e[3]};
}


// ============ Selection =============
static bad_forceinline f32x4 f32x4_blend(f32x4_vec0 a, f32x4_vec1 b, mask128_vec2 m)
{
    mask128 a_mask = f32x4_as_mask128(a);
    mask128 b_mask = f32x4_as_mask128(b);
            a_mask = mask128_or(mask128_and(a_mask, m), mask128_and_not(b_mask, m));
    
    return mask128_as_f32x4(res);
}


// =========== Conversion =============
static bad_forceinline mask128 f32x4_as_mask128(f32x4_vec0 a)
{
    mask128 res;

    res.e[0] = *(u32*)&a.e[0];
    res.e[1] = *(u32*)&a.e[1];
    res.e[2] = *(u32*)&a.e[2];
    res.e[3] = *(u32*)&a.e[3];

    return res;
}


static bad_forceinline mask128 bad_veccall f32x4_to_s32x4(f32x4_vec0 a)
{
    mask128 res;

    res.e[0] = (s32)a.e[0];
    res.e[1] = (s32)a.e[1];
    res.e[2] = (s32)a.e[2];
    res.e[3] = (s32)a.e[3];

    return res;
}


static bad_forceinline mask128 bad_veccall f32x4_to_u32x4(f32x4_vec0 a)
{
    mask128 res;

    res.e[0] = (u32)a.e[0];
    res.e[1] = (u32)a.e[1];
    res.e[2] = (u32)a.e[2];
    res.e[3] = (u32)a.e[3];

    return res;
}