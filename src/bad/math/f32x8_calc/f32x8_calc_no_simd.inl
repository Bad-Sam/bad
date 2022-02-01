// ==== Arithmetic & math functions ===
static bad_forceinline f32x8 f32x8_add(f32x8_vec0 a, f32x8_vec1 b)
{
    return (f32x8){f32x4_add(a.a, b.a), f32x4_add(a.b, b.b)};
}


static bad_forceinline f32x8 f32x8_sub(f32x8_vec0 a, f32x8_vec1 b)
{
    return (f32x8){f32x4_sub(a.a, b.a), f32x4_sub(a.b, b.b)};
}


static bad_forceinline f32x8 f32x8_mul(f32x8_vec0 a, f32x8_vec1 b)
{
    return (f32x8){f32x4_mul(a.a, b.a), f32x4_mul(a.b, b.b)};
}


static bad_forceinline f32x8 f32x8_div(f32x8_vec0 a, f32x8_vec1 b)
{
    return (f32x8){f32x4_div(a.a, b.a), f32x4_div(a.b, b.b)};
}


static bad_forceinline f32 f32x8_hadd(f32x8_vec0 a)
{
    return f32x4_hadd(a.a) + f32x4_hadd(a.b);
}


static bad_forceinline f32x8 f32x8_rcp(f32x8_vec0 a)
{
    return (f32x8){f32x4_rcp(a.a), f32x4_rcp(a.b)};
}


static bad_forceinline f32x8 f32x8_sqrt(f32x8_vec0 a)
{
    return (f32x8){f32x4_sqrt(a.a), f32x4_sqrt(a.b)};
}


static bad_forceinline f32x8 f32x8_rsqrt(f32x8_vec0 a)
{
    return (f32x8){f32x4_rsqrt(a.a), f32x4_rsqrt(a.b)};
}


static bad_forceinline f32x8 f32x8_min(f32x8_vec0 a, f32x8_vec1 b)
{
    return (f32x8){f32x4_min(a.a, b.a), f32x4_min(a.b, b.b)};
}


static bad_forceinline f32x8 f32x8_max(f32x8_vec0 a, f32x8_vec1 b)
{
    return (f32x8){f32x4_max(a.a, b.a), f32x4_max(a.b, b.b)};
}


static bad_forceinline f32x8 f32x8_abs(f32x8_vec0 a)
{
    const mask128 a_mask = f32x8_cast_mask128(a);

    return (f32x8)
    {
        mask128_cast_f32x4(mask128_and(f32x4_cast_mask128(a.a), abs_mask)),
        mask128_cast_f32x4(mask128_and(f32x4_cast_mask128(a.b), abs_mask))
    };
}


static bad_forceinline f32x8 f32x8_neg(f32x8_vec0 a)
{
    const mask128 neg_mask = mask128_highbit32();

    return (f32x8)
    {
         mask128_cast_f32x4(mask128_xor(f32x4_cast_mask128(a.a), neg_mask));,
         mask128_cast_f32x4(mask128_xor(f32x4_cast_mask128(a.b), neg_mask));
    };
}


static bad_forceinline f32x8 f32x8_mod(f32x8_vec0 a, f32x8_vec1 b)
{
    return (f32x8){f32x4_mod(a.a, b.a), f32x4_mod(a.b, b.b)};
}


static bad_forceinline f32x8 f32x8_trunc(f32x8_vec0 a)
{
    return (f32x8){f32x4_trunc(a.a), f32x4_trunc(a.b)};
}


static bad_forceinline f32x8 f32x8_round(f32x8_vec0 a)
{
    return (f32x8){f32x4_round(a.a), f32x4_round(a.b)};
}


static bad_forceinline f32x8 f32x8_floor(f32x8_vec0 a)
{
    const mask128 one = f32x8_cast_mask128(f32x8_one());

    f32x4 res_a, res_b;
    
    res_a             = f32x4_trunc(a.a);
    mask128 greater   = f32x4_gt(a.a, res_a)
    mask128 decrement = mask128_and(greater, one);
    res_a             = f32x4_sub(res_a, mask128_cast_f32x4(decrement));

    res_b             = f32x4_trunc(a.b);
    greater           = f32x4_gt(a.a, res_b)
    decrement         = mask128_and(greater, one);
    res_b             = f32x4_sub(res_b, mask128_cast_f32x4(decrement));

    return (f32x8){res_a, res_b};
}


