#include "test_f32x8_calc.h"

#include "../test.h"
#include "../test_values.h"

#include <bad/types.h>
#include <bad/qualifiers.h>
#include <bad/math/f32x8_calc.h>

BAD_NAMESPACE_START

void test_f32x8_hadd()
{
    const f32x8 a0 = f32x8_set(snanf, -1.f, .0f, 8.f, 1.f, 10000.f, -99.9999f, .0f);
    const f32x8 a1 = f32x8_set(-inff, -1.f, .0f, 8.f, 1.f, 10000.f, -99.9999f, .0f);
    const f32x8 a2 = f32x8_set(inff, -1.f, .0f, 8.f, 1.f, 10000.f, -99.9999f, .0f);
    const f32x8 a3 = f32x8_set(denormf, -1.f, .0f, 8.f, 1.f, 10000.f, -99.9999f, .0f);

    const f32 expected_hadd1 = -inff;
    const f32 expected_hadd2 = inff;
    const f32 expected_hadd3 = denormf - 1.f + 8.f + 1.f + 10000.f - 99.9999f;

    const f32 hadd0_store = f32x8_hadd(a0);
    const f32 hadd1_store = f32x8_hadd(a1);
    const f32 hadd2_store = f32x8_hadd(a2);
    const f32 hadd3_store = f32x8_hadd(a3);

    bad_test_check(is_snan(hadd0_store)
                && hadd1_store == expected_hadd1
                && hadd2_store == expected_hadd2
                && hadd3_store == expected_hadd3);
}


void test_f32x8_abs()
{
    const f32 a[8] = {qnanf, -inff, inff, -denormf, snanf, zerof, highbit32f, -zerof};
    const f32 b[8] = {-10.26f, -.1f, .1f, 3.56f, 1.f, 10000.f, -99.9999f, .0f};

    f32 a_abs[8];
    f32 b_abs[8];
    f32x8_storeu(a_abs, f32x8_abs(f32x8_loadu(a)));
    f32x8_storeu(b_abs, f32x8_abs(f32x8_loadu(b)));

    const f32 expected_a[8] = {snanf, inff, inff, -denormf, snanf, zerof, zerof, zerof};
    const f32 expected_b[8] = {10.26f, .1f, .1f, 3.56f, 1.f, 10000.f, 99.9999f, .0f};

    bad_test_check(is_snan(a_abs[0])
                && a_abs[1] == expected_a[1]
                && a_abs[2] == expected_a[2]
                && a_abs[3] == expected_a[3]
                && is_snan(a_abs[4])
                && a_abs[5] == expected_a[5]
                && a_abs[6] == expected_a[6]
                && a_abs[7] == expected_a[7]
                && b_abs[0] == expected_b[0]
                && b_abs[1] == expected_b[1]
                && b_abs[2] == expected_b[2]
                && b_abs[3] == expected_b[3]
                && b_abs[4] == expected_b[4]
                && b_abs[5] == expected_b[5]
                && b_abs[6] == expected_b[6]
                && b_abs[7] == expected_b[7]);
}


void test_f32x8_sign()
{
    const f32x8 a = f32x8_set(qnanf, -inff, inff, denormf, snanf, lowbit32f, highbit32f, zerof);
    const f32x8 b = f32x8_set(-10.26f, -.1f, .1f, 3.56f, -1e35f, 26.9000001f, -zerof, 1e-10f);

    const f32 expected_a[8] = {-1.f, -1.f, 1.f, -1.f, 1.f, 1.f, -1.f, 1.f};
    const f32 expected_b[8] = {-1.f, -1.f, 1.f, 1.f, -1.f, 1.f, -1.f, 1.f};

    f32 a_sign_out[8];
    f32 b_sign_out[8];
    f32x8_storeu(a_sign_out, f32x8_sign(a));
    f32x8_storeu(b_sign_out, f32x8_sign(b));

    bad_test_check(a_sign_out[0] == expected_a[0]
                && a_sign_out[1] == expected_a[1]
                && a_sign_out[2] == expected_a[2]
                && a_sign_out[3] == expected_a[3]
                && a_sign_out[4] == expected_a[4]
                && a_sign_out[5] == expected_a[5]
                && a_sign_out[6] == expected_a[6]
                && a_sign_out[7] == expected_a[7]
                && b_sign_out[0] == expected_b[0]
                && b_sign_out[1] == expected_b[1]
                && b_sign_out[2] == expected_b[2]
                && b_sign_out[3] == expected_b[3]
                && b_sign_out[4] == expected_b[4]
                && b_sign_out[5] == expected_b[5]
                && b_sign_out[6] == expected_b[6]
                && b_sign_out[7] == expected_b[7]);
}


