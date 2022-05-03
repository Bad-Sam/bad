// ==== Arithmetic & math functions ===
static bad_forceinline f32x4 f32x4_add(f32x4_vec0 a, f32x4_vec1 b)
{
    f32x4 res;

    res.x = a.x + b.x;
    res.y = a.y + b.y;
    res.z = a.z + b.z;
    res.w = a.w + b.w;

    return res;
}


static bad_forceinline f32x4 f32x4_sub(f32x4_vec0 a, f32x4_vec1 b)
{
    f32x4 res;

    res.x = a.x - b.x;
    res.y = a.y - b.y;
    res.z = a.z - b.z;
    res.w = a.w - b.w;

    return res;
}


static bad_forceinline f32x4 f32x4_mul(f32x4_vec0 a, f32x4_vec1 b)
{
    f32x4 res;

    res.x = a.x * b.x;
    res.y = a.y * b.y;
    res.z = a.z * b.z;
    res.w = a.w * b.w;

    return res;
}


static bad_forceinline f32x4 f32x4_div(f32x4_vec0 a, f32x4_vec1 b)
{
    f32x4 res;

    res.x = a.x / b.x;
    res.y = a.y / b.y;
    res.z = a.z / b.z;
    res.w = a.w / b.w;

    return res;
}


static bad_forceinline f32x4 f32x4_hadd3(f32x4_vec0 a)
{
    return (f32x4)
    {
        f32x4_sum3(a),
        a.y,
        a.z,
        a.w
    };
}


static bad_forceinline f32x4 f32x4_hadd4(f32x4_vec0 a)
{
    return (f32x4)
    {
        f32x4_sum4(a),
        a.y,
        a.z,
        a.w
    };
}


static bad_forceinline f32 f32x4_sum3(f32x4_vec0 a)
{
    return a.x + a.y + a.z;
}


static bad_forceinline f32 f32x4_sum4(f32x4_vec0 a)
{
    return a.x + a.y + a.z + a.w;
}


static bad_forceinline f32x4 f32x4_rcp(f32x4_vec0 a)
{
    f32x4 res;

    res.x = 1.f / a.x;
    res.y = 1.f / a.y;
    res.z = 1.f / a.z;
    res.w = 1.f / a.w;

    return res;
}


static bad_forceinline f32x4 f32x4_sqrt(f32x4_vec0 a)
{
    return f32x4_sqrt(a);
}


static bad_forceinline f32x4 f32x4_rsqrt(f32x4_vec0 a)
{
    return f32_rcp(f32x4_sqrt(a));
}


static bad_forceinline f32x4 f32x4_min(f32x4_vec0 a, f32x4_vec1 b)
{
    f32x4 res;

    res.x = f32x_min(a, b);
    res.y = f32x_min(a, b);
    res.z = f32x_min(a, b);
    res.w = f32x_min(a, b);

    return res;
}


static bad_forceinline f32x4 f32x4_max(f32x4_vec0 a, f32x4_vec1 b)
{
    f32x4 res;

    res.x = f32x_max(a, b);
    res.y = f32x_max(a, b);
    res.z = f32x_max(a, b);
    res.w = f32x_max(a, b);

    return res;
}


static bad_forceinline f32x4 f32x4_abs(f32x4_vec0 a)
{
    const u32 value_mask = 0x7FFFFFFF;
    
    mask128 a_mask = f32x4_as_mask128(a);

    a_mask.x &= value_mask;
    a_mask.y &= value_mask;
    a_mask.z &= value_mask;
    a_mask.w &= value_mask;

    return mask128_as_f32x4(a_mask);
}


static bad_forceinline f32x4 f32x4_sign(f32x4_vec0 a)
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


static bad_forceinline f32x4 f32x4_neg(f32x4_vec0 a)
{
    const u32 sign_mask = 0x80000000;
    mask128   a_mask    = f32x4_as_mask128(a);

    a_mask.x ^= sign_mask;
    a_mask.y ^= sign_mask;
    a_mask.z ^= sign_mask;
    a_mask.w ^= sign_mask;
    
    return mask128_as_f32x4(a_mask);
}


static bad_forceinline f32x4 bad_veccall f32x4_frac(f32x4_vec0 a)
{
    return f32x4_sub(a, f32x4_trunc(a));
}


