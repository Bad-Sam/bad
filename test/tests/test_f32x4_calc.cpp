#include "test_f32x4_calc.h"

#include "../test.h"
#include "../test_values.h"

#include <bad/qualifiers.h>
#include <bad/math/f32x4_calc.h>

BAD_NAMESPACE_START

void test_f32x4_hadd3()
{
    f32x4 a0 = f32x4_set(-1.f,   snanf, .0f, 8.f);
    f32x4 a1 = f32x4_set(-1.f,   -inff, .0f, 8.f);
    f32x4 a2 = f32x4_set(-1.f,    inff, .0f, 8.f);
    f32x4 a3 = f32x4_set(-1.f, denormf, .0f, 8.f);

    f32 expected_hadd[4] = {qnanf, -inff, inff, denormf - 1.f};

    f32 hadd0_store[4], hadd1_store[4], hadd2_store[4], hadd3_store[4];

    f32x4_store(hadd0_store, f32x4_hadd3(a0));
    f32x4_store(hadd1_store, f32x4_hadd3(a1));
    f32x4_store(hadd2_store, f32x4_hadd3(a2));
    f32x4_store(hadd3_store, f32x4_hadd3(a3));

    bad_test_check(is_qnan(hadd0_store[0])
                && hadd1_store[0] == expected_hadd[1]
                && hadd2_store[0] == expected_hadd[2]
                && hadd3_store[0] == expected_hadd[3]);
}


void test_f32x4_hadd4()
{
    f32x4 a0 = f32x4_set(snanf,   -1.f, .0f, 8.f);
    f32x4 a1 = f32x4_set(-inff,   -1.f, .0f, 8.f);
    f32x4 a2 = f32x4_set(inff,    -1.f, .0f, 8.f);
    f32x4 a3 = f32x4_set(denormf, -1.f, .0f, 8.f);

    f32 expected_hadd[4] = {qnanf, -inff, inff, denormf + 7.f};

    f32 hadd0_store[4], hadd1_store[4], hadd2_store[4], hadd3_store[4];

    f32x4_store(hadd0_store, f32x4_hadd4(a0));
    f32x4_store(hadd1_store, f32x4_hadd4(a1));
    f32x4_store(hadd2_store, f32x4_hadd4(a2));
    f32x4_store(hadd3_store, f32x4_hadd4(a3));

    bad_test_check(is_qnan(hadd0_store[0])
                && hadd1_store[0] == expected_hadd[1]
                && hadd2_store[0] == expected_hadd[2]
                && hadd3_store[0] == expected_hadd[3]);
}


void test_f32x4_sum3()
{
    f32x4 a0 = f32x4_set(-1.f,   snanf, .0f, 8.f);
    f32x4 a1 = f32x4_set(-1.f,   -inff, .0f, 8.f);
    f32x4 a2 = f32x4_set(-1.f,    inff, .0f, 8.f);
    f32x4 a3 = f32x4_set(-1.f, denormf, .0f, 8.f);

    f32 expected_sum[4] = {qnanf, -inff, inff, denormf - 1.f};

    f32 sum0_store = f32x4_sum3(a0);
    f32 sum1_store = f32x4_sum3(a1);
    f32 sum2_store = f32x4_sum3(a2);
    f32 sum3_store = f32x4_sum3(a3);

    bad_test_check(is_qnan(sum0_store)
                && sum1_store == expected_sum[1]
                && sum2_store == expected_sum[2]
                && sum3_store == expected_sum[3]);
}


void test_f32x4_sum4()
{
    f32x4 a0 = f32x4_set(snanf,   -1.f, .0f, 8.f);
    f32x4 a1 = f32x4_set(-inff,   -1.f, .0f, 8.f);
    f32x4 a2 = f32x4_set(inff,    -1.f, .0f, 8.f);
    f32x4 a3 = f32x4_set(denormf, -1.f, .0f, 8.f);

    f32 expected_sum[4] = {qnan, -inff, inff, denormf + 7.f};

    f32 sum0_store = f32x4_sum4(a0);
    f32 sum1_store = f32x4_sum4(a1);
    f32 sum2_store = f32x4_sum4(a2);
    f32 sum3_store = f32x4_sum4(a3);

    bad_test_check(is_qnan(sum0_store)
                && sum1_store == expected_sum[1]
                && sum2_store == expected_sum[2]
                && sum3_store == expected_sum[3]);
}


