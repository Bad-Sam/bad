static bad_forceinline mask256 mask256_load(const mask_elem* mem_addr)
{
    return (mask256){mask128_load(mem_addr), mask128_load(mem_addr + 4)};
}


static bad_forceinline mask256 mask256_loadu(const mask_elem* mem_addr)
{
    return (mask256){mask128_loadu(mem_addr), mask128_loadu(mem_addr + 4)};
}


static bad_forceinline mask256 mask256_set(mask_elem a, mask_elem b, mask_elem c, mask_elem d,
                                           mask_elem e, mask_elem f, mask_elem g, mask_elem h)
{
    return (mask256){mask128_set(a, b, c, d), mask128_set(e, f, g, h)};
}


static bad_forceinline mask256 mask256_set_all(mask_elem k)
{
    return (mask256){mask128_set_all(k), mask128_set_all(k)};
}


static bad_forceinline void mask256_store(mask_elem* mem_addr, mask256_vec0 a)
{
    mask128_store(mem_addr, a.a);
    mask128_store(mem_addr + 4, a.b);
}


static bad_forceinline void mask256_storeu(mask_elem* mem_addr, mask256_vec0 a)
{
    mask128_storeu(mem_addr, a.a);
    mask128_storeu(mem_addr + 4, a.b);
}


static bad_forceinline mask256 mask256_zero()
{
    return (mask256){mask128_zero(), mask128_zero()};
}


static bad_forceinline mask256 mask256_all1()
{
    return (mask256){mask128_all1(), mask128_all1()};
}


static bad_forceinline mask256 mask256_value32()
{
    return (mask256){mask128_value32(), mask128_value32()};
}


static bad_forceinline mask256 mask128_highbit32()
{
    return (mask256){mask128_highbit32(), mask128_highbit32()};
}


static bad_forceinline mask256 mask256_lowbit32()
{
    return (mask256){mask128_lowbit32(), mask128_lowbit32()};
}


static bad_forceinline mask256 mask256_exponent32()
{
    return (mask256){mask128_exponent32(), mask128_exponent32()};
}


// ========== Comparison ==========
static bad_forceinline mask256 mask256_eq(mask256_vec0 a, mask256_vec1 b)
{
    return (mask256){mask128_eq(a.a, b.a), mask128_eq(a.b, b.b)};
}


static bad_forceinline mask256 mask256_neq(mask256_vec0 a, mask256_vec1 b)
{
    return (mask256){mask128_neq(a.a, b.a), mask128_neq(a.b, b.b)};
}


// ============= Logical ==============
static bad_forceinline mask256 bad_veccall mask256_and(mask256_vec0 a, mask256_vec1 b)
{
    return (mask256){mask128_and(a.a, b.a), mask128_and(a.b, b.b)};
}


static bad_forceinline mask256 bad_veccall mask256_and_not(mask256_vec0 a, mask256_vec1 b)
{
    return (mask256){mask128_and_not(a.a, b.a), mask128_and_not(a.b, b.b)};
}


static bad_forceinline mask256 bad_veccall mask256_or(mask256_vec0 a, mask256_vec1 b)
{
    return (mask256){mask128_or(a.a, b.a), mask128_or(a.b, b.b)};
}


static bad_forceinline mask256 bad_veccall mask256_xor(mask256_vec0 a, mask256_vec1 b)
{
    return (mask256){mask128_xor(a.a, b.a), mask128_xor(a.b, b.b)};
}


// ============ Conversion =============
static bad_forceinline f32x8 bad_veccall mask256_as_f32x8(mask256_vec0 a)
{
    return (mask256){mask128_as_f32x4(a.a), mask128_as_f32x4(a.b)};
}


static bad_forceinline f32x8 bad_veccall mask256_u32x8_to_f32x8(mask256_vec0 a)
{
    return (mask256){mask128_u32x4_to_f32x4(a.a), mask128_u32x4_to_f32x4(a.b)};
}


static bad_forceinline f32x8 bad_veccall mask256_s32x8_to_f32x8(mask256_vec0 a)
{
    return (mask256){mask128_s32x4_to_f32x4(a.a), mask128_s32x4_to_f32x4(a.b)};;
}