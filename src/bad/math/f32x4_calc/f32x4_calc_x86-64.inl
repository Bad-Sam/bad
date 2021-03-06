// =========== Arithmetic ===========
static bad_forceinline f32x4 bad_veccall f32x4_add(f32x4 a, f32x4 b)
{
    return _mm_add_ps(a, b);
}


static bad_forceinline f32x4 bad_veccall f32x4_sub(f32x4 a, f32x4 b)
{
    return _mm_sub_ps(a, b);
}


static bad_forceinline f32x4 bad_veccall f32x4_mul(f32x4 a, f32x4 b)
{
    return _mm_mul_ps(a, b);
}


// NOTE: using _mm_rcp_ps + _mm_mul_ps brings significant imprecision
static bad_forceinline f32x4 bad_veccall f32x4_div(f32x4 a, f32x4 b)
{
    return _mm_div_ps(a, b);
}


// See Peter Cordes' very comprehensive explanation: https://stackoverflow.com/a/35270026/15315204
static bad_forceinline f32x4 bad_veccall f32x4_hadd3(f32x4 a)
{
    // shuf = (a[1], a[1], a[3], x)
#if defined(__SSE3__)
    f32x4 shuf = _mm_movehdup_ps(a);
#else
    f32x4 shuf = _mm_shuffle_ps(a, a, _MM_SHUFFLE(2, 3, 0, 1));
#endif

    // sums = (a[0] + a[1], a[1], a[2], a[3])
    f32x4 sums = _mm_add_ss(a, shuf);
    // shuf = (a[2], a[3], a[3], x)
          shuf = _mm_movehl_ps(shuf, sums);
    
    // a[0] + a[1] + a[2]
    return _mm_add_ss(sums, shuf);
}


static bad_forceinline f32x4 bad_veccall f32x4_hadd4(f32x4 a)
{
    // shuf = (a[1], a[1], a[3], x)
#if defined(__SSE3__)
    f32x4 shuf = _mm_movehdup_ps(a);
#else
    f32x4 shuf = _mm_shuffle_ps(a, a, _MM_SHUFFLE(2, 3, 0, 1));
#endif

    // sums = (a[0] + a[1], a[1] + a[1], a[2] + a[3], a[3] + a[3])
    f32x4 sums = _mm_add_ps(a, shuf);
    // shuf = (a[2] + a[3], a[3] + a[3], a[3], x)
          shuf = _mm_movehl_ps(shuf, sums);
    
    // a[0] + a[1] + a[2] + a[3]
    return _mm_add_ss(sums, shuf);
}


static bad_forceinline f32 bad_veccall f32x4_sum3(f32x4 a)
{
    return f32x4_get_0(f32x4_hadd3(a));
}


static bad_forceinline f32 bad_veccall f32x4_sum4(f32x4 a)
{
    return f32x4_get_0(f32x4_hadd4(a));
}


// ====== Advanced arithmetic =======
static bad_forceinline f32x4 bad_veccall f32x4_rcp(f32x4 a)
{
    return _mm_rcp_ps(a);
}


static bad_forceinline f32x4 bad_veccall f32x4_sqrt(f32x4 a)
{
    return _mm_sqrt_ps(a);
}


static bad_forceinline f32x4 bad_veccall f32x4_rsqrt(f32x4 a)
{
    return _mm_rsqrt_ps(a);
}


static bad_forceinline f32x4 bad_veccall f32x4_min(f32x4 a, f32x4 b)
{
    return _mm_min_ps(a, b);
}


static bad_forceinline f32x4 bad_veccall f32x4_max(f32x4 a, f32x4 b)
{
    return _mm_max_ps(a, b);
}


static bad_forceinline f32x4 bad_veccall f32x4_abs(f32x4 a)
{
#if defined(__SSE2__)
    // Shift out the sign bit, shift in zero instead
    return _mm_castsi128_ps(_mm_srli_epi32(_mm_slli_epi32(_mm_castps_si128(a), 1), 1));
#else
    return _mm_and_ps(mask128_value32(), a);
#endif
}


static bad_forceinline f32x4 bad_veccall f32x4_sign(f32x4 a)
{
#if defined(__SSE2__)
    mask128 a_sign = _mm_cmpeq_epi32(_mm_castps_si128(a), _mm_castps_si128(a));
    mask128 one    = _mm_slli_epi32(_mm_srli_epi32(a_sign, 25), 23);

    a_sign = mask128_keep_highbit32(f32x4_as_mask128(a));

    return _mm_castsi128_ps(_mm_or_si128(one, a_sign));
#else
    f32x4 one    = f32x4_one();
    f32x4 a_sign = _mm_and_ps(mask128_highbit32(), a);

    return _mm_or_ps(a_sign, one);
#endif
}


