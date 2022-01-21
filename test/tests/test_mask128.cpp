#include "test_mask128.h"
#include "../test.h"

#include <bad/common/mask128.h>
#include <bad/qualifiers.h>

BAD_NAMESPACE_START

void test_mask128_load_store()
{
// With SSE, mask128_load/mask128_store is the same as _mm_load_ps/_mm_store_ps,
// which are already tested in test_f32x4.cpp
#if defined(__SSE2__)
    bad_align(16) const u32 a[4] = {0xFFFFFFFF, 0x7FFFFFFF, 0x00000000, 0x00000001};
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
    const u32 a[4] = {0xFFFFFFFF, 0x7FFFFFFF, 0x00000000, 0x00000001};
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


void test_mask128_all1()
{
    u32 all1_out[4];

    mask128_storeu(all1_out, mask128_all1());

#if defined(__SSE2__)
    const u32 expected_all1 = 0xFFFFFFFF;
#else
    const u32 all1_bits     = 0xFFFFFFFF;
    const f32 expected_all1 = *(f32*)&all1_bits;
#endif

    bad_test_check(all1_out[0] == expected_all1
                && all1_out[1] == expected_all1
                && all1_out[2] == expected_all1
                && all1_out[3] == expected_all1);
}


void test_mask128_value32()
{
    mask_elem value32_out[4];

    mask128_storeu(value32_out, mask128_value32());

#if defined(__SSE2__)
    const u32 expected_value32 = 0x7FFFFFFF;
#else
    const u32 value32_bits     = 0x7FFFFFFF;
    const f32 expected_value32 = *(f32*)&value32_bits;
#endif

    bad_test_check(value32_out[0] == expected_value32
                && value32_out[1] == expected_value32
                && value32_out[2] == expected_value32
                && value32_out[3] == expected_value32);
}


void test_mask128_highbit32()
{
    mask_elem highbit32_out[4];

    mask128_storeu(highbit32_out, mask128_highbit32());

#if defined(__SSE2__)
    const u32 expected_highbit32 = 0x80000000;
#else
    const u32 highbit32_bits     = 0x80000000;
    const f32 expected_highbit32 = *(f32*)&highbit32_bits;
#endif

    bad_test_check(highbit32_out[0] == expected_highbit32
                && highbit32_out[1] == expected_highbit32
                && highbit32_out[2] == expected_highbit32
                && highbit32_out[3] == expected_highbit32);
}


void test_mask128_lowbit32()
{
    mask_elem lowbit32_out[4];

    mask128_storeu(lowbit32_out, mask128_lowbit32());

#if defined(__SSE2__)
    const u32 expected_lowbit32 = 0x00000001;
#else
    const u32 lowbit32_bits     = 0x00000001;
    const f32 expected_lowbit32 = *(f32*)&lowbit32_bits;
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

#if defined(__SSE2__)
    const u32 expected_exponent32 = 0x7F800000;
#else
    const u32 exponent32_bits     = 0x7F800000;
    const f32 expected_exponent32 = *(f32*)&exponent32_bits;
#endif

    bad_test_check(exponent32_out[0] == expected_exponent32
                && exponent32_out[1] == expected_exponent32
                && exponent32_out[2] == expected_exponent32
                && exponent32_out[3] == expected_exponent32);
}

BAD_NAMESPACE_END