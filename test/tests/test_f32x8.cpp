#include "test_f32x8.h" 
#include "../test.h"
#include "../test_values.h" // qnan, inff, -inff, denormf, all1

#include <bad/qualifiers.h>
#include <bad/common/f32x8.h>

BAD_NAMESPACE_START

void test_f32x8_zero()
{
    const f32 expected_zero = .0f;

    f32 zero_store[8];
    f32x8_storeu(zero_store, f32x8_zero());

    bad_test_check(zero_store[0] == expected_zero
                && zero_store[1] == expected_zero
                && zero_store[2] == expected_zero
                && zero_store[3] == expected_zero
                && zero_store[4] == expected_zero
                && zero_store[5] == expected_zero
                && zero_store[6] == expected_zero
                && zero_store[7] == expected_zero);
}


void test_f32x8_one()
{
    const f32 expected_one = 1.f;

    f32 one_store[8];
    f32x8_storeu(one_store, f32x8_one());

    bad_test_check(one_store[0] == expected_one
                && one_store[1] == expected_one
                && one_store[2] == expected_one
                && one_store[3] == expected_one
                && one_store[4] == expected_one
                && one_store[5] == expected_one
                && one_store[6] == expected_one
                && one_store[7] == expected_one);
}


void test_f32x8_load_store()
{
    bad_align(32) const f32 a[8] = {qnanf, inff, -inff, denormf, snanf, .0f, -.0f, 1.f};
    bad_align(32) const f32 b[8] = {-10.f, 1.f, -2.f, 10.f, 8641654.2154f, -.1f, 100.f, -99.9999f};
    bad_align(32) f32 a_load_store[8];
    bad_align(32) f32 b_load_store[8];

    f32x8_store(a_load_store, f32x8_load(a));
    f32x8_store(b_load_store, f32x8_load(b));
    
    bad_test_check(is_qnan(a_load_store[0])
                && a[1] == a_load_store[1]
                && a[2] == a_load_store[2]
                && a[3] == a_load_store[3]
                && is_snan(a[4])
                && a[5] == a_load_store[5]
                && a[6] == a_load_store[6]
                && a[7] == a_load_store[7]
                && b[0] == b_load_store[0]
                && b[1] == b_load_store[1]
                && b[2] == b_load_store[2]
                && b[3] == b_load_store[3]
                && b[4] == b_load_store[4]
                && b[5] == b_load_store[5]
                && b[6] == b_load_store[6]
                && b[7] == b_load_store[7]);
}


void test_f32x8_loadu_storeu()
{
    const f32 a[8] = {qnanf, inff, -inff, denormf, snanf, .0f, -.0f, 1.f};
    const f32 b[8] = {-10.f, 1.f, -2.f, 10.f, 8641654.2154f, -.1f, 100.f, -99.9999f};
    f32 a_loadu_storeu[8];
    f32 b_loadu_storeu[8];

    f32x8_storeu(a_loadu_storeu, f32x8_loadu(a));
    f32x8_storeu(b_loadu_storeu, f32x8_loadu(b));
    
    bad_test_check(is_qnan(a_loadu_storeu[0])
                && a[1] == a_loadu_storeu[1]
                && a[2] == a_loadu_storeu[2]
                && a[3] == a_loadu_storeu[3]
                && is_snan(a_loadu_storeu[4])
                && a[5] == a_loadu_storeu[5]
                && a[6] == a_loadu_storeu[6]
                && a[7] == a_loadu_storeu[7]
                && b[0] == b_loadu_storeu[0]
                && b[1] == b_loadu_storeu[1]
                && b[2] == b_loadu_storeu[2]
                && b[3] == b_loadu_storeu[3]
                && b[4] == b_loadu_storeu[4]
                && b[5] == b_loadu_storeu[5]
                && b[6] == b_loadu_storeu[6]
                && b[7] == b_loadu_storeu[7]);
}