void test_f32x4_abs()
{
    f32x4 a = f32x4_set(qnanf, -inff, inff, -denormf);
    f32x4 b = f32x4_set(-10.26f, -.0f, .0f, 3.56f);

    f32 expected_a[4] = {snanf, inff, inff, -denormf};
    f32 expected_b[4] = {10.26f, .0f, .0f, 3.56f};

    f32 a_abs_out[4];
    f32 b_abs_out[4];
    f32x4_storeu(a_abs_out, f32x4_abs(a));
    f32x4_storeu(b_abs_out, f32x4_abs(b));

    bad_test_check(is_nan(a_abs_out[0])
                && a_abs_out[1] == expected_a[1]
                && a_abs_out[2] == expected_a[2]
                && a_abs_out[3] == expected_a[3]
                && b_abs_out[0] == expected_b[0]
                && b_abs_out[1] == expected_b[1]
                && b_abs_out[2] == expected_b[2]
                && b_abs_out[3] == expected_b[3]);
}


void test_f32x4_sign()
{
    f32x4 a = f32x4_set(-qnanf, -inff, inff, denormf);
    f32x4 b = f32x4_set(-10.26f, -.0f, .0f, 3.56f);

    f32 expected_a[4] = {-1.f, -1.f, 1.f, -1.f};
    f32 expected_b[4] = {-1.f, -1.f, 1.f, 1.f};

    f32 a_sign_out[4];
    f32 b_sign_out[4];
    f32x4_storeu(a_sign_out, f32x4_sign(a));
    f32x4_storeu(b_sign_out, f32x4_sign(b));

    bad_test_check(a_sign_out[0] == expected_a[0]
                && a_sign_out[1] == expected_a[1]
                && a_sign_out[2] == expected_a[2]
                && a_sign_out[3] == expected_a[3]
                && b_sign_out[0] == expected_b[0]
                && b_sign_out[1] == expected_b[1]
                && b_sign_out[2] == expected_b[2]
                && b_sign_out[3] == expected_b[3]);
}


void test_f32x4_neg()
{
    f32x4 a = f32x4_set(snanf, inff, -inff, -denormf);
    f32x4 b = f32x4_set(-10.f, -.0f, 12.f, 3.f);

    f32 expected_a_neg[4] = {qnanf, -inff, inff, denormf};
    f32 expected_b_neg[4] = {10.f, .0f, -12.f, -3.f};

    f32 a_neg_out[4];
    f32 b_neg_out[4];
    f32x4_storeu(a_neg_out, f32x4_neg(a));
    f32x4_storeu(b_neg_out, f32x4_neg(b));

    bad_test_check(is_nan(a_neg_out[0])
                && a_neg_out[1] == expected_a_neg[1]
                && a_neg_out[2] == expected_a_neg[2]
                && a_neg_out[3] == expected_a_neg[3]
                && b_neg_out[0] == expected_b_neg[0]
                && b_neg_out[1] == expected_b_neg[1]
                && b_neg_out[2] == expected_b_neg[2]
                && b_neg_out[3] == expected_b_neg[3]);
}


void test_f32x4_frac()
{
    f32x4 a = f32x4_set(snanf, inff, ninff, -denormf);
    f32x4 b = f32x4_set(-10.f, -.9f, .1f, 3.868f);

    f32 expected_a_frac[4] = {qnanf, qnanf, qnanf, -denormf};
    f32 expected_b_frac[4] = {.0f, -.9f, .1f, .868000030517578125f};

    f32 a_frac_out[4];
    f32 b_frac_out[4];
    f32x4_storeu(a_frac_out, f32x4_frac(a));
    f32x4_storeu(b_frac_out, f32x4_frac(b));

    bad_test_check(is_qnan(a_frac_out[0])
                && is_qnan(a_frac_out[1])
                && is_qnan(a_frac_out[2])
                && a_frac_out[3] == expected_a_frac[3]
                && b_frac_out[0] == expected_b_frac[0]
                && b_frac_out[1] == expected_b_frac[1]
                && b_frac_out[2] == expected_b_frac[2]
                && b_frac_out[3] == expected_b_frac[3]);
}


