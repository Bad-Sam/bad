#ifndef BAD_TEST_H
#define BAD_TEST_H

#include <bad/bad.h>
#include <bad/types/scalar_types.h>

BAD_NAMESPACE_START

extern s32 test_results[2];

// Test framework
#define bad_test_check(cond) test_check(cond, __FUNCTION__, sizeof(__FUNCTION__) - 1u)

void test_check(u32 cond, const char* func_name, u32 func_name_size);
void test_report();

u32  is_nan(f32 a);
u32  is_qnan(f32 a);
u32  is_snan(f32 a);
u8   unbiased_exponent(f32 a);
s8   exponent(f32 a);
f32  ulp(f32 a);
u32  are_equal_ulp(f32 a, f32 b);
u32  are_equal_n_ulp(f32 a, f32 b, f32 ulp_delta);

BAD_NAMESPACE_END

#endif