void test_f32x8_neg()
{
    const f32 a[8] = {snanf, inff, -inff, -denormf, qnanf, zerof, highbit32f, -zerof};
    const f32 b[8] = {-10.f, -.1f, 12.f, 3.f, 1.f, 10000.f, -99.9999f, zerof};

    f32 a_neg[8];
    f32 b_neg[8];
    f32x8_storeu(a_neg, f32x8_neg(f32x8_loadu(a)));
    f32x8_storeu(b_neg, f32x8_neg(f32x8_loadu(b)));

    const f32 expected_a_neg[8] = {-a[0], -a[1], -a[2], -a[3], -a[4], -a[5], -a[6], -a[7]};
    const f32 expected_b_neg[8] = {-b[0], -b[1], -b[2], -b[3], -b[4], -b[5], -b[6], -b[7]};

    bad_test_check(is_qnan(a_neg[0])
                && a_neg[1] == expected_a_neg[1]
                && a_neg[2] == expected_a_neg[2]
                && a_neg[3] == expected_a_neg[3]
                && is_snan(a_neg[4])
                && a_neg[5] == expected_a_neg[5]
                && a_neg[6] == expected_a_neg[6]
                && a_neg[7] == expected_a_neg[7]
                && b_neg[0] == expected_b_neg[0]
                && b_neg[1] == expected_b_neg[1]
                && b_neg[2] == expected_b_neg[2]
                && b_neg[3] == expected_b_neg[3]
                && b_neg[4] == expected_b_neg[4]
                && b_neg[5] == expected_b_neg[5]
                && b_neg[6] == expected_b_neg[6]
                && b_neg[7] == expected_b_neg[7]);
}


void test_f32x8_mod()
{
    const f32x8 a = f32x8_set(snanf, inff, -inff, -denormf, qnanf, zerof, highbit32f, -zerof);
    const f32x8 b = f32x8_set(-10.f, -.1f, 12.f, 3.f, 1.f, 10000.f, -99.9999f, zerof);
    const f32x8 m = f32x8_set(3.f, 5.f, 5.25f, 1.f, 10.f, 10.f, 10.f, .0f);

    f32 a_mod_m_store[8];
    f32 b_mod_m_store[8];

    f32x8_storeu(a_mod_m_store, f32x8_mod(a, m));
    f32x8_storeu(b_mod_m_store, f32x8_mod(b, m));

    const f32 expected_a_mod[8] = {snanf, inff, -inff, -denormf, qnanf, zerof, zerof, snanf};
    const f32 expected_b_mod[8] = {-1.f, -.1f, 1.5f, .0f, 1.f, .0f, -9.9999f, snanf};

    bad_test_check(is_snan(a_mod_m_store[0])
#if defined(__SSE__)
                && is_qnan(a_mod_m_store[1])
                && is_qnan(a_mod_m_store[2])
#else
                && a_mod_m_store[1] == expected_a_mod[1]
                && a_mod_m_store[2] == expected_a_mod[2]
#endif
                && a_mod_m_store[3] == expected_a_mod[3]
                && is_qnan(a_mod_m_store[4])
                && a_mod_m_store[5] == expected_a_mod[5]
                && a_mod_m_store[6] == expected_a_mod[6]
                && is_snan(a_mod_m_store[7])
                && b_mod_m_store[0] == expected_b_mod[0]
                && b_mod_m_store[1] == expected_b_mod[1]
                && b_mod_m_store[2] == expected_b_mod[2]
                && b_mod_m_store[3] == expected_b_mod[3]
                && b_mod_m_store[4] == expected_b_mod[4]
                && b_mod_m_store[5] == expected_b_mod[5]
                && are_equal_ulp(b_mod_m_store[6], expected_b_mod[6])
                && is_snan(b_mod_m_store[7]));
}


