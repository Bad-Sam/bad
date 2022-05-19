#include "test_mask256.h"
#include "../test.h"
#include "../test_values.h"

#include <bad/common/mask256.h>
#include <bad/qualifiers.h>

#if defined(__SSE__) && !defined(__SSE2__)
#   define BAD_TEST_F32_MASK
#endif

BAD_NAMESPACE_START

void test_mask256_load_store()
{
    bad_align(32) const u32 a[8] = {all1_bits, nosign_bits, zero_bits, lowbit32_bits, denorm_bits, snan_bits, all1_bits, highbit32_bits};
    bad_align(32) const u32 b[8] = {0x00E00100, 0xFFFFFFFF, 0x12345678, 0xF9182765, 0x11111111, 0xAAAAAAAA, 0xA1B2C3D4, 0xFEDCBA65};

    bad_align(32) u32 a_out[8];
    bad_align(32) u32 b_out[8];
    mask256_store(a_out, mask256_load(a));
    mask256_store(b_out, mask256_load(b));

    bad_test_check(a_out[0] == a[0] && a_out[1] == a[1] && a_out[2] == a[2] && a_out[3] == a[3]
                && a_out[4] == a[4] && a_out[5] == a[5] && a_out[6] == a[6] && a_out[7] == a[7]
                && b_out[0] == b[0] && b_out[1] == b[1] && b_out[2] == b[2] && b_out[3] == b[3]
                && b_out[4] == b[4] && b_out[5] == b[5] && b_out[6] == b[6] && b_out[7] == b[7]);
}


void test_mask256_loadu_storeu()
{
    const u32 a[8] = {all1_bits, nosign_bits, zero_bits, lowbit32_bits, denorm_bits, snan_bits, all1_bits, highbit32_bits};
    const u32 b[8] = {0x00E00100, 0xF0F0F0F0, 0x12345678, 0xF9182765, 0x11111111, 0xAAAAAAAA, 0xA1B2C3D4, 0xFEDCBA65};

    u32 a_out[8];
    u32 b_out[8];
    mask256_storeu(a_out, mask256_loadu(a));
    mask256_storeu(b_out, mask256_loadu(b));

    bad_test_check(a_out[0] == a[0] && a_out[1] == a[1] && a_out[2] == a[2] && a_out[3] == a[3]
                && a_out[4] == a[4] && a_out[5] == a[5] && a_out[6] == a[6] && a_out[7] == a[7]
                && b_out[0] == b[0] && b_out[1] == b[1] && b_out[2] == b[2] && b_out[3] == b[3]
                && b_out[4] == b[4] && b_out[5] == b[5] && b_out[6] == b[6] && b_out[7] == b[7]);
}


void test_mask256_set()
{
    const u32 a[8] = {all1_bits, nosign_bits, zero_bits, lowbit32_bits, denorm_bits, snan_bits, all1_bits, highbit32_bits};
    const u32 b[8] = {0x00E00100, 0xFFFFFFFF, 0x12345678, 0xF9182765, 0x11111111, 0xAAAAAAAA, 0xA1B2C3D4, 0xFEDCBA65};

    u32 a_out[8];
    u32 b_out[8];
    mask256_storeu(a_out, mask256_set(a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7]));
    mask256_storeu(b_out, mask256_set(b[0], b[1], b[2], b[3], b[4], b[5], b[6], b[7]));
    
    bad_test_check(a_out[0] == a[0] && a_out[1] == a[1] && a_out[2] == a[2] && a_out[3] == a[3]
                && a_out[4] == a[4] && a_out[5] == a[5] && a_out[6] == a[6] && a_out[7] == a[7]
                && b_out[0] == b[0] && b_out[1] == b[1] && b_out[2] == b[2] && b_out[3] == b[3]
                && b_out[4] == b[4] && b_out[5] == b[5] && b_out[6] == b[6] && b_out[7] == b[7]);
}