void test_f32x8_set()
{
    const f32 a[8] = {qnanf, inff, -inff, denormf, snanf, .0f, -.0f, 1.f};
    const f32 b[8] = {-10.f, 1.f, -2.f, 10.f, 8641654.2154f, -.1f, 100.f, -99.9999f};
    f32 a_set[8];
    f32 b_set[8];

    f32x8_storeu(a_set, f32x8_set(a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7]));
    f32x8_storeu(b_set, f32x8_set(b[0], b[1], b[2], b[3], b[4], b[5], b[6], b[7]));
    
    bad_test_check(is_qnan(a_set[0])
                && a[1] == a_set[1]
                && a[2] == a_set[2]
                && a[3] == a_set[3]
                && is_snan(a_set[4])
                && a[5] == a_set[5]
                && a[6] == a_set[6]
                && a[7] == a_set[7]
                && b[0] == b_set[0]
                && b[1] == b_set[1]
                && b[2] == b_set[2]
                && b[3] == b_set[3]
                && b[4] == b_set[4]
                && b[5] == b_set[5]
                && b[6] == b_set[6]
                && b[7] == b_set[7]);
}


void test_f32x8_set_all()
{
    const f32 a[4] = {qnanf, inff, -inff, denormf};
    const f32 b[4] = {-10.f, 1.f, -2.f, 10.f};
    f32 a0_set[8];
    f32 a1_set[8];
    f32 a2_set[8];
    f32 a3_set[8];
    f32 b0_set[8];
    f32 b1_set[8];
    f32 b2_set[8];
    f32 b3_set[8];

    f32x8_storeu(a0_set, f32x8_set_all(a[0]));
    f32x8_storeu(a1_set, f32x8_set_all(a[1]));
    f32x8_storeu(a2_set, f32x8_set_all(a[2]));
    f32x8_storeu(a3_set, f32x8_set_all(a[3]));
    f32x8_storeu(b0_set, f32x8_set_all(b[0]));
    f32x8_storeu(b1_set, f32x8_set_all(b[1]));
    f32x8_storeu(b2_set, f32x8_set_all(b[2]));
    f32x8_storeu(b3_set, f32x8_set_all(b[3]));
    
    bad_test_check(is_qnan(a0_set[0]) && is_qnan(a0_set[1]) && is_qnan(a0_set[2]) && is_qnan(a0_set[3])
                && is_qnan(a0_set[4]) && is_qnan(a0_set[5]) && is_qnan(a0_set[6]) && is_qnan(a0_set[7])
                && a1_set[0] == a[1] && a1_set[1] == a[1] && a1_set[2] == a[1] && a1_set[3] == a[1]
                && a1_set[4] == a[1] && a1_set[5] == a[1] && a1_set[6] == a[1] && a1_set[7] == a[1]
                && a2_set[0] == a[2] && a2_set[1] == a[2] && a2_set[2] == a[2] && a2_set[3] == a[2]
                && a2_set[4] == a[2] && a2_set[5] == a[2] && a2_set[6] == a[2] && a2_set[7] == a[2]
                && a3_set[0] == a[3] && a3_set[1] == a[3] && a3_set[2] == a[3] && a3_set[3] == a[3]
                && a3_set[4] == a[3] && a3_set[5] == a[3] && a3_set[6] == a[3] && a3_set[7] == a[3]
                && b0_set[0] == b[0] && b0_set[1] == b[0] && b0_set[2] == b[0] && b0_set[3] == b[0]
                && b0_set[4] == b[0] && b0_set[5] == b[0] && b0_set[6] == b[0] && b0_set[7] == b[0]
                && b1_set[0] == b[1] && b1_set[1] == b[1] && b1_set[2] == b[1] && b1_set[3] == b[1]
                && b1_set[4] == b[1] && b1_set[5] == b[1] && b1_set[6] == b[1] && b1_set[7] == b[1]
                && b2_set[0] == b[2] && b2_set[1] == b[2] && b2_set[2] == b[2] && b2_set[3] == b[2]
                && b2_set[4] == b[2] && b2_set[5] == b[2] && b2_set[6] == b[2] && b2_set[7] == b[2]
                && b3_set[0] == b[3] && b3_set[1] == b[3] && b3_set[2] == b[3] && b3_set[3] == b[3]
                && b3_set[4] == b[3] && b3_set[5] == b[3] && b3_set[6] == b[3] && b3_set[7] == b[3]);
}


