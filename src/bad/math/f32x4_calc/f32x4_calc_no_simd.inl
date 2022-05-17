// ==== Arithmetic & math functions ===
static bad_forceinline f32x4 f32x4_add(f32x4 a, f32x4 b)
{
    f32x4 res;

    res.x = a.x + b.x;
    res.y = a.y + b.y;
    res.z = a.z + b.z;
    res.w = a.w + b.w;

    return res;
}


static bad_forceinline f32x4 f32x4_sub(f32x4 a, f32x4 b)
{
    f32x4 res;

    res.x = a.x - b.x;
    res.y = a.y - b.y;
    res.z = a.z - b.z;
    res.w = a.w - b.w;

    return res;
}


static bad_forceinline f32x4 f32x4_mul(f32x4 a, f32x4 b)
{
    f32x4 res;

    res.x = a.x * b.x;
    res.y = a.y * b.y;
    res.z = a.z * b.z;
    res.w = a.w * b.w;

    return res;
}


static bad_forceinline f32x4 f32x4_div(f32x4 a, f32x4 b)
{
    f32x4 res;

    res.x = a.x / b.x;
    res.y = a.y / b.y;
    res.z = a.z / b.z;
    res.w = a.w / b.w;

    return res;
}


static bad_forceinline f32x4 f32x4_hadd3(f32x4 a)
{
    return (f32x4)
    {
        f32x4_sum3(a),
        a.y,
        a.z,
        a.w
    };
}


static bad_forceinline f32x4 f32x4_hadd4(f32x4 a)
{
    return (f32x4)
    {
        f32x4_sum4(a),
        a.y,
        a.z,
        a.w
    };
}


static bad_forceinline f32 f32x4_sum3(f32x4 a)
{
    return a.x + a.y + a.z;
}


static bad_forceinline f32 f32x4_sum4(f32x4 a)
{
    return a.x + a.y + a.z + a.w;
}


static bad_forceinline f32x4 f32x4_rcp(f32x4 a)
{
    f32x4 res;

    res.x = 1.f / a.x;
    res.y = 1.f / a.y;
    res.z = 1.f / a.z;
    res.w = 1.f / a.w;

    return res;
}


static bad_forceinline f32x4 f32x4_sqrt(f32x4 a)
{
    return f32x4_sqrt(a);
}


static bad_forceinline f32x4 f32x4_rsqrt(f32x4 a)
{
    return f32_rcp(f32x4_sqrt(a));
}


static bad_forceinline f32x4 f32x4_min(f32x4 a, f32x4 b)
{
    f32x4 res;

    res.x = f32x_min(a, b);
    res.y = f32x_min(a, b);
    res.z = f32x_min(a, b);
    res.w = f32x_min(a, b);

    return res;
}


static bad_forceinline f32x4 f32x4_max(f32x4 a, f32x4 b)
{
    f32x4 res;

    res.x = f32x_max(a, b);
    res.y = f32x_max(a, b);
    res.z = f32x_max(a, b);
    res.w = f32x_max(a, b);

    return res;
}


static bad_forceinline f32x4 f32x4_abs(f32x4 a)
{
    const u32 value_mask = 0x7FFFFFFF;
    
    mask128 a_mask = f32x4_as_mask128(a);

    a_mask.x &= value_mask;
    a_mask.y &= value_mask;
    a_mask.z &= value_mask;
    a_mask.w &= value_mask;

    return mask128_as_f32x4(a_mask);
}


static bad_forceinline f32x4 f32x4_sign(f32x4 a)
{
    const u32 sign_mask = 0x80000000;
    const u32 one_mask  = 0x3F800000;
    mask128   a_mask    = f32x4_as_mask128(a);

    a_mask.x = (a_mask.x & sign_mask) | one_mask;
    a_mask.y = (a_mask.y & sign_mask) | one_mask;
    a_mask.z = (a_mask.z & sign_mask) | one_mask;
    a_mask.w = (a_mask.w & sign_mask) | one_mask;

    return mask128_as_f32x4(a_mask);
}


static bad_forceinline f32x4 f32x4_neg(f32x4 a)
{
    const u32 sign_mask = 0x80000000;
    mask128   a_mask    = f32x4_as_mask128(a);

    a_mask.x ^= sign_mask;
    a_mask.y ^= sign_mask;
    a_mask.z ^= sign_mask;
    a_mask.w ^= sign_mask;
    
    return mask128_as_f32x4(a_mask);
}


static bad_forceinline f32x4 bad_veccall f32x4_frac(f32x4 a)
{
    return f32x4_sub(a, f32x4_trunc(a));
}


