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
    bad_align_to(mask128) u32 a[4] = {all1_bits, nosign_bits, zero_bits, lowbit32_bits};
    bad_align_to(mask128) u32 b[4] = {6484587u, 3u, 55u, 987654321u};

    bad_align_to(mask128) u32 a_out[4];
    bad_align_to(mask128) u32 b_out[4];
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
    u32 a[4] = {all1_bits, nosign_bits, zero_bits, lowbit32_bits};
    u32 b[4] = {6484587u, 3u, 55u, 987654321u};

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
    u32 a[4] = {all1_bits, nosign_bits, zero_bits, lowbit32_bits};
    u32 b[4] = {6484587u, 3u, 55u, 987654321u};

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


void test_mask128_set_all()
{
// With SSE, mask128_set1 is the same as _mm_set1_ps,
// which is already tested in test_f32x4.cpp
#if defined(__SSE2__)
    u32 a = all1_bits;
    u32 b = 6484587u;

    u32 a_set1_store[4];
    u32 b_set1_store[4];
    mask128_storeu(a_set1_store, mask128_set_all(a));
    mask128_storeu(b_set1_store, mask128_set_all(b));
    
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

    bad_test_check(zero_store[0] == zero_bits
                && zero_store[1] == zero_bits
                && zero_store[2] == zero_bits
                && zero_store[3] == zero_bits);
}


void test_mask128_all1()
{
    u32 all1_out[4];
    mask128_storeu(all1_out, mask128_all1());

    bad_test_check(all1_out[0] == all1_bits
                && all1_out[1] == all1_bits
                && all1_out[2] == all1_bits
                && all1_out[3] == all1_bits);
}


void test_mask128_value32()
{
    mask_elem value32_out[4];
    mask128_storeu(value32_out, mask128_value32());

    bad_test_check(value32_out[0] == nosign_bits
                && value32_out[1] == nosign_bits
                && value32_out[2] == nosign_bits
                && value32_out[3] == nosign_bits);
}


void test_mask128_highbit32()
{
    mask_elem highbit32_out[4];
    mask128_storeu(highbit32_out, mask128_highbit32());

    bad_test_check(highbit32_out[0] == highbit32_bits
                && highbit32_out[1] == highbit32_bits
                && highbit32_out[2] == highbit32_bits
                && highbit32_out[3] == highbit32_bits);
}


void test_mask128_lowbit32()
{
    mask_elem lowbit32_out[4];
    mask128_storeu(lowbit32_out, mask128_lowbit32());

#if defined(BAD_TEST_F32_MASK)
    f32 expected_lowbit32 = lowbit32();
#else
    u32 expected_lowbit32 = lowbit32_bits;
#endif

    bad_test_check(lowbit32_out[0] == expected_lowbit32
                && lowbit32_out[1] == expected_lowbit32
                && lowbit32_out[2] == expected_lowbit32
                && lowbit32_out[3] == expected_lowbit32);
}


void test_mask128_exponent32()
{
    mask_elem exponent32_out[4];
    mask128_storeu(exponent32_out, mask128_exponent32());

#if defined(BAD_TEST_F32_MASK)
    f32 expected_exponent32 = inf();
#else
    u32 expected_exponent32 = inf_bits;
#endif

    bad_test_check(exponent32_out[0] == expected_exponent32
                && exponent32_out[1] == expected_exponent32
                && exponent32_out[2] == expected_exponent32
                && exponent32_out[3] == expected_exponent32);
}