static bad_forceinline f32x4 bad_veccall f32x4_neg(f32x4 a)
{
#if defined(__SSE2__)
    // si128 version has a better throughput
    return _mm_castsi128_ps(_mm_xor_si128(mask128_highbit32(), _mm_castps_si128(a)));
#else
    return _mm_xor_ps(mask128_highbit32(), a);
#endif
}


static bad_forceinline f32x4 bad_veccall f32x4_frac(f32x4 a)
{
    return f32x4_sub(a, f32x4_trunc(a));
}


static bad_forceinline f32x4 bad_veccall f32x4_mod(f32x4 a, f32x4 b)
{
    f32x4 trunc = _mm_div_ps(a, b);
          trunc = f32x4_trunc(trunc);
    
    return f32x4_nmul_add(trunc, b, a);
}


static bad_forceinline f32x4 bad_veccall f32x4_trunc(f32x4 a)
{
#if defined(__SSE4_1__)
    return _mm_round_ps(a, _MM_FROUND_TO_ZERO | _MM_FROUND_NO_EXC);
#elif defined(__SSE2__)
    return _mm_cvtepi32_ps(_mm_cvttps_epi32(a));
#elif defined(__SSE__) && defined(__MMX__)
    __m64 low  = _mm_cvttps_pi32(a);
    __m64 high = _mm_cvttps_pi32(_mm_movehl_ps(a, a));

    return _mm_cvtpi32x2_ps(low, high);
#endif
}


static bad_forceinline f32x4 bad_veccall f32x4_round(f32x4 a)
{
#if defined(__SSE4_1__)
    return _mm_round_ps(a, _MM_FROUND_TO_NEAREST_INT | _MM_FROUND_NO_EXC);
#elif defined(__SSE2__)
    return _mm_cvtepi32_ps(_mm_cvtps_epi32(a));
#else
    __m64 low  = _mm_cvtps_pi32(a);
    __m64 high = _mm_cvtps_pi32(_mm_movehl_ps(a, a));

    return _mm_cvtpi32x2_ps(low, high);
#endif
}


static bad_forceinline f32x4 bad_veccall f32x4_floor(f32x4 a)
{
#if defined(__SSE4_2__)
    return _mm_floor_ps(a);
#elif defined(__SSE4_1__)
    return _mm_round_ps(a, _MM_FROUND_TO_NEG_INF | _MM_FROUND_NO_EXC);
#elif defined(__SSE2__)
    f32x4 truncated = _mm_cvtepi32_ps(_mm_cvttps_epi32(a));
    f32x4 decrement = _mm_cmpgt_ps(truncated, a);
          decrement = _mm_and_si128(decrement, f32x4_one());

    return _mm_sub_ps(truncated, decrement);
#else
    __m64 low       = _mm_cvttps_pi32(a);
    __m64 high      = _mm_cvttps_pi32(_mm_movehl_ps(a, a));
    f32x4 truncated = _mm_cvtpi32x2_ps(low, high);
    f32x4 decrement = _mm_cmpgt_ps(truncated, a);
          decrement = _mm_and_ps(decrement, f32x4_one());

    return _mm_sub_ps(truncated, decrement);
#endif
}


static bad_forceinline f32x4 bad_veccall f32x4_ceil(f32x4 a)
{
#if defined(__SSE4_2__)
    return _mm_ceil_ps(a);
#elif defined(__SSE4_1__)
    return _mm_round_ps(a, _MM_FROUND_TO_POS_INF | _MM_FROUND_NO_EXC);
#elif defined(__SSE2__)
    f32x4 truncated = _mm_cvtepi32_ps(_mm_cvttps_epi32(a));
    f32x4 increment = _mm_cmplt_ps(truncated, a);
          increment = _mm_and_si128(increment, f32x4_one());

    return _mm_add_ps(truncated, increment);
#else
    __m64 low       = _mm_cvttps_pi32(a);
    __m64 high      = _mm_cvttps_pi32(_mm_movehl_ps(a, a));
    f32x4 truncated = _mm_cvtpi32x2_ps(low, high);
    f32x4 increment = _mm_cmplt_ps(truncated, a);
    f32x4 increment = _mm_and_ps(increment, f32x4_one());

    return _mm_add_ps(truncated, increment);
#endif
}


static bad_forceinline f32x4 bad_veccall f32x4_clamp(f32x4 a, f32x4 min, f32x4 max)
{
    return _mm_min_ps(_mm_max_ps(a, min), max);
}


