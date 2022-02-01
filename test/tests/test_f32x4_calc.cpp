#include "test_f32x4_calc.h"

#include "../test.h"
#include "../f32_values.h"

#include <bad/types.h>
#include <bad/qualifiers.h>
#include <bad/math/f32x4_calc.h>

BAD_NAMESPACE_START

void test_f32x4_hadd()
{
    const f32x4 a0 = f32x4_set(snan, -1.f, .0f, 8.f);
    const f32x4 a1 = f32x4_set(-inf, -1.f, .0f, 8.f);
    const f32x4 a2 = f32x4_set(inf, -1.f, .0f, 8.f);
    const f32x4 a3 = f32x4_set(denorm, -1.f, .0f, 8.f);

    //const f32 expected_hadd0 = snan;
    const f32 expected_hadd1 = -inf;
    const f32 expected_hadd2 = inf;
    const f32 expected_hadd3 = denorm + 7.f;

    f32 hadd0_store = f32x4_hadd(a0);
    f32 hadd1_store = f32x4_hadd(a1);
    f32 hadd2_store = f32x4_hadd(a2);
    f32 hadd3_store = f32x4_hadd(a3);

    bad_test_check(is_snan(hadd0_store)
                && hadd1_store == expected_hadd1
                && hadd2_store == expected_hadd2
                && hadd3_store == expected_hadd3);
}


