static const u32 mask128_all_bits_set   = 0xFFFFFFFF;
static const u32 mask128_all_bits_clear = 0x00000000;

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

    res.x = a;
    res.y = b;
    res.z = c;
    res.w = d;

    return res;
}


static bad_forceinline mask128 mask128_set1(mask_elem k)
{
    return mask128_set(k, k, k, k);
}


static bad_forceinline void mask128_store(mask_elem* mem_addr, mask128_vec0 a)
{
    mem_addr[0] = a.x;
    mem_addr[1] = a.y;
    mem_addr[2] = a.z;
    mem_addr[3] = a.w;
}


static bad_forceinline void mask128_storeu(mask_elem* mem_addr, mask128_vec0 a)
{
    return mask128_store(mem_addr, a);
}


static bad_forceinline mask128 mask128_zero()
{
    mask128 res;

    res.x = mask128_all_bits_clear;
    res.y = mask128_all_bits_clear;
    res.z = mask128_all_bits_clear;
    res.w = mask128_all_bits_clear;

    return res;
}


static bad_forceinline mask128 mask128_all1()
{
    mask128 res;

    res.x = mask128_all_bits_set;
    res.y = mask128_all_bits_set;
    res.z = mask128_all_bits_set;
    res.w = mask128_all_bits_set;

    return res;
}


static bad_forceinline mask128 mask128_value32()
{
    mask128 res;

    res.x = 0x7FFFFFFF;
    res.y = 0x7FFFFFFF;
    res.z = 0x7FFFFFFF;
    res.w = 0x7FFFFFFF;

    return res;
}


static bad_forceinline mask128 mask128_highbit32()
{
    mask128 res;

    res.x = 0x80000000;
    res.y = 0x80000000;
    res.z = 0x80000000;
    res.w = 0x80000000;

    return res;
}


static bad_forceinline mask128 mask128_lowbit32()
{
    mask128 res;

    res.x = 0x00000001;
    res.y = 0x00000001;
    res.z = 0x00000001;
    res.w = 0x00000001;

    return res;
}


static bad_forceinline mask128 mask128_exponent32()
{
    mask128 res;

    res.x = 0x7F800000;
    res.y = 0x7F800000;
    res.z = 0x7F800000;
    res.w = 0x7F800000;

    return res;
}


// ========== Comparison ==========
static bad_forceinline mask128 mask128_eq(mask128_vec0 a, mask128_vec1 b)
{
    mask128 res;

    res.x = (a.x == b.x) ? mask128_all_bits_set : mask128_all_bits_clear;
    res.y = (a.y == b.y) ? mask128_all_bits_set : mask128_all_bits_clear;
    res.z = (a.z == b.z) ? mask128_all_bits_set : mask128_all_bits_clear;
    res.w = (a.w == b.w) ? mask128_all_bits_set : mask128_all_bits_clear;

    return res;
}


static bad_forceinline mask128 mask128_neq(mask128_vec0 a, mask128_vec1 b)
{
    mask128 res;

    res.x = (a.x != b.x) ? mask128_all_bits_set : mask128_all_bits_clear;
    res.y = (a.y != b.y) ? mask128_all_bits_set : mask128_all_bits_clear;
    res.z = (a.z != b.z) ? mask128_all_bits_set : mask128_all_bits_clear;
    res.w = (a.w != b.w) ? mask128_all_bits_set : mask128_all_bits_clear;

    return res;
}


// ============= Logical ==============
static bad_forceinline mask128 bad_veccall mask128_and(mask128_vec0 a, mask128_vec1 b)
{
    mask128 res;

    res.x = a.x & b.x;
    res.y = a.y & b.y;
    res.z = a.z & b.z;
    res.w = a.w & b.w;

    return res;
}


static bad_forceinline mask128 bad_veccall mask128_and_not(mask128_vec0 a, mask128_vec1 b)
{
    mask128 res;

    res.x = a.x & ~b.x;
    res.y = a.y & ~b.y;
    res.z = a.z & ~b.z;
    res.w = a.w & ~b.w;

    return res;
}


static bad_forceinline mask128 bad_veccall mask128_or(mask128_vec0 a, mask128_vec1 b)
{
    mask128 res;

    res.x = a.x | b.x;
    res.y = a.y | b.y;
    res.z = a.z | b.z;
    res.w = a.w | b.w;

    return res;
}


static bad_forceinline mask128 bad_veccall mask128_xor(mask128_vec0 a, mask128_vec1 b)
{
    mask128 res;

    res.x = a.x ^ b.x;
    res.y = a.y ^ b.y;
    res.z = a.z ^ b.z;
    res.w = a.w ^ b.w;

    return res;
}


static bad_forceinline mask128 bad_veccall mask128_not(mask128_vec0 a)
{
    mask128 res;

    res.x = ~a.x;
    res.y = ~a.y;
    res.z = ~a.z;
    res.w = ~a.w;

    return res;
}


// ============ Conversion =============
static bad_forceinline f32x4 bad_veccall mask128_cast_f32x4(mask128_vec0 a)
{
    f32x4 res;

    res.x = *(f32*)&a.x;
    res.y = *(f32*)&a.y;
    res.z = *(f32*)&a.z;
    res.w = *(f32*)&a.w;

    return res;
}