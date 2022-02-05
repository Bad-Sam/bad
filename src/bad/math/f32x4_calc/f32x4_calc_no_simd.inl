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


static bad_forceinline f32 f32x4_hadd(f32x4_vec0 a)
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
    // TODO
    return a;
}


static bad_forceinline f32x4 f32x4_rsqrt(f32x4_vec0 a)
{
    // TODO
    return a;
}


static bad_forceinline f32x4 f32x4_min(f32x4_vec0 a, f32x4_vec1 b)
{
    f32x4 res;

    res.x = (a.x < b.x) ? a.x : b.x;
    res.y = (a.y < b.y) ? a.y : b.y;
    res.z = (a.z < b.z) ? a.z : b.z;
    res.w = (a.w < b.w) ? a.w : b.w;

    return res;
}


static bad_forceinline f32x4 f32x4_max(f32x4_vec0 a, f32x4_vec1 b)
{
    f32x4 res;

    res.x = (a.x > b.x) ? a.x : b.x;
    res.y = (a.y > b.y) ? a.y : b.y;
    res.z = (a.z > b.z) ? a.z : b.z;
    res.w = (a.w > b.w) ? a.w : b.w;

    return res;
}


static bad_forceinline f32x4 f32x4_abs(f32x4_vec0 a)
{
    const u32 value_mask = 0x7FFFFFFF;
    const mask128 a_mask = f32x4_cast_mask128(a);

    a_mask.x &= value_mask;
    a_mask.y &= value_mask;
    a_mask.z &= value_mask;
    a_mask.w &= value_mask;

    return mask128_cast_f32x4(a_mask);
}


static bad_forceinline f32x4 f32x4_sign(f32x4_vec0 a)
{
    const u32 sign_mask = 0x80000000;
    const u32 one_mask  = 0x3F800000;
    mask128   a_mask    = f32x4_cast_mask128(a);

    a_mask.x = (a_mask.x & sign_mask) | one_mask;
    a_mask.y = (a_mask.y & sign_mask) | one_mask;
    a_mask.z = (a_mask.z & sign_mask) | one_mask;
    a_mask.w = (a_mask.w & sign_mask) | one_mask;

    return mask128_cast_f32x4(a_mask);
}


static bad_forceinline f32x4 f32x4_neg(f32x4_vec0 a)
{
    const u32 sign_mask = 0x80000000;
    mask128   a_mask    = f32x4_cast_mask128(a);

    a_mask.x ^= sign_mask;
    a_mask.y ^= sign_mask;
    a_mask.z ^= sign_mask;
    a_mask.w ^= sign_mask;
    
    return mask128_cast_f32x4(a_mask);
}


static bad_forceinline f32x4 f32x4_mod(f32x4_vec0 a, f32x4_vec1 b)
{
    const f32x4 a_div_b   = f32x4_div(a, b);
    const f32x4 truncated = f32x4_trunc(a_div_b);
    
    return f32x4_sub(a, f32x4_mul(truncated, b));
}


static bad_forceinline f32x4 f32x4_trunc(f32x4_vec0 a)
{
    f32x4 res;

    res.x = (f32)((s32)a.x);
    res.y = (f32)((s32)a.y);
    res.z = (f32)((s32)a.z);
    res.w = (f32)((s32)a.w);

    return res;
}


static bad_forceinline f32x4 f32x4_round(f32x4_vec0 a)
{
    // TODO
    return a;
}


static bad_forceinline f32x4 f32x4_floor(f32x4_vec0 a)
{
    const u32   one       = 0x3F800000;
    const f32x4 truncated = f32x4_trunc(a);
    mask128     decrement = f32x4_gt(a, truncated);
    
    decrement.x &= one;
    decrement.y &= one;
    decrement.z &= one;
    decrement.w &= one;

    return f32x4_sub(truncated, mask128_cast_f32x4(decrement));
}


static bad_forceinline f32x4 f32x4_ceil(f32x4_vec0 a)
{
    const u32   one       = 0x3F800000;
    const f32x4 truncated = f32x4_trunc(a);
    mask128     increment = f32x4_lt(a, truncated);

    increment.x &= one;
    increment.y &= one;
    increment.z &= one;
    increment.w &= one;

    return f32x4_add(truncated, mask128_cast_f32x4(increment));
}


static bad_forceinline f32x4 bad_veccall f32x4_clamp(f32x4_vec0 a, f32x4_vec1 min, f32x4_vec2 max)
{
    return f32x4_min(f32x4_max(a, min), max);
}


static bad_forceinline f32x4 bad_veccall f32x4_mul_add(f32x4_vec0 a, f32x4_vec1 b, f32x4_vec2 c)
{
    return f32x4_add(f32x4_mul(a, b), c);
}


static bad_forceinline f32x4 bad_veccall f32x4_mul_sub(f32x4_vec0 a, f32x4_vec1 b, f32x4_vec2 c)
{
    return f32x4_sub(f32x4_mul(a, b), c);
}


static bad_forceinline f32x4 bad_veccall f32x4_nmul_add(f32x4_vec0 a, f32x4_vec1 b, f32x4_vec2 c)
{
    return f32x4_neg(f32x4_mul_sub(a, b, c));
}


static bad_forceinline f32x4 bad_veccall f32x4_nmul_sub(f32x4_vec0 a, f32x4_vec1 b, f32x4_vec2 c)
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
    mask128   a_mask     = f32x4_cast_mask128(a);

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
    const u32 exp_mask = 0x7F800000;
    mask128   a_mask   = f32x4_cast_mask128(a);

    a_mask.x &= exp_mask;
    a_mask.y &= exp_mask;
    a_mask.z &= exp_mask;
    a_mask.w &= exp_mask;

    a_mask.x = (a_mask.x != exp_mask) ? mask128_all_bits_set : mask128_all_bits_clear;
    a_mask.y = (a_mask.y != exp_mask) ? mask128_all_bits_set : mask128_all_bits_clear;
    a_mask.z = (a_mask.z != exp_mask) ? mask128_all_bits_set : mask128_all_bits_clear;
    a_mask.w = (a_mask.w != exp_mask) ? mask128_all_bits_set : mask128_all_bits_clear;

    return a_mask;
}