void test_f32x4_abs()
{
    const f32x4 a = f32x4_set(qnan, -inf, inf, -denorm);
    const f32x4 b = f32x4_set(-10.26f, -.0f, .0f, 3.56f);

    const f32 expected_a[4] = {snan, inf, inf, denorm};
    const f32 expected_b[4] = {10.26f, .0f, .0f, 3.56f};

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


void test_f32x4_neg()
{
    const f32x4 a = f32x4_set(snan, inf, -inf, -denorm);
    const f32x4 b = f32x4_set(-10.f, -.0f, 12.f, 3.f);

    const f32 expected_a_neg[4] = {qnan, -inf, inf, denorm};
    const f32 expected_b_neg[4] = {10.f, .0f, -12.f, -3.f};

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


void test_f32x4_mod()
{
    const f32x4 a = f32x4_set(qnan, inf, -inf, denorm);
    const f32x4 b = f32x4_set(-10.f, 5.f, 12.f, 3.25f);
    const f32x4 m = f32x4_set(3.f, 5.f, 5.25f, 1.f);

#if 0 && defined(__SSE__)
    const f32 expected_a[4] = {qnan, qnan, qnan, denorm};
#else
    const f32 expected_a[4] = {qnan, inf, -inf, denorm};
#endif
    const f32 expected_b[4] = {-1.f, .0f, 1.5f, .25f};

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
    const f32x4 a             = f32x4_set(-10.5f, -.9f, .1f, 3.268f);
    const f32   expected_a[4] = {-10.f, -.0f, .0f, 3.f};

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
    const f32x4 a             = f32x4_set(-10.5f, -.9f, .2f, .0f);
    const f32   expected_a[4] = {-10.f, -1.f, .0f, .0f};

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
    const f32x4 a             = f32x4_set(-10.5f, -.9f, .1f, 3.868f);
    const f32   expected_a[4] = {-11.f, -1.f, .0f, 3.f};

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
    const f32x4 a             = f32x4_set(-10.5f, -.9f, .1f, 3.868f);
    const f32   expected_a[4] = {-10.f, -.0f, 1.f, 4.f};

    f32 ceil_a_out[4];
    f32x4_storeu(ceil_a_out, f32x4_ceil(a));

    bad_test_check(ceil_a_out[0] == expected_a[0]
                && ceil_a_out[1] == expected_a[1]
                && ceil_a_out[2] == expected_a[2]
                && ceil_a_out[3] == expected_a[3]);
}


void test_f32x4_clamp()
{
    const f32x4 a0  = f32x4_set(snan, -inf, inf, denorm);
    const f32x4 a1  = f32x4_set(-.0f, .0f, -11.f, -56.25f);
    const f32x4 min = f32x4_set(.0f, -inf, -10.f, -56.8f);
    const f32x4 max = f32x4_set(1.f, 75.56f, 10.f, -56.f);

    const f32 expected_clamp1[4] = {.0f, -inf, 10.f, -56.f};
    const f32 expected_clamp2[4] = {.0f, .0f, -10.f, -56.25f};

    f32 clamp1_store[4];
    f32 clamp2_store[4];

    f32x4_storeu(clamp1_store, f32x4_clamp(a0, min, max));
    f32x4_storeu(clamp2_store, f32x4_clamp(a1, min, max));

    bad_test_check(clamp1_store[0] == expected_clamp1[0]
                && clamp1_store[1] == expected_clamp1[1]
                && clamp1_store[2] == expected_clamp1[2]
                && clamp1_store[3] == expected_clamp1[3]
                && clamp2_store[0] == expected_clamp2[0]
                && clamp2_store[1] == expected_clamp2[1]
                && clamp2_store[2] == expected_clamp2[2]
                && clamp2_store[3] == expected_clamp2[3]);
}


void test_f32x4_mul_add()
{
    const f32x4 a0 = f32x4_set(snan, -inf, inf, denorm);
    const f32x4 a1 = f32x4_set(10.1f, .0f, -2.85f, 6.5f);
    const f32x4 b  = f32x4_set(1.f, -.0f, 10.6f, -9595.608f);
    const f32x4 c  = f32x4_set(.0f, 1000.f, -6.2f, .0f);

    const f32 expected_fma0[4] = {snan, snan, inf, -denorm * 9595.608f};
    const f32 expected_fma1[4] = {10.1f, 1000.f, -36.41f, -62371.453125f /* closest f32 */};

    f32 fma0_store[4];
    f32 fma1_store[4];

    f32x4_storeu(fma0_store, f32x4_mul_add(a0, b, c));
    f32x4_storeu(fma1_store, f32x4_mul_add(a1, b, c));

    bad_test_check(is_snan(fma0_store[0])
                && is_snan(fma0_store[1])
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
    const f32x4 a0 = f32x4_set(snan, -inf, inf, denorm);
    const f32x4 a1 = f32x4_set(10.1f, .0f, -2.85f, 6.5f);
    const f32x4 b  = f32x4_set(1.f, -.0f, 10.6f, -9595.608f);
    const f32x4 c  = f32x4_set(.0f, 1000.f, -6.2f, .0f);

    const f32 expected_fms1[4] = {snan, snan, inf, -denorm * 9595.608f};
    const f32 expected_fms2[4] = {10.1f, -1000.f, -24.01f, -62371.453125f /* closest f32 */};

    f32 fms1_store[4];
    f32 fms2_store[4];

    f32x4_storeu(fms1_store, f32x4_mul_sub(a0, b, c));
    f32x4_storeu(fms2_store, f32x4_mul_sub(a1, b, c));

    bad_test_check(is_snan(fms1_store[0])
                && is_snan(fms1_store[1])
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
    const f32x4 a0 = f32x4_set(snan, -inf, inf, denorm);
    const f32x4 a1 = f32x4_set(10.1f, .0f, -2.85f, 6.5f);
    const f32x4 b  = f32x4_set(1.f, -.0f, 10.6f, -9595.608f);
    const f32x4 c  = f32x4_set(.0f, 1000.f, -6.2f, .0f);

    const f32 expected_fnma0[4] = {qnan, snan, -inf, denorm * 9595.608f};
    const f32 expected_fnma1[4] = {-10.1f, 1000.f, 24.01f, 62371.453125f /* closest f32 */};

    f32 fnma0_store[4];
    f32 fnma1_store[4];

    f32x4_storeu(fnma0_store, f32x4_nmul_add(a0, b, c));
    f32x4_storeu(fnma1_store, f32x4_nmul_add(a1, b, c));

    // Behaviour with nan slightly differs between FMA3 and SSE operations
    bad_test_check(is_qnan(fnma0_store[0])
#if defined(__FMA__)
                && is_snan(fnma0_store[1])
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
    const f32x4 a0 = f32x4_set(snan, -inf, inf, denorm);
    const f32x4 a1 = f32x4_set(10.1f, .0f, -2.85f, 6.5f);
    const f32x4 b  = f32x4_set(1.f, -.0f, 10.6f, -9595.608f);
    const f32x4 c  = f32x4_set(.0f, 1000.f, -6.2f, .0f);

    const f32 expected_fnms1[4] = {qnan, snan, -inf, denorm * 9595.608f};
    const f32 expected_fnms2[4] = {-10.1f, -1000.f, 36.41f, 62371.453125f};

    f32 fnms1_store[4];
    f32 fnms2_store[4];

    f32x4_storeu(fnms1_store, f32x4_nmul_sub(a0, b, c));
    f32x4_storeu(fnms2_store, f32x4_nmul_sub(a1, b, c));

    // Behaviour with nan slightly differs between FMA3 and SSE operations
    bad_test_check(is_qnan(fnms1_store[0])
#if defined(__FMA__)
                && is_snan(fnms1_store[1])
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

void test_f32x4_is_nan()
{
    const f32x4 a = f32x4_set(snan, qnan, -inf, denorm);
    const f32x4 b = f32x4_set(.0f, -.0f, 10.6f, -9595.608f);

#if defined(__SSE2__)
    const mask_elem expected_a_is_nan[4] = {0xFFFFFFFF, 0xFFFFFFFF, 0x00000000, 0x00000000};
    const mask_elem expected_b_is_nan[4] = {0x00000000, 0x00000000, 0x00000000, 0x00000000};
#else
    const mask_elem expected_a_is_nan[4] = {all1, all1, .0f, .0f};
    const mask_elem expected_b_is_nan[4] = {.0f, .0f, .0f, .0f};
#endif

    mask_elem a_is_nan_out[4];
    mask_elem b_store[4];
    mask128_storeu(a_is_nan_out, f32x4_is_nan(a));
    mask128_storeu(b_store, f32x4_is_nan(b));

    bad_test_check(a_is_nan_out[0] == expected_a_is_nan[0]
                && a_is_nan_out[1] == expected_a_is_nan[1]
                && a_is_nan_out[2] == expected_a_is_nan[2]
                && a_is_nan_out[3] == expected_a_is_nan[3]
                && b_store[0] == expected_b_is_nan[0]
                && b_store[1] == expected_b_is_nan[1]
                && b_store[2] == expected_b_is_nan[2]
                && b_store[3] == expected_b_is_nan[3]);
}


void test_f32x4_is_infinite()
{
    const f32x4 a = f32x4_set(snan, -inf, inf, denorm);
    const f32x4 b = f32x4_set(.0f, -.0f, 10.6f, -9595.608f);

#if defined(__SSE2__)
    const mask_elem expected_a_is_infinity[4] = {0x00000000, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000};
    const mask_elem expected_b_is_infinity[4] = {0x00000000, 0x00000000, 0x00000000, 0x00000000};
#else
    const mask_elem expected_a_is_infinity[4] = {.0f, all1, all1, .0f};
    const mask_elem expected_b_is_infinity[4] = {.0f, .0f, .0f, .0f};
#endif

    mask_elem a_store[4];
    mask_elem b_store[4];
    mask128_storeu(a_store, f32x4_is_infinite(a));
    mask128_storeu(b_store, f32x4_is_infinite(b));

    bad_test_check(a_store[0] == expected_a_is_infinity[0]
                && a_store[1] == expected_a_is_infinity[1]
                && a_store[2] == expected_a_is_infinity[2]
                && a_store[3] == expected_a_is_infinity[3]
                && b_store[0] == expected_b_is_infinity[0]
                && b_store[1] == expected_b_is_infinity[1]
                && b_store[2] == expected_b_is_infinity[2]
                && b_store[3] == expected_b_is_infinity[3]);
}


void test_f32x4_is_finite()
{
    const f32x4 a = f32x4_set(snan, -inf, inf, denorm);
    const f32x4 b = f32x4_set(.0f, -.0f, 10.6f, -9595.608f);

#if defined(__SSE2__)
    const mask_elem expected_a_is_finite[4] = {0x00000000, 0x00000000, 0x00000000, 0xFFFFFFFF};
    const mask_elem expected_b_is_finite[4] = {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF};
#else
    const mask_elem expected_a_is_finite[4] = {.0f, .0f, .0f, all1};
    const mask_elem expected_b_is_finite[4] = {all1, all1, all1, all1};
#endif

    mask_elem a_store[4];
    mask_elem b_store[4];
    mask128_storeu(a_store, f32x4_is_finite(a));
    mask128_storeu(b_store, f32x4_is_finite(b));

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