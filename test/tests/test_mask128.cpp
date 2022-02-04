#include "test_mask128.h"
#include "../test.h"
#include "../test_values.h"

#include <bad/common/mask128.h>
#include <bad/qualifiers.h>

BAD_NAMESPACE_START

void test_mask128_load_store()
{
// With SSE, mask128_load/mask128_store is the same as _mm_load_ps/_mm_store_ps,
// which are already tested in test_f32x4.cpp
#if defined(__SSE2__)
    bad_align(16) const u32 a[4] = {all1, nosign, zero, lowbit32};
    bad_align(16) const u32 b[4] = {6484587u, 3u, 55u, 987654321u};

    bad_align(16) u32 a_out[4];
    bad_align(16) u32 b_out[4];
    mask128_store(a_out, mask128_load(a));
    mask128_store(b_out, mask128_load(b));

    bad_test_check(a_out[0] == a[0]
                && a_out[1] == a[1]
                && a_out[2] == a[2]
                && a_out[3] == a[3]
                && b_out[0] == b[0]
                && b_out[1] == b[1]
                && b_out[2] == b[2]
                && b_out[3] == b[3]);
#endif
}


void test_mask128_loadu_storeu()
{
// With SSE, mask128_loadu/mask128_storeu is the same as _mm_loadu_ps/_mm_storeu_ps,
// which are already tested in test_f32x4.cpp
#if defined(__SSE2__)
    const u32 a[4] = {all1, nosign, zero, lowbit32};
    const u32 b[4] = {6484587u, 3u, 55u, 987654321u};

    u32 a_out[4];
    u32 b_out[4];
    mask128_storeu(a_out, mask128_loadu(a));
    mask128_storeu(b_out, mask128_loadu(b));

    bad_test_check(a_out[0] == a[0]
                && a_out[1] == a[1]
                && a_out[2] == a[2]
                && a_out[3] == a[3]
                && b_out[0] == b[0]
                && b_out[1] == b[1]
                && b_out[2] == b[2]
                && b_out[3] == b[3]);
#endif
}


void test_mask128_set()
{
// With SSE, mask128_set is the same as _mm_set_ps,
// which is already tested in test_f32x4.cpp
#if defined(__SSE2__)
    const u32 a[4] = {all1, nosign, zero, lowbit32};
    const u32 b[4] = {6484587u, 3u, 55u, 987654321u};

    u32 a_set_store[4];
    u32 b_set_store[4];
    mask128_storeu(a_set_store, mask128_set(a[0], a[1], a[2], a[3]));
    mask128_storeu(b_set_store, mask128_set(b[0], b[1], b[2], b[3]));
    
    bad_test_check(a[0] == a_set_store[0]
                && a[1] == a_set_store[1]
                && a[2] == a_set_store[2]
                && a[3] == a_set_store[3]
                && b[0] == b_set_store[0]
                && b[1] == b_set_store[1]
                && b[2] == b_set_store[2]
                && b[3] == b_set_store[3]);
#endif
}


void test_mask128_set1()
{
// With SSE, mask128_set1 is the same as _mm_set1_ps,
// which is already tested in test_f32x4.cpp
#if defined(__SSE2__)
    const u32 a = all1;
    const u32 b = 6484587u;

    u32 a_set1_store[4];
    u32 b_set1_store[4];
    mask128_storeu(a_set1_store, mask128_set1(a));
    mask128_storeu(b_set1_store, mask128_set1(b));
    
    bad_test_check(a == a_set1_store[0]
                && a == a_set1_store[1]
                && a == a_set1_store[2]
                && a == a_set1_store[3]
                && b == b_set1_store[0]
                && b == b_set1_store[1]
                && b == b_set1_store[2]
                && b == b_set1_store[3]);
#endif
}


void test_mask128_zero()
{
    mask_elem zero_store[4];
    mask128_storeu(zero_store, mask128_zero());

    bad_test_check(zero_store[0] == zero
                && zero_store[1] == zero
                && zero_store[2] == zero
                && zero_store[3] == zero);
}


void test_mask128_all1()
{
    u32 all1_out[4];
    mask128_storeu(all1_out, mask128_all1());

    bad_test_check(all1_out[0] == all1
                && all1_out[1] == all1
                && all1_out[2] == all1
                && all1_out[3] == all1);
}


void test_mask128_value32()
{
    mask_elem value32_out[4];
    mask128_storeu(value32_out, mask128_value32());

    bad_test_check(value32_out[0] == nosign
                && value32_out[1] == nosign
                && value32_out[2] == nosign
                && value32_out[3] == nosign);
}


