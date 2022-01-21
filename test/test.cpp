#include "test.h"
#include <bad/common/f32x4.h>

BAD_NAMESPACE_START

s32 test_results[2] = {0, 0};

void test_report()
{
    fprintf(stderr, "\n\nSum-up: %i passed, %i failed", test_results[1], test_results[0]);
    test_results[0] = 0;
    test_results[1] = 0;
}


f32 random_f32(const s32 min, const f32 range)
{
    return min + (rand() / (f32)RAND_MAX) * range;
}


void randomize_f32_array(f32* array, const s32 n, const f32 min, const f32 max)
{
    srand(__rdtsc());
    
    const f32 range = max - min;
    
    for (s32 i = 0; i < n; i++)
    {
        array[i] = min + (rand() / (f32)RAND_MAX) * range;
    }
}

void randomize_f32x4_array(f32x4* array, const s32 n, const f32 min, const f32 max)
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


void reset_f32_array(f32* array, const s32 n)
{
    for (s32 i = 0; i < n; i++)
    {
        array[i] = .0f;
    }
}

bool is_nan(const f32 a)
{
    return a != a;
/*
    const u32 bits = *(u32*)&a;

    return ((bits & 0x7F800000) == 0x7F800000)
        && ((bits & 0x007FFFFF) != 0);
*/
}

bool is_qnan(const f32 a)
{
    const u32 bits = *(u32*)&a;

    return is_nan(a) && (bits & 0x80000000);
}


bool is_snan(const f32 a)
{
    const u32 bits = *(u32*)&a;

    return is_nan(a) && (bits & 0x80000000) == 0;
}


u8 biased_exponent(const f32 a)
{
    const u32 bits = *(u32*)&a;

    return (u8)((bits & 0x7F800000) >> 23);
}

s8 unbiased_exponent(const f32 a)
{
    return (s8)(biased_exponent(a) - 127u);
}


f32 abs(const f32 a)
{
    const u32 bits     = *(u32*)&a;
    const u32 abs_bits = bits & 0x7FFFFFFF;

    return *(f32*)&abs_bits;
}


f32 ulp(const f32 a)
{
    // 32-bits floating point machine epsilon (0x34000000)
    f32       res    = 1.1920928955078125e-7f;
    s8        expo_a = unbiased_exponent(a);
    const f32 mul    = expo_a & 0x80 ? .5f : 2.f;

    // abs
    expo_a &= 0x7F;

    for (s8 i = 0; i < expo_a; i++)
    {
        res *= mul;
    }

    return res;
}


bool are_equal_ulp(const f32 a, const f32 b)
{
    // 2 ^ exp * e
    const f32 a_ulp   = ulp(a);
    const f32 b_ulp   = ulp(b);
    const f32 max_ulp = (a_ulp > b_ulp) ? a_ulp : b_ulp;

    return abs(a - b) <= max_ulp;
}

BAD_NAMESPACE_END