void test_f32x4_mod()
{
    f32x4 a = f32x4_set(qnanf, inff, -inff, denormf);
    f32x4 b = f32x4_set(-10.f, 5.f, 12.f, 3.25f);
    f32x4 m = f32x4_set(3.f, 5.f, 5.25f, 1.f);

#if defined(__SSE__)
    f32 expected_a[4] = {qnanf, qnanf, qnanf, denormf};
#else
    f32 expected_a[4] = {qnanf, inff, -inff, denormf};
#endif
    f32 expected_b[4] = {-1.f, .0f, 1.5f, .25f};

    f32 a_mod_m_store[4];
    f32 b_mod_m_store[4];

    f32x4_storeu(a_mod_m_store, f32x4_mod(a, m));
    f32x4_storeu(b_mod_m_store, f32x4_mod(b, m));

    bad_test_check(is_nan(a_mod_m_store[0])
#if defined(__SSE__)
                && is_qnan(a_mod_m_store[1])
                && is_qnan(a_mod_m_store[2])
#else
                && a_mod_m_store[1] == expected_a[1]
                && a_mod_m_store[2] == expected_a[2]
#endif
                && a_mod_m_store[3] == expected_a[3]
                && b_mod_m_store[0] == expected_b[0]
                && b_mod_m_store[1] == expected_b[1]
                && b_mod_m_store[2] == expected_b[2]
                && b_mod_m_store[3] == expected_b[3]);
}


void test_f32x4_trunc()
{
    // Edge cases can be handled with f32x4_is_finite() + f32x4_blend()
    f32x4 a             = f32x4_set(-10.5f, -.9f, .1f, 3.268f);
    f32   expected_a[4] = {-10.f, -.0f, .0f, 3.f};

    f32 trunc_a_out[4];
    f32x4_storeu(trunc_a_out, f32x4_trunc(a));

    bad_test_check(trunc_a_out[0] == expected_a[0]
                && trunc_a_out[1] == expected_a[1]
                && trunc_a_out[2] == expected_a[2]
                && trunc_a_out[3] == expected_a[3]);
}


void test_f32x4_round()
{
    // Edge cases can be handled with f32x4_is_finite() + f32x4_blend()
    f32x4 a             = f32x4_set(-10.5f, -.9f, .2f, .0f);
    f32   expected_a[4] = {-10.f, -1.f, .0f, .0f};

    f32 round_a_store[4];
    f32x4_storeu(round_a_store, f32x4_round(a));

    bad_test_check(round_a_store[0] == expected_a[0]
                && round_a_store[1] == expected_a[1]
                && round_a_store[2] == expected_a[2]
                && round_a_store[3] == expected_a[3]);
}


void test_f32x4_floor()
{
    // Edge cases can be handled with f32x4_is_finite() + f32x4_blend()
    f32x4 a             = f32x4_set(-10.5f, -.9f, .1f, 3.868f);
    f32   expected_a[4] = {-11.f, -1.f, .0f, 3.f};

    f32 trunc_a_out[4];
    f32x4_storeu(trunc_a_out, f32x4_floor(a));

    bad_test_check(trunc_a_out[0] == expected_a[0]
                && trunc_a_out[1] == expected_a[1]
                && trunc_a_out[2] == expected_a[2]
                && trunc_a_out[3] == expected_a[3]);
}


void test_f32x4_ceil()
{
    // Edge cases can be handled with f32x4_is_finite() + f32x4_blend()
    f32x4 a             = f32x4_set(-10.5f, -.9f, .1f, 3.868f);
    f32   expected_a[4] = {-10.f, -.0f, 1.f, 4.f};

    f32 ceil_a_out[4];
    f32x4_storeu(ceil_a_out, f32x4_ceil(a));

    bad_test_check(ceil_a_out[0] == expected_a[0]
                && ceil_a_out[1] == expected_a[1]
                && ceil_a_out[2] == expected_a[2]
                && ceil_a_out[3] == expected_a[3]);
}


