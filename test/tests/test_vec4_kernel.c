#include "test_vec4_kernel.h" 

#include "../test.h"
#include "../test_values.h"

#include <bad/math/vec4_kernel.h>

BAD_NAMESPACE_START

void test_vec4_ker_dot()
{
    bad_align(16) f32 a[4 * 3] =
    {
        snan(),   .0f,  1.f, -2.f,
         inf(),   .0f,  1.f, -2.f,
         -10.f,   1.f, -2.f,  .0f, 
    };

    bad_align(16) f32 b[4 * 3] =
    {
        ninf(), .0f,  1.f, -2.f,
        denorm(), .0f,  1.f, -2.f,
            10.f, 5.f,  2.f,  1.f
    };

    bad_align(16) f32 dot[3];
    vec4_ker_dot(dot, a, b, 3);

    bad_test_check(is_qnan(dot[0])
                && dot[1] == (inf() * denorm() - 3.f)
                && dot[2] == -99.f);
}


void test_vec4_ker_length_squared()
{
    bad_align(16) f32 a[4 * 5] =
    {
          snan(), .0f,  1.f, -2.f,
           inf(), .0f,  1.f, -2.f,
          ninf(), .0f,  1.f, -2.f,
        denorm(), .0f,  1.f, -2.f,
            10.f, 5.f,  2.f,  1.f
    };

    bad_align(16) f32 len_sqr[5];
    vec4_ker_length_squared(len_sqr, a, 5);

    bad_test_check(is_qnan(len_sqr[0])
                && len_sqr[1] == inf()
                && len_sqr[2] == inf()
                && len_sqr[3] == denorm() * denorm() + 5.f
                && len_sqr[4] == 130.f);
}


void test_vec4_ker_length()
{
    bad_align(16) f32 a[4 * 5] =
    {
        snan(),   .0f,  1.f, -2.f,
        inf(),    .0f,  1.f, -2.f,
        ninf(),   .0f,  1.f, -2.f,
        denorm(), .0f,  1.f, -2.f,
        10.f,    5.f,  2.f,  1.f
    };

    bad_align(16) f32 len[5];
    vec4_ker_length(len, a, 5);

    bad_test_check(is_qnan(len[0])
                && len[1] == inf()
                && len[2] == inf()
                && len[3] == 2.23606797749978969641f
                && len[4] == 11.40175425099137979136f);
}


void test_vec4_ker_lerp()
{

}

BAD_NAMESPACE_END