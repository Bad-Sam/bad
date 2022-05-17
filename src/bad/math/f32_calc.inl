// (1) scalar
// =========== Arithmetic ===========
static bad_forceinline f32 f32_add(f32 a, f32 b)
{
    return a + b;
}


static bad_forceinline f32 f32_sub(f32 a, f32 b)
{
    return a - b;
}


static bad_forceinline f32 f32_mul(f32 a, f32 b)
{
    return a * b;
}


static bad_forceinline f32 f32_div(f32 a, f32 b)
{
    return a / b;
}


// ====== Advanced arithmetic =======
static bad_forceinline f32 f32_rcp(f32 a)
{
#if defined(__SSE__)
    f32x4 va    = f32x4_set_lower(a);
    f32x4 rcp_a = _mm_rcp_ss(va);

    return f32x4_get_0(rcp_a);
#else
    return 1.f / a;
#endif
}


static bad_forceinline f32 f32_sqrt(f32 a)
{
#if defined(__SSE__)
    f32x4 va     = f32x4_set_lower(a);
    f32x4 sqrt_a = _mm_sqrt_ss(va);

    return f32x4_get_0(sqrt_a);
#else
    return 1.f / f32_rsqrt(a);
#endif
}


static bad_forceinline f32 f32_rsqrt(f32 a)
{
#if defined(__SSE__)
    f32x4 va      = f32x4_set_lower(a);
    f32x4 rsqrt_a = _mm_rsqrt_ss(va);

    return f32x4_get_0(rsqrt_a);
#else
    f32 half_a = -.5f * a;
    u32 int_a  = 0x5F37599E - (f32_as_u32(a) >> 1);
    
    a  = u32_as_f32(int_a);
    a *= f32_mul_add(half_a * a, a, 1.5f);
    a *= f32_mul_add(half_a * a, a, 1.5f);
    
    return a;
#endif
}


static bad_forceinline f32 f32_min(f32 a, f32 b)
{
    return (a < b) ? a : b;
}


static bad_forceinline f32 f32_max(f32 a, f32 b)
{
    return (a > b) ? a : b;
}


// (1) builtin (2) simd (3) scalar
static bad_forceinline f32 f32_abs(f32 a)
{
#if bad_has_builtin(__builtin_fabsf)
    return __builtin_fabsf(a);
#elif defined(__SSE__)
    f32x4 va    = f32x4_set_lower(a);
    f32x4 abs_a = f32x4_abs(va);

    return f32x4_get_0(abs_a);
#else
    const u32 abs_mask = 0x7FFFFFFF;

    u32 a_abs = f32_as_u32(a) & abs_mask;

    return u32_as_f32(a_abs);
#endif
}


// (1) builtin (2) simd (3) scalar
static bad_forceinline f32 f32_sign(f32 a)
{
#if bad_has_builtin(__builtin_copysignf)
    return __builtin_copysignf(1.f, a);
#elif defined(__SSE__)
    f32x4 va     = f32x4_set_lower(a);
    f32x4 sign_a = f32x4_sign(va);

    return f32x4_get_0(sign_a);
#else
    const u32 sign_mask = 0x80000000;
    const u32 f32_one   = 0x3F800000;

    u32 sign_a = (f32_as_u32(a) & sign_mask) | f32_one;

    return u32_as_f32(sign_a);
#endif
}


static bad_forceinline f32 f32_neg(f32 a)
{
    return -a;
}


static bad_forceinline f32 f32_frac(f32 a)
{
    return a - f32_trunc(a);
}


static bad_forceinline f32 f32_mod(f32 a, f32 b)
{
    f32 a_div_b   = f32_div(a, b);
    f32 truncated = f32_trunc(a_div_b);
    
    return f32_mul_sub(truncated, b, a);
}


// (1) builtin (2) simd (3) scalar
static bad_forceinline f32 f32_trunc(f32 a)
{
#if bad_has_builtin(__builtin_truncf)
    return __builtin_truncf(a);
#elif defined(__SSE__)
    f32x4 va = f32x4_set_lower(a);

#   if defined(__SSE4_1__)
    f32x4 trunc_a = _mm_round_ss(va, va, _MM_FROUND_TO_ZERO | _MM_FROUND_NO_EXC);
#   else
    f32x4 trunc_a = f32x4_trunc(va);
#   endif

    return f32x4_get_0(trunc_a);
#else
    return (f32)(s32)a;
#endif
}