void test_f32x4_clamp()
{
    f32x4 a0  = f32x4_set(snanf, -inff, inff, denormf);
    f32x4 a1  = f32x4_set(-.0f, .0f, -11.f, -56.25f);
    f32x4 min = f32x4_set(.0f, -inff, -10.f, -56.8f);
    f32x4 max = f32x4_set(1.f, 75.56f, 10.f, -56.f);

    f32 expected_clamp0[4] = {.0f, -inff, 10.f, -56.f};
    f32 expected_clamp1[4] = {.0f, .0f, -10.f, -56.25f};

    f32 clamp0_store[4];
    f32 clamp1_store[4];

    f32x4_storeu(clamp0_store, f32x4_clamp(a0, min, max));
    f32x4_storeu(clamp1_store, f32x4_clamp(a1, min, max));

    bad_test_check(clamp0_store[0] == expected_clamp0[0]
                && clamp0_store[1] == expected_clamp0[1]
                && clamp0_store[2] == expected_clamp0[2]
                && clamp0_store[3] == expected_clamp0[3]
                && clamp1_store[0] == expected_clamp1[0]
                && clamp1_store[1] == expected_clamp1[1]
                && clamp1_store[2] == expected_clamp1[2]
                && clamp1_store[3] == expected_clamp1[3]);
}


void test_f32x4_lerp()
{
    f32x4 a0 = f32x4_set(snanf, -inff, inff, denormf);
    f32x4 a1 = f32x4_set(10.1f, .0f, -2.85f, 6.5f);
    f32x4 b  = f32x4_set(1.f, -.0f, 10.6f, -9595.6083984375f);
    f32x4 t  = f32x4_set(.0f, .25f, .5f, 1.f);

    f32 expected_lerp0[4] = {qnanf, -inff, inff, -9595.6083984375f};
    f32 expected_lerp1[4] = {10.1f, .0f, 3.875f, -9595.6083984375f};

    f32 lerp0_store[4];
    f32 lerp1_store[4];
    f32x4_storeu(lerp0_store, f32x4_lerp(a0, b, t));
    f32x4_storeu(lerp1_store, f32x4_lerp(a1, b, t));

    bad_test_check(is_qnan(lerp0_store[0])
                && lerp0_store[1] == expected_lerp0[1]
                && lerp0_store[2] == expected_lerp0[2]
                && lerp0_store[3] == expected_lerp0[3]
                && lerp1_store[0] == expected_lerp1[0]
                && lerp1_store[1] == expected_lerp1[1]
                && are_equal_ulp(lerp1_store[2], expected_lerp1[2])
                && lerp1_store[3] == expected_lerp1[3]);
}


void test_f32x4_mul_add()
{
    f32x4 a0 = f32x4_set(snanf, -inff, inff, denormf);
    f32x4 a1 = f32x4_set(10.1f, .0f, -2.85f, 6.5f);
    f32x4 b  = f32x4_set(1.f, -.0f, 10.6f, -9595.6083984375f);
    f32x4 c  = f32x4_set(.0f, 1000.f, -6.2f, .0f);

    f32 expected_fma0[4] = {qnanf, qnanf, inff, -denormf * 9595.6083984375f};
    f32 expected_fma1[4] = {10.1f, 1000.f, -36.41f, -62371.453125f /* closest f32 */};

    f32 fma0_store[4];
    f32 fma1_store[4];

    f32x4_storeu(fma0_store, f32x4_mul_add(a0, b, c));
    f32x4_storeu(fma1_store, f32x4_mul_add(a1, b, c));

    bad_test_check(is_qnan(fma0_store[0])
                && is_qnan(fma0_store[1])
                && fma0_store[2] == expected_fma0[2]
                && fma0_store[3] == expected_fma0[3]
#if defined(__FMA__)
                && fma1_store[0] == expected_fma1[0]
                && fma1_store[1] == expected_fma1[1]
                && fma1_store[2] == expected_fma1[2]
                && fma1_store[3] == expected_fma1[3]
#else
                && are_equal_ulp(fma1_store[0], expected_fma1[0])
                && are_equal_ulp(fma1_store[1], expected_fma1[1])
                && are_equal_ulp(fma1_store[2], expected_fma1[2])
                && are_equal_ulp(fma1_store[3], expected_fma1[3])
#endif
                  );
}


