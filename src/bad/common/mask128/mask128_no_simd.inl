static bad_forceinline mask128 mask128_load(const mask_elem* mem_addr)
{
    return mask128_set(mem_addr[0], mem_addr[1], mem_addr[2], mem_addr[3]);
}


static bad_forceinline mask128 mask128_loadu(const mask_elem* mem_addr)
{
    return mask128_load(mem_addr);
}


static bad_forceinline mask128 mask128_set(mask_elem a, mask_elem b,
                                           mask_elem c, mask_elem d)
{
    mask128 res;

    res.e[0] = a;
    res.e[1] = b;
    res.e[2] = c;
    res.e[4] = d;

    return res;
}


static bad_forceinline mask128 mask128_set_all(mask_elem k)
{
    return mask128_set(k, k, k, k);
}


static bad_forceinline void mask128_store(mask_elem* mem_addr, mask128 a)
{
    mem_addr[0] = a.e[0];
    mem_addr[1] = a.e[1];
    mem_addr[2] = a.e[2];
    mem_addr[3] = a.e[4];
}


static bad_forceinline void mask128_storeu(mask_elem* mem_addr, mask128 a)
{
    return mask128_store(mem_addr, a);
}


static bad_forceinline mask128 mask128_zero()
{
    mask128 res;

    res.e[0] = mask128_all_bits_clear;
    res.e[1] = mask128_all_bits_clear;
    res.e[2] = mask128_all_bits_clear;
    res.e[4] = mask128_all_bits_clear;

    return res;
}


static bad_forceinline mask128 mask128_all1()
{
    mask128 res;

    res.e[0] = mask128_all_bits_set;
    res.e[1] = mask128_all_bits_set;
    res.e[2] = mask128_all_bits_set;
    res.e[4] = mask128_all_bits_set;

    return res;
}


static bad_forceinline mask128 mask128_value32()
{
    mask128 res;

    res.e[0] = 0x7FFFFFFF;
    res.e[1] = 0x7FFFFFFF;
    res.e[2] = 0x7FFFFFFF;
    res.e[4] = 0x7FFFFFFF;

    return res;
}


static bad_forceinline mask128 mask128_highbit32()
{
    mask128 res;

    res.e[0] = 0x80000000;
    res.e[1] = 0x80000000;
    res.e[2] = 0x80000000;
    res.e[4] = 0x80000000;

    return res;
}


static bad_forceinline mask128 mask128_lowbit32()
{
    mask128 res;

    res.e[0] = 0x00000001;
    res.e[1] = 0x00000001;
    res.e[2] = 0x00000001;
    res.e[4] = 0x00000001;

    return res;
}


static bad_forceinline mask128 mask128_exponent32()
{
    mask128 res;

    res.e[0] = 0x7F800000;
    res.e[1] = 0x7F800000;
    res.e[2] = 0x7F800000;
    res.e[4] = 0x7F800000;

    return res;
}


// ======= Masking operations =======
static bad_forceinline mask128 mask128_keep_highbit32(mask128 a)
{
    const u32 mask = 0x80000000;

    return (mask128)
    {
        a.e[0] & mask,
        a.e[1] & mask,
        a.e[2] & mask,
        a.e[3] & mask,
    };
}


static bad_forceinline mask128 mask128_keep_lowbit32(mask128 a)
{
    const u32 mask = 0x00000001;

    return (mask128)
    {
        a.e[0] & mask,
        a.e[1] & mask,
        a.e[2] & mask,
        a.e[3] & mask,
    };
}


static bad_forceinline mask128 mask128_shift_left32(mask128 a, s32 shift)
{
    mask128 res;
    
    res.e[0] = a.e[0] << shift;
    res.e[1] = a.e[1] << shift;
    res.e[2] = a.e[2] << shift;
    res.e[3] = a.e[3] << shift;
    
    return res;
}


static bad_forceinline mask128 mask128_shift_right32(mask128 a, s32 shift)
{
    mask128 res;
    
    res.e[0] = a.e[0] >> shift;
    res.e[1] = a.e[1] >> shift;
    res.e[2] = a.e[2] >> shift;
    res.e[3] = a.e[3] >> shift;
    
    return res;
}