void test_mask256_set_all()
{
    const u32 a = all1_bits;
    const u32 b = 0xF9182765;

    u32 a_out[8];
    u32 b_out[8];
    mask256_storeu(a_out, mask256_set_all(a));
    mask256_storeu(b_out, mask256_set_all(b));
    
    bad_test_check(a == a_out[0] && a == a_out[1] && a == a_out[2] && a == a_out[3]
                && a == a_out[4] && a == a_out[5] && a == a_out[6] && a == a_out[7]
                && b == b_out[0] && b == b_out[1] && b == b_out[2] && b == b_out[3]
                && b == b_out[4] && b == b_out[5] && b == b_out[6] && b == b_out[7]);
}


void test_mask256_zero()
{
    u32 zero_bits_store[8];
    mask256_storeu(zero_bits_store, mask256_zero());

    bad_test_check(zero_bits_store[0] == zero_bits && zero_bits_store[1] == zero_bits
                && zero_bits_store[2] == zero_bits && zero_bits_store[3] == zero_bits
                && zero_bits_store[4] == zero_bits && zero_bits_store[5] == zero_bits
                && zero_bits_store[6] == zero_bits && zero_bits_store[7] == zero_bits);
}


void test_mask256_all1()
{
    u32 all1_out[8];
    mask256_storeu(all1_out, mask256_all1());

    bad_test_check(all1_out[0] == all1_bits && all1_out[1] == all1_bits
                && all1_out[2] == all1_bits && all1_out[3] == all1_bits
                && all1_out[4] == all1_bits && all1_out[5] == all1_bits
                && all1_out[6] == all1_bits && all1_out[7] == all1_bits);
}


void test_mask256_value32()
{ 
    u32 value32_out[8];
    mask256_storeu(value32_out, mask256_value32());

    bad_test_check(value32_out[0] == nosign_bits && value32_out[1] == nosign_bits
                && value32_out[2] == nosign_bits && value32_out[3] == nosign_bits
                && value32_out[4] == nosign_bits && value32_out[5] == nosign_bits
                && value32_out[6] == nosign_bits && value32_out[7] == nosign_bits);
}


void test_mask256_highbit32()
{
    u32 highbit32_bits_out[8];
    mask256_storeu(highbit32_bits_out, mask256_highbit32());

    bad_test_check(highbit32_bits_out[0] == highbit32_bits && highbit32_bits_out[1] == highbit32_bits
                && highbit32_bits_out[2] == highbit32_bits && highbit32_bits_out[3] == highbit32_bits
                && highbit32_bits_out[4] == highbit32_bits && highbit32_bits_out[5] == highbit32_bits
                && highbit32_bits_out[6] == highbit32_bits && highbit32_bits_out[7] == highbit32_bits);
}


void test_mask256_lowbit32()
{
    u32 lowbit32_bits_out[8];
    mask256_storeu(lowbit32_bits_out, mask256_lowbit32());

    bad_test_check(lowbit32_bits_out[0] == lowbit32_bits && lowbit32_bits_out[1] == lowbit32_bits
                && lowbit32_bits_out[2] == lowbit32_bits && lowbit32_bits_out[3] == lowbit32_bits
                && lowbit32_bits_out[4] == lowbit32_bits && lowbit32_bits_out[5] == lowbit32_bits
                && lowbit32_bits_out[6] == lowbit32_bits && lowbit32_bits_out[7] == lowbit32_bits);
}


void test_mask256_exponent32()
{
    u32 exponent32_out[8];
    mask256_storeu(exponent32_out, mask256_exponent32());

    bad_test_check(exponent32_out[0] == inf_bits && exponent32_out[1] == inf_bits
                && exponent32_out[2] == inf_bits && exponent32_out[3] == inf_bits
                && exponent32_out[4] == inf_bits && exponent32_out[5] == inf_bits
                && exponent32_out[6] == inf_bits && exponent32_out[7] == inf_bits);
}