void test_f32x8_trunc()
{
    // Edge cases can be handled with f32x8_is_finite() + f32x8_blend()
    const f32 a[8] = {-10.26f, -.1f, 12.f, 3.01f, 1.f, -10000.f, -99.9999f, zerof};

    f32 trunc_a[8];
    f32x8_storeu(trunc_a, f32x8_trunc(f32x8_loadu(a)));

    const f32 expected_a[8] = {-10.f, -.0f, 12.f, 3.f, 1.f, -10000.f, -99.f, zerof};
    
    bad_test_check(trunc_a[0] == expected_a[0]
                && trunc_a[1] == expected_a[1]
                && trunc_a[2] == expected_a[2]
                && trunc_a[3] == expected_a[3]
                && trunc_a[4] == expected_a[4]
                && trunc_a[5] == expected_a[5]
                && trunc_a[6] == expected_a[6]
                && trunc_a[7] == expected_a[7]);
}


void test_f32x8_round()
{
    // Edge cases can be handled with f32x8_is_finite() + f32x8_blend()
    const f32x8 a = f32x8_set(-10.9f, -.1f, 12.f, 3.26f, -1.f, 10000.05f, -99.9999f, zerof);

    f32 round_a_store[8];
    f32x8_storeu(round_a_store, f32x8_round(a));

    const f32 expected_a[8] = {-11.f, -.0f, 12.f, 3.f, -1.f, 10000.f, -100.f, zerof};

    bad_test_check(round_a_store[0] == expected_a[0]
                && round_a_store[1] == expected_a[1]
                && round_a_store[2] == expected_a[2]
                && round_a_store[3] == expected_a[3]
                && round_a_store[4] == expected_a[4]
                && round_a_store[5] == expected_a[5]
                && round_a_store[6] == expected_a[6]
                && round_a_store[7] == expected_a[7]);
}


void test_f32x8_floor()
{
    // Edge cases can be handled with f32x8_is_finite() + f32x8_blend()
    const f32x8 a = f32x8_set(-10.5f, -.9f, 12.f, 3.26f, -1.f, 10000.05f, -99.9999f, zerof);

    f32 trunc_a[8];
    f32x8_storeu(trunc_a, f32x8_floor(a));

    const f32 expected_a[8] = {-11.f, -1.f, 12.f, 3.f, -1.f, 10000.f, -100.f, zerof};

    bad_test_check(trunc_a[0] == expected_a[0]
                && trunc_a[1] == expected_a[1]
                && trunc_a[2] == expected_a[2]
                && trunc_a[3] == expected_a[3]
                && trunc_a[4] == expected_a[4]
                && trunc_a[5] == expected_a[5]
                && trunc_a[6] == expected_a[6]
                && trunc_a[7] == expected_a[7]);
}


void test_f32x8_ceil()
{
    // Edge cases can be handled with f32x8_is_finite() + f32x8_blend()
    const f32x8 a = f32x8_set(-10.5f, -.9f, 12.f, 3.26f, -1.f, 10000.05f, -99.9999f, zerof);

    f32 ceil_a[8];
    f32x8_storeu(ceil_a, f32x8_ceil(a));

    const f32 expected_a[8] = {-10.f, -.0f, 12.f, 4.f, -1.f, 10001.f, -99.f, zerof};

    bad_test_check(ceil_a[0] == expected_a[0]
                && ceil_a[1] == expected_a[1]
                && ceil_a[2] == expected_a[2]
                && ceil_a[3] == expected_a[3]
                && ceil_a[4] == expected_a[4]
                && ceil_a[5] == expected_a[5]
                && ceil_a[6] == expected_a[6]
                && ceil_a[7] == expected_a[7]);
}


void test_f32x8_clamp()
{
    const f32x8 a   = f32x8_set(snanf, -inff, inff, denormf, -.0f,  .0f,   -11.f, -56.25f);
    const f32x8 min = f32x8_set(.0f,   -inff, inff,  -100.f, -.0f, -1.f, -11.25f,   -50.f);
    const f32x8 max = f32x8_set(1.f,  75.56f, inff,   100.f, 10.f,  1.f, -10.75f,     .0f);


    f32 clamp_store[8];
    f32x8_storeu(clamp_store, f32x8_clamp(a, min, max));

    const f32 expected_clamp[8] = {.0f, -inff, inff, denormf, -.0f, .0f, -11.f, -50.f};

    bad_test_check(clamp_store[0] == expected_clamp[0]
                && clamp_store[1] == expected_clamp[1]
                && clamp_store[2] == expected_clamp[2]
                && clamp_store[3] == expected_clamp[3]
                && clamp_store[4] == expected_clamp[4]
                && clamp_store[5] == expected_clamp[5]
                && clamp_store[6] == expected_clamp[6]
                && clamp_store[7] == expected_clamp[7]);
}