void test_f32x4_mul_sub()
{
    f32x4 a0 = f32x4_set(snanf, -inff, inff, denormf);
    f32x4 a1 = f32x4_set(10.1f, .0f, -2.85f, 6.5f);
    f32x4 b  = f32x4_set(1.f, -.0f, 10.6f, -9595.6083984375f);
    f32x4 c  = f32x4_set(.0f, 1000.f, -6.2f, .0f);

    f32 expected_fms1[4] = {qnanf, qnanf, inff, -denormf * 9595.6083984375f};
    f32 expected_fms2[4] = {10.1f, -1000.f, -24.01f, -62371.453125f /* closest f32 */};

    f32 fms1_store[4];
    f32 fms2_store[4];

    f32x4_storeu(fms1_store, f32x4_mul_sub(a0, b, c));
    f32x4_storeu(fms2_store, f32x4_mul_sub(a1, b, c));

    bad_test_check(is_qnan(fms1_store[0])
                && is_qnan(fms1_store[1])
                && fms1_store[2] == expected_fms1[2]
                && fms1_store[3] == expected_fms1[3]
#if defined(__FMA__)
                && fms2_store[0] == expected_fms2[0]
                && fms2_store[1] == expected_fms2[1]
                && fms2_store[2] == expected_fms2[2]
                && fms2_store[3] == expected_fms2[3]
#else
                && are_equal_ulp(fms2_store[0], expected_fms2[0])
                && are_equal_ulp(fms2_store[1], expected_fms2[1])
                && are_equal_ulp(fms2_store[2], expected_fms2[2])
                && are_equal_ulp(fms2_store[3], expected_fms2[3])
#endif
                  );
}


void test_f32x4_nmul_add()
{
    f32x4 a0 = f32x4_set(snanf, -inff, inff, denormf);
    f32x4 a1 = f32x4_set(10.1f, .0f, -2.85f, 6.5f);
    f32x4 b  = f32x4_set(1.f, -.0f, 10.6f, -9595.6083984375f);
    f32x4 c  = f32x4_set(.0f, 1000.f, -6.2f, .0f);

    f32 expected_fnma0[4] = {qnanf, qnanf, -inff, denormf * 9595.6083984375f};
    f32 expected_fnma1[4] = {-10.1f, 1000.f, 24.01f, 62371.453125f /* closest f32 */};

    f32 fnma0_store[4];
    f32 fnma1_store[4];

    f32x4_storeu(fnma0_store, f32x4_nmul_add(a0, b, c));
    f32x4_storeu(fnma1_store, f32x4_nmul_add(a1, b, c));

    // Behaviour with nan slightly differs between FMA3 and SSE operations
    bad_test_check(is_qnan(fnma0_store[0])
#if defined(__FMA__)
                && is_qnan(fnma0_store[1])
                && fnma0_store[2] == expected_fnma0[2]
                && fnma0_store[3] == expected_fnma0[3]
                && fnma1_store[0] == expected_fnma1[0]
                && fnma1_store[1] == expected_fnma1[1]
                && fnma1_store[2] == expected_fnma1[2]
                && fnma1_store[3] == expected_fnma1[3]
#else
                && is_qnan(fnma0_store[1])
                && fnma0_store[2] == expected_fnma0[2]
                && fnma0_store[3] == expected_fnma0[3]
                && are_equal_ulp(fnma1_store[0], expected_fnma1[0])
                && are_equal_ulp(fnma1_store[1], expected_fnma1[1])
                && are_equal_ulp(fnma1_store[2], expected_fnma1[2])
                && are_equal_ulp(fnma1_store[3], expected_fnma1[3])
#endif
                  );
}