// (1) simd (2) scalar
static bad_forceinline f32 f32_round(f32 a)
{
#if defined(__SSE__)
    f32x4 va = f32x4_set_lower(a);
    
#   if defined(__SSE4_1__)
    f32x4 round_a = _mm_round_ss(va, va, _MM_FROUND_TO_NEAREST_INT | _MM_FROUND_NO_EXC);
#   else
    f32x4 round_a = f32x4_round(va);
#   endif

    return f32x4_get_0(round_a);
#else
    f32 sign_a  = f32_sign(a);
    f32 trunc_a = f32_trunc(a);
    f32 offset  = sign_a * (a - trunc_a);

    offset = (offset > .5f);

    return f32_mul_add(sign_a, offset, trunc_a);
#endif
}


static bad_forceinline f32 f32_floor(f32 a)
{
#if bad_has_builtin(__builtin_floorf)
    return __builtin_floorf(a);
#elif defined(__SSE__)
    f32x4 va = f32x4_set_lower(a);
    
#   if defined(__SSE4_2__)
    f32x4 floor_a = _mm_floor_ss(va, va);
#   elif defined(__SSE4_1__)
    f32x4 floor_a = _mm_round_ss(va, va, _MM_FROUND_TO_NEG_INF | _MM_FROUND_NO_EXC);
#   else
    f32x4 floor_a = f32x4_floor(va);
#   endif

    return f32x4_get_0(floor_a);
#else
    u32 a_bits = f32_as_u32(x);

    u32 expo = (a_bits >> 23) & 0x000000FF;

    u32 is_neg        = u32_bool_to_mask((a_bits & 0x80000000) >> 31);
    u32 is_under_zero = u32_bool_to_mask(expo < 127u);
    u32 m             = 0x007FFFFF >> (expo - 127u);

    a_bits += is_neg & m;
    a_bits &= ~m;

    return f32_blend(is_neg & 0xBF800000, a_bits, is_under_zero);
#endif
}


static bad_forceinline f32 f32_ceil(f32 a)
{
#if bad_has_builtin(__builtin_ceilf)
    return __builtin_ceilf(a);
#elif defined(__SSE__)
    f32x4 va = f32x4_set_lower(a);
    
#   if defined(__SSE4_2__)
    f32x4 ceil_a = _mm_ceil_ss(va, va);
#   elif defined(__SSE4_1__)
    f32x4 ceil_a = _mm_round_ss(va, va, _MM_FROUND_TO_POS_INF | _MM_FROUND_NO_EXC);
#   else
    f32x4 ceil_a = f32x4_ceil(va);
#   endif

    return f32x4_get_0(ceil_a);
#else
    f32 trunc_a   = f32_trunc(a);
    f32 increment = (trunc_a < a);

    return trunc_a + increment;
#endif
}


static bad_forceinline f32 f32_clamp(f32 a, f32 min, f32 max)
{
    return f32_min(f32_max(a, min), max);
}


static bad_forceinline f32 f32_lerp(f32 a, f32 b, f32 t)
{
    return a * (1.f - t) + b * t;
}


static bad_forceinline f32 f32_copysign(f32 a, f32 reference_sign)
{
#if bad_has_builtin(__builtin_copysignf)
    return __builtin_copysignf(a, reference_sign);
#elif defined(__SSE__)
    f32x4 va        = f32x4_set_lower(a);
    f32x4 vref_sign = f32x4_set_lower(reference_sign);

    f32x4 res = f32x4_copysign(va, vref_sign);

    return f32x4_get_0(res);
#else
    u32 a_bits    = f32_as_u32(sa);
    u32 sign_bits = f32_as_u32(sreference_sign);

    u32 res = (a_bits & 0x7FFFFFFF) | (sign_bits & ~0x80000000);

    return u32_as_f32(res);
#endif
}


static bad_forceinline f32 f32_mul_by_sign(f32 a, f32 reference_sign)
{
#if defined(__SSE__)
    f32x4 va        = f32x4_set_lower(a);
    f32x4 vref_sign = f32x4_set_lower(reference_sign);

    f32x4 res = f32x4_mul_by_sign(va, vref_sign);

    return f32x4_get_0(res);
#else
    u32 a_mask    = f32_as_u32(sa);
    u32 sign_mask = f32_as_u32(sreference_sign);

    u32 res = (a_mask & 0x7FFFFFFF) | (sign_mask & 0x80000000);

    return u32_as_f32(res);
#endif
}




