// =========== Arithmetic ===========
static bad_forceinline f32x8 bad_veccall f32x8_add(f32x8 a, f32x8 b)
{
    return (f32x8){f32x4_add(a.a, b.a), f32x4_add(a.b, b.b)};
}


static bad_forceinline f32x8 bad_veccall f32x8_sub(f32x8 a, f32x8 b)
{
    return (f32x8){f32x4_sub(a.a, b.a), f32x4_sub(a.b, b.b)};
}


static bad_forceinline f32x8 bad_veccall f32x8_mul(f32x8 a, f32x8 b)
{
    return (f32x8){f32x4_mul(a.a, b.a), f32x4_mul(a.b, b.b)};
}


static bad_forceinline f32x8 bad_veccall f32x8_div(f32x8 a, f32x8 b)
{
    return (f32x8){f32x4_div(a.a, b.a), f32x4_div(a.b, b.b)};
}


static bad_forceinline f32x8 bad_veccall f32x8_hadd4(f32x8 a)
{
    f32x4 hadd8 = f32x4_add(f32x4_hadd4(a.a), f32x4_hadd4(a.b));

    return (f32x8){hadd4, hadd4};
}

static bad_forceinline f32 bad_veccall f32x4_sum4(f32x8 a)
{
    return f32x4_sum4(a.a) + f32x4_sum4(a.b);
}


// ====== Advanced arithmetic =======
static bad_forceinline f32x8 bad_veccall f32x8_rcp(f32x8 a)
{
    return (f32x8){f32x4_rcp(a.a), f32x4_rcp(a.b)};
}


static bad_forceinline f32x8 bad_veccall f32x8_sqrt(f32x8 a)
{
    return (f32x8){f32x4_sqrt(a.a), f32x4_sqrt(a.b)};
}


static bad_forceinline f32x8 bad_veccall f32x8_rsqrt(f32x8 a)
{
    return (f32x8){f32x4_rsqrt(a.a), f32x4_rsqrt(a.b)};
}


static bad_forceinline f32x8 bad_veccall f32x8_min(f32x8 a, f32x8 b)
{
    return (f32x8){f32x4_min(a.a, b.a), f32x4_min(a.b, b.b)};
}


static bad_forceinline f32x8 bad_veccall f32x8_max(f32x8 a, f32x8 b)
{
    return (f32x8){f32x4_max(a.a, b.a), f32x4_max(a.b, b.b)};
}


static bad_forceinline f32x8 bad_veccall f32x8_abs(f32x8 a)
{
    return (f32x8){f32x4_abs(a.a), f32x4_abs(a.b)};
}


static bad_forceinline f32x8 bad_veccall f32x8_sign(f32x8 a)
{
    mask128 b_sign = vceqq_u32(vreinterpretq_u32_f32(a.a), vreinterpretq_u32_f32(a.a));
    mask128 one    = vshlq_n_u32(vshrq_n_u32(b_sign, 25), 23);
    mask128 a_sign = mask128_keep_highbit32(f32x4_as_mask128(a.a));

    b_sign = mask128_keep_highbit32(f32x4_as_mask128(a.b));

    return (f32x8)
    {
        vreinterpretq_f32_u32(vorq_u32(one, a_sign)),
        vreinterpretq_f32_u32(vorq_u32(one, b_sign))
    };
}


static bad_forceinline f32x8 bad_veccall f32x8_neg(f32x8 a)
{
    return (f32x8){f32x4_neg(a.a, b.a), f32x4_neg(a.b, b.b)};
}


static bad_forceinline f32x8 bad_veccall f32x8_frac(f32x8 a)
{
    return f32x8_sub(a, f32x8_trunc(a));
}


static bad_forceinline f32x8 bad_veccall f32x8_mod(f32x8 a, f32x8 b)
{
    return (f32x8){f32x4_mod(a.a, b.a), f32x4_mod(a.b, b.b)};
}


static bad_forceinline f32x8 bad_veccall f32x8_trunc(f32x8 a)
{
    return (f32x8){f32x4_trunc(a.a), f32x4_trunc(a.b)};
}


static bad_forceinline f32x8 bad_veccall f32x8_round(f32x8 a)
{
    return (f32x8){f32x4_round(a.a), f32x4_round(a.b)};
}


static bad_forceinline f32x8 bad_veccall f32x8_floor(f32x8 a)
{
    return (f32x8){f32x4_floor(a.a), f32x4_floor(a.b)};
}


static bad_forceinline f32x8 bad_veccall f32x8_ceil(f32x8 a)
{
    return (f32x8){f32x4_ceil(a.a), f32x4_ceil(a.b)};
}


static bad_forceinline f32x8 bad_veccall f32x8_clamp(f32x8 a, f32x8 min, f32x8 max)
{
    return (f32x8){f32x4_clamp(a.a), f32x4_clamp(a.b)};
}


static bad_forceinline f32x8 bad_veccall f32x8_lerp(f32x8 a, f32x8 b, f32x8 t)
{
    f32x4 one = f32x4_one();

    return (f32x8)
    {
        f32x4_add(f32x4_mul(f32x4_sub(one, t.a), a.a), f32x4_mul(t.a, b.a)),
        f32x4_add(f32x4_mul(f32x4_sub(one, t.b), a.b), f32x4_mul(t.b, b.b))
    };
}


static bad_inline f32x8 bad_veccall f32x8_copysign(f32x8 a, f32x8 reference_sign)
{
    return (f32x8)
    {
        f32x4_copysign(a.a, reference_sign.a),
        f32x4_copysign(a.b, reference_sign.b)
    };
}


