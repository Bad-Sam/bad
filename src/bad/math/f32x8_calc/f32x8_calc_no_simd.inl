// ==== Arithmetic & math functions ===
static bad_forceinline f32x8 f32x8_add(f32x8 a, f32x8 b)
{
    return (f32x8){f32x4_add(a.a, b.a), f32x4_add(a.b, b.b)};
}


static bad_forceinline f32x8 f32x8_sub(f32x8 a, f32x8 b)
{
    return (f32x8){f32x4_sub(a.a, b.a), f32x4_sub(a.b, b.b)};
}


static bad_forceinline f32x8 f32x8_mul(f32x8 a, f32x8 b)
{
    return (f32x8){f32x4_mul(a.a, b.a), f32x4_mul(a.b, b.b)};
}


static bad_forceinline f32x8 f32x8_div(f32x8 a, f32x8 b)
{
    return (f32x8){f32x4_div(a.a, b.a), f32x4_div(a.b, b.b)};
}


static bad_forceinline f32 f32x8_hadd4(f32x8 a)
{
    f32x8 res;

    res.a[0] = f32x4_sum4(a);

    return res;
}


static bad_forceinline f32 f32x4_sum4(f32x8 a)
{
    return f32x4_sum4(a.a) + f32x4_sum4(a.b);
}


static bad_forceinline f32x8 f32x8_rcp(f32x8 a)
{
    return (f32x8){f32x4_rcp(a.a), f32x4_rcp(a.b)};
}


static bad_forceinline f32x8 f32x8_sqrt(f32x8 a)
{
    return (f32x8){f32x4_sqrt(a.a), f32x4_sqrt(a.b)};
}


static bad_forceinline f32x8 f32x8_rsqrt(f32x8 a)
{
    return (f32x8){f32x4_rsqrt(a.a), f32x4_rsqrt(a.b)};
}


static bad_forceinline f32x8 f32x8_min(f32x8 a, f32x8 b)
{
    return (f32x8){f32x4_min(a.a, b.a), f32x4_min(a.b, b.b)};
}


static bad_forceinline f32x8 f32x8_max(f32x8 a, f32x8 b)
{
    return (f32x8){f32x4_max(a.a, b.a), f32x4_max(a.b, b.b)};
}


static bad_forceinline f32x8 f32x8_value(f32x8 a)
{
    const u32 value_mask = 0x7FFFFFFF;
    mask128   a_mask     = f32x4_as_mask128(a.a);
    mask128   b_mask     = f32x4_as_mask128(a.b);

    a_mask.x &= value_mask;
    a_mask.y &= value_mask;
    a_mask.z &= value_mask;
    a_mask.w &= value_mask;
    b_mask.x &= value_mask;
    b_mask.y &= value_mask;
    b_mask.z &= value_mask;
    b_mask.w &= value_mask;

    return (f32x8){mask128_as_f32x4(a_mask), mask128_as_f32x4(b_mask)};
}


static bad_forceinline f32x8 f32x8_sign(f32x8 a)
{
    const u32 sign_mask = 0x80000000;
    const u32 one_mask  = 0x3F800000;
    mask128   a_mask    = f32x4_as_mask128(a.a);
    mask128   b_mask    = f32x4_as_mask128(a.b);

    a_mask.x = (a_mask.x & sign_mask) | one_mask;
    a_mask.y = (a_mask.y & sign_mask) | one_mask;
    a_mask.z = (a_mask.z & sign_mask) | one_mask;
    a_mask.w = (a_mask.w & sign_mask) | one_mask;
    b_mask.x = (b_mask.x & sign_mask) | one_mask;
    b_mask.y = (b_mask.y & sign_mask) | one_mask;
    b_mask.z = (b_mask.z & sign_mask) | one_mask;
    b_mask.w = (b_mask.w & sign_mask) | one_mask;

    return (f32x8){mask128_as_f32x4(a_mask), mask128_as_f32x4(b_mask)};
}


