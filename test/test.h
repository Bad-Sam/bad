#ifndef BAD_TEST_H
#define BAD_TEST_H

#include <bad/bad.h>
#include <bad/types.h>
#include <bad/detect/os.h>
#include <bad/qualifiers.h>
#include <bad/args.h>

#include <stdio.h>

#if defined(BAD_LINUX)
#   include <time.h>
#else
#   include <Windows.h>
#endif

BAD_NAMESPACE_START

extern s32 test_results[2];

// Test framework
#if defined(BAD_WINDOWS)
#   define bad_test_check(cond)                                                            \
    do                                                                                     \
    {                                                                                      \
        bool test_res = (cond);                                                            \
        test_results[(s32)test_res]++;                                                     \
        HANDLE err = GetStdHandle(STD_ERROR_HANDLE);                                       \
        WriteFile(err, "\n[", 2, NULL, NULL);                                              \
        if (test_res)                                                                      \
        {                                                                                  \
            SetConsoleTextAttribute(err, FOREGROUND_GREEN);                                \
            WriteFile(err, "Passed", 6, NULL, NULL);                                       \
        }                                                                                  \
        else                                                                               \
        {                                                                                  \
            SetConsoleTextAttribute(err, FOREGROUND_RED);                                  \
            WriteFile(err, "Failed", 6, NULL, NULL);                                       \
        }                                                                                  \
        SetConsoleTextAttribute(err, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); \
        WriteFile(err, "] ", 2, NULL, NULL);                                               \
        WriteFile(err, __FUNCTION__, sizeof(__FUNCTION__) - 1, NULL, NULL);                \
    } while (0)
#else
#   define BAD_PASSED "\033[1m\033[32mPassed\033[0m\033[0m"
#   define BAD_FAILED "\033[1m\033[31mFailed\033[0m\033[0m"
#   define bad_test_check(cond)                                                         \
    do                                                                                  \
    {                                                                                   \
        bool test_res = (cond);                                                         \
        test_results[(s32)test_res]++;                                                  \
        fprintf(stderr, "\n[%s] %s", test_res ? BAD_PASSED : BAD_FAILED, __FUNCTION__); \
    } while (0)
#endif

void test_report();


// Tools
#define print_f32x4(__v)                                                                \
do                                                                                    \
{                                                                                     \
    f32 __c[4];                                                                       \
    f32x4_storeu(__c, (__v));                                                         \
    fprintf(stderr, "\n%s = [%f, %f, %f, %f]", #__v, __c[0], __c[1], __c[2], __c[3]); \
} while(0)

#define print_mask128(__v)                                                            \
do                                                                                    \
{                                                                                     \
    mask_elem __c[4];                                                                 \
    mask128_storeu(__c, (__v));                                                       \
    fprintf(stderr, "\n%s = [%X, %X, %X, %X]", #__v, __c[0], __c[1], __c[2], __c[3]); \
} while(0)

f32  random_f32(const s32 min, const f32 range);
void randomize_f32_array(f32* array, const s32 n, const f32 min, const f32 max);
void randomize_f32x4_array(f32x4* array, const s32 n, const f32 min, const f32 max);
void reset_f32_array(f32* array, const s32 n);
bool is_nan(const f32 a);
bool is_qnan(const f32 a);
bool is_snan(const f32 a);
u8   biased_exponent(const f32 a);
s8   unbiased_exponent(const f32 a);
s8   sign(const s8 a);
f32  abs(const f32 a);
f32  ulp(const f32 a);
bool are_equal_ulp(const f32 a, const f32 b);

BAD_NAMESPACE_END

#endif