static bad_inline f32x8 bad_veccall f32x8_mul_by_sign(f32x8 a, f32x8 reference_sign)
{
    return (f32x8)
    {
        f32x4_mul_by_sign(a.a, reference_sign.a),
        f32x4_mul_by_sign(a.b, reference_sign.b)
    };
}


// ========== Trigonometry ===========
static bad_inline f32x8 bad_veccall f32x8_cos(f32x8 a)
{
    return (f32x8){f32x4_cos(a.a), f32x4_cos(a.b)};
}


static bad_inline f32x8 bad_veccall f32x8_cos_0_halfpi(f32x8 a)
{
    return (f32x8){f32x4_cos_0_halfp(a.a), f32x4_cos_0_halfp(a.b)};
}


static bad_inline f32x8 bad_veccall f32x8_sin(f32x8 a)
{
    return (f32x8){f32x4_sin(a.a), f32x4_sin(a.b)};
}


static bad_inline f32x8 bad_veccall f32x8_sin_npi_pi(f32x8 a)
{
    return (f32x8){f32x8_sin_npi_pi(a.a), f32x8_sin_npi_pi(a.b)};
}


static bad_inline f32x8 bad_veccall f32x8_tan(f32x8 a)
{
    return (f32x8){f32x4_tan(a.a), f32x4_tan(a.b)};
}


static bad_inline f32x8 bad_veccall f32x8_acos(f32x8 a)
{
    return (f32x8){f32x4_acos(a.a), f32x4_acos(a.b)};
}


// ======== Fused operations ========
// a * b + c
static bad_forceinline f32x8 bad_veccall f32x8_mul_add(f32x8 a, f32x8 b, f32x8 c)
{
    return (f32x8){f32x4_mul_add(a.a, b.a, c.a), f32x4_mul_add(a.b, b.b, c.b)};
}


// a * b - c
static bad_forceinline f32x8 bad_veccall f32x8_mul_sub(f32x8 a, f32x8 b, f32x8 c)
{
    return (f32x8){f32x4_mul_sub(a.a, b.a, c.a), f32x4_mul_sub(a.b, b.b, c.b)};
}


// -a * b + c
static bad_forceinline f32x8 bad_veccall f32x8_nmul_add(f32x8 a, f32x8 b, f32x8 c)
{
    return (f32x8){f32x4_mul_sub(a.a, b.a, c.a), f32x4_mul_sub(a.b, b.b, c.b)};
}


// -a * b - c
static bad_forceinline f32x8 bad_veccall f32x8_nmul_sub(f32x8 a, f32x8 b, f32x8 c)
{
    return (f32x8){f32x4_nmul_sub(a.a, b.a, c.a), f32x4_nmul_sub(a.b, b.b, c.b)};
}


// ============ Comparison ============
static bad_forceinline mask128 bad_veccall f32x8_neq(f32x8 a, f32x8 b)
{
    return (f32x8){f32x4_neq(a.a, b.a), f32x4_neq(a.b, b.b)};
}


static bad_forceinline mask128 bad_veccall f32x8_eq(f32x8 a, f32x8 b)
{
    return (f32x8){f32x4_eq(a.a, b.a), f32x4_eq(a.b, b.b)};
}


static bad_forceinline mask128 bad_veccall f32x8_ge(f32x8 a, f32x8 b)
{
    return (f32x8){f32x4_ge(a.a, b.a), f32x4_ge(a.b, b.b)};
}


static bad_forceinline mask128 bad_veccall f32x8_gt(f32x8 a, f32x8 b)
{
    return (f32x8){f32x4_gt(a.a, b.a), f32x4_gt(a.b, b.b)};
}


static bad_forceinline mask128 bad_veccall f32x8_le(f32x8 a, f32x8 b)
{
    return (f32x8){f32x4_le(a.a, b.a), f32x4_le(a.b, b.b)};
}


static bad_forceinline mask128 bad_veccall f32x8_lt(f32x8 a, f32x8 b)
{
    return (f32x8){f32x4_lt(a.a, b.a), f32x4_lt(a.b, b.b)};
}



// ======= Selection & tests ========
static bad_forceinline mask128 bad_veccall f32x8_is_nan(f32x8 a)
{
    return (f32x8){f32x4_is_nan(a.a), f32x4_is_nan(a.b)};
}


static bad_forceinline mask128 bad_veccall f32x8_is_infinite(f32x8 a)
{
    // +inf is 0x7F800000, -inf is 0xFF800000
    mask128 inf_mask   = mask128_all1();
    mask128 value_mask = vshrq_n_u32(all1_mask, 1);
            inf_mask   = vshrq_n_u32(vshlq_n_u32(all1_mask, 24), 1);

    return (f32x8)
    {
        vceqq_f32(vandq_u32(value_mask, vreinterpretq_u32_f32(a.a)), inf_mask),
        vceqq_f32(vandq_u32(value_mask, vreinterpretq_u32_f32(a.b)), inf_mask)
    };
}


static bad_forceinline mask128 bad_veccall f32x8_is_finite(f32x8 a)
{
    mask128 exp = mask128_exponent32();

    return (f32x8)
    {
        vmvnq_u32(vceqq_f32(vandq_u32(vreinterpretq_u32_f32(a.a), exp), exp)),
        vmvnq_u32(vceqq_f32(vandq_u32(vreinterpretq_u32_f32(a.b), exp), exp))
    };
}