void test_mask128_eq()
{
#if defined(BAD_TEST_F32_MASK)
    mask128 a1 = mask128_set(qnan(), ninf(), inf(), denorm());
    mask128 a2 = mask128_set(.0f, -53.5f, 36.84841f, -.0f);
    mask128 b1 = mask128_set(qnan(), inf(), ninf(), denorm());
#else
    mask128 a1 = mask128_set(qnan_bits, ninf_bits, inf_bits, denorm_bits);
    mask128 a2 = mask128_set(6484587u, 0u, 55u, 987654321u);
    mask128 b1 = mask128_set(qnan_bits, inf_bits, ninf_bits, denorm_bits);
#endif

    mask_elem eq1_store[4];
    mask_elem eq2_store[4];
    mask128_storeu(eq1_store, mask128_eq(a1, b1));
    mask128_storeu(eq2_store, mask128_eq(a2, a2));    

#if defined(BAD_TEST_F32_MASK)
    f32 expected_eq1[4] = {all1(), zero(), zero(), all1()};
    f32 expected_eq2[4] = {all1(), all1(), all1(), all1()};

    bad_test_check(eq1_store[0] == expected_eq1[0]
                && eq1_store[1] == expected_eq1[1]
                && eq1_store[2] == expected_eq1[2]
                && is_qnan(eq1_store[3])
                && is_qnan(eq2_store[0])
                && is_qnan(eq2_store[1])
                && is_qnan(eq2_store[2])
                && is_qnan(eq2_store[3]));
#else
    u32 expected_eq1[4] = {all1_bits, zero_bits, zero_bits, all1_bits};
    u32 expected_eq2[4] = {all1_bits, all1_bits, all1_bits, all1_bits};

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
    mask128 a1 = mask128_set(qnan(), ninf(), inf(), denorm());
    mask128 a2 = mask128_set(.0f, -53.5f, 36.84841f, -.0f);
    mask128 b1 = mask128_set(qnan(), inf(), ninf(), denorm());
#else
    mask128 a1 = mask128_set(qnan_bits, ninf_bits, inf_bits, denorm_bits);
    mask128 a2 = mask128_set(6484587u, 0u, 55u, 987654321u);
    mask128 b1 = mask128_set(qnan_bits, inf_bits, ninf_bits, denorm_bits);
#endif

    mask_elem eq1_store[4];
    mask_elem eq2_store[4];
    mask128_storeu(eq1_store, mask128_neq(a1, b1));
    mask128_storeu(eq2_store, mask128_neq(a2, a2));

#if defined(BAD_TEST_F32_MASK)
    f32 expected_eq1[4] = {.0f, all1(), all1(), .0f};
    f32 expected_eq2[4] = {.0f, .0f, .0f, .0f};

    bad_test_check(is_qnan(eq1_store[0])
                && is_qnan(eq1_store[1])
                && is_qnan(eq1_store[2])
                && eq1_store[3] == expected_eq1[3]
                && eq2_store[0] == expected_eq2[0]
                && eq2_store[1] == expected_eq2[1]
                && eq2_store[2] == expected_eq2[2]
                && eq2_store[3] == expected_eq2[3]);
#else
    u32 expected_eq1[4] = {zero_bits, all1_bits, all1_bits, zero_bits};
    u32 expected_eq2[4] = {zero_bits, zero_bits, zero_bits, zero_bits};

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
    mask128 a1 = mask128_set(qnan(), ninf(), denorm(), all1());
    mask128 a2 = mask128_set(all1(), .0f, -.0f, lowbit32());
    mask128 b  = mask128_set(1.f, 2.f, -3.f, 4.f);
#else
    mask128 a1 = mask128_set(qnan_bits, ninf_bits, denorm_bits, all1_bits);
    mask128 a2 = mask128_set(all1_bits, zero_bits, highbit32_bits, lowbit32_bits);
    mask128 b  = mask128_set(0x3F800000, 0x40000000, 0xC0400000, 0x40800000);
#endif

    mask_elem and1_store[4];
    mask_elem and2_store[4];
    mask128_storeu(and1_store, mask128_and(a1, b));
    mask128_storeu(and2_store, mask128_and(a2, b));

#if defined(BAD_TEST_F32_MASK)
    f32 expected_and1[4] = {1.f, 2.f, 2.f, 4.f};
    f32 expected_and2[4] = {1.f, .0f, -.0f, .0f};
#else
    u32 expected_and1[4] = {0x3F800000, 0x40000000, highbit32_bits, 0x40800000};
    u32 expected_and2[4] = {0x3F800000, zero_bits, highbit32_bits, zero_bits};
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
    f32 a0[4] = {qnan(), ninf(), denorm(),     all1()};
    f32 a1[4] = {all1(),    .0f,     -.0f, lowbit32()};
    f32 b [4] = {1.f,       2.f,     -3.f,        4.f};
#else
    u32 a0[4] = {qnan_bits, ninf_bits,    denorm_bits, all1_bits};
    u32 a1[4] = {all1_bits, zero_bits, highbit32_bits,  lowbit32_bits};
    u32 b [4] = {0x3F800000, 0x40000000, 0xC0400000, 0x40800000};
#endif

    mask_elem and_not0_store[4];
    mask_elem and_not1_store[4];
    mask128_storeu(and_not0_store, mask128_and_not(mask128_loadu(a0), mask128_loadu(b)));
    mask128_storeu(and_not1_store, mask128_and_not(mask128_loadu(a1), mask128_loadu(b)));
#if defined(BAD_TEST_F32_MASK)
    f32 expected_and_not0[4] = {qnan(), .0f, -.0f, lowbit32()};
    f32 expected_and_not1[4] = {   1.f, 2.f, -.0f,        4.f};
#else
    u32 expected_and_not0[4] = {a0[0] & ~b[0], a0[1] & ~b[1], a0[2] & ~b[2], a0[3] & ~b[3]};
    u32 expected_and_not1[4] = {a1[0] & ~b[0], a1[1] & ~b[1], a1[2] & ~b[2], a1[3] & ~b[3]};
#endif

    bad_test_check(and_not0_store[0] == expected_and_not0[0]
                && and_not0_store[1] == expected_and_not0[1]
                && and_not0_store[2] == expected_and_not0[2]
                && and_not0_store[3] == expected_and_not0[3]
                && and_not1_store[0] == expected_and_not1[0]
                && and_not1_store[1] == expected_and_not1[1]
                && and_not1_store[2] == expected_and_not1[2]
                && and_not1_store[3] == expected_and_not1[3]);
}