void test_f32x4_nmul_sub()
{
    f32x4 a0 = f32x4_set(snanf, -inff, inff, denormf);
    f32x4 a1 = f32x4_set(10.1f, .0f, -2.85f, 6.5f);
    f32x4 b  = f32x4_set(1.f, -.0f, 10.6f, -9595.6083984375f);
    f32x4 c  = f32x4_set(.0f, 1000.f, -6.2f, .0f);

    f32 expected_fnms1[4] = {qnanf, qnanf, -inff, denormf * 9595.6083984375f};
    f32 expected_fnms2[4] = {-10.1f, -1000.f, 36.41f, 62371.453125f};

    f32 fnms1_store[4];
    f32 fnms2_store[4];

    f32x4_storeu(fnms1_store, f32x4_nmul_sub(a0, b, c));
    f32x4_storeu(fnms2_store, f32x4_nmul_sub(a1, b, c));

    // Behaviour with nan slightly differs between FMA3 and SSE operations
    bad_test_check(is_qnan(fnms1_store[0])
#if defined(__FMA__)
                && is_qnan(fnms1_store[1])
                && fnms1_store[2] == expected_fnms1[2]
                && fnms1_store[3] == expected_fnms1[3]
                && fnms2_store[0] == expected_fnms2[0]
                && fnms2_store[1] == expected_fnms2[1]
                && fnms2_store[2] == expected_fnms2[2]
                && fnms2_store[3] == expected_fnms2[3]
#else
                && is_qnan(fnms1_store[1])
                && fnms1_store[2] == expected_fnms1[2]
                && fnms1_store[3] == expected_fnms1[3]
                && are_equal_ulp(fnms2_store[0], expected_fnms2[0])
                && are_equal_ulp(fnms2_store[1], expected_fnms2[1])
                && are_equal_ulp(fnms2_store[2], expected_fnms2[2])
                && are_equal_ulp(fnms2_store[3], expected_fnms2[3])
#endif
                  );
}


// =========== Trigonometry ===========
void test_f32x4_sin()
{
    f32x4 a = f32x4_set(qnanf, ninff, inff, denormf);
    //  0, pi, pi / 4, pi / 2
    f32x4 b = f32x4_set(.0f, 3.14159265358979323846f, .78539816339744830962f, 1.57079632679489661923f);

    f32 sin0_store[4];
    f32 sin1_store[4];
    f32x4_store(sin0_store, f32x4_sin(a));
    f32x4_store(sin1_store, f32x4_sin(b));

    f32 expected_sin0[4] = {qnanf, qnanf, qnanf, denormf};
    f32 expected_sin1[4] = {.0f, -.0f, .7071067811865475244f, 1.f};

    bad_test_check(is_qnan(sin0_store[0])
                && is_qnan(sin0_store[1])
                && is_qnan(sin0_store[2])
                && are_equal_n_ulp(sin0_store[3], expected_sin0[3], 5.f)
                && are_equal_n_ulp(sin1_store[0], expected_sin1[0], 5.f)
                && are_equal_n_ulp(sin1_store[1], expected_sin1[1], 5.f)
                && are_equal_n_ulp(sin1_store[2], expected_sin1[2], 5.f)
                && are_equal_n_ulp(sin1_store[3], expected_sin1[3], 5.f));
}


// ============ Comparison ============
void test_f32x4_neq()
{
    f32x4 a0 = f32x4_set(snanf, qnanf, -inff, denormf);
    f32x4 a1 = f32x4_set(.0f, 2.f, -1.f, -denormf);
    f32x4 b  = f32x4_set(qnanf, qnanf, -inff, -denormf);

    u32 neq0_store[4];
    u32 neq1_store[4];
    mask128_storeu(neq0_store, f32x4_neq(a0, b));
    mask128_storeu(neq1_store, f32x4_neq(a1, b));

    u32 expected_neq0[4] = {all1, all1, zero, all1};
    u32 expected_neq1[4] = {all1, all1, all1, zero};

    bad_test_check(neq0_store[0] == expected_neq0[0]
                && neq0_store[1] == expected_neq0[1]
                && neq0_store[2] == expected_neq0[2]
                && neq0_store[3] == expected_neq0[3]
                && neq1_store[0] == expected_neq1[0]
                && neq1_store[1] == expected_neq1[1]
                && neq1_store[2] == expected_neq1[2]
                && neq1_store[3] == expected_neq1[3]);
}