static bad_forceinline f32x4 bad_veccall f32x4_lerp(f32x4 a, f32x4 b, f32x4 t)
{
    const f32x4 vone = f32x4_one();

    f32x4 one_min_t = f32x4_sub(vone, t);

    return f32x4_mul_add(one_min_t, a, f32x4_mul(t, b));
}


static bad_forceinline f32x4 bad_veccall f32x4_copysign(f32x4 a, f32x4 reference_sign)
{
    const mask128 value_mask = {0x7FFFFFFF7FFFFFFF, 0x7FFFFFFF7FFFFFFF};

    mask128 a_bits    = f32x4_as_mask128(a);
    mask128 sign_bits = f32x4_as_mask128(reference_sign);
            sign_bits = mask128_and_not(sign_bits, value_mask);
    mask128 a_value   = mask128_and(a_bits, value_mask);
    mask128 copysign  = mask128_or(a_value, sign_bits);

    return mask128_as_f32x4(copysign);
}


static bad_forceinline f32x4 bad_veccall f32x4_mul_by_sign(f32x4 a, f32x4 reference_sign)
{
    mask128 a_bits    = f32x4_as_mask128(a);
    mask128 sign_bits = f32x4_as_mask128(reference_sign);
            sign_bits = mask128_keep_highbit32(sign_bits);

    mask128 mul_by_sign_bits = mask128_xor(a_bits, sign_bits);

    return mask128_as_f32x4(mul_by_sign_bits);
}


// ========== Trigonometry ===========
// TODO(review): try to find an approximation proper to cos? Or keep it as is?
static bad_inline f32x4 bad_veccall f32x4_cos(f32x4 x)
{
    const f32x4 vhalf_pi = f32x4_set_all(half_pi);

    f32x4 shifted_x = f32x4_add(x, vhalf_pi);
    
    return f32x4_sin(shifted_x);
}


// Expects inputs in [0, pi/2]
static bad_inline f32x4 bad_veccall f32x4_cos_0_halfpi(f32x4 x)
{
    const f32x4 a2  = f32x4_set_all(-.4999999963f);
    const f32x4 a4  = f32x4_set_all( .0416666418f);
    const f32x4 a6  = f32x4_set_all(-.0013888397f);
    const f32x4 a8  = f32x4_set_all( .0000247609f);
    const f32x4 a10 = f32x4_set_all(-.0000002605f);
    const f32x4 one = f32x4_one();

    f32x4 x2  = f32x4_mul(x, x);
    f32x4 res = f32x4_mul_add(a10, x2,  a8);
          res = f32x4_mul_add(res, x2,  a6);
          res = f32x4_mul_add(res, x2,  a4);
          res = f32x4_mul_add(res, x2,  a2);
          res = f32x4_mul_add(res, x2, one);

    return res;
}


// Expects values in [-pi, pi]
static bad_inline f32x4 bad_veccall f32x4_sin(f32x4 x)
{
    const f32x4 vpi_rcp = f32x4_set_all(pi_rcp);
    const f32x4 vpi     = f32x4_set_all(pi);

    f32x4   euclidian_div_f32 = f32x4_mul(x, vpi_rcp);
            euclidian_div_f32 = f32x4_trunc(euclidian_div_f32);
    mask128 euclidian_div_s32 = f32x4_to_s32x4(euclidian_div_f32);
    mask128 sin_x_neg         = mask128_keep_lowbit32(euclidian_div_s32);
            sin_x_neg         = mask128_shift_left32(sin_x_neg, 31);

    x = f32x4_nmul_add(euclidian_div_f32, vpi, x);

    f32x4   sin_x             = f32x4_sin_npi_pi(x);
    mask128 signed_sin_x_bits = f32x4_as_mask128(sin_x);
            signed_sin_x_bits = mask128_xor(signed_sin_x_bits, sin_x_neg);

    return mask128_as_f32x4(signed_sin_x_bits);
}


// Expects inputs in [-pi, pi]
static bad_inline f32x4 bad_veccall f32x4_sin_npi_pi(f32x4 x)
{
    const f32x4 c1  = f32x4_set_all(-.10132118f);
    const f32x4 c3  = f32x4_set_all( .0066208798f);
    const f32x4 c5  = f32x4_set_all(-.00017350505f);
    const f32x4 c7  = f32x4_set_all( .0000025222919f);
    const f32x4 c9  = f32x4_set_all(-.000000023317787f);
    const f32x4 c11 = f32x4_set_all( .00000000013291342f);
    const f32x4 er  = f32x4_set_all(3.1415927f + .00000008742278f);

    f32x4 x2  = f32x4_mul(x, x);
    f32x4 res = f32x4_mul_add(x2, c11, c9);
          res = f32x4_mul_add(x2, res, c7);
          res = f32x4_mul_add(x2, res, c5);
          res = f32x4_mul_add(x2, res, c3);
          res = f32x4_mul_add(x2, res, c1);
          res = f32x4_mul(x, res);
          res = f32x4_mul(res, f32x4_sub(x, er));

    return f32x4_mul(res, f32x4_add(x, er));
}