void test_mask256_eq()
{
    const u32 a1[8] = {all1_bits, nosign_bits, zero_bits, lowbit32_bits, denorm_bits, snan_bits, all1_bits, highbit32_bits};
    const u32 a2[8] = {0x00E00100, 0x7FFFFFFF, 0x12345678, 0xF9182765, 0x11111111, 0xAAAAAAAA, 0xA1B2C3D4, 0xFEDCBA65};
    const u32 b[8]  = {all1_bits, 0x12345678, all1_bits, denorm_bits, snan_bits, zero_bits, 0xFEDCBA65, nosign_bits};

    u32 eq1_store[8];
    u32 eq2_store[8];
    mask256_storeu(eq1_store, mask256_eq(mask256_loadu(a1), mask256_loadu(b)));
    mask256_storeu(eq2_store, mask256_eq(mask256_loadu(a2), mask256_loadu(b)));

    const u32 expected_eq1[8] =
    {
        (a1[0] == b[0]) * 0xFFFFFFFF, (a1[1] == b[1]) * 0xFFFFFFFF, 
        (a1[2] == b[2]) * 0xFFFFFFFF, (a1[3] == b[3]) * 0xFFFFFFFF,
        (a1[4] == b[4]) * 0xFFFFFFFF, (a1[5] == b[5]) * 0xFFFFFFFF,
        (a1[6] == b[6]) * 0xFFFFFFFF, (a1[7] == b[7]) * 0xFFFFFFFF
    };
    const u32 expected_eq2[8] =
    {
        (a2[0] == b[0]) * 0xFFFFFFFF, (a2[1] == b[1]) * 0xFFFFFFFF, 
        (a2[2] == b[2]) * 0xFFFFFFFF, (a2[3] == b[3]) * 0xFFFFFFFF,
        (a2[4] == b[4]) * 0xFFFFFFFF, (a2[5] == b[5]) * 0xFFFFFFFF,
        (a2[6] == b[6]) * 0xFFFFFFFF, (a2[7] == b[7]) * 0xFFFFFFFF
    };

    bad_test_check(eq1_store[0] == expected_eq1[0] && eq1_store[1] == expected_eq1[1]
                && eq1_store[2] == expected_eq1[2] && eq1_store[3] == expected_eq1[3]
                && eq1_store[4] == expected_eq1[4] && eq1_store[5] == expected_eq1[5]
                && eq1_store[6] == expected_eq1[6] && eq1_store[7] == expected_eq1[7]
                && eq2_store[0] == expected_eq2[0] && eq2_store[1] == expected_eq2[1]
                && eq2_store[2] == expected_eq2[2] && eq2_store[3] == expected_eq2[3]
                && eq2_store[4] == expected_eq2[4] && eq2_store[5] == expected_eq2[5]
                && eq2_store[6] == expected_eq2[6] && eq2_store[7] == expected_eq2[7]);
}


void test_mask256_neq()
{
    const u32 a1[8] = {all1_bits, nosign_bits, zero_bits, lowbit32_bits, denorm_bits, snan_bits, all1_bits, highbit32_bits};
    const u32 a2[8] = {0x00E00100, 0x7FFFFFFF, 0x12345678, 0xF9182765, 0x11111111, 0xAAAAAAAA, 0xA1B2C3D4, 0xFEDCBA65};
    const u32 b[8]  = {all1_bits, 0x12345678, all1_bits, denorm_bits, snan_bits, zero_bits, 0xFEDCBA65, nosign_bits};

    u32 neq1_store[8];
    u32 neq2_store[8];
    mask256_storeu(neq1_store, mask256_neq(mask256_loadu(a1), mask256_loadu(b)));
    mask256_storeu(neq2_store, mask256_neq(mask256_loadu(a2), mask256_loadu(b)));

    const u32 expected_neq1[8] =
    {
        (a1[0] != b[0]) * 0xFFFFFFFF, (a1[1] != b[1]) * 0xFFFFFFFF,
        (a1[2] != b[2]) * 0xFFFFFFFF, (a1[3] != b[3]) * 0xFFFFFFFF,
        (a1[4] != b[4]) * 0xFFFFFFFF, (a1[5] != b[5]) * 0xFFFFFFFF,
        (a1[6] != b[6]) * 0xFFFFFFFF, (a1[7] != b[7]) * 0xFFFFFFFF
    };
    const u32 expected_neq2[8] =
    {
        (a2[0] != b[0]) * 0xFFFFFFFF, (a2[1] != b[1]) * 0xFFFFFFFF,
        (a2[2] != b[2]) * 0xFFFFFFFF, (a2[3] != b[3]) * 0xFFFFFFFF,
        (a2[4] != b[4]) * 0xFFFFFFFF, (a2[5] != b[5]) * 0xFFFFFFFF,
        (a2[6] != b[6]) * 0xFFFFFFFF, (a2[7] != b[7]) * 0xFFFFFFFF
    };

    bad_test_check(neq1_store[0] == expected_neq1[0] && neq1_store[1] == expected_neq1[1]
                && neq1_store[2] == expected_neq1[2] && neq1_store[3] == expected_neq1[3]
                && neq1_store[4] == expected_neq1[4] && neq1_store[5] == expected_neq1[5]
                && neq1_store[6] == expected_neq1[6] && neq1_store[7] == expected_neq1[7]
                && neq2_store[0] == expected_neq2[0] && neq2_store[1] == expected_neq2[1]
                && neq2_store[2] == expected_neq2[2] && neq2_store[3] == expected_neq2[3]
                && neq2_store[4] == expected_neq2[4] && neq2_store[5] == expected_neq2[5]
                && neq2_store[6] == expected_neq2[6] && neq2_store[7] == expected_neq2[7]);
}