// ========== Trigonometry ===========
static bad_inline f32 f32_cos(f32 x)
{
    static const u32 sign_table[4] = {0x00000000, 0x80000000, 0x80000000, 0x00000000};
    static const f32 offset[2]     = {.0f, half_pi};

    x = f32_abs(x);

    u32 euclidian_div = x * half_pi_rcp;
    u32 is_odd        = euclidian_div & 1;
    u32 sign_idx      = euclidian_div & 3;
    u32 offset_x_sign = is_odd << 31;

    x = f32_nmul_add((f32)euclidian_div, half_pi, x);

    u32 x_bits = f32_as_u32(x) ^ offset_x_sign;
    x = offset[is_odd] + u32_as_f32(x_bits);

    f32 cos_x             = f32_cos_0_halfpi(x);
    u32 signed_cos_x_bits = f32_as_u32(cos_x) | sign_table[sign_idx];

    return u32_as_f32(signed_cos_x_bits);
}


// Expects input between in [0, pi/2]
static bad_inline f32 f32_cos_0_halfpi(f32 x)
{
    static const f32 a2  = -.4999999963f;
    static const f32 a4  =  .0416666418f;
    static const f32 a6  = -.0013888397f;
    static const f32 a8  =  .0000247609f;
    static const f32 a10 = -.0000002605f;
    static const f32 one = 1.f;

    f32 x2  = x * x;
    f32 res = f32_mul_add(a10, x2,  a8);
        res = f32_mul_add(res, x2,  a6);
        res = f32_mul_add(res, x2,  a4);
        res = f32_mul_add(res, x2,  a2);
        res = f32_mul_add(res, x2, one);

    return res;
}


// TODO: implement and keep only scalar
static bad_inline f32 f32_sin(f32 x)
{
    f32 euclidian_div_f32 = f32_trunc(x * pi_rcp);
    s32 euclidian_div_s32 = (s32)euclidian_div_f32;
    u32 sin_x_neg         = (euclidian_div_s32 & 1) << 31; 

    x = f32_nmul_add(euclidian_div_f32, pi, x);

    f32 sin_x             = f32_sin_npi_pi(x);
    u32 signed_sin_x_bits = f32_as_u32(sin_x) ^ sin_x_neg;

    return u32_as_f32(signed_sin_x_bits);
}


// Expects inputs in [-pi, pi]
static bad_inline f32 f32_sin_npi_pi(f32 x)
{
    // Based on Chebyshev polynomials
    static const f32 c1  = -.10132118f;
    static const f32 c3  =  .0066208798f;
    static const f32 c5  = -.00017350505f;
    static const f32 c7  =  .0000025222919f;
    static const f32 c9  = -.000000023317787f;
    static const f32 c11 =  .00000000013291342f;
    static const f32 err = pi + .00000008742278f;

    f32 x2   = x * x;
    f32 res  = f32_mul_add(x2, c11, c9);
        res  = f32_mul_add(x2, res, c7);
        res  = f32_mul_add(x2, res, c5);
        res  = f32_mul_add(x2, res, c3);
        res  = f32_mul_add(x2, res, c1);
        res *= (x - err) * (x + err) * x;

    return res;
}


// TODO: implement and keep only scalar
// From the "Even faster math" GDC talk by Green Robin
// https://www.gdcvault.com/play/1026734/Math-in-Game-Development-Summit
static bad_inline f32 f32_tan(f32 x)
{
    f32x4 vx    = f32x4_set_lower(x);
    f32x4 tan_x = f32x4_tan(vx);

    return f32x4_get_0(tan_x);
}


static bad_inline f32 f32_acos(f32 x)
{
    static const f32 a2 = -0.0392588f;
    static const f32 a4 = 0.179323f;
    static const f32 a6 = -1.75866f;
    static const f32 a8 = -3.66063f;

    f32 abs_x = f32_abs(x);

    f32 acos  = f32_mul_add(a2,   abs_x, a4);
        acos  = f32_mul_add(acos, abs_x, a6);
        acos  = f32_mul_add(acos, abs_x, a8);
        acos  = f32_mul_sub(abs_x, abs_x, abs_x) / acos;
        acos += abs_x;

    f32 mul = f32_mul_by_sign(f32_sqrt(1.f - acos) - 1.f, x);

    return f32_mul_add(mul, half_pi, half_pi);
}




// ======== Fused operations ========
static bad_forceinline f32 f32_mul_add(f32 a, f32 b, f32 c)
{
#if bad_has_builtin(__builtin_fmaf)
    return __builtin_fmaf(a, b, c);
#elif defined(__SSE__)
    // Generated code is not good, but there is no other way to
    // generate the desired µops with MSVC. This makes me sad
    f32x4 va = f32x4_set_lower(a);
    f32x4 vb = f32x4_set_lower(b);
    f32x4 vc = f32x4_set_lower(c);

#   if defined(__FMA__)
    f32x4 fmadd_abc = _mm_fmadd_ss(va, vb, vc);
#   else
    f32x4 fmadd_abc = _mm_add_ps(_mm_mul_ps(va, vb), vc);
#   endif

    return _mm_cvtss_f32(fmadd_abc);
#else
    return a * b + c;
#endif
}