void test_f32x8_mul_add()
{
    const f32x8 a = f32x8_set(snanf, -inff, inff, denormf, 10.1f, .0f, -2.85f, 6.5f);
    const f32x8 b = f32x8_set(1.f, -.0f, 10.6f, -9595.608f, 1.f, -.0f, 10.6f, -9595.608f);
    const f32x8 c = f32x8_set(.0f, 1000.f, -6.2f, .0f, .0f, 1000.f, -6.2f, .0f);

    f32 fma_store[8];
    f32x8_storeu(fma_store, f32x8_mul_add(a, b, c));

    const f32 expected_fma[8] = {snanf, snanf, inff, -denormf * 9595.608f, 10.1f, 1000.f, -36.41f, -62371.453125f};
    
    bad_test_check(is_snan(fma_store[0])
                && is_snan(fma_store[1])
                && fma_store[2] == expected_fma[2]
                && fma_store[3] == expected_fma[3]
#if defined(__FMA__)
                && fma_store[4] == expected_fma[4]
                && fma_store[5] == expected_fma[5]
                && fma_store[6] == expected_fma[6]
                && fma_store[7] == expected_fma[7]
#else
                && are_equal_ulp(fma_store[4], expected_fma[4])
                && are_equal_ulp(fma_store[5], expected_fma[5])
                && are_equal_ulp(fma_store[6], expected_fma[6])
                && are_equal_ulp(fma_store[7], expected_fma[7])
#endif
                  );
}


void test_f32x8_mul_sub()
{
    const f32x8 a = f32x8_set(snanf, -inff, inff, denormf, 10.1f, .0f, -2.85f, 6.5f);
    const f32x8 b = f32x8_set(1.f, -.0f, 10.6f, -9595.608f, 1.f, -.0f, 10.6f, -9595.608f);
    const f32x8 c = f32x8_set(.0f, 1000.f, -6.2f, .0f, .0f, 1000.f, -6.2f, .0f);

    f32 fms_store[8];
    f32x8_storeu(fms_store, f32x8_mul_sub(a, b, c));

    const f32 expected_fms[8] = {snanf, snanf, inff, -denormf * 9595.608f, 10.1f, -1000.f, -24.01f, -62371.453125f};

    bad_test_check(is_snan(fms_store[0])
                && is_snan(fms_store[1])
                && fms_store[2] == expected_fms[2]
                && fms_store[3] == expected_fms[3]
#if defined(__FMA__)
                && fms_store[4] == expected_fms[4]
                && fms_store[5] == expected_fms[5]
                && fms_store[6] == expected_fms[6]
                && fms_store[7] == expected_fms[7]
#else
                && are_equal_ulp(fms_store[4], expected_fms[4])
                && are_equal_ulp(fms_store[5], expected_fms[5])
                && are_equal_ulp(fms_store[6], expected_fms[6])
                && are_equal_ulp(fms_store[7], expected_fms[7])
#endif
                  );
}


void test_f32x8_nmul_add()
{
    const f32x8 a = f32x8_set(snanf, -inff, inff, denormf, 10.1f, .0f, -2.85f, 6.5f);
    const f32x8 b = f32x8_set(1.f, -.0f, 10.6f, -9595.608f, 1.f, -.0f, 10.6f, -9595.608f);
    const f32x8 c = f32x8_set(.0f, 1000.f, -6.2f, .0f, .0f, 1000.f, -6.2f, .0f);

    f32 fnma_store[8];
    f32x8_storeu(fnma_store, f32x8_nmul_add(a, b, c));

    const f32 expected_fnma[8] = {qnanf, snanf, -inff, denormf * 9595.608f, -10.1f, 1000.f, 24.01f, 62371.453125f};

    // Behaviour with nan slightly differs between FMA3 and SSE operations
    bad_test_check(is_qnan(fnma_store[0])
#if defined(__FMA__)
                && is_snan(fnma_store[1])
                && fnma_store[2] == expected_fnma[2]
                && fnma_store[3] == expected_fnma[3]
                && fnma_store[4] == expected_fnma[4]
                && fnma_store[5] == expected_fnma[5]
                && fnma_store[6] == expected_fnma[6]
                && fnma_store[7] == expected_fnma[7]
#else
                && is_qnan(fnma_store[1])
                && fnma_store[2] == expected_fnma[2]
                && fnma_store[3] == expected_fnma[3]
                && are_equal_ulp(fnma_store[4], expected_fnma[4])
                && are_equal_ulp(fnma_store[5], expected_fnma[5])
                && are_equal_ulp(fnma_store[6], expected_fnma[6])
                && are_equal_ulp(fnma_store[7], expected_fnma[7])
#endif
                  );
}