void test_mask256_and()
{
    const u32 a1[8] = {all1_bits, nosign_bits, zero_bits, lowbit32_bits, denorm_bits, snan_bits, all1_bits, highbit32_bits};
    const u32 a2[8] = {0x00E00100, 0x7FFFFFFF, 0x12345678, 0xF9182765, 0x11111111, 0xAAAAAAAA, 0xA1B2C3D4, 0xFEDCBA65};
    const u32 b[8]  = {all1_bits, 0x12345678, all1_bits, denorm_bits, snan_bits, zero_bits, 0xFEDCBA65, nosign_bits};

    u32 and1_store[8];
    u32 and2_store[8];
    mask256_storeu(and1_store, mask256_and(mask256_loadu(a1), mask256_loadu(b)));
    mask256_storeu(and2_store, mask256_and(mask256_loadu(a2), mask256_loadu(b)));

    const u32 expected_and1[8] = {a1[0] & b[0], a1[1] & b[1], a1[2] & b[2], a1[3] & b[3],
                                  a1[4] & b[4], a1[5] & b[5], a1[6] & b[6], a1[7] & b[7]};
    const u32 expected_and2[8] = {a2[0] & b[0], a2[1] & b[1], a2[2] & b[2], a2[3] & b[3],
                                  a2[4] & b[4], a2[5] & b[5], a2[6] & b[6], a2[7] & b[7]};

    bad_test_check(and1_store[0] == expected_and1[0] && and1_store[1] == expected_and1[1]
                && and1_store[2] == expected_and1[2] && and1_store[3] == expected_and1[3]
                && and1_store[4] == expected_and1[4] && and1_store[5] == expected_and1[5]
                && and1_store[6] == expected_and1[6] && and1_store[7] == expected_and1[7]
                && and2_store[0] == expected_and2[0] && and2_store[1] == expected_and2[1]
                && and2_store[2] == expected_and2[2] && and2_store[3] == expected_and2[3]
                && and2_store[4] == expected_and2[4] && and2_store[5] == expected_and2[5]
                && and2_store[6] == expected_and2[6] && and2_store[7] == expected_and2[7]);
}