void test_mask128_highbit32()
{
    mask_elem highbit32_out[4];
    mask128_storeu(highbit32_out, mask128_highbit32());

    bad_test_check(highbit32_out[0] == highbit32
                && highbit32_out[1] == highbit32
                && highbit32_out[2] == highbit32
                && highbit32_out[3] == highbit32);
}


void test_mask128_lowbit32()
{
    mask_elem lowbit32_out[4];
    mask128_storeu(lowbit32_out, mask128_lowbit32());

    const f32 expected_lowbit32 = lowbit32;

    bad_test_check(lowbit32_out[0] == expected_lowbit32
                && lowbit32_out[1] == expected_lowbit32
                && lowbit32_out[2] == expected_lowbit32
                && lowbit32_out[3] == expected_lowbit32);
}


void test_mask128_exponent32()
{
    mask_elem exponent32_out[4];
    mask128_storeu(exponent32_out, mask128_exponent32());

    const f32 expected_exponent32 = inf;

    bad_test_check(exponent32_out[0] == expected_exponent32
                && exponent32_out[1] == expected_exponent32
                && exponent32_out[2] == expected_exponent32
                && exponent32_out[3] == expected_exponent32);
}


void test_mask128_eq()
{
#if defined(BAD_TEST_F32_MASK)
    const mask128 a1 = mask128_set(qnan, -inf, inf, denorm);
    const mask128 a2 = mask128_set(.0f, -53.5f, 36.84841f, -.0f);
    const mask128 b1 = mask128_set(qnan, inf, -inf, denorm);
#else
    const mask128 a1 = mask128_set(qnan, ninf, inf, denorm);
    const mask128 a2 = mask128_set(6484587u, 0u, 55u, 987654321u);
    const mask128 b1 = mask128_set(qnan, inf, ninf, denorm);
#endif

    mask_elem eq1_store[4];
    mask_elem eq2_store[4];
    mask128_storeu(eq1_store, mask128_eq(a1, b1));
    mask128_storeu(eq2_store, mask128_eq(a2, a2));    

    const f32 expected_eq1[4] = {all1, zero, zero, all1};
    const f32 expected_eq2[4] = {all1, all1, all1, all1};

#if defined(BAD_TEST_F32_MASK)
    bad_test_check(eq1_store[0] == expected_eq1[0]
                && eq1_store[1] == expected_eq1[1]
                && eq1_store[2] == expected_eq1[2]
                && is_qnan(eq1_store[3])
                && is_qnan(eq2_store[0])
                && is_qnan(eq2_store[1])
                && is_qnan(eq2_store[2])
                && is_qnan(eq2_store[3]));
#else
    bad_test_check(eq1_store[0] == expected_eq1[0]
                && eq1_store[1] == expected_eq1[1]
                && eq1_store[2] == expected_eq1[2]
                && eq1_store[3] == expected_eq1[3]
                && eq2_store[0] == expected_eq2[0]
                && eq2_store[1] == expected_eq2[1]
                && eq2_store[2] == expected_eq2[2]
                && eq2_store[3] == expected_eq2[3]);
#endif
}


void test_mask128_neq()
{
#if defined(BAD_TEST_F32_MASK)
    const mask128 a1 = mask128_set(qnan, -inf, inf, denorm);
    const mask128 a2 = mask128_set(.0f, -53.5f, 36.84841f, -.0f);
    const mask128 b1 = mask128_set(qnan, inf, -inf, denorm);
#else
    const mask128 a1 = mask128_set(qnan, ninf, inf, denorm);
    const mask128 a2 = mask128_set(6484587u, 0u, 55u, 987654321u);
    const mask128 b1 = mask128_set(qnan, inf, ninf, denorm);
#endif

    mask_elem eq1_store[4];
    mask_elem eq2_store[4];
    mask128_storeu(eq1_store, mask128_neq(a1, b1));
    mask128_storeu(eq2_store, mask128_neq(a2, a2));

#if defined(BAD_TEST_F32_MASK)
    const f32 expected_eq1[4] = {.0f, all1, all1, .0f};
    const f32 expected_eq2[4] = {.0f, .0f, .0f, .0f};

    bad_test_check(is_qnan(eq1_store[0])
                && is_qnan(eq1_store[1])
                && is_qnan(eq1_store[2])
                && eq1_store[3] == expected_eq1[3]
                && eq2_store[0] == expected_eq2[0]
                && eq2_store[1] == expected_eq2[1]
                && eq2_store[2] == expected_eq2[2]
                && eq2_store[3] == expected_eq2[3]);
#else
    const f32 expected_eq1[4] = {zero, all1, all1, zero};
    const f32 expected_eq2[4] = {zero, zero, zero, zero};

    bad_test_check(eq1_store[0] == expected_eq1[0]
                && eq1_store[1] == expected_eq1[1]
                && eq1_store[2] == expected_eq1[2]
                && eq1_store[3] == expected_eq1[3]
                && eq2_store[0] == expected_eq2[0]
                && eq2_store[1] == expected_eq2[1]
                && eq2_store[2] == expected_eq2[2]
                && eq2_store[3] == expected_eq2[3]);
#endif
}


