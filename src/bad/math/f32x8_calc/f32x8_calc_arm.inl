// =========== Arithmetic ===========
static bad_forceinline f32x8 bad_veccall f32x8_add(f32x8_vec0 a, f32x8_vec1 b)
{
    return (f32x8){f32x4_add(a.a, b.a), f32x4_add(a.b, b.b)};
}


static bad_forceinline f32x8 bad_veccall f32x8_sub(f32x8_vec0 a, f32x8_vec1 b)
{
    return (f32x8){f32x4_sub(a.a, b.a), f32x4_sub(a.b, b.b)};
}


static bad_forceinline f32x8 bad_veccall f32x8_mul(f32x8_vec0 a, f32x8_vec1 b)
{
    return (f32x8){f32x4_mul(a.a, b.a), f32x4_mul(a.b, b.b)};
}


static bad_forceinline f32x8 bad_veccall f32x8_div(f32x8_vec0 a, f32x8_vec1 b)
{
    return (f32x8){f32x4_div(a.a, b.a), f32x4_div(a.b, b.b)};
}


static bad_forceinline f32 bad_veccall f32x8_hadd(f32x8_vec0 a)
{
    return f32x4_hadd(a.a) + f32x4_hadd(a.b);
}


// ====== Advanced arithmetic =======
static bad_forceinline f32x8 bad_veccall f32x8_rcp(f32x8_vec0 a)
{
    return (f32x8){f32x4_rcp(a.a), f32x4_rcp(a.b)};
}


static bad_forceinline f32x8 bad_veccall f32x8_sqrt(f32x8_vec0 a)
{
    return (f32x8){f32x4_sqrt(a.a), f32x4_sqrt(a.b)};
}


static bad_forceinline f32x8 bad_veccall f32x8_rsqrt(f32x8_vec0 a)
{
    return (f32x8){f32x4_rsqrt(a.a), f32x4_rsqrt(a.b)};
}


static bad_forceinline f32x8 bad_veccall f32x8_min(f32x8_vec0 a, f32x8_vec1 b)
{
    return (f32x8){f32x4_min(a.a, b.a), f32x4_min(a.b, b.b)};
}


static bad_forceinline f32x8 bad_veccall f32x8_max(f32x8_vec0 a, f32x8_vec1 b)
{
    return (f32x8){f32x4_max(a.a, b.a), f32x4_max(a.b, b.b)};
}


static bad_forceinline f32x8 bad_veccall f32x8_abs(f32x8_vec0 a)
{
    return (f32x8){f32x4_abs(a.a), f32x4_abs(a.b)};
}


static bad_forceinline f32x8 bad_veccall f32x8_neg(f32x8_vec0 a)
{
    return (f32x8){f32x4_neg(a.a, b.a), f32x4_neg(a.b, b.b)};
}


static bad_forceinline f32x8 bad_veccall f32x8_mod(f32x8_vec0 a, f32x8_vec1 b)
{
    return (f32x8){f32x4_mod(a.a, b.a), f32x4_mod(a.b, b.b)};
}


static bad_forceinline f32x8 bad_veccall f32x8_trunc(f32x8_vec0 a)
{
    return (f32x8){f32x4_trunc(a.a), f32x4_trunc(a.b)};
}


static bad_forceinline f32x8 bad_veccall f32x8_round(f32x8_vec0 a)
{
    return (f32x8){f32x4_round(a.a), f32x4_round(a.b)};
}


static bad_forceinline f32x8 bad_veccall f32x8_floor(f32x8_vec0 a)
{
    return (f32x8){f32x4_floor(a.a), f32x4_floor(a.b)};
}


static bad_forceinline f32x8 bad_veccall f32x8_ceil(f32x8_vec0 a)
{
    return (f32x8){f32x4_ceil(a.a), f32x4_ceil(a.b)};
}


static bad_forceinline f32x8 bad_veccall f32x8_clamp(f32x8_vec0 a, f32x8_vec1 min, f32x8_vec2 max)
{
    return (f32x8){f32x4_clamp(a.a), f32x4_clamp(a.b)};
}

