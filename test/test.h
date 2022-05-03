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
#define print_f32x4(__v)                                                              \
do                                                                                    \
{                                                                                     \
    f32 __c[4];                                                                       \
    f32x4_storeu(__c, (__v));                                                         \
    fprintf(stderr, "\n%s = [%.20f, %.20f, %.20f, %.20f]", #__v, __c[0], __c[1], __c[2], __c[3]); \
} while(0)

#define print_f32x8(__v)                                                     \
do                                                                           \
{                                                                            \
    f32 __c[8];                                                              \
    f32x8_storeu(__c, (__v));                                                \
    fprintf(stderr, "\n%s = [%f, %f, %f, %f, %f, %f, %f, %f]", #__v,         \
            __c[0], __c[1], __c[2], __c[3], __c[4], __c[5], __c[6], __c[7]); \
} while(0)

#define print_mask128(__v)                                                            \
do                                                                                    \
{                                                                                     \
    mask_elem __c[4];                                                                 \
    mask128_storeu(__c, (__v));                                                       \
    fprintf(stderr, "\n%s = [%X, %X, %X, %X]", #__v, __c[0], __c[1], __c[2], __c[3]); \
} while(0)

#define print_mask256(__v)                                                   \
do                                                                           \
{                                                                            \
    u32 __c[8];                                                              \
    mask256_storeu(__c, (__v));                                              \
    fprintf(stderr, "\n%s = [%X, %X, %X, %X, %X, %X, %X, %X]", #__v,         \
            __c[0], __c[1], __c[2], __c[3], __c[4], __c[5], __c[6], __c[7]); \
} while(0)

#define test_debug(cond)                                                      \
do                                                                            \
{                                                                             \
    bool __cond_res = (cond);                                                 \
    fprintf(stderr, "\n%s returns %s", #cond, __cond_res ? "true" : "false"); \
} while(0)

f32  random_f32(f32 min, f32 range);
void randomize_f32_array(f32* array, s32 n, f32 min, f32 max);
void randomize_f32x4_array(f32x4* array, s32 n, f32 min, f32 max);
void reset_f32_array(f32* array, s32 n);
bool is_nan(f32 a);
bool is_qnan(f32 a);
bool is_snan(f32 a);
u8   unbiased_exponent(f32 a);
s8   exponent(f32 a);
s8   sign(s8 a);
f32  abs(f32 a);
f32  ulp(f32 a);
bool are_equal_ulp(f32 a, f32 b);
bool are_equal_n_ulp(f32 a, f32 b, f32 ulp_delta);

BAD_NAMESPACE_END

#endif