void test_mask128_and()
{
#if defined(BAD_TEST_F32_MASK)
    const mask128 a1 = mask128_set(qnan, -inf, denorm, all1);
    const mask128 a2 = mask128_set(all1, .0f, -.0f, lowbit32);
    const mask128 b  = mask128_set(1.f, 2.f, -3.f, 4.f);
#else
    const mask128 a1 = mask128_set(qnan, ninf, denorm, all1);
    const mask128 a2 = mask128_set(all1, zero, highbit32, lowbit32);
    const mask128 b  = mask128_set(0x3F800000, 0x40000000, 0xC0400000, 0x40800000);
#endif

    mask_elem and1_store[4];
    mask_elem and2_store[4];
    mask128_storeu(and1_store, mask128_and(a1, b));
    mask128_storeu(and2_store, mask128_and(a2, b));

#if defined(BAD_TEST_F32_MASK)
    const f32 expected_and1[4] = {1.f, 2.f, 2.f, 4.f};
    const f32 expected_and2[4] = {1.f, .0f, -.0f, .0f};
#else
    const u32 expected_and1[4] = {0x3F800000, 0x40000000, highbit32, 0x40800000};
    const u32 expected_and2[4] = {0x3F800000, zero, highbit32, zero};
#endif

    bad_test_check(and1_store[0] == expected_and1[0]
                && and1_store[1] == expected_and1[1]
                && and1_store[2] == expected_and1[2]
                && and1_store[3] == expected_and1[3]
                && and2_store[0] == expected_and2[0]
                && and2_store[1] == expected_and2[1]
                && and2_store[2] == expected_and2[2]
                && and2_store[3] == expected_and2[3]);
}


void test_mask128_and_not()
{
#if defined(BAD_TEST_F32_MASK)
    const mask128 a1 = mask128_set(qnan, -inf, denorm, all1);
    const mask128 a2 = mask128_set(all1, .0f, -.0f, lowbit32);
    const mask128 b  = mask128_set(1.f, 2.f, -3.f, 4.f);
#else
    const mask128 a1 = mask128_set(qnan, ninf, denorm, all1);
    const mask128 a2 = mask128_set(all1, zero, highbit32, lowbit32);
    const mask128 b  = mask128_set(0x3F800000, 0x40000000, 0xC0400000, 0x40800000);
#endif

    mask_elem and_not1_store[4];
    mask_elem and_not2_store[4];
    mask128_storeu(and_not1_store, mask128_and_not(a1, b));
    mask128_storeu(and_not2_store, mask128_and_not(a2, b));

#if defined(BAD_TEST_F32_MASK)
    const f32 expected_and_not1[4] = {0xC00A6A0C, 0xBF800000, 0x0019010E, 0xBF7FFFFF};
    const f32 expected_and_not2[4] = {0xC07FFFFF, .0f, .0f, lowbit32};
#else
    const u32 expected_and_not1[4] = {0xC00A6A0C, 0xBF800000, 0x0019010E, 0xBF7FFFFF};
    const u32 expected_and_not2[4] = {0xC07FFFFF, zero, zero, lowbit32};
#endif

    bad_test_check(and_not1_store[0] == expected_and_not1[0]
                && and_not1_store[1] == expected_and_not1[1]
                && and_not1_store[2] == expected_and_not1[2]
                && and_not1_store[3] == expected_and_not1[3]
                && and_not2_store[0] == expected_and_not2[0]
                && and_not2_store[1] == expected_and_not2[1]
                && and_not2_store[2] == expected_and_not2[2]
                && and_not2_store[3] == expected_and_not2[3]);
}