static bad_forceinline f32 f32_mul_sub(f32 a, f32 b, f32 c)
{
#if bad_has_builtin(__builtin_fmaf)
    return __builtin_fmaf(a, b, -c);
#elif defined(__SSE__)
    f32x4 va = f32x4_set_lower(a);
    f32x4 vb = f32x4_set_lower(b);
    f32x4 vc = f32x4_set_lower(c);
#   if defined(__FMA__)
    f32x4 fmsub_abc = _mm_fmsub_ss(va, vb, vc);
#   else
    f32x4 fmsub_abc = _mm_sub_ps(_mm_mul_ps(va, vb), vc);
#   endif

    return _mm_cvtss_f32(fmsub_abc);
#else
    return a * b - c;
#endif
}


static bad_forceinline f32 f32_nmul_add(f32 a, f32 b, f32 c)
{
#if bad_has_builtin(__builtin_fmaf)
    return __builtin_fmaf(-a, b, c);
#elif defined(__SSE__)
    f32x4 va = f32x4_set_lower(a);
    f32x4 vb = f32x4_set_lower(b);
    f32x4 vc = f32x4_set_lower(c);

#   if defined(__FMA__)
    f32x4 fnmadd_abc = _mm_fnmadd_ss(va, vb, vc);
#   else
    f32x4 fnmadd_abc = _mm_sub_ps(vc, _mm_mul_ps(va, vb));
#endif

    return _mm_cvtss_f32(fnmadd_abc);
#else
    return -a * b + c;
#endif
}


static bad_forceinline f32 f32_nmul_sub(f32 a, f32 b, f32 c)
{
#if bad_has_builtin(__builtin_fmaf)
    return __builtin_fmaf(-a, b, -c);
#elif defined(__SSE__) && defined(__FMA__)
    f32x4 va = f32x4_set_lower(a);
    f32x4 vb = f32x4_set_lower(b);
    f32x4 vc = f32x4_set_lower(c);

    f32x4 fnmsub_abc = _mm_fnmsub_ss(va, vb, vc);

    return _mm_cvtss_f32(fnmsub_abc);
#else
    return -f32_mul_add(a, b, c);
#endif
}




// ============ Comparison ============
static bad_forceinline u32 f32_neq(f32 a, f32 b)
{
    return a != b;
}


static bad_forceinline u32 f32_eq(f32 a, f32 b)
{
    return a == b;
}


static bad_forceinline u32 f32_ge(f32 a, f32 b)
{
#if bad_has_builtin(__builtin_isgreaterequal)
    return __builtin_isgreaterequal(a, b);
#else
    return a >= b;
#endif
}


static bad_forceinline u32 f32_gt(f32 a, f32 b)
{
#if bad_has_builtin(__builtin_isgreater)
    return __builtin_isgreater(a, b);
#else
    return a > b;
#endif
}


static bad_forceinline u32 f32_le(f32 a, f32 b)
{
#if bad_has_builtin(__builtin_islessequal)
    return __builtin_islessequal(a, b);
#else
    return a <= b;
#endif
}


static bad_forceinline u32 f32_lt(f32 a, f32 b)
{
#if bad_has_builtin(__builtin_isless)
    return __builtin_isless(a, b);
#else
    return a < b;
#endif
}




// ======= Tests ========
static bad_forceinline u32 f32_is_nan(f32 a)
{
#if bad_has_builtin(__builtin_isnan)
    return __builtin_isnan(a);
#else
    return u32_bool_to_mask(a != a);
#endif
}


static bad_forceinline u32 f32_is_infinite(f32 a)
{
#if bad_has_builtin(__builtin_isinf)
    return __builtin_isinf(a);
#else
    const u32 abs_mask = 0x7FFFFFFF;
    const u32 inf_mask = 0x7F800000;

    u32 is_infinite = (f32_as_u32(a) & abs_mask) == inf_mask;

    return u32_bool_to_mask(is_infinite);
#endif
}


static bad_forceinline u32 f32_is_finite(f32 a)
{
#if bad_has_builtin(__builtin_isfinite)
    return __builtin_isfinite(a);
#else
    const u32 expo_mask = 0x7F800000;

    u32 is_finite = (f32_as_u32(a) != expo_mask);

    return u32_bool_to_mask(is_finite);
#endif
}