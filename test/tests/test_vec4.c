#include "test_vec4.h" 
#include "../test.h"
#include "../test_values.h"

#include <bad/common/f32x4.h>
#include <bad/math/vec4.h>

BAD_NAMESPACE_START

void test_vec4_dot()
{
    vec4 a0 = f32x4_set(  snan(), .0f,  1.f, -2.f);
    vec4 a1 = f32x4_set(   inf(), .0f,  1.f, -2.f);
    vec4 a2 = f32x4_set(  ninf(), .0f,  1.f, -2.f);
    vec4 a3 = f32x4_set(denorm(), .0f,  1.f, -2.f);
    vec4 b  = f32x4_set(    10.f, 5.f,  2.f,  1.f);

    f32 dot0_store = vec4_dot(a0, b);
    f32 dot1_store = vec4_dot(a1, b);
    f32 dot2_store = vec4_dot(a2, b);
    f32 dot3_store = vec4_dot(a3, b);

    bad_test_check(is_qnan(dot0_store)
                && dot1_store == inf()
                && dot2_store == ninf()
                && dot3_store == denorm() * 10.f);
}


void test_vec4_length_squared()
{
    vec4 a0 = f32x4_set(  snan(), .0f,  1.f, -2.f);
    vec4 a1 = f32x4_set(   inf(), .0f,  1.f, -2.f);
    vec4 a2 = f32x4_set(  ninf(), .0f,  1.f, -2.f);
    vec4 a3 = f32x4_set(denorm(), .0f,  1.f, -2.f);
    vec4 a4 = f32x4_set(    10.f, 5.f,  2.f,  1.f);

    f32 length_squared0_store = vec4_length_squared(a0);
    f32 length_squared1_store = vec4_length_squared(a1);
    f32 length_squared2_store = vec4_length_squared(a2);
    f32 length_squared3_store = vec4_length_squared(a3);
    f32 length_squared4_store = vec4_length_squared(a4);

    bad_test_check(is_qnan(length_squared0_store)
                && length_squared1_store == inf()
                && length_squared2_store == inf()
                && length_squared3_store == 5.f
                && length_squared4_store == 130.f);
}


void test_vec4_length()
{
    vec4 a0 = f32x4_set(  snan(), .0f,  1.f, -2.f);
    vec4 a1 = f32x4_set(   inf(), .0f,  1.f, -2.f);
    vec4 a2 = f32x4_set(  ninf(), .0f,  1.f, -2.f);
    vec4 a3 = f32x4_set(denorm(), .0f,  1.f, -2.f);
    vec4 a4 = f32x4_set(    10.f, 5.f,  2.f,  1.f);

    f32 length0_store = vec4_length(a0);
    f32 length1_store = vec4_length(a1);
    f32 length2_store = vec4_length(a2);
    f32 length3_store = vec4_length(a3);
    f32 length4_store = vec4_length(a4);

    bad_test_check(is_qnan(length0_store)
                && length1_store == inf()
                && length2_store == inf()
                && length3_store == 2.2360680103302001953125f
                && length4_store == 11.4017543792724609375f);
}


void test_vec4_lerp()
{
    vec4 a0 = f32x4_set(  snan(), .0f,  1.f, -2.f);
    vec4 a1 = f32x4_set(   inf(), .0f,  1.f, -2.f);
    vec4 a2 = f32x4_set(  ninf(), .0f,  1.f, -2.f);
    vec4 a3 = f32x4_set(denorm(), .0f,  1.f, -2.f);
    vec4 c  = f32x4_set(    10.f, 5.f, -2.f,  1.f);

    f32 lerp0_store[4];
    f32 lerp1_store[4];
    f32 lerp2_store[4];
    f32 lerp3_store[4];
    f32 lerp4_store[4];

    f32x4_store(lerp0_store, vec4_lerp(a0, c, .5f));
    f32x4_store(lerp1_store, vec4_lerp(a1, c, 1.f));
    f32x4_store(lerp2_store, vec4_lerp(a2, c, .5f));
    f32x4_store(lerp3_store, vec4_lerp(a3, c, .5f));
    f32x4_store(lerp4_store, vec4_lerp(a3, c, 1.f));

    bad_test_check(is_qnan(lerp0_store[0])                  && lerp0_store[1] == 2.5f
                && lerp0_store[2] == -.5f                   && lerp0_store[3] == -.5f
                && is_qnan(lerp1_store[0])                  && lerp1_store[1] == 5.f 
                && lerp1_store[2] == -2.f                   && lerp1_store[3] == 1.f
                && lerp2_store[0] == ninf()                 && lerp2_store[1] == 2.5f
                && lerp2_store[2] == -.5f                   && lerp2_store[3] == -.5f
                && lerp3_store[0] == (denorm() * .5f + 5.f) && lerp3_store[1] == 2.5f
                && lerp3_store[2] == -.5f                   && lerp3_store[3] == -.5f
                && lerp4_store[0] == 10.f                   && lerp4_store[1] == 5.f
                && lerp4_store[2] == -2.f                   && lerp4_store[3] == 1.f);
}

BAD_NAMESPACE_END