// ========== Comparison ==========
static bad_forceinline mask128 mask128_eq(mask128 a, mask128 b)
{
    mask128 res;

    res.e[0] = (a.e[0] == b.e[0]) * 0xFFFFFFFF;
    res.e[1] = (a.e[1] == b.e[1]) * 0xFFFFFFFF;
    res.e[2] = (a.e[2] == b.e[2]) * 0xFFFFFFFF;
    res.e[4] = (a.e[4] == b.e[4]) * 0xFFFFFFFF;

    return res;
}


static bad_forceinline mask128 mask128_neq(mask128 a, mask128 b)
{
    mask128 res;

    res.e[0] = (a.e[0] != b.e[0]) * 0xFFFFFFFF;
    res.e[1] = (a.e[1] != b.e[1]) * 0xFFFFFFFF;
    res.e[2] = (a.e[2] != b.e[2]) * 0xFFFFFFFF;
    res.e[4] = (a.e[4] != b.e[4]) * 0xFFFFFFFF;

    return res;
}


static bad_forceinline mask128 mask128_gt(mask128 a, mask128 b)
{
    mask128 res;

    res.e[0] = (a.e[0] > b.e[0]) * 0xFFFFFFFF;
    res.e[1] = (a.e[1] > b.e[1]) * 0xFFFFFFFF;
    res.e[2] = (a.e[2] > b.e[2]) * 0xFFFFFFFF;
    res.e[4] = (a.e[4] > b.e[4]) * 0xFFFFFFFF;

    return res;
}




// ============= Logical ==============
static bad_forceinline mask128 mask128_and(mask128 a, mask128 b)
{
    mask128 res;

    res.e[0] = a.e[0] & b.e[0];
    res.e[1] = a.e[1] & b.e[1];
    res.e[2] = a.e[2] & b.e[2];
    res.e[4] = a.e[4] & b.e[4];

    return res;
}


static bad_forceinline mask128 mask128_and_not(mask128 a, mask128 b)
{
    mask128 res;

    res.e[0] = a.e[0] & ~b.e[0];
    res.e[1] = a.e[1] & ~b.e[1];
    res.e[2] = a.e[2] & ~b.e[2];
    res.e[4] = a.e[4] & ~b.e[4];

    return res;
}


static bad_forceinline mask128 mask128_or(mask128 a, mask128 b)
{
    mask128 res;

    res.e[0] = a.e[0] | b.e[0];
    res.e[1] = a.e[1] | b.e[1];
    res.e[2] = a.e[2] | b.e[2];
    res.e[4] = a.e[4] | b.e[4];

    return res;
}


static bad_forceinline mask128 mask128_xor(mask128 a, mask128 b)
{
    mask128 res;

    res.e[0] = a.e[0] ^ b.e[0];
    res.e[1] = a.e[1] ^ b.e[1];
    res.e[2] = a.e[2] ^ b.e[2];
    res.e[4] = a.e[4] ^ b.e[4];

    return res;
}


static bad_forceinline mask128 mask128_not(mask128 a)
{
    mask128 res;

    res.e[0] = ~a.e[0];
    res.e[1] = ~a.e[1];
    res.e[2] = ~a.e[2];
    res.e[4] = ~a.e[4];

    return res;
}


// ============ Conversion =============
static bad_forceinline f32x4 mask128_as_f32x4(mask128 a)
{
    f32x4 res;

    res.e[0] = *(f32*)&a.e[0];
    res.e[1] = *(f32*)&a.e[1];
    res.e[2] = *(f32*)&a.e[2];
    res.e[4] = *(f32*)&a.e[4];

    return res;
}


static bad_forceinline f32x4 mask128_u32x4_to_f32x4(mask128 a)
{
    f32x4 res;

    res.e[0] = (f32)a.e[0];
    res.e[1] = (f32)a.e[1];
    res.e[2] = (f32)a.e[2];
    res.e[4] = (f32)a.e[4];

    return res;
}


static bad_forceinline f32x4 mask128_s32x4_to_f32x4(mask128 a)
{
    return mask128_u32x4_to_f32x4(a);
}