void test_f32x8_nmul_sub()
{
    const f32x8 a = f32x8_set(snanf, -inff, inff, denormf, 10.1f, .0f, -2.85f, 6.5f);
    const f32x8 b = f32x8_set(1.f, -.0f, 10.6f, -9595.608f, 1.f, -.0f, 10.6f, -9595.608f);
    const f32x8 c = f32x8_set(.0f, 1000.f, -6.2f, .0f, .0f, 1000.f, -6.2f, .0f);

    f32 fnms_store[8];
    f32x8_storeu(fnms_store, f32x8_nmul_sub(a, b, c));

    const f32 expected_fnms[8] = {qnanf, snanf, -inff, denormf * 9595.608f,
                                  -10.1f, -1000.f, 36.41f, 62371.453125f};

    // Behaviour with nan slightly differs between FMA3 and SSE operations
    bad_test_check(is_qnan(fnms_store[0])
#if defined(__FMA__)
                && is_snan(fnms_store[1])
                && fnms_store[2] == expected_fnms[2]
                && fnms_store[3] == expected_fnms[3]
                && fnms_store[4] == expected_fnms[4]
                && fnms_store[5] == expected_fnms[5]
                && fnms_store[6] == expected_fnms[6]
                && fnms_store[7] == expected_fnms[7]
#else
                && is_qnan(fnms_store[1])
                && fnms_store[2] == expected_fnms[2]
                && fnms_store[3] == expected_fnms[3]
                && are_equal_ulp(fnms_store[4], expected_fnms[4])
                && are_equal_ulp(fnms_store[5], expected_fnms[5])
                && are_equal_ulp(fnms_store[6], expected_fnms[6])
                && are_equal_ulp(fnms_store[7], expected_fnms[7])
#endif
                  );
}


void test_f32x8_neq()
{
    const f32x8 a = f32x8_set(snanf, qnanf, -inff, denormf, .0f, 2.f, -1.f, -denormf);
    const f32x8 b = f32x8_set(qnanf, qnanf, -inff, -denormf, qnanf, qnanf, -inff, -denormf);

    u32 neq_store[8];
    mask256_storeu(neq_store, f32x8_neq(a, b));

    const u32 expected_neq[8] = {all1, all1, zero, all1, all1, all1, all1, zero};

    bad_test_check(neq_store[0] == expected_neq[0]
                && neq_store[1] == expected_neq[1]
                && neq_store[2] == expected_neq[2]
                && neq_store[3] == expected_neq[3]
                && neq_store[4] == expected_neq[4]
                && neq_store[5] == expected_neq[5]
                && neq_store[6] == expected_neq[6]
                && neq_store[7] == expected_neq[7]);
}


void test_f32x8_eq()
{
    const f32x8 a = f32x8_set(snanf, qnanf, -inff, denormf, .0f, 2.f, -1.f, -denormf);
    const f32x8 b = f32x8_set(qnanf, qnanf, -inff, -denormf, qnanf, qnanf, -inff, -denormf);

    u32 eq_store[8];
    mask256_storeu(eq_store, f32x8_eq(a, b));

    const u32 expected_eq[8] = {zero, zero, all1, zero, zero, zero, zero, all1};

    bad_test_check(eq_store[0] == expected_eq[0]
                && eq_store[1] == expected_eq[1]
                && eq_store[2] == expected_eq[2]
                && eq_store[3] == expected_eq[3]
                && eq_store[4] == expected_eq[4]
                && eq_store[5] == expected_eq[5]
                && eq_store[6] == expected_eq[6]
                && eq_store[7] == expected_eq[7]);
}


