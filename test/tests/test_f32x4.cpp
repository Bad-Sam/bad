#include "test_f32x4.h" 
#include "../test.h"
#include "../f32_values.h"

#include <bad/types.h>
#include <bad/qualifiers.h>
#include <bad/common/f32x4.h>


BAD_NAMESPACE_START

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
    bad_align(16) const f32 a[4] = {qnan, inf, -inf, denorm};
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
    const f32 a[4] = {qnan, inf, -inf, denorm};
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


void test_f32x4_blend()
{
    const f32x4 a = f32x4_set(snan, qnan, -inf, denorm);
    const f32x4 b = f32x4_set(.0f, -.0f, 10.6f, -9595.608f);

#if defined(__SSE2__)
    const mask128 mask = mask128_set(0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000);
#else
    const mask128 mask = mask128_set(all1, all1, all1, .0f);
#endif
    const f32 expected_blend1[4] = {snan, qnan, -inf, -9595.608f};
    const f32 expected_blend2[4] = {.0f, -.0f, 10.6f, denorm};

    f32 blend1_store[4];
    f32 blend2_store[4];
    f32x4_storeu(blend1_store, f32x4_blend(a, b, mask));
    f32x4_storeu(blend2_store, f32x4_blend(b, a, mask));

    bad_test_check(is_snan(blend1_store[0])
                && is_qnan(blend1_store[1])
                && blend1_store[2] == expected_blend1[2]
                && blend1_store[3] == expected_blend1[3]
                && blend2_store[0] == expected_blend2[0]
                && blend2_store[1] == expected_blend2[1]
                && blend2_store[2] == expected_blend2[2]
                && blend2_store[3] == expected_blend2[3]);
}

BAD_NAMESPACE_END