static bad_forceinline f32x8 f32x8_neg(f32x8 a)
{
    const u32 neg_mask = 0x80000000;
    mask128   a_mask   = f32x4_as_mask128(a.a);
    mask128   b_mask   = f32x4_as_mask128(a.b);

    a_mask.x ^= neg_mask;
    a_mask.y ^= neg_mask;
    a_mask.z ^= neg_mask;
    a_mask.w ^= neg_mask;
    b_mask.x ^= neg_mask;
    b_mask.y ^= neg_mask;
    b_mask.z ^= neg_mask;
    b_mask.w ^= neg_mask;

    return (f32x8){mask128_as_f32x4(a_mask), mask128_as_f32x4(b_mask)};
}


static bad_forceinline f32x8 bad_veccall f32x8_frac(f32x8 a)
{
    return f32x8_sub(a, f32x8_trunc(a));
}


static bad_forceinline f32x8 f32x8_mod(f32x8 a, f32x8 b)
{
    return (f32x8){f32x4_mod(a.a, b.a), f32x4_mod(a.b, b.b)};
}


static bad_forceinline f32x8 f32x8_trunc(f32x8 a)
{
    return (f32x8){f32x4_trunc(a.a), f32x4_trunc(a.b)};
}


static bad_forceinline f32x8 f32x8_round(f32x8 a)
{
    return (f32x8){f32x4_round(a.a), f32x4_round(a.b)};
}


static bad_forceinline f32x8 f32x8_floor(f32x8 a)
{
    const u32 one = 0x3F800000;
    
    f32x4 res_a       = f32x4_trunc(a.a);
    mask128 decrement = f32x4_gt(a.a, res_a)
    decrement.x      &= one;
    decrement.y      &= one;
    decrement.z      &= one;
    decrement.w      &= one;
    res_a             = f32x4_sub(res_a, mask128_as_f32x4(decrement));

    f32x4 res_b       = f32x4_trunc(a.b);
    decrement         = f32x4_gt(a.b, res_b)
    decrement.x      &= one;
    decrement.y      &= one;
    decrement.z      &= one;
    decrement.w      &= one;
    res_b             = f32x4_sub(res_b, mask128_as_f32x4(decrement));

    return (f32x8){res_a, res_b};
}


static bad_forceinline f32x8 f32x8_ceil(f32x8 a)
{
    const u32 one = 0x3F800000;

    f32x4 res_a       = f32x8_trunc(a.a);
    mask128 increment = f32x4_lt(a.a, res_a);
    increment.x      &= one;
    increment.y      &= one;
    increment.z      &= one;
    increment.w      &= one;
    res_a             = f32x4_add(res_a, mask128_as_f32x4(increment));

    f32x4 res_b       = f32x8_trunc(a.b);
    increment         = f32x4_lt(a.b, res_b);
    increment.x      &= one;
    increment.y      &= one;
    increment.z      &= one;
    increment.w      &= one;
    res_b             = f32x4_add(res_b, mask128_as_f32x4(increment));

    return (f32x8){res_a, res_b};
}


static bad_forceinline f32x8 bad_veccall f32x8_clamp(f32x8 a, f32x8 min, f32x8 max)
{
    return (f32x8)
    {
        f32x4_min(f32x4_max(a.a, min.a), max.a),
        f32x4_min(f32x4_max(a.b, min.b), max.b)
    };
}