void test_mask128_or()
{
#if defined(BAD_TEST_F32_MASK)
    f32 a0[4] = {qnan(), ninf(), denorm(),     all1()};
    f32 a1[4] = {all1(),    .0f,     -.0f, lowbit32()};
    f32 b [4] = {   1.f,    2.f,     -3.f,        4.f};
#else
    u32 a0[4] = {qnan_bits, ninf_bits,    denorm_bits,      all1_bits};
    u32 a1[4] = {all1_bits, zero_bits, highbit32_bits,  lowbit32_bits};
    u32 b [4] = {0x3F800000, 0x40000000, 0xC0400000, 0x40800000};
#endif
    mask_elem or0_store[4];
    mask_elem or1_store[4];
    mask128_storeu(or0_store, mask128_or(mask128_loadu(a0), mask128_loadu(b)));
    mask128_storeu(or1_store, mask128_or(mask128_loadu(a1), mask128_loadu(b)));

#if defined(BAD_TEST_F32_MASK)
    f32 expected_or0[4] = {qnan(), ninf(), -3.390689373016357421875f,                  all1()};
    f32 expected_or1[4] = {all1(),    2.f,                      -3.f, 4.000000476837158203125f};
#else
    u32 expected_or0[4] = {a0[0] | b[0], a0[1] | b[1], a0[2] | b[2], a0[3] | b[3]};
    u32 expected_or1[4] = {a1[0] | b[0], a1[1] | b[1], a1[2] | b[2], a1[3] | b[3]};
#endif

#if defined(BAD_TEST_F32_MASK)
    bad_test_check(is_qnan(or0_store[0])
#else
    bad_test_check(or0_store[0] == expected_or0[0]
#endif
                && or0_store[1] == expected_or0[1]
                && or0_store[2] == expected_or0[2]
                && or0_store[3] == expected_or0[3]
                && or1_store[0] == expected_or1[0]
                && or1_store[1] == expected_or1[1]
                && or1_store[2] == expected_or1[2]
                && or1_store[3] == expected_or1[3]);
}


void test_mask128_xor()
{
#if defined(BAD_TEST_F32_MASK)
    f32 a0[4] = {qnan(), ninf(), denorm(),     all1()};
    f32 a1[4] = {all1(),    .0f,     -.0f, lowbit32()};
    f32 b [4] = { 1.f,  2.f,   -3.f,      4.f};
#else
    u32 a0[4] = {qnan_bits, ninf_bits,    denorm_bits,     all1_bits};
    u32 a1[4] = {all1_bits, zero_bits, highbit32_bits, lowbit32_bits};
    u32 b [4] = {0x3F800000, 0x40000000, 0xC0400000, 0x40800000};
#endif

    mask_elem xor0_store[4];
    mask_elem xor1_store[4];
    mask128_storeu(xor0_store, mask128_xor(mask128_loadu(a0), mask128_loadu(b)));
    mask128_storeu(xor1_store, mask128_xor(mask128_loadu(a1), mask128_loadu(b)));

#if defined(BAD_TEST_F32_MASK)
    f32 expected_xor0[4] = {3.f, -1.f, 3.390689373016357421875f, -.999999940395355224609375f};
    f32 expected_xor1[4] = {-3.9999997615814208984375f, 2.f, 3.f, 4.000000476837158203125f};
#else
    u32 expected_xor0[4] = {a0[0] ^ b[0], a0[1] ^ b[1], a0[2] ^ b[2], a0[3] ^ b[3]};
    u32 expected_xor1[4] = {a1[0] ^ b[0], a1[1] ^ b[1], a1[2] ^ b[2], a1[3] ^ b[3]};
#endif

    bad_test_check(xor0_store[0] == expected_xor0[0]
                && xor0_store[1] == expected_xor0[1]
                && xor0_store[2] == expected_xor0[2]
                && xor0_store[3] == expected_xor0[3]
                && xor1_store[0] == expected_xor1[0]
                && xor1_store[1] == expected_xor1[1]
                && xor1_store[2] == expected_xor1[2]
                && xor1_store[3] == expected_xor1[3]);
}


void test_mask128_not()
{
#if defined(BAD_TEST_F32_MASK)
    f32 a[4] = {qnan(), ninf(), denorm(), all1()};
    f32 b[4] = {   1.f,    2.f,     -3.f,    4.f};
#else
    u32 a[4] = { qnan_bits,  ninf_bits, denorm_bits,  all1_bits};
    u32 b[4] = {0x3F800000, 0x40000000,  0xC0400000, 0x40800000};
#endif

    mask_elem not_a_store[4];
    mask_elem not_b_store[4];
    mask128_storeu(not_a_store, mask128_not(mask128_loadu(a)));
    mask128_storeu(not_b_store, mask128_not(mask128_loadu(b)));

#if defined(BAD_TEST_F32_MASK)
    f32 expected_not_a[4] = {-5.87747035281e-39f, 1.17549421069e-38f, qnan(), .0f};
    f32 expected_not_b[4] = {-3.99999976158f, -1.99999988079f, 1.49999988079f, -.999999940395f};
#else
    u32 expected_not_a[4] = {~a[0], ~a[1], ~a[2], ~a[3]};
    u32 expected_not_b[4] = {~b[0], ~b[1], ~b[2], ~b[3]};
#endif

    bad_test_check(not_a_store[0] == expected_not_a[0]
                && not_a_store[1] == expected_not_a[1]
#if defined(BAD_TEST_F32_MASK)
                && is_qnan(not_a_store[2])
#else
                && not_a_store[2] == expected_not_a[2]
#endif
                && not_a_store[3] == expected_not_a[3]
                && not_b_store[0] == expected_not_b[0]
                && not_b_store[1] == expected_not_b[1]
                && not_b_store[2] == expected_not_b[2]
                && not_b_store[3] == expected_not_b[3]);
}

BAD_NAMESPACE_END