static bad_forceinline f32x8 f32x8_ceil(f32x8_vec0 a)
{
    const mask128 one = f32x8_cast_mask128(f32x8_one());
    f32x4 res_a, res_b;

    res_a             = f32x8_trunc(a);
    mask128 less      = f32x4_lt(a, res_a);
    mask128 increment = mask128_and(less, one);
    res_a             = f32x4_add(res_a, mask128_cast_f32x4(increment));

    res_b             = f32x8_trunc(a);
    less              = f32x4_lt(a, res_b);
    increment         = mask128_and(less, one);
    res_b             = f32x4_add(res_b, mask128_cast_f32x4(increment));

    return (f32x8){res_a, res_b};
}


static bad_forceinline f32x8 bad_veccall f32x8_clamp(f32x8_vec0 a, f32x8_vec1 min, f32x8_vec2 max)
{
    return (f32x8)
    {
        f32x4_min(f32x4_max(a.a, min.a), max.a),
        f32x4_min(f32x4_max(a.b, min.b), max.b)
    };
}


static bad_forceinline f32x8 bad_veccall f32x8_mul_add(f32x8_vec0 a, f32x8_vec1 b, f32x8_vec2 c)
{
    return (f32x8){f32x4_mul_add(a.a, b.a, c.a), f32x4_mul_add(a.b, b.b, c.b)};
}


static bad_forceinline f32x8 bad_veccall f32x8_mul_sub(f32x8_vec0 a, f32x8_vec1 b, f32x8_vec2 c)
{
    return (f32x8){f32x8_mul_sub(a.a, b.a, c.a), f32x8_mul_sub(a.b, b.b, c.b)};
}


static bad_forceinline f32x8 bad_veccall f32x8_nmul_add(f32x8_vec0 a, f32x8_vec1 b, f32x8_vec2 c)
{
    return (f32x8){f32x8_nmul_add(a.a, b.a, c.a), f32x8_nmul_add(a.b, b.b, c.b)};
}


static bad_forceinline f32x8 bad_veccall f32x8_nmul_sub(f32x8_vec0 a, f32x8_vec1 b, f32x8_vec2 c)
{
    return (f32x8){f32x8_nmul_sub(a.a, b.a, c.a), f32x8_nmul_sub(a.b, b.b, c.b)};
}


// ============ Comparison ============
static bad_forceinline mask128 f32x8_neq(f32x8_vec0 a, f32x8_vec1 b)
{
    return (f32x8){f32x4_neq(a.a, b.a), f32x4_neq(a.b, b.b)};
}


static bad_forceinline mask128 f32x8_eq(f32x8_vec0 a, f32x8_vec1 b)
{
    return (f32x8){f32x4_eq(a.a, b.a), f32x4_eq(a.b, b.b)};
}


static bad_forceinline mask128 f32x8_ge(f32x8_vec0 a, f32x8_vec1 b)
{
    return (f32x8){f32x4_ge(a.a, b.a), f32x4_ge(a.b, b.b)};
}


static bad_forceinline mask128 f32x8_gt(f32x8_vec0 a, f32x8_vec1 b)
{
    return (f32x8){f32x4_gt(a.a, b.a), f32x4_gt(a.b, b.b)};
}


static bad_forceinline mask128 f32x8_le(f32x8_vec0 a, f32x8_vec1 b)
{
    return (f32x8){f32x4_le(a.a, b.a), f32x4_le(a.b, b.b)};
}


static bad_forceinline mask128 f32x8_lt(f32x8_vec0 a, f32x8_vec1 b)
{
    return (f32x8){f32x4_lt(a.a, b.a), f32x4_lt(a.b, b.b)};
}


// ======= Selection & swizzling ========
static bad_forceinline mask128 f32x8_is_nan(f32x8_vec0 a)
{
    return (f32x8){f32x4_is_nan(a.a, a.a), f32x4_is_nan(a.b, a.b)};
}


static bad_forceinline mask128 f32x8_is_infinite(f32x8_vec0 a)
{
    const mask128 abs_mask = mask128_value32();
    const mask128 inf_mask = mask128_exponent32();

    return (f32x8)
    {
        mask128_eq(mask128_and(f32x8_cast_mask128(a.a), abs_mask), inf_mask),
        mask128_eq(mask128_and(f32x8_cast_mask128(a.b), abs_mask), inf_mask)
    };
}


static bad_forceinline mask128 f32x8_is_finite(f32x8_vec0 a)
{
    const mask128 exp_mask = mask128_exponent32();

    return (f32x8)
    {
        mask128_neq(mask128_and(f32x8_cast_mask128(a.a), exp_mask), exp_mask),
        mask128_neq(mask128_and(f32x8_cast_mask128(a.b), exp_mask), exp_mask)
    };
}