static bad_forceinline f32x4 f32x4_mod(f32x4 a, f32x4 b)
{
    a.x = f32_mod(a.x, b.x);
    a.y = f32_mod(a.y, b.y);
    a.z = f32_mod(a.z, b.z);
    a.w = f32_mod(a.w, b.w);

    return a;
}


static bad_forceinline f32x4 f32x4_trunc(f32x4 a)
{
    f32x4 res;

    res.x = (f32)(s32)a.x;
    res.y = (f32)(s32)a.y;
    res.z = (f32)(s32)a.z;
    res.w = (f32)(s32)a.w;

    return res;
}


static bad_forceinline f32x4 f32x4_round(f32x4 a)
{
    f32x4   sign_a  = f32x4_sign(a);
    f32x4   trunc_a = f32x4_trunc(a);
    f32x4   offset  = f32x4_mul(sign_a, f32x4_sub(a, trunc_a));
    
    offset.x = (offset.x > .5f) ? 1.f : .0f;
    offset.y = (offset.y > .5f) ? 1.f : .0f;
    offset.z = (offset.z > .5f) ? 1.f : .0f;
    offset.w = (offset.w > .5f) ? 1.f : .0f;

    return f32x4_mul_add(sign_a, offset, trunc_a);
}


static bad_forceinline f32x4 f32x4_floor(f32x4 a)
{
    a.x = f32_floor(a.x);
    a.y = f32_floor(a.y);
    a.z = f32_floor(a.z);
    a.w = f32_floor(a.w);

    return a;
}


static bad_forceinline f32x4 f32x4_ceil(f32x4 a)
{
    a.x = f32_ceil(a.x);
    a.y = f32_ceil(a.y);
    a.z = f32_ceil(a.z);
    a.w = f32_ceil(a.w);

    return a;
}


static bad_forceinline f32x4 f32x4_clamp(f32x4 a, f32x4 min, f32x4 max)
{
    return f32x4_min(f32x4_max(a, min), max);
}


static bad_forceinline f32x4 f32x4_lerp(f32x4 a, f32x4 b, f32x4 t)
{
    f32x4 one_min_t = f32x4_sub(f32x4_one(), t);

    return f32x4_mul_add(a, one_min_t, f32x4_mul(b, t));
}


static bad_forceinline f32x4 bad_veccall f32x4_copysign(f32x4 a, f32x4 reference_sign)
{
    mask128 res;
    mask128 a_mask    = f32x4_as_mask128(a);
    mask128 sign_mask = f32x4_as_mask128(reference_sign);

    res.x = (a_mask.x & 0x7FFFFFFF) | (sign_mask.x & 0x80000000);
    res.y = (a_mask.y & 0x7FFFFFFF) | (sign_mask.y & 0x80000000);
    res.z = (a_mask.z & 0x7FFFFFFF) | (sign_mask.z & 0x80000000);
    res.w = (a_mask.w & 0x7FFFFFFF) | (sign_mask.w & 0x80000000);

    return mask128_as_f32x4(res);
}


static bad_forceinline f32x4 f32x4_mul_by_sign(f32x4 a, f32x4 reference_sign)
{
    mask128 res;
    mask128 a_bits    = f32x4_as_mask128(a);
    mask128 sign_bits = f32x4_as_mask128(reference_sign);

    res.x = a_bits.x ^ (sign_bits.x & 0x80000000);
    res.y = a_bits.y ^ (sign_bits.y & 0x80000000);
    res.z = a_bits.z ^ (sign_bits.z & 0x80000000);
    res.w = a_bits.w ^ (sign_bits.w & 0x80000000);

    return mask128_as_f32x4(res);
}




// ========== Trigonometry ===========
static bad_forceinline f32x4 bad_veccall f32x4_cos(f32x4 a)
{
    return (f32x4)
    {
        f32_cos(x.x),
        f32_cos(x.y),
        f32_cos(x.z),
        f32_cos(x.w)
    };
}


static bad_forceinline f32x4 bad_veccall f32x4_sin(f32x4 a)
{
        return (f32x4)
    {
        f32_sin(x.x),
        f32_sin(x.y),
        f32_sin(x.z),
        f32_sin(x.w)
    };
}


static bad_forceinline f32x4 bad_veccall f32x4_tan(f32x4 a)
{
        return (f32x4)
    {
        f32_tan(x.x),
        f32_tan(x.y),
        f32_tan(x.z),
        f32_tan(x.w)
    };
}


// Expects inputs in [-1; 1]
// Max error: ~1.5974045e-5
// Max relative error: ~0.0005%
static bad_forceinline f32x4 bad_veccall f32x4_acos(f32x4 x)
{
    return (f32x4)
    {
        f32_acos(x.x),
        f32_acos(x.y),
        f32_acos(x.z),
        f32_acos(x.w)
    };
}