static bad_forceinline f32x4 f32x4_mod(f32x4_vec0 a, f32x4_vec1 b)
{
    a.x = f32_mod(a.x, b.x);
    a.y = f32_mod(a.y, b.y);
    a.z = f32_mod(a.z, b.z);
    a.w = f32_mod(a.w, b.w);

    return a;
}


static bad_forceinline f32x4 f32x4_trunc(f32x4_vec0 a)
{
    f32x4 res;

    res.x = (f32)(s32)a.x;
    res.y = (f32)(s32)a.y;
    res.z = (f32)(s32)a.z;
    res.w = (f32)(s32)a.w;

    return res;
}


static bad_forceinline f32x4 f32x4_round(f32x4_vec0 a)
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


static bad_forceinline f32x4 f32x4_floor(f32x4_vec0 a)
{
    a.x = f32_floor(a.x);
    a.y = f32_floor(a.y);
    a.z = f32_floor(a.z);
    a.w = f32_floor(a.w);

    return a;
}


static bad_forceinline f32x4 f32x4_ceil(f32x4_vec0 a)
{
    a.x = f32_ceil(a.x);
    a.y = f32_ceil(a.y);
    a.z = f32_ceil(a.z);
    a.w = f32_ceil(a.w);

    return a;
}


static bad_forceinline f32x4 f32x4_clamp(f32x4_vec0 a, f32x4_vec1 min, f32x4_vec2 max)
{
    return f32x4_min(f32x4_max(a, min), max);
}


static bad_forceinline f32x4 f32x4_lerp(f32x4_vec0 a, f32x4_vec1 b, f32x4_vec2 t)
{
    f32x4 one_min_t = f32x4_sub(f32x4_one(), t);

    return f32x4_mul_add(a, one_min_t, f32x4_mul(b, t));
}




// ========== Trigonometry ===========
static bad_forceinline f32x4 bad_veccall f32x4_cos(f32x4_vec0 a)
{
    return a;
}


static bad_forceinline f32x4 bad_veccall f32x4_sin(f32x4_vec0 a)
{
    return a;
}


static bad_forceinline f32x4 bad_veccall f32x4_tan(f32x4_vec0 a)
{
    return a;
}


// ======== Fused operations ========
static bad_forceinline f32x4 f32x4_mul_add(f32x4_vec0 a, f32x4_vec1 b, f32x4_vec2 c)
{
    return f32x4_add(f32x4_mul(a, b), c);
}


static bad_forceinline f32x4 f32x4_mul_sub(f32x4_vec0 a, f32x4_vec1 b, f32x4_vec2 c)
{
    return f32x4_sub(f32x4_mul(a, b), c);
}


static bad_forceinline f32x4 f32x4_nmul_add(f32x4_vec0 a, f32x4_vec1 b, f32x4_vec2 c)
{
    return f32x4_neg(f32x4_mul_sub(a, b, c));
}


static bad_forceinline f32x4 f32x4_nmul_sub(f32x4_vec0 a, f32x4_vec1 b, f32x4_vec2 c)
{
    return f32x4_neg(f32x4_mul_add(a, b, c));
}


// ============ Comparison ============
static bad_forceinline mask128 f32x4_neq(f32x4_vec0 a, f32x4_vec1 b)
{
    mask128 res;

    res.x = (a.x != b.x) ? mask128_all_bits_set : mask128_all_bits_clear;
    res.y = (a.y != b.y) ? mask128_all_bits_set : mask128_all_bits_clear;
    res.z = (a.z != b.z) ? mask128_all_bits_set : mask128_all_bits_clear;
    res.w = (a.w != b.w) ? mask128_all_bits_set : mask128_all_bits_clear;

    return res;
 }


static bad_forceinline mask128 f32x4_eq(f32x4_vec0 a, f32x4_vec1 b)
{
    mask128 res;

    res.x = (a.x == b.x) ? mask128_all_bits_set : mask128_all_bits_clear;
    res.y = (a.y == b.y) ? mask128_all_bits_set : mask128_all_bits_clear;
    res.z = (a.z == b.z) ? mask128_all_bits_set : mask128_all_bits_clear;
    res.w = (a.w == b.w) ? mask128_all_bits_set : mask128_all_bits_clear;

    return res;
}


