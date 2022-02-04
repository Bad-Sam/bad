#include "test_vec4.h" 
#include "../test.h"
#include "../test_values.h"

#include <bad/types.h>
#include <bad/qualifiers.h>
#include <bad/math/vec4.h>

BAD_NAMESPACE_START

void test_vec4_dot()
{
    const vec4 a0 = f32x4_set(snanf,   .0f,  1.f, -2.f);
    const vec4 a1 = f32x4_set(inff,    .0f,  1.f, -2.f);
    const vec4 a2 = f32x4_set(-inff,   .0f,  1.f, -2.f);
    const vec4 a3 = f32x4_set(denormf, .0f,  1.f, -2.f);
    const vec4 b  = f32x4_set(10.f,    5.f,  2.f,  1.f);

    const f32 dot0_store = vec4_dot(a0, b);
    const f32 dot1_store = vec4_dot(a1, b);
    const f32 dot2_store = vec4_dot(a2, b);
    const f32 dot3_store = vec4_dot(a3, b);

    bad_test_check(is_snan(dot0_store)
                && dot1_store == inff
                && dot2_store == -inff
                && dot3_store == denormf * 10.f);
}

BAD_NAMESPACE_END