static bad_forceinline f32x8 bad_veccall f32x8_lerp(f32x8 a, f32x8 b, f32x8 t)
{
    f32x8 res;

    res.a[0] = (1.f - t.a[0]) * a.a[0] + t.a[0] * b.a[0];
    res.a[1] = (1.f - t.a[1]) * a.a[1] + t.a[1] * b.a[1];
    res.a[2] = (1.f - t.a[2]) * a.a[2] + t.a[2] * b.a[2];
    res.a[3] = (1.f - t.a[3]) * a.a[3] + t.a[3] * b.a[3];
    
    res.b[0] = (1.f - t.b[0]) * a.b[0] + t.b[0] * b.b[0];
    res.b[1] = (1.f - t.b[1]) * a.b[1] + t.b[1] * b.b[1];
    res.b[2] = (1.f - t.b[2]) * a.b[2] + t.b[2] * b.b[2];
    res.b[3] = (1.f - t.b[3]) * a.b[3] + t.b[3] * b.b[3];

    return res;
}


// ========== Trigonometry ===========
static bad_forceinline f32x8 bad_veccall f32x8_cos(f32x8 a)
{
    return (f32x8){f32x4_cos(a.a), f32x4_cos(a.b)};
}


static bad_inline f32x8 bad_veccall f32x8_cos_0_halfpi(f32x8 a)
{
    return (f32x8){f32x4_cos_0_halfp(a.a), f32x4_cos_0_halfp(a.b)};
}


static bad_forceinline f32x8 bad_veccall f32x8_sin(f32x8 a)
{
    return (f32x8){f32x8_sin(a.a), f32x8_sin(a.b)};
}


static bad_inline f32x8 bad_veccall f32x8_sin_npi_pi(f32x8 a)
{
    return (f32x8){f32x8_sin_npi_pi(a.a), f32x8_sin_npi_pi(a.b)};
}


static bad_forceinline f32x8 bad_veccall f32x8_tan(f32x8 a)
{
    return (f32x8){f32x8_tan(a.a), f32x8_tan(a.b)};
}


static bad_inline f32x8 bad_veccall f32x8_acos(f32x8 a)
{
    return (f32x8){f32x4_acos(a.a), f32x4_acos(a.b)};
}


// ======== Fused operations ========
static bad_forceinline f32x8 bad_veccall f32x8_mul_add(f32x8 a, f32x8 b, f32x8 c)
{
    return (f32x8){f32x4_mul_add(a.a, b.a, c.a), f32x4_mul_add(a.b, b.b, c.b)};
}


static bad_forceinline f32x8 bad_veccall f32x8_mul_sub(f32x8 a, f32x8 b, f32x8 c)
{
    return (f32x8){f32x8_mul_sub(a.a, b.a, c.a), f32x8_mul_sub(a.b, b.b, c.b)};
}


static bad_forceinline f32x8 bad_veccall f32x8_nmul_add(f32x8 a, f32x8 b, f32x8 c)
{
    return (f32x8){f32x8_nmul_add(a.a, b.a, c.a), f32x8_nmul_add(a.b, b.b, c.b)};
}


static bad_forceinline f32x8 bad_veccall f32x8_nmul_sub(f32x8 a, f32x8 b, f32x8 c)
{
    return (f32x8){f32x8_nmul_sub(a.a, b.a, c.a), f32x8_nmul_sub(a.b, b.b, c.b)};
}


// ============ Comparison ============
static bad_forceinline mask128 f32x8_neq(f32x8 a, f32x8 b)
{
    return (f32x8){f32x4_neq(a.a, b.a), f32x4_neq(a.b, b.b)};
}


static bad_forceinline mask128 f32x8_eq(f32x8 a, f32x8 b)
{
    return (f32x8){f32x4_eq(a.a, b.a), f32x4_eq(a.b, b.b)};
}


static bad_forceinline mask128 f32x8_ge(f32x8 a, f32x8 b)
{
    return (f32x8){f32x4_ge(a.a, b.a), f32x4_ge(a.b, b.b)};
}


static bad_forceinline mask128 f32x8_gt(f32x8 a, f32x8 b)
{
    return (f32x8){f32x4_gt(a.a, b.a), f32x4_gt(a.b, b.b)};
}


static bad_forceinline mask128 f32x8_le(f32x8 a, f32x8 b)
{
    return (f32x8){f32x4_le(a.a, b.a), f32x4_le(a.b, b.b)};
}