void test_f32x4_eq()
{
    f32x4 a0 = f32x4_set(snanf, qnanf, -inff, denormf);
    f32x4 a1 = f32x4_set(.0f, 2.f, -1.f, -denormf);
    f32x4 b  = f32x4_set(qnanf, qnanf, -inff, -denormf);

    u32 eq0_store[4];
    u32 eq1_store[4];
    mask128_storeu(eq0_store, f32x4_eq(a0, b));
    mask128_storeu(eq1_store, f32x4_eq(a1, b));

    u32 expected_eq0[4] = {zero, zero, all1, zero};
    u32 expected_eq1[4] = {zero, zero, zero, all1};

    bad_test_check(eq0_store[0] == expected_eq0[0]
                && eq0_store[1] == expected_eq0[1]
                && eq0_store[2] == expected_eq0[2]
                && eq0_store[3] == expected_eq0[3]
                && eq1_store[0] == expected_eq1[0]
                && eq1_store[1] == expected_eq1[1]
                && eq1_store[2] == expected_eq1[2]
                && eq1_store[3] == expected_eq1[3]);
}


void test_f32x4_ge()
{
    f32x4 a0 = f32x4_set(snanf, qnanf, -inff, denormf);
    f32x4 a1 = f32x4_set(.0f, 2.f, -1.f, -denormf);
    f32x4 b  = f32x4_set(1.f, 2.f, -inff, .0f);

    u32 ge0_store[4];
    u32 ge1_store[4];
    mask128_storeu(ge0_store, f32x4_ge(a0, b));
    mask128_storeu(ge1_store, f32x4_ge(a1, b));

    u32 expected_ge0[4] = {zero, zero, all1, zero};
    u32 expected_ge1[4] = {zero, all1, all1, all1};

    bad_test_check(ge0_store[0] == expected_ge0[0]
                && ge0_store[1] == expected_ge0[1]
                && ge0_store[2] == expected_ge0[2]
                && ge0_store[3] == expected_ge0[3]
                && ge1_store[0] == expected_ge1[0]
                && ge1_store[1] == expected_ge1[1]
                && ge1_store[2] == expected_ge1[2]
                && ge1_store[3] == expected_ge1[3]);
}


void test_f32x4_gt()
{
    f32x4 a0 = f32x4_set(snanf, qnanf, -inff, denormf);
    f32x4 a1 = f32x4_set(.0f, 2.f, -1.f, -denormf);
    f32x4 b  = f32x4_set(1.f, 2.f, -inff, .0f);

    u32 gt0_store[4];
    u32 gt1_store[4];
    mask128_storeu(gt0_store, f32x4_gt(a0, b));
    mask128_storeu(gt1_store, f32x4_gt(a1, b));

    u32 expected_gt0[4] = {zero, zero, zero, zero};
    u32 expected_gt1[4] = {zero, zero, all1, all1};

    bad_test_check(gt0_store[0] == expected_gt0[0]
                && gt0_store[1] == expected_gt0[1]
                && gt0_store[2] == expected_gt0[2]
                && gt0_store[3] == expected_gt0[3]
                && gt1_store[0] == expected_gt1[0]
                && gt1_store[1] == expected_gt1[1]
                && gt1_store[2] == expected_gt1[2]
                && gt1_store[3] == expected_gt1[3]);
}


void test_f32x4_le()
{
    f32x4 a0 = f32x4_set(snanf, qnanf, -inff, denormf);
    f32x4 a1 = f32x4_set(.0f, 2.f, -1.f, -denormf);
    f32x4 b  = f32x4_set(1.f, 2.f, -inff, .0f);

    u32 le0_store[4];
    u32 le1_store[4];
    mask128_storeu(le0_store, f32x4_le(a0, b));
    mask128_storeu(le1_store, f32x4_le(a1, b));

    u32 expected_le0[4] = {zero, zero, all1, all1};
    u32 expected_le1[4] = {all1, all1, zero, zero};

    bad_test_check(le0_store[0] == expected_le0[0]
                && le0_store[1] == expected_le0[1]
                && le0_store[2] == expected_le0[2]
                && le0_store[3] == expected_le0[3]
                && le1_store[0] == expected_le1[0]
                && le1_store[1] == expected_le1[1]
                && le1_store[2] == expected_le1[2]
                && le1_store[3] == expected_le1[3]);
}