void test_f32x8_ge()
{
    const f32x8 a = f32x8_set(snanf, qnanf, -inff, denormf, .0f, 2.f, -1.f, -denormf);
    const f32x8 b = f32x8_set(1.f, 2.f, -inff, .0f, 1.f, 2.f, -inff, .0f);

    u32 ge_store[8];
    mask256_storeu(ge_store, f32x8_ge(a, b));

    const u32 expected_ge[8] = {zero, zero, all1, zero, zero, all1, all1, all1};

    bad_test_check(ge_store[0] == expected_ge[0]
                && ge_store[1] == expected_ge[1]
                && ge_store[2] == expected_ge[2]
                && ge_store[3] == expected_ge[3]
                && ge_store[4] == expected_ge[4]
                && ge_store[5] == expected_ge[5]
                && ge_store[6] == expected_ge[6]
                && ge_store[7] == expected_ge[7]);
}


void test_f32x8_gt()
{
    const f32x8 a = f32x8_set(snanf, qnanf, -inff, denormf, .0f, 2.f, -1.f, -denormf);
    const f32x8 b = f32x8_set(1.f, 2.f, -inff, .0f, 1.f, 2.f, -inff, .0f);

    u32 gt_store[8];
    mask256_storeu(gt_store, f32x8_gt(a, b));

    const u32 expected_gt[8] = {zero, zero, zero, zero, zero, zero, all1, all1};

    bad_test_check(gt_store[0] == expected_gt[0]
                && gt_store[1] == expected_gt[1]
                && gt_store[2] == expected_gt[2]
                && gt_store[3] == expected_gt[3]
                && gt_store[4] == expected_gt[4]
                && gt_store[5] == expected_gt[5]
                && gt_store[6] == expected_gt[6]
                && gt_store[7] == expected_gt[7]);
}


void test_f32x8_le()
{
    const f32x8 a = f32x8_set(snanf, qnanf, -inff, denormf, .0f, 2.f, -1.f, -denormf);
    const f32x8 b = f32x8_set(1.f, 2.f, -inff, .0f, 1.f, 2.f, -inff, .0f);

    u32 le_store[8];
    mask256_storeu(le_store, f32x8_le(a, b));

    const u32 expected_le[8] = {zero, zero, all1, all1, all1, all1, zero, zero};

    bad_test_check(le_store[0] == expected_le[0]
                && le_store[1] == expected_le[1]
                && le_store[2] == expected_le[2]
                && le_store[3] == expected_le[3]
                && le_store[4] == expected_le[4]
                && le_store[5] == expected_le[5]
                && le_store[6] == expected_le[6]
                && le_store[7] == expected_le[7]);
}


void test_f32x8_lt()
{
    const f32x8 a = f32x8_set(snanf, qnanf, -inff, denormf, .0f, 2.f, -1.f, -denormf);
    const f32x8 b = f32x8_set(1.f, 2.f, -inff, .0f, 1.f, 2.f, -inff, .0f);

    u32 lt_store[8];
    mask256_storeu(lt_store, f32x8_lt(a, b));

    const u32 expected_lt[8] = {zero, zero, zero, all1, all1, zero, zero, zero};

    bad_test_check(lt_store[0] == expected_lt[0]
                && lt_store[1] == expected_lt[1]
                && lt_store[2] == expected_lt[2]
                && lt_store[3] == expected_lt[3]
                && lt_store[4] == expected_lt[4]
                && lt_store[5] == expected_lt[5]
                && lt_store[6] == expected_lt[6]
                && lt_store[7] == expected_lt[7]);
}


void test_f32x8_is_nan()
{
    const f32x8 a = f32x8_set(snanf, qnanf, -inff, denormf, inff, zerof, lowbit32, highbit32f);
    const f32x8 b = f32x8_set(.0f, -.0f, 10.6f, -9595.608f, 1.f, 10000.f, -99.9999f, zerof);

    u32 a_is_nan[8];
    u32 b_is_nan[8];
    mask256_storeu(a_is_nan, f32x8_is_nan(a));
    mask256_storeu(b_is_nan, f32x8_is_nan(b));

    const u32 expected_a_is_nan[8] = {all1, all1, zero, zero, zero, zero, zero, zero};
    const u32 expected_b_is_nan[8] = {zero, zero, zero, zero, zero, zero, zero, zero};

    bad_test_check(a_is_nan[0] == expected_a_is_nan[0] && a_is_nan[1] == expected_a_is_nan[1]
                && a_is_nan[2] == expected_a_is_nan[2] && a_is_nan[3] == expected_a_is_nan[3]
                && a_is_nan[4] == expected_a_is_nan[4] && a_is_nan[5] == expected_a_is_nan[5]
                && a_is_nan[6] == expected_a_is_nan[6] && a_is_nan[7] == expected_a_is_nan[7]
                && b_is_nan[0] == expected_b_is_nan[0] && b_is_nan[1] == expected_b_is_nan[1]
                && b_is_nan[2] == expected_b_is_nan[2] && b_is_nan[3] == expected_b_is_nan[3]
                && b_is_nan[4] == expected_b_is_nan[4] && b_is_nan[5] == expected_b_is_nan[5]
                && b_is_nan[6] == expected_b_is_nan[6] && b_is_nan[7] == expected_b_is_nan[7]);
}