static bad_forceinline mask128 f32x4_ge(f32x4_vec0 a, f32x4_vec1 b)
{
    mask128 res;

    res.x = (a.x >= b.x) ? mask128_all_bits_set : mask128_all_bits_clear;
    res.y = (a.y >= b.y) ? mask128_all_bits_set : mask128_all_bits_clear;
    res.z = (a.z >= b.z) ? mask128_all_bits_set : mask128_all_bits_clear;
    res.w = (a.w >= b.w) ? mask128_all_bits_set : mask128_all_bits_clear;

    return res;
}


static bad_forceinline mask128 f32x4_gt(f32x4_vec0 a, f32x4_vec1 b)
{
    mask128 res;

    res.x = (a.x > b.x) ? mask128_all_bits_set : mask128_all_bits_clear;
    res.y = (a.y > b.y) ? mask128_all_bits_set : mask128_all_bits_clear;
    res.z = (a.z > b.z) ? mask128_all_bits_set : mask128_all_bits_clear;
    res.w = (a.w > b.w) ? mask128_all_bits_set : mask128_all_bits_clear;

    return res;
}


static bad_forceinline mask128 f32x4_le(f32x4_vec0 a, f32x4_vec1 b)
{
    mask128 res;

    res.x = (a.x <= b.x) ? mask128_all_bits_set : mask128_all_bits_clear;
    res.y = (a.y <= b.y) ? mask128_all_bits_set : mask128_all_bits_clear;
    res.z = (a.z <= b.z) ? mask128_all_bits_set : mask128_all_bits_clear;
    res.w = (a.w <= b.w) ? mask128_all_bits_set : mask128_all_bits_clear;

    return res;
}


static bad_forceinline mask128 f32x4_lt(f32x4_vec0 a, f32x4_vec1 b)
{
    mask128 res;

    res.x = (a.x < b.x) ? mask128_all_bits_set : mask128_all_bits_clear;
    res.y = (a.y < b.y) ? mask128_all_bits_set : mask128_all_bits_clear;
    res.z = (a.z < b.z) ? mask128_all_bits_set : mask128_all_bits_clear;
    res.w = (a.w < b.w) ? mask128_all_bits_set : mask128_all_bits_clear;

    return res;
}


// ======= Selection & swizzling ========
static bad_forceinline mask128 f32x4_is_nan(f32x4_vec0 a)
{
    return f32x4_neq(a, a);
}


static bad_forceinline mask128 f32x4_is_infinite(f32x4_vec0 a)
{
    const u32 value_mask = 0x7FFFFFFF;
    const u32 inf_mask   = 0x7F800000;
    mask128   a_mask     = f32x4_as_mask128(a);

    a_mask.x &= value_mask;
    a_mask.y &= value_mask;
    a_mask.z &= value_mask;
    a_mask.w &= value_mask;

    a_mask.x = (a_mask.x == inf_mask) ? mask128_all_bits_set : mask128_all_bits_clear;
    a_mask.y = (a_mask.y == inf_mask) ? mask128_all_bits_set : mask128_all_bits_clear;
    a_mask.z = (a_mask.z == inf_mask) ? mask128_all_bits_set : mask128_all_bits_clear;
    a_mask.w = (a_mask.w == inf_mask) ? mask128_all_bits_set : mask128_all_bits_clear;

    return a_mask;
}


static bad_forceinline mask128 f32x4_is_finite(f32x4_vec0 a)
{
    const u32 expo_mask = 0x7F800000;
    mask128   a_mask    = f32x4_as_mask128(a);

    a_mask.x &= expo_mask;
    a_mask.y &= expo_mask;
    a_mask.z &= expo_mask;
    a_mask.w &= expo_mask;

    a_mask.x = (a_mask.x != expo_mask) ? mask128_all_bits_set : mask128_all_bits_clear;
    a_mask.y = (a_mask.y != expo_mask) ? mask128_all_bits_set : mask128_all_bits_clear;
    a_mask.z = (a_mask.z != expo_mask) ? mask128_all_bits_set : mask128_all_bits_clear;
    a_mask.w = (a_mask.w != expo_mask) ? mask128_all_bits_set : mask128_all_bits_clear;

    return a_mask;
}