static bad_inline f32x4 bad_veccall f32x4_tan(f32x4 a)
{
/*
    // Constants
#if defined(__SSE2__)
    const mask128 three = _mm_srli_epi32(mask128_all1(), 30);
#else
    const mask128 three = mask128_set_all(3u);
#endif

    const f32x4 four_over_pi = f32x4_set_all(1.27323954473516268615f),
                       pi_over_four = f32x4_set_all(.78539816339744830962f),
                       c3           = f32x4_set_all(.333331568548f),
                       c5           = f32x4_set_all(.133387994085f),
                       c7           = f32x4_set_all(.0534112807f),
                       c9           = f32x4_set_all(.0244301354525f),
                       c11          = f32x4_set_all(.00311992232697f),
                       c13          = f32x4_set_all(.00938540185543f);

    f32x4 sign_a = f32x4_sign(a);
    a            = f32x4_abs(a);
    f32x4 k      = f32x4_floor(f32x4_mul(a, four_over_pi));
    f32x4 y      = f32x4_nmul_add(k, pi_over_four, x);

#if defined(__SSE2__)
    mask128 k_mod_4 = _mm_cvtps_epi32(k);
            k_mod_4 = mask128_and(k_mod_4, three);
#endif
    mask128 k_mod_4 = mask128_and(k, three);
#endif
    f32x4 z;

    { // Select z
        f32 z_table[4] =
        {
            y,
            f32x4_sub(pi_over_4, y),
            f32x4_neg(y),
            f32x4_sub(y, pi_over_4)
        };

        f32x4_copy_0(z, z_table[mask128_get_0(k)]));
        f32x4_copy_1(z, z_table[mask128_get_1(k)]));
        f32x4_copy_2(z, z_table[mask128_get_2(k)]));
        f32x4_copy_3(z, z_table[mask128_get_3(k)]));
    }

    f32 z2    = f32x4_mul(z, z);
    f32 tan_z = f32x4_mul_add(  c13, z2, c11);
        tan_z = f32x4_mul_add(tan_z, z2, c9);
        tan_z = f32x4_mul_add(tan_z, z2, c7);
        tan_z = f32x4_mul_add(tan_z, z2, c5);
        tan_z = f32x4_mul_add(tan_z, z2, c3);
    
    tan_z = f32x4_mul(tan_z, z);

    f32x4 tan_z_rcp = f32x4_rcp(tan_z);
    f32x4
    if (k == 1 || k == 2)
    {
        tan_z = 1.f / tan_z;
    }

    return sign_a * tan_z;
*/
    return a;
}


// Expects inputs in [-1; 1]
// Max error: ~1.5974045e-5
// Max relative error: ~0.0005%
static bad_inline f32x4 bad_veccall f32x4_acos(f32x4 x)
{
    const f32x4 vhalf_pi = f32x4_set_all(half_pi);
    const f32x4 vone     = f32x4_one();
    const f32x4 a2       = f32x4_set_all(-.0392588f);
    const f32x4 a4       = f32x4_set_all(.179323f);
    const f32x4 a6       = f32x4_set_all(-1.75866f);
    const f32x4 a8       = f32x4_set_all(-3.66063f);

    f32x4 abs_x = f32x4_abs(x);

    f32x4 acos  = f32x4_mul_add(a2,   abs_x, a4);
          acos  = f32x4_mul_add(acos, abs_x, a6);
          acos  = f32x4_mul_add(acos, abs_x, a8);
    f32x4 shift = f32x4_mul_sub(abs_x, abs_x, abs_x);
          acos  = f32x4_div(shift, acos);
          acos  = f32x4_add(abs_x, acos);

    f32x4 left = f32x4_sqrt(f32x4_sub(vone, acos));
          left = f32x4_sub(left, vone);
    f32x4 mul  = f32x4_mul_by_sign(left, x);

    return f32x4_mul_add(mul, vhalf_pi, vhalf_pi);
}




// ======== Fused operations ========
// a * b + c
static bad_forceinline f32x4 bad_veccall f32x4_mul_add(f32x4 a, f32x4 b, f32x4 c)
{
#if defined(__FMA__)
    return _mm_fmadd_ps(a, b, c);
#else
    return _mm_add_ps(_mm_mul_ps(a, b), c);
#endif
}