// a * b + c
static bad_forceinline f32x8 bad_veccall f32x8_mul_add(f32x8_vec0 a, f32x8_vec1 b, f32x8_vec2 c)
{
    return (f32x8){f32x4_mul_add(a.a, b.a, c.a), f32x4_mul_add(a.b, b.b, c.b)};
}

// a * b - c
static bad_forceinline f32x8 bad_veccall f32x8_mul_sub(f32x8_vec0 a, f32x8_vec1 b, f32x8_vec2 c)
{
    return (f32x8){f32x4_mul_sub(a.a, b.a, c.a), f32x4_mul_sub(a.b, b.b, c.b)};
}

// -a * b + c
static bad_forceinline f32x8 bad_veccall f32x8_nmul_add(f32x8_vec0 a, f32x8_vec1 b, f32x8_vec2 c)
{
    return (f32x8){f32x4_mul_sub(a.a, b.a, c.a), f32x4_mul_sub(a.b, b.b, c.b)};
}

// -a * b - c
static bad_forceinline f32x8 bad_veccall f32x8_nmul_sub(f32x8_vec0 a, f32x8_vec1 b, f32x8_vec2 c)
{
    return (f32x8){f32x4_nmul_sub(a.a, b.a, c.a), f32x4_nmul_sub(a.b, b.b, c.b)};
}


// ============ Comparison ============
static bad_forceinline mask128 bad_veccall f32x8_neq(f32x8_vec0 a, f32x8_vec1 b)
{
    return (f32x8){f32x4_neq(a.a, b.a), f32x4_neq(a.b, b.b)};
}


static bad_forceinline mask128 bad_veccall f32x8_eq(f32x8_vec0 a, f32x8_vec1 b)
{
    return (f32x8){f32x4_eq(a.a, b.a), f32x4_eq(a.b, b.b)};
}


static bad_forceinline mask128 bad_veccall f32x8_ge(f32x8_vec0 a, f32x8_vec1 b)
{
    return (f32x8){f32x4_ge(a.a, b.a), f32x4_ge(a.b, b.b)};
}


static bad_forceinline mask128 bad_veccall f32x8_gt(f32x8_vec0 a, f32x8_vec1 b)
{
    return (f32x8){f32x4_gt(a.a, b.a), f32x4_gt(a.b, b.b)};
}


static bad_forceinline mask128 bad_veccall f32x8_le(f32x8_vec0 a, f32x8_vec1 b)
{
    return (f32x8){f32x4_le(a.a, b.a), f32x4_le(a.b, b.b)};
}


static bad_forceinline mask128 bad_veccall f32x8_lt(f32x8_vec0 a, f32x8_vec1 b)
{
    return (f32x8){f32x4_lt(a.a, b.a), f32x4_lt(a.b, b.b)};
}



// ======= Selection & tests ========
static bad_forceinline mask128 bad_veccall f32x8_is_nan(f32x8_vec0 a)
{
    return (f32x8){f32x4_is_nan(a.a), f32x4_is_nan(a.b)};
}


static bad_forceinline mask128 bad_veccall f32x8_is_infinite(f32x8_vec0 a)
{
    // +inf is 0x7F800000, -inf is 0xFF800000
    const mask128 inf_mask   = mask128_all1();
    const mask128 value_mask = vshrq_n_u32(all1_mask, 1);
                  inf_mask   = vshrq_n_u32(vshlq_n_u32(all1_mask, 24), 1);

    return (f32x8)
    {
        vceqq_f32(vandq_u32(value_mask, vreinterpretq_u32_f32(a.a)), inf_mask),
        vceqq_f32(vandq_u32(value_mask, vreinterpretq_u32_f32(a.b)), inf_mask)
    };
}


static bad_forceinline mask128 bad_veccall f32x8_is_finite(f32x8_vec0 a)
{
    const mask128 exp = mask128_exponent32();

    return (f32x8)
    {
        vmvnq_u32(vceqq_f32(vandq_u32(vreinterpretq_u32_f32(a.a), exp), exp)),
        vmvnq_u32(vceqq_f32(vandq_u32(vreinterpretq_u32_f32(a.b), exp), exp))
    };
}