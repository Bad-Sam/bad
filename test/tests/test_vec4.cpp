#include "test_vec4.h" 
#include "../test.h"
#include "../f32_values.h"

#include <bad/types.h>
#include <bad/qualifiers.h>
#include <bad/math/vec4.h>

BAD_NAMESPACE_START

void test_vec4_dot()
{
    const vec4 a0 = f32x4_set(snan,   .0f,  1.f, -2.f);
    const vec4 a1 = f32x4_set(inf,    .0f,  1.f, -2.f);
    const vec4 a2 = f32x4_set(-inf,   .0f,  1.f, -2.f);
    const vec4 a3 = f32x4_set(denorm, .0f,  1.f, -2.f);
    const vec4 b  = f32x4_set(10.f,   5.f,  2.f,  1.f);

    // const f32 expected_dot0 = qnan;
    const f32 expected_dot1 = inf;
    const f32 expected_dot2 = -inf;
    const f32 expected_dot3 = denorm * 10.f;

    const f32 dot0_store = vec4_dot(a0, b);
    const f32 dot1_store = vec4_dot(a1, b);
    const f32 dot2_store = vec4_dot(a2, b);
    const f32 dot3_store = vec4_dot(a3, b);

    bad_test_check(is_snan(dot0_store)
                && dot1_store == expected_dot1
                && dot2_store == expected_dot2
                && dot3_store == expected_dot3);
}

BAD_NAMESPACE_END