void test_f32x8_is_infinite()
{
    const f32x8 a = f32x8_set(snanf, -inff, inff, denormf, inff, zerof, lowbit32, highbit32f);
    const f32x8 b = f32x8_set(.0f, -.0f, 10.6f, -9595.608f, 1.f, 10000.f, -99.9999f, -inff * 2.f);

    u32 a_is_inf[8];
    u32 b_is_inf[8];
    mask256_storeu(a_is_inf, f32x8_is_infinite(a));
    mask256_storeu(b_is_inf, f32x8_is_infinite(b));

    const u32 expected_a_is_inf[8] = {zero, all1, all1, zero, all1, zero, zero, zero};
    const u32 expected_b_is_inf[8] = {zero, zero, zero, zero, zero, zero, zero, all1};

    bad_test_check(a_is_inf[0] == expected_a_is_inf[0] && a_is_inf[1] == expected_a_is_inf[1]
                && a_is_inf[2] == expected_a_is_inf[2] && a_is_inf[3] == expected_a_is_inf[3]
                && a_is_inf[4] == expected_a_is_inf[4] && a_is_inf[5] == expected_a_is_inf[5]
                && a_is_inf[6] == expected_a_is_inf[6] && a_is_inf[7] == expected_a_is_inf[7]
                && b_is_inf[0] == expected_b_is_inf[0] && b_is_inf[1] == expected_b_is_inf[1]
                && b_is_inf[2] == expected_b_is_inf[2] && b_is_inf[3] == expected_b_is_inf[3]
                && b_is_inf[4] == expected_b_is_inf[4] && b_is_inf[5] == expected_b_is_inf[5]
                && b_is_inf[6] == expected_b_is_inf[6] && b_is_inf[7] == expected_b_is_inf[7]);
}


void test_f32x8_is_finite()
{
    const f32x8 a = f32x8_set(snanf, -inff, inff, denormf, inff, zerof, lowbit32, highbit32f);
    const f32x8 b = f32x8_set(.0f, -.0f, 10.6f, -9595.608f, 1.f, 10000.f, -99.9999f, -inff * 2.f);

    u32 a_is_fin[8];
    u32 b_is_fin[8];
    mask256_storeu(a_is_fin, f32x8_is_finite(a));
    mask256_storeu(b_is_fin, f32x8_is_finite(b));

    const u32 expected_a_is_fin[8] = {zero, zero, zero, all1, zero, all1, all1, all1};
    const u32 expected_b_is_fin[8] = {all1, all1, all1, all1, all1, all1, all1, zero};

    bad_test_check(a_is_fin[0] == expected_a_is_fin[0] && a_is_fin[1] == expected_a_is_fin[1]
                && a_is_fin[2] == expected_a_is_fin[2] && a_is_fin[3] == expected_a_is_fin[3]
                && a_is_fin[4] == expected_a_is_fin[4] && a_is_fin[5] == expected_a_is_fin[5]
                && a_is_fin[6] == expected_a_is_fin[6] && a_is_fin[7] == expected_a_is_fin[7]
                && b_is_fin[0] == expected_b_is_fin[0] && b_is_fin[1] == expected_b_is_fin[1]
                && b_is_fin[2] == expected_b_is_fin[2] && b_is_fin[3] == expected_b_is_fin[3]
                && b_is_fin[4] == expected_b_is_fin[4] && b_is_fin[5] == expected_b_is_fin[5]
                && b_is_fin[6] == expected_b_is_fin[6] && b_is_fin[7] == expected_b_is_fin[7]);
}

BAD_NAMESPACE_END