void test_f32x4_lt()
{
    f32x4 a0 = f32x4_set(snanf, qnanf, -inff, denormf);
    f32x4 a1 = f32x4_set(.0f, 2.f, -1.f, -denormf);
    f32x4 b  = f32x4_set(1.f, 2.f, -inff, .0f);

    u32 lt0_store[4];
    u32 lt1_store[4];
    mask128_storeu(lt0_store, f32x4_lt(a0, b));
    mask128_storeu(lt1_store, f32x4_lt(a1, b));

    u32 expected_lt0[4] = {zero, zero, zero, all1};
    u32 expected_lt1[4] = {all1, zero, zero, zero};

    bad_test_check(lt0_store[0] == expected_lt0[0]
                && lt0_store[1] == expected_lt0[1]
                && lt0_store[2] == expected_lt0[2]
                && lt0_store[3] == expected_lt0[3]
                && lt1_store[0] == expected_lt1[0]
                && lt1_store[1] == expected_lt1[1]
                && lt1_store[2] == expected_lt1[2]
                && lt1_store[3] == expected_lt1[3]);
}


void test_f32x4_is_nan()
{
    f32x4 a = f32x4_set(snanf, qnanf, -inff, denormf);
    f32x4 b = f32x4_set(.0f, -.0f, 10.6f, -9595.6083984375f);

    mask_elem a_is_nan[4];
    mask_elem b_is_nan[4];
    mask128_storeu(a_is_nan, f32x4_is_nan(a));
    mask128_storeu(b_is_nan, f32x4_is_nan(b));

    mask_elem expected_a_is_nan[4] = {all1, all1, zero, zero};
    mask_elem expected_b_is_nan[4] = {zero, zero, zero, zero};

    bad_test_check(a_is_nan[0] == expected_a_is_nan[0]
                && a_is_nan[1] == expected_a_is_nan[1]
                && a_is_nan[2] == expected_a_is_nan[2]
                && a_is_nan[3] == expected_a_is_nan[3]
                && b_is_nan[0] == expected_b_is_nan[0]
                && b_is_nan[1] == expected_b_is_nan[1]
                && b_is_nan[2] == expected_b_is_nan[2]
                && b_is_nan[3] == expected_b_is_nan[3]);
}


void test_f32x4_is_infinite()
{
    f32x4 a = f32x4_set(snanf, -inff, inff, denormf);
    f32x4 b = f32x4_set(.0f, -.0f, 10.6f, -9595.6083984375f);

    mask_elem a_store[4];
    mask_elem b_store[4];
    mask128_storeu(a_store, f32x4_is_infinite(a));
    mask128_storeu(b_store, f32x4_is_infinite(b));

    mask_elem expected_a_is_inffinity[4] = {zero, all1, all1, zero};
    mask_elem expected_b_is_inffinity[4] = {zero, zero, zero, zero};

    bad_test_check(a_store[0] == expected_a_is_inffinity[0]
                && a_store[1] == expected_a_is_inffinity[1]
                && a_store[2] == expected_a_is_inffinity[2]
                && a_store[3] == expected_a_is_inffinity[3]
                && b_store[0] == expected_b_is_inffinity[0]
                && b_store[1] == expected_b_is_inffinity[1]
                && b_store[2] == expected_b_is_inffinity[2]
                && b_store[3] == expected_b_is_inffinity[3]);
}


void test_f32x4_is_finite()
{
    f32x4 a = f32x4_set(snanf, -inff, inff, denormf);
    f32x4 b = f32x4_set(.0f, -.0f, 10.6f, -9595.6083984375f);

    mask_elem a_store[4];
    mask_elem b_store[4];
    mask128_storeu(a_store, f32x4_is_finite(a));
    mask128_storeu(b_store, f32x4_is_finite(b));

    mask_elem expected_a_is_finite[4] = {zero, zero, zero, all1};
    mask_elem expected_b_is_finite[4] = {all1, all1, all1, all1};

    bad_test_check(a_store[0] == expected_a_is_finite[0]
                && a_store[1] == expected_a_is_finite[1]
                && a_store[2] == expected_a_is_finite[2]
                && a_store[3] == expected_a_is_finite[3]
                && b_store[0] == expected_b_is_finite[0]
                && b_store[1] == expected_b_is_finite[1]
                && b_store[2] == expected_b_is_finite[2]
                && b_store[3] == expected_b_is_finite[3]);
}

BAD_NAMESPACE_END