static bad_forceinline mask128 f32x8_lt(f32x8 a, f32x8 b)
{
    return (f32x8){f32x4_lt(a.a, b.a), f32x4_lt(a.b, b.b)};
}


// ======= Selection & swizzling ========
static bad_forceinline mask128 f32x8_is_nan(f32x8 a)
{
    return (f32x8){f32x4_is_nan(a.a, a.a), f32x4_is_nan(a.b, a.b)};
}


static bad_forceinline mask128 f32x8_is_infinite(f32x8 a)
{
    const u32 value_mask = 0x7FFFFFFF;
    const u32 inf_mask   = 0x7F800000;
    mask128   a_mask     = f32x4_as_mask128(a.a);
    mask128   b_mask     = f32x4_as_mask128(a.b);

    a_mask.x &= value_mask;
    a_mask.y &= value_mask;
    a_mask.z &= value_mask;
    a_mask.w &= value_mask;
    b_mask.x &= value_mask;
    b_mask.y &= value_mask;
    b_mask.z &= value_mask;
    b_mask.w &= value_mask;

    a_mask.x = (a_mask.x == inf_mask) ? mask128_all_bits_set : mask128_all_bits_clear;
    a_mask.y = (a_mask.y == inf_mask) ? mask128_all_bits_set : mask128_all_bits_clear;
    a_mask.z = (a_mask.z == inf_mask) ? mask128_all_bits_set : mask128_all_bits_clear;
    a_mask.w = (a_mask.w == inf_mask) ? mask128_all_bits_set : mask128_all_bits_clear;
    b_mask.x = (b_mask.x == inf_mask) ? mask128_all_bits_set : mask128_all_bits_clear;
    b_mask.y = (b_mask.y == inf_mask) ? mask128_all_bits_set : mask128_all_bits_clear;
    b_mask.z = (b_mask.z == inf_mask) ? mask128_all_bits_set : mask128_all_bits_clear;
    b_mask.w = (b_mask.w == inf_mask) ? mask128_all_bits_set : mask128_all_bits_clear;

    return (f32x8){mask128_as_f32x4(a_mask), mask128_as_f32x4(b_mask)};
}


static bad_forceinline mask128 f32x8_is_finite(f32x8 a)
{
    const u32 exp_mask = 0x7F800000;
    mask128   a_mask   = f32x4_as_mask128(a.a);
    mask128   b_mask   = f32x4_as_mask128(a.b);

    a_mask.x &= exp_mask;
    a_mask.y &= exp_mask;
    a_mask.z &= exp_mask;
    a_mask.w &= exp_mask;
    b_mask.x &= exp_mask;
    b_mask.y &= exp_mask;
    b_mask.z &= exp_mask;
    b_mask.w &= exp_mask;

    a_mask.x = (a_mask.x != exp_mask) ? mask128_all_bits_set : mask128_all_bits_clear;
    a_mask.y = (a_mask.y != exp_mask) ? mask128_all_bits_set : mask128_all_bits_clear;
    a_mask.z = (a_mask.z != exp_mask) ? mask128_all_bits_set : mask128_all_bits_clear;
    a_mask.w = (a_mask.w != exp_mask) ? mask128_all_bits_set : mask128_all_bits_clear;
    b_mask.x = (b_mask.x != exp_mask) ? mask128_all_bits_set : mask128_all_bits_clear;
    b_mask.y = (b_mask.y != exp_mask) ? mask128_all_bits_set : mask128_all_bits_clear;
    b_mask.z = (b_mask.z != exp_mask) ? mask128_all_bits_set : mask128_all_bits_clear;
    b_mask.w = (b_mask.w != exp_mask) ? mask128_all_bits_set : mask128_all_bits_clear;

    return (f32x8){mask128_as_f32x4(a_mask), mask128_as_f32x4(b_mask)};
}