void test_mask256_and_not()
{
    const u32 a1[8] = {all1_bits, nosign_bits, zero_bits, lowbit32_bits, denorm_bits, snan_bits, all1_bits, highbit32_bits};
    const u32 a2[8] = {0x00E00100, 0x7FFFFFFF, 0x12345678, 0xF9182765, 0x11111111, 0xAAAAAAAA, 0xA1B2C3D4, 0xFEDCBA65};
    const u32 b[8]  = {all1_bits, 0x12345678, all1_bits, denorm_bits, snan_bits, zero_bits, 0xFEDCBA65, nosign_bits};

    u32 and_not1_store[8];
    u32 and_not2_store[8];
    mask256_storeu(and_not1_store, mask256_and_not(mask256_loadu(a1), mask256_loadu(b)));
    mask256_storeu(and_not2_store, mask256_and_not(mask256_loadu(a2), mask256_loadu(b)));

    const u32 expected_and_not1[8] = {a1[0] & ~b[0], a1[1] & ~b[1], a1[2] & ~b[2], a1[3] & ~b[3],
                                      a1[4] & ~b[4], a1[5] & ~b[5], a1[6] & ~b[6], a1[7] & ~b[7]};
    const u32 expected_and_not2[8] = {a2[0] & ~b[0], a2[1] & ~b[1], a2[2] & ~b[2], a2[3] & ~b[3],
                                      a2[4] & ~b[4], a2[5] & ~b[5], a2[6] & ~b[6], a2[7] & ~b[7]};

    bad_test_check(and_not1_store[0] == expected_and_not1[0] && and_not1_store[1] == expected_and_not1[1]
                && and_not1_store[2] == expected_and_not1[2] && and_not1_store[3] == expected_and_not1[3]
                && and_not1_store[4] == expected_and_not1[4] && and_not1_store[5] == expected_and_not1[5]
                && and_not1_store[6] == expected_and_not1[6] && and_not1_store[7] == expected_and_not1[7]
                && and_not2_store[0] == expected_and_not2[0] && and_not2_store[1] == expected_and_not2[1]
                && and_not2_store[2] == expected_and_not2[2] && and_not2_store[3] == expected_and_not2[3]
                && and_not2_store[4] == expected_and_not2[4] && and_not2_store[5] == expected_and_not2[5]
                && and_not2_store[6] == expected_and_not2[6] && and_not2_store[7] == expected_and_not2[7]);
}


void test_mask256_or()
{
    const u32 a1[8] = {all1_bits, nosign_bits, zero_bits, lowbit32_bits, denorm_bits, snan_bits, all1_bits, highbit32_bits};
    const u32 a2[8] = {0x00E00100, 0x7FFFFFFF, 0x12345678, 0xF9182765, 0x11111111, 0xAAAAAAAA, 0xA1B2C3D4, 0xFEDCBA65};
    const u32 b[8]  = {all1_bits, 0x12345678, all1_bits, denorm_bits, snan_bits, zero_bits, 0xFEDCBA65, nosign_bits};

    u32 or1_store[8];
    u32 or2_store[8];
    mask256_storeu(or1_store, mask256_or(mask256_loadu(a1), mask256_loadu(b)));
    mask256_storeu(or2_store, mask256_or(mask256_loadu(a2), mask256_loadu(b)));

    const u32 expected_or1[8] = {a1[0] | b[0], a1[1] | b[1], a1[2] | b[2], a1[3] | b[3],
                                 a1[4] | b[4], a1[5] | b[5], a1[6] | b[6], a1[7] | b[7]};
    const u32 expected_or2[8] = {a2[0] | b[0], a2[1] | b[1], a2[2] | b[2], a2[3] | b[3],
                                 a2[4] | b[4], a2[5] | b[5], a2[6] | b[6], a2[7] | b[7]};

    bad_test_check(or1_store[0] == expected_or1[0] && or1_store[1] == expected_or1[1]
                && or1_store[2] == expected_or1[2] && or1_store[3] == expected_or1[3]
                && or1_store[4] == expected_or1[4] && or1_store[5] == expected_or1[5]
                && or1_store[6] == expected_or1[6] && or1_store[7] == expected_or1[7]
                && or2_store[0] == expected_or2[0] && or2_store[1] == expected_or2[1]
                && or2_store[2] == expected_or2[2] && or2_store[3] == expected_or2[3]
                && or2_store[4] == expected_or2[4] && or2_store[5] == expected_or2[5]
                && or2_store[6] == expected_or2[6] && or2_store[7] == expected_or2[7]);
}


