#include "test_vec3.h"

#include "../test.h"
#include "../test_values.h"
#include <bad/math/vec3.h>

BAD_NAMESPACE_START

void test_vec3_cross()
{
    vec3 a = vec3_set(snan(), inf(), ninf());
    vec3 b = vec3_set(  1.f,  .0f,   .0f);
    vec3 c = vec3_set( 10.f,  .0f,   .0f);
    vec3 d = vec3_set(  .0f,  1.f,   .0f);

    f32 cross0[3];
    f32 cross1[3];
    f32 cross2[3];
    vec3_store(cross0, vec3_cross(b, a));
    vec3_store(cross1, vec3_cross(b, c));
    vec3_store(cross2, vec3_cross(b, d)); 

    f32 expected_cross1[3] = {.0f, .0f, .0f};
    f32 expected_cross2[3] = {.0f, .0f, 1.f};

    bad_test_check(is_qnan(cross0[0]) && is_qnan(cross0[1]) && is_qnan(cross0[2])
                && cross1[0] == expected_cross1[0]
                && cross1[1] == expected_cross1[1]
                && cross1[2] == expected_cross1[2]
                && cross2[0] == expected_cross2[0]
                && cross2[1] == expected_cross2[1]
                && cross2[2] == expected_cross2[2]);
}

BAD_NAMESPACE_END