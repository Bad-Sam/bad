#include "test.h"
#include "test_values.h"

#include <bad/common/f32x4.h>

#include <stdio.h>

BAD_NAMESPACE_START

s32 test_results[2] = {0, 0};

void test_check(u32 cond, const char* func_name, u32 func_name_size)
{
    test_results[cond]++;
    
    static const char* test_result_texts[2] = {"Failed", "Passed"};

#if defined(_MSC_VER)
    static const u16 test_colors[2] = {FOREGROUND_RED, FOREGROUND_GREEN};

    _write(2, "\n[", 2u);
    
    HANDLE stderr_handle = (HANDLE)_get_osfhandle(2);
    SetConsoleTextAttribute(stderr_handle, test_colors[cond]);
    _write(2, test_result_texts[cond], 6u);
    SetConsoleTextAttribute(stderr_handle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

    _write(2, "] ", 2u);
    _write(2, func_name, func_name_size);
#else
    static const char* test_result_texts[2] =
    {
        "\n[\033[1m\033[31mFailed\033[0m\033[0m]",
        "\n[\033[1m\033[32mPassed\033[0m\033[0m]"
    };

    write(2, test_result_texts[cond], 26u);
    write(2, func_name, func_name_size);
#endif
}


void test_report()
{
    fprintf(stderr, "\n\nSum-up: %i passed, %i failed", test_results[1], test_results[0]);

    test_results[0] = 0;
    test_results[1] = 0;
}


u32 is_nan(f32 a)
{
    return a != a;
}


u32 is_qnan(f32 a)
{
    u32 bits = *(u32*)&a;

    return is_nan(a) && (bits & 0x00400000);
}


u32 is_snan(f32 a)
{
    u32 bits = *(u32*)&a;

    return is_nan(a) && (bits & 0x00400000) == 0;
}


u8 unbiased_exponent(f32 a)
{
    u32 bits = *(u32*)&a;

    return (u8)((bits & 0x7F800000) >> 23);
}

s8 exponent(f32 a)
{
    return (s8)(unbiased_exponent(a) - 127u);
}


f32 absf(f32 a)
{
    u32 bits     = *(u32*)&a;
    u32 abs_bits = bits & 0x7FFFFFFF;

    return *(f32*)&abs_bits;
}


f32 ulp(f32 a)
{
    // 32-bits floating point epsilon (0x34000000)
    f32 res      = 1.1920928955078125e-7f;
    f32 mul      = 2.f;
    s8  expo_a   = exponent(a);
    s8  a_is_neg = expo_a & 0x80;

    if (a_is_neg)
    {
        mul    = .5f;
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
