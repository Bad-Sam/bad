#include "test_f32x4.h" 
#include "../test.h"
#include "../test_values.h" // qnan, inff, -inff, denormf, all1

#include <bad/types.h>
#include <bad/qualifiers.h>
#include <bad/common/f32x4.h>


BAD_NAMESPACE_START

void test_f32x4_zero()
{
    const f32 expected_zero = .0f;

    f32 zero_store[4];
    f32x4_storeu(zero_store, f32x4_zero());

    bad_test_check(zero_store[0] == expected_zero
                && zero_store[1] == expected_zero
                && zero_store[2] == expected_zero
                && zero_store[3] == expected_zero);
}


void test_f32x4_one()
{
    const f32 expected_one = 1.f;

    f32 one_store[4];
    f32x4_storeu(one_store, f32x4_one());

    bad_test_check(one_store[0] == expected_one
                && one_store[1] == expected_one
                && one_store[2] == expected_one
                && one_store[3] == expected_one);
}


void test_f32x4_load_store()
{
    bad_align(16) const f32 a[4] = {qnanf, inff, -inff, denormf};
    bad_align(16) const f32 b[4] = {.0f, 1.f, -2.f, 10.f};
    bad_align(16) f32 a_load_store[4];
    bad_align(16) f32 b_load_store[4];

    f32x4_store(a_load_store, f32x4_load(a));
    f32x4_store(b_load_store, f32x4_load(b));
    
    bad_test_check(is_qnan(a_load_store[0])
                && a[1] == a_load_store[1]
                && a[2] == a_load_store[2]
                && a[3] == a_load_store[3]
                && b[0] == b_load_store[0]
                && b[1] == b_load_store[1]
                && b[2] == b_load_store[2]
                && b[3] == b_load_store[3]);
}


void test_f32x4_loadu_storeu()
{
    const f32 a[4] = {qnanf, inff, -inff, denormf};
    const f32 b[4] = {.0f, 1.f, -2.f, 10.f};
    f32 a_loadu_storeu[4];
    f32 b_loadu_storeu[4];

    f32x4_storeu(a_loadu_storeu, f32x4_loadu(a));
    f32x4_storeu(b_loadu_storeu, f32x4_loadu(b));
    
    bad_test_check(is_qnan(a_loadu_storeu[0])
                && a[1] == a_loadu_storeu[1]
                && a[2] == a_loadu_storeu[2]
                && a[3] == a_loadu_storeu[3]
                && b[0] == b_loadu_storeu[0]
                && b[1] == b_loadu_storeu[1]
                && b[2] == b_loadu_storeu[2]
                && b[3] == b_loadu_storeu[3]);
}


void test_f32x4_set()
{
    const f32 a[4] = {qnanf, inff, -inff, denormf};
    const f32 b[4] = {.0f, 1.f, -2.f, 10.f};
    f32 a_set[4];
    f32 b_set[4];

    f32x4_storeu(a_set, f32x4_set(a[0], a[1], a[2], a[3]));
    f32x4_storeu(b_set, f32x4_set(b[0], b[1], b[2], b[3]));
    
    bad_test_check(is_qnan(a_set[0])
                && a[1] == a_set[1]
                && a[2] == a_set[2]
                && a[3] == a_set[3]
                && b[0] == b_set[0]
                && b[1] == b_set[1]
                && b[2] == b_set[2]
                && b[3] == b_set[3]);
}


