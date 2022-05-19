#include "test.h"
#include "test_values.h"

#include <bad/common/f32x4.h>

BAD_NAMESPACE_START

s32 test_results[2] = {0, 0};

void test_report()
{
    fprintf(stderr, "\n\nSum-up: %i passed, %i failed", test_results[1], test_results[0]);
    test_results[0] = 0;
    test_results[1] = 0;
}


f32 random_f32(f32 min, f32 range)
{
    return min + (rand() / (f32)RAND_MAX) * range;
}


void randomize_f32_array(f32* array, s32 n, f32 min, f32 max)
{
    srand(__rdtsc());
    
    const f32 range = max - min;
    
    for (s32 i = 0; i < n; i++)
    {
        array[i] = min + (rand() / (f32)RAND_MAX) * range;
    }
}


void randomize_f32x4_array(f32x4* array, s32 n, f32 min, f32 max)
{
    srand(__rdtsc());

    const f32 range = max - min;
    
    for (s32 i = 0; i < n; i++)
    {
        bad_align(16) const f32 values[4] =
        {
            random_f32(min, range),
            random_f32(min, range),
            random_f32(min, range),
            random_f32(min, range)
        };

        array[i] = f32x4_load(values);
    }
}


void reset_f32_array(f32* array, s32 n)
{
    for (s32 i = 0; i < n; i++)
    {
        array[i] = .0f;
    }
}


u32 is_nan(f32 a)
{
    return a != a;
}


u32 is_qnan(f32 a)
{
    const u32 bits = *(u32*)&a;

    return is_nan(a) && (bits & 0x00400000);
}


u32 is_snan(f32 a)
{
    const u32 bits = *(u32*)&a;

    return is_nan(a) && (bits & 0x00400000) == 0;
}


u8 unbiased_exponent(f32 a)
{
    const u32 bits = *(u32*)&a;

    return (u8)((bits & 0x7F800000) >> 23);
}

s8 exponent(f32 a)
{
    return (s8)(unbiased_exponent(a) - 127u);
}


f32 absf(f32 a)
{
    const u32 bits     = *(u32*)&a;
    const u32 abs_bits = bits & 0x7FFFFFFF;

    return *(f32*)&abs_bits;
}


f32 ulp(f32 a)
{
    // 32-bits floating point machine epsilon (0x34000000)
    f32       res      = 1.1920928955078125e-7f;
    f32       mul      = 2.f;
    s8        expo_a   = exponent(a);
    const s8  a_is_neg = expo_a & 0x80;

    if (a_is_neg)
    {
        mul = .5f;
        expo_a = -expo_a;
    }

    for (s8 i = 0; i < expo_a; i++)
    {
        res *= mul;
    }

    return res;
}


u32 are_equal_ulp(f32 a, f32 b)
{
    const f32 a_ulp   = ulp(a);
    const f32 b_ulp   = ulp(b);
    const f32 max_ulp = (a_ulp > b_ulp) ? a_ulp : b_ulp;

    return absf(a - b) <= max_ulp;
}


u32 are_equal_n_ulp(f32 a, f32 b, f32 ulp_delta)
{
    f32 a_ulp   = ulp(a);
    f32 b_ulp   = ulp(b);
    f32 max_ulp = (a_ulp > b_ulp) ? a_ulp : b_ulp;

    return absf(a - b) <= max_ulp * ulp_delta;
}


BAD_NAMESPACE_END