// a * b - c
static bad_forceinline f32x4 bad_veccall f32x4_mul_sub(f32x4 a, f32x4 b, f32x4 c)
{
#if defined(__FMA__)
    return _mm_fmsub_ps(a, b, c);
#else
    return _mm_sub_ps(_mm_mul_ps(a, b), c);
#endif
}


// -a * b + c
static bad_forceinline f32x4 bad_veccall f32x4_nmul_add(f32x4 a, f32x4 b, f32x4 c)
{
#if defined(__FMA__)
    return _mm_fnmadd_ps(a, b, c);
#else
    return f32x4_sub(c, f32x4_mul(a, b));
#endif
}


// -a * b - c
static bad_forceinline f32x4 bad_veccall f32x4_nmul_sub(f32x4 a, f32x4 b, f32x4 c)
{
#if defined(__FMA__)
    return _mm_fnmsub_ps(a, b, c);
#else
    return f32x4_sub(f32x4_neg(c), f32x4_mul(a, b));
#endif
}


// ============ Comparison ============
static bad_forceinline mask128 bad_veccall f32x4_neq(f32x4 a, f32x4 b)
{
    return f32x4_as_mask128(_mm_cmpneq_ps(a, b));
}


static bad_forceinline mask128 bad_veccall f32x4_eq(f32x4 a, f32x4 b)
{
    return f32x4_as_mask128(_mm_cmpeq_ps(a, b));
}


static bad_forceinline mask128 bad_veccall f32x4_ge(f32x4 a, f32x4 b)
{
    return f32x4_as_mask128(_mm_cmpge_ps(a, b));
}


static bad_forceinline mask128 bad_veccall f32x4_gt(f32x4 a, f32x4 b)
{
    return f32x4_as_mask128(_mm_cmpgt_ps(a, b));
}


static bad_forceinline mask128 bad_veccall f32x4_le(f32x4 a, f32x4 b)
{
    return f32x4_as_mask128(_mm_cmple_ps(a, b));
}


static bad_forceinline mask128 bad_veccall f32x4_lt(f32x4 a, f32x4 b)
{
    return f32x4_as_mask128(_mm_cmplt_ps(a, b));
}


// ============= Tests ==============
static bad_forceinline mask128 bad_veccall f32x4_is_positive(f32x4 a)
{
#if defined(__SSE2__)
    mask128 a_mask    = f32x4_as_mask128(a);
    mask128 sign_only = mask128_shift_right32(a_mask, 31);
    mask128 zero_mask = mask128_zero();

    return _mm_cmpeq_epi32(sign_only, zero_mask);
#else
    f32x4 vzero = f32x4_zero();
    
    return f32x4_ge(a, vzero);
#endif
}


static bad_forceinline mask128 bad_veccall f32x4_is_negative(f32x4 a)
{
#if defined(__SSE2__)
    mask128 a_mask    = f32x4_as_mask128(a);
    mask128 zero_mask = mask128_zero();

    return _mm_cmpgt_epi32(a_mask, zero_mask);
#else
    f32x4 vzero = f32x4_zero();
    
    return f32x4_neq(a_mask, vzero);
#endif
}


static bad_forceinline mask128 bad_veccall f32x4_is_nan(f32x4 a)
{
    // nan is the only value for which a == a returns false
    // NOTE: I have not found any faster implementation
    //       (_mm_cmpneq_epi32 only exists with AVX512F + AVX512VL)
    return f32x4_neq(a, a);
}


static bad_forceinline mask128 bad_veccall f32x4_is_infinite(f32x4 a)
{
    // +inf is 0x7F800000, ninf() is 0xFF800000
#if defined(__SSE2__)
    mask128 a_abs    = mask128_all1();
    mask128 inf_mask = _mm_srli_epi32(_mm_slli_epi32(a_abs, 24), 1);
            a_abs    = mask128_and(_mm_srli_epi32(a_abs, 1), _mm_castps_si128(a));

    return _mm_cmpeq_epi32(a_abs, inf_mask);
#else
    mask128 value    = mask128_value32();
    mask128 inf_mask = mask128_exponent32();
    return _mm_cmpeq_ps(_mm_and_ps(value, a), inf_mask);
#endif
}


static bad_forceinline mask128 bad_veccall f32x4_is_finite(f32x4 a)
{
    // a is finite if its exponent is not all 1
    mask128 exp = mask128_exponent32();
    
    return mask128_neq(mask128_and(f32x4_as_mask128(a), exp), exp);
}