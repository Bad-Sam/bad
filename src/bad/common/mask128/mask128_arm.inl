static bad_forceinline mask128 mask128_load(const mask_elem* mem_addr)
{
    return vld1q_u32(mem_addr);
}


static bad_forceinline mask128 mask128_loadu(const mask_elem* mem_addr)
{
    return mask128_load(mem_addr);
}


static bad_forceinline mask128 mask128_set(mask_elem a, mask_elem b,
                                           mask_elem c, mask_elem d)
{
    bad_align(16) const mask_elem e[4] = {a, b, c, d};

    return mask128_load(e);
}


static bad_forceinline mask128 mask128_set1(mask_elem k)
{
    return mask128_set(k, k, k, k);
}


static bad_forceinline void mask128_store(mask_elem* mem_addr, mask128_vec0 a)
{
    vst1q_u32(mem_addr, a);
}


static bad_forceinline void mask128_storeu(mask_elem* mem_addr, mask128_vec0 a)
{
    return mask128_store(mem_addr, a);
}


static bad_forceinline mask128 mask128_zero()
{
    return vdupq_n_u32(0u);
}


static bad_forceinline mask128 mask128_all1()
{
    mask128 m;

    return vceqq_u32(m, m);
}


static bad_forceinline mask128 mask128_value32()
{
    return vshrq_n_u32(mask128_all1(), 1);
}


static bad_forceinline mask128 mask128_highbit32()
{
    return vshlq_n_u32(mask128_all1(), 31);
}


static bad_forceinline mask128 mask128_lowbit32()
{
    return vshrq_n_u32(mask128_all1(), 1);
}


static bad_forceinline mask128 mask128_exponent32()
{
    return vshrq_n_u32(vshlq_n_u32(mask128_all1(), 24), 1);
}


static bad_forceinline mask128 mask128_eq(mask128_vec0 a, mask128_vec1 b)
{
    return vceqq_u32(a, b);
}


static bad_forceinline mask128 mask128_neq(mask128_vec0 a, mask128_vec1 b)
{
    return vmvnq_u32(vceqq_u32(a, b));
}


// ============= Logical ==============
static bad_forceinline mask128 bad_veccall mask128_and(mask128_vec0 a, mask128_vec1 b)
{
    return vandq_u32(a, b);
}


static bad_forceinline mask128 bad_veccall mask128_and_not(mask128_vec0 a, mask128_vec1 b)
{
    return vbicq_u32(a, b);
}


static bad_forceinline mask128 bad_veccall mask128_or(mask128_vec0 a, mask128_vec1 b)
{
    return vorq_u32(a, b);
}


static bad_forceinline mask128 bad_veccall mask128_xor(mask128_vec0 a, mask128_vec1 b)
{
    return veorq_u32(a, b);
}

static bad_forceinline mask128 bad_veccall mask128_not(mask128_vec0 a)
{
    return vmvnq_u32(a);
}


// ============ Conversion =============
static bad_forceinline f32x4 bad_veccall mask128_cast_f32x4(mask128_vec0 a)
{
    return vreinterpretq_f32_u32(a);
}