void test_f32x8_blend()
{
    const f32 a[8]  = {qnanf, inff, -inff, denormf, snanf, .0f, -.0f, 1.f};
    const f32 b[8]  = {-10.f, 1.f, -2.f, 10.f, 8641654.2154f, -.1f, 100.f, -99.9999f};


    const mask256 mask = mask256_set(0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000,
                                     0x00000000, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF);

    const f32 expected_blend1[8] = {a[0], a[1], a[2], b[3], b[4], a[5], b[6], a[7]};
    const f32 expected_blend2[8] = {b[0], b[1], b[2], a[3], a[4], b[5], a[6], b[7]};

    f32 blend1_store[8];
    f32 blend2_store[8];
    f32x8_storeu(blend1_store, f32x8_blend(f32x8_loadu(a), f32x8_loadu(b), mask));
    f32x8_storeu(blend2_store, f32x8_blend(f32x8_loadu(b), f32x8_loadu(a), mask));

    bad_test_check(is_qnan(blend1_store[0])
                && blend1_store[1] == expected_blend1[1]
                && blend1_store[2] == expected_blend1[2]
                && blend1_store[3] == expected_blend1[3]
                && blend1_store[4] == expected_blend1[4]
                && blend1_store[5] == expected_blend1[5]
                && blend1_store[6] == expected_blend1[6]
                && blend1_store[7] == expected_blend1[7]
                && blend2_store[0] == expected_blend2[0]
                && blend2_store[1] == expected_blend2[1]
                && blend2_store[2] == expected_blend2[2]
                && blend2_store[3] == expected_blend2[3]
                && is_snan(blend2_store[4])
                && blend2_store[5] == expected_blend2[5]
                && blend2_store[6] == expected_blend2[6]
                && blend2_store[7] == expected_blend2[7]);
}


void test_f32x8_as_mask256()
{
    const f32 a[8] = {qnanf, inff, -inff, denormf, snanf, .0f, -.0f, 1.f};
    const f32 b[8] = {-10.f, 1.f, -2.f, 10.f, 8641654.2154f, -.1f, 100.f, -99.9999f};

    const u32 expected_a_cast[8] = {qnan, inf, ninf, denorm, snan, zero, highbit32, 0x3F800000};
    const u32 expected_b_cast[8] = {0xC1200000, 0x3F800000, 0xC0000000, 0x41200000, 0x4B03DC76, 0xBDCCCCCD, 0x42C80000, 0xC2C7FFF3};

    u32 cast_a_store[8];
    u32 cast_b_store[8];
    mask256_storeu(cast_a_store, f32x8_as_mask256(f32x8_loadu(a)));
    mask256_storeu(cast_b_store, f32x8_as_mask256(f32x8_loadu(b)));

    bad_test_check(cast_a_store[0] == expected_a_cast[0]
                && cast_a_store[1] == expected_a_cast[1]
                && cast_a_store[2] == expected_a_cast[2]
                && cast_a_store[3] == expected_a_cast[3]
                && cast_a_store[4] == expected_a_cast[4]
                && cast_a_store[5] == expected_a_cast[5]
                && cast_a_store[6] == expected_a_cast[6]
                && cast_a_store[7] == expected_a_cast[7]
                && cast_b_store[0] == expected_b_cast[0]
                && cast_b_store[1] == expected_b_cast[1]
                && cast_b_store[2] == expected_b_cast[2]
                && cast_b_store[3] == expected_b_cast[3]
                && cast_b_store[4] == expected_b_cast[4]
                && cast_b_store[5] == expected_b_cast[5]
                && cast_b_store[6] == expected_b_cast[6]
                && cast_b_store[7] == expected_b_cast[7]);
}

BAD_NAMESPACE_END