void test_mask128_or()
{
#if defined(BAD_TEST_F32_MASK)
    const mask128 a1 = mask128_set(qnan, -inf, denorm, all1);
    const mask128 a2 = mask128_set(all1, .0f, -.0f, lowbit32);
    const mask128 b  = mask128_set(1.f, 2.f, -3.f, 4.f);
#else
    const mask128 a1 = mask128_set(qnan, ninf, denorm, all1);
    const mask128 a2 = mask128_set(all1, zero, highbit32, lowbit32);
    const mask128 b  = mask128_set(0x3F800000, 0x40000000, 0xC0400000, 0x40800000);
#endif

    mask_elem or1_store[4];
    mask_elem or2_store[4];
    mask128_storeu(or1_store, mask128_or(a1, b));
    mask128_storeu(or2_store, mask128_or(a2, b));

#if defined(BAD_TEST_F32_MASK)
    const f32 expected_or1[4] = {0xFF8A6A0C, -inf, 0xC059010E, all1};
    const f32 expected_or2[4] = {all1, 2.f, -3.f, 0x40800001};
#else
    const u32 expected_or1[4] = {0xFF8A6A0C, ninf, 0xC059010E, all1};
    const u32 expected_or2[4] = {all1, 0x40000000, 0xC0400000, 0x40800001};
#endif

#if defined(BAD_TEST_F32_MASK)
    bad_test_check((*(u32*)&or1_store[0]) & (*(u32*)&expected_or1[0]) == expected_or1[0]
#else
    bad_test_check(or1_store[0] == expected_or1[0]
#endif
                && or1_store[1] == expected_or1[1]
                && or1_store[2] == expected_or1[2]
                && or1_store[3] == expected_or1[3]
                && or2_store[0] == expected_or2[0]
                && or2_store[1] == expected_or2[1]
                && or2_store[2] == expected_or2[2]
                && or2_store[3] == expected_or2[3]);
}


void test_mask128_xor()
{
#if defined(BAD_TEST_F32_MASK)
    const mask128 a1 = mask128_set(qnan, -inf, denorm, all1);
    const mask128 a2 = mask128_set(all1, .0f, -.0f, lowbit32);
    const mask128 b  = mask128_set(1.f, 2.f, -3.f, 4.f);
#else
    const mask128 a1 = mask128_set(qnan, ninf, denorm, all1);
    const mask128 a2 = mask128_set(all1, zero, highbit32, lowbit32);
    const mask128 b  = mask128_set(0x3F800000, 0x40000000, 0xC0400000, 0x40800000);
#endif

    mask_elem xor1_store[4];
    mask_elem xor2_store[4];
    mask128_storeu(xor1_store, mask128_xor(a1, b));
    mask128_storeu(xor2_store, mask128_xor(a2, b));

    const mask_elem expected_xor1[4] = {0xC00A6A0C, 0xBF800000, 0x4059010E, 0xBF7FFFFF};
    const mask_elem expected_xor2[4] = {0xC07FFFFF, 0x40000000, 0x40400000, 0x40800001};

    bad_test_check(xor1_store[0] == expected_xor1[0]
                && xor1_store[1] == expected_xor1[1]
                && xor1_store[2] == expected_xor1[2]
                && xor1_store[3] == expected_xor1[3]
                && xor2_store[0] == expected_xor2[0]
                && xor2_store[1] == expected_xor2[1]
                && xor2_store[2] == expected_xor2[2]
                && xor2_store[3] == expected_xor2[3]);
}


void test_mask128_not()
{
#if defined(BAD_TEST_F32_MASK)
    const mask128 a = mask128_set(qnan, -inf, denorm, all1);
    const mask128 b = mask128_set(1.f, 2.f, -3.f, 4.f);
#else
    const mask128 a = mask128_set(qnan, ninf, denorm, all1);
    const mask128 b = mask128_set(0x3F800000, 0x40000000, 0xC0400000, 0x40800000);
#endif

    mask_elem not_a_store[4];
    mask_elem not_b_store[4];
    mask128_storeu(not_a_store, mask128_not(a));
    mask128_storeu(not_b_store, mask128_not(b));

    const mask_elem expected_not_a[4] = {0x007595F3, 0x007FFFFF, 0x7FE6FEF1, 0x00000000};
    const mask_elem expected_not_b[4] = {0xC07FFFFF, 0xBFFFFFFF, 0x3FBFFFFF, 0xBF7FFFFF};

    bad_test_check(not_a_store[0] == expected_not_a[0]
                && not_a_store[1] == expected_not_a[1]
                && not_a_store[2] == expected_not_a[2]
                && not_a_store[3] == expected_not_a[3]
                && not_b_store[0] == expected_not_b[0]
#if defined(BAD_TEST_F32_MASK)
                && is_qnan(not_b_store[1])
#else
                && not_b_store[1] == expected_not_b[1]
#endif
                && not_b_store[2] == expected_not_b[2]
                && not_b_store[3] == expected_not_b[3]);
}

BAD_NAMESPACE_END