// ======== Fused operations ========
static bad_forceinline f32x4 f32x4_mul_add(f32x4 a, f32x4 b, f32x4 c)
{
    return f32x4_add(f32x4_mul(a, b), c);
}


static bad_forceinline f32x4 f32x4_mul_sub(f32x4 a, f32x4 b, f32x4 c)
{
    return f32x4_sub(f32x4_mul(a, b), c);
}


static bad_forceinline f32x4 f32x4_nmul_add(f32x4 a, f32x4 b, f32x4 c)
{
    return f32x4_neg(f32x4_mul_sub(a, b, c));
}


static bad_forceinline f32x4 f32x4_nmul_sub(f32x4 a, f32x4 b, f32x4 c)
{
    return f32x4_neg(f32x4_mul_add(a, b, c));
}


// ============ Comparison ============
static bad_forceinline mask128 f32x4_neq(f32x4 a, f32x4 b)
{
    mask128 res;

    res.x = (a.x != b.x);
    res.y = (a.y != b.y);
    res.z = (a.z != b.z);
    res.w = (a.w != b.w);

    return res;
 }


static bad_forceinline mask128 f32x4_eq(f32x4 a, f32x4 b)
{
    mask128 res;

    res.x = (a.x == b.x);
    res.y = (a.y == b.y);
    res.z = (a.z == b.z);
    res.w = (a.w == b.w);

    return res;
}


static bad_forceinline mask128 f32x4_ge(f32x4 a, f32x4 b)
{
    mask128 res;

    res.x = (a.x >= b.x);
    res.y = (a.y >= b.y);
    res.z = (a.z >= b.z);
    res.w = (a.w >= b.w);

    return res;
}


static bad_forceinline mask128 f32x4_gt(f32x4 a, f32x4 b)
{
    mask128 res;

    res.x = (a.x > b.x);
    res.y = (a.y > b.y);
    res.z = (a.z > b.z);
    res.w = (a.w > b.w);

    return res;
}


static bad_forceinline mask128 f32x4_le(f32x4 a, f32x4 b)
{
    mask128 res;

    res.x = (a.x <= b.x);
    res.y = (a.y <= b.y);
    res.z = (a.z <= b.z);
    res.w = (a.w <= b.w);

    return res;
}


static bad_forceinline mask128 f32x4_lt(f32x4 a, f32x4 b)
{
    mask128 res;

    res.x = (a.x < b.x);
    res.y = (a.y < b.y);
    res.z = (a.z < b.z);
    res.w = (a.w < b.w);

    return res;
}


// ======= Selection & tests ========
static bad_forceinline mask128 f32x4_is_positive(f32x4 a)
{
    mask128 res;

    res.x = (a.x >= .0f);
    res.y = (a.y >= .0f);
    res.z = (a.z >= .0f);
    res.w = (a.w >= .0f);

    return res;
}


static bad_forceinline mask128 f32x4_is_negative(f32x4 a)
{
    mask128 res;

    res.x = (a.x < .0f);
    res.y = (a.y < .0f);
    res.z = (a.z < .0f);
    res.w = (a.w < .0f);

    return res;
}

static bad_forceinline mask128 f32x4_is_nan(f32x4 a)
{
    return f32x4_neq(a, a);
}


static bad_forceinline mask128 f32x4_is_infinite(f32x4 a)
{
    const u32 value_mask = 0x7FFFFFFF;
    const u32 inf_mask   = 0x7F800000;
    mask128   a_mask     = f32x4_as_mask128(a);

    a_mask.x &= value_mask;
    a_mask.y &= value_mask;
    a_mask.z &= value_mask;
    a_mask.w &= value_mask;

    a_mask.x = (a_mask.x == inf_mask);
    a_mask.y = (a_mask.y == inf_mask);
    a_mask.z = (a_mask.z == inf_mask);
    a_mask.w = (a_mask.w == inf_mask);

    return a_mask;
}


static bad_forceinline mask128 f32x4_is_finite(f32x4 a)
{
    const u32 expo_mask = 0x7F800000;
    mask128   a_mask    = f32x4_as_mask128(a);

    a_mask.x &= expo_mask;
    a_mask.y &= expo_mask;
    a_mask.z &= expo_mask;
    a_mask.w &= expo_mask;

    a_mask.x = (a_mask.x != expo_mask);
    a_mask.y = (a_mask.y != expo_mask);
    a_mask.z = (a_mask.z != expo_mask);
    a_mask.w = (a_mask.w != expo_mask);

    return a_mask;
}