void test_f32x4_set1()
{
    const f32 a[4] = {qnanf, inff, -inff, denormf};
    const f32 b[4] = {.0f, 1.f, -2.f, 10.f};
    f32 a0_set[4];
    f32 a1_set[4];
    f32 a2_set[4];
    f32 a3_set[4];
    f32 b0_set[4];
    f32 b1_set[4];
    f32 b2_set[4];
    f32 b3_set[4];

    f32x4_storeu(a0_set, f32x4_set1(a[0]));
    f32x4_storeu(a1_set, f32x4_set1(a[1]));
    f32x4_storeu(a2_set, f32x4_set1(a[2]));
    f32x4_storeu(a3_set, f32x4_set1(a[3]));
    f32x4_storeu(b0_set, f32x4_set1(b[0]));
    f32x4_storeu(b1_set, f32x4_set1(b[1]));
    f32x4_storeu(b2_set, f32x4_set1(b[2]));
    f32x4_storeu(b3_set, f32x4_set1(b[3]));
    
    bad_test_check(is_qnan(a0_set[0]) && is_qnan(a0_set[1]) && is_qnan(a0_set[2]) && is_qnan(a0_set[3])
                && a1_set[0] == a[1] && a1_set[1] == a[1] && a1_set[2] == a[1] && a1_set[3] == a[1]
                && a2_set[0] == a[2] && a2_set[1] == a[2] && a2_set[2] == a[2] && a2_set[3] == a[2]
                && a3_set[0] == a[3] && a3_set[1] == a[3] && a3_set[2] == a[3] && a3_set[3] == a[3]
                && b0_set[0] == b[0] && b0_set[1] == b[0] && b0_set[2] == b[0] && b0_set[3] == b[0]
                && b1_set[0] == b[1] && b1_set[1] == b[1] && b1_set[2] == b[1] && b1_set[3] == b[1]
                && b2_set[0] == b[2] && b2_set[1] == b[2] && b2_set[2] == b[2] && b2_set[3] == b[2]
                && b3_set[0] == b[3] && b3_set[1] == b[3] && b3_set[2] == b[3] && b3_set[3] == b[3]);
}


void test_f32x4_blend()
{
    const f32x4 a      = f32x4_set(snanf, qnanf, -inff, denormf);
    const f32x4 b      = f32x4_set(.0f, -.0f, 10.6f, -9595.608f);
    const mask128 mask = mask128_set(all1, all1, all1, zero);

    f32 blend1_store[4];
    f32 blend2_store[4];
    f32x4_storeu(blend1_store, f32x4_blend(a, b, mask));
    f32x4_storeu(blend2_store, f32x4_blend(b, a, mask));

    const f32 expected_blend1[4] = {snanf, qnanf, -inff, -9595.608f};
    const f32 expected_blend2[4] = {.0f, -.0f, 10.6f, denormf};

    bad_test_check(is_snan(blend1_store[0])
                && is_qnan(blend1_store[1])
                && blend1_store[2] == expected_blend1[2]
                && blend1_store[3] == expected_blend1[3]
                && blend2_store[0] == expected_blend2[0]
                && blend2_store[1] == expected_blend2[1]
                && blend2_store[2] == expected_blend2[2]
                && blend2_store[3] == expected_blend2[3]);
}


void test_f32x4_cast_mask128()
{
    const f32x4 a = f32x4_set(snanf, qnanf, -inff, denormf);
    const f32x4 b = f32x4_set(.0f, -.0f, 10.6f, -9595.608f);

    mask_elem cast_a_store[4];
    mask_elem cast_b_store[4];
    mask128_storeu(cast_a_store, f32x4_cast_mask128(a));
    mask128_storeu(cast_b_store, f32x4_cast_mask128(b));

    const mask_elem expected_a_cast[4] = {snan, qnan, ninf, denorm};
    const mask_elem expected_b_cast[4] = {0x00000000, 0x80000000, 0x4129999A, 0xC615EE6F};

#if defined(BAD_TEST_F32_MASK)
    bad_test_check(is_snan(cast_a_store[0])
                && is_qnan(cast_a_store[1])
                && cast_a_store[2] == expected_a_cast[2]
                && cast_a_store[3] == expected_a_cast[3]
                && cast_b_store[0] == expected_b_cast[0]
                && cast_b_store[1] == expected_b_cast[1]
                && cast_b_store[2] == expected_b_cast[2]
                && cast_b_store[3] == expected_b_cast[3]);
#else
    bad_test_check(cast_a_store[0] == expected_a_cast[0]
                && cast_a_store[1] == expected_a_cast[1]
                && cast_a_store[2] == expected_a_cast[2]
                && cast_a_store[3] == expected_a_cast[3]
                && cast_b_store[0] == expected_b_cast[0]
                && cast_b_store[1] == expected_b_cast[1]
                && cast_b_store[2] == expected_b_cast[2]
                && cast_b_store[3] == expected_b_cast[3]);
#endif
}

BAD_NAMESPACE_END