void test_mask256_xor()
{
    const u32 a1[8] = {all1_bits, nosign_bits, zero_bits, lowbit32_bits, denorm_bits, snan_bits, all1_bits, highbit32_bits};
    const u32 a2[8] = {0x00E00100, 0x7FFFFFFF, 0x12345678, 0xF9182765, 0x11111111, 0xAAAAAAAA, 0xA1B2C3D4, 0xFEDCBA65};
    const u32 b[8]  = {all1_bits, 0x12345678, all1_bits, denorm_bits, snan_bits, zero_bits, 0xFEDCBA65, nosign_bits};

    u32 xor1_store[8];
    u32 xor2_store[8];
    mask256_storeu(xor1_store, mask256_xor(mask256_loadu(a1), mask256_loadu(b)));
    mask256_storeu(xor2_store, mask256_xor(mask256_loadu(a2), mask256_loadu(b)));

    const u32 expected_xor1[8] = {a1[0] ^ b[0], a1[1] ^ b[1], a1[2] ^ b[2], a1[3] ^ b[3],
                                  a1[4] ^ b[4], a1[5] ^ b[5], a1[6] ^ b[6], a1[7] ^ b[7]};
    const u32 expected_xor2[8] = {a2[0] ^ b[0], a2[1] ^ b[1], a2[2] ^ b[2], a2[3] ^ b[3],
                                  a2[4] ^ b[4], a2[5] ^ b[5], a2[6] ^ b[6], a2[7] ^ b[7]};

    bad_test_check(xor1_store[0] == expected_xor1[0] && xor1_store[1] == expected_xor1[1]
                && xor1_store[2] == expected_xor1[2] && xor1_store[3] == expected_xor1[3]
                && xor1_store[4] == expected_xor1[4] && xor1_store[5] == expected_xor1[5]
                && xor1_store[6] == expected_xor1[6] && xor1_store[7] == expected_xor1[7]
                && xor2_store[0] == expected_xor2[0] && xor2_store[1] == expected_xor2[1]
                && xor2_store[2] == expected_xor2[2] && xor2_store[3] == expected_xor2[3]
                && xor2_store[4] == expected_xor2[4] && xor2_store[5] == expected_xor2[5]
                && xor2_store[6] == expected_xor2[6] && xor2_store[7] == expected_xor2[7]);
}


void test_mask256_not()
{
    const u32 a[8] = {all1_bits, nosign_bits, zero_bits, lowbit32_bits, denorm_bits, snan_bits, all1_bits, highbit32_bits};
    const u32 b[8] = {0x00E00100, 0x7FFFFFFF, 0x12345678, 0xF9182765, 0x11111111, 0xAAAAAAAA, 0xA1B2C3D4, 0xFEDCBA65};
    
    u32 not1_store[8];
    u32 not2_store[8];
    mask256_storeu(not1_store, mask256_not(mask256_loadu(a)));
    mask256_storeu(not2_store, mask256_not(mask256_loadu(b)));

    const u32 expected_not1[8] = {~a[0], ~a[1], ~a[2], ~a[3], ~a[4], ~a[5], ~a[6], ~a[7]};
    const u32 expected_not2[8] = {~b[0], ~b[1], ~b[2], ~b[3], ~b[4], ~b[5], ~b[6], ~b[7]};

    bad_test_check(not1_store[0] == expected_not1[0] && not1_store[1] == expected_not1[1]
                && not1_store[2] == expected_not1[2] && not1_store[3] == expected_not1[3]
                && not1_store[4] == expected_not1[4] && not1_store[5] == expected_not1[5]
                && not1_store[6] == expected_not1[6] && not1_store[7] == expected_not1[7]
                && not2_store[0] == expected_not2[0] && not2_store[1] == expected_not2[1]
                && not2_store[2] == expected_not2[2] && not2_store[3] == expected_not2[3]
                && not2_store[4] == expected_not2[4] && not2_store[5] == expected_not2[5]
                && not2_store[6] == expected_not2[6] && not2_store[7] == expected_not2[7]);
}

BAD_NAMESPACE_END