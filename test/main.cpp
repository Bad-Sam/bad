#include "test.h"

#include "tests/test_mask128.h"
#include "tests/test_f32x4.h"
#include "tests/test_f32x4_calc.h"

#include <bad/common/f32x4.h>

#if defined(__cplusplus)
using namespace bad;
#endif

int main()
{
    // mask128
    test_mask128_load_store();
    test_mask128_loadu_storeu();
    test_mask128_all1();
    test_mask128_value32();
    test_mask128_highbit32();
    test_mask128_lowbit32();
    test_mask128_exponent32();

    // f32x4
    test_f32x4_one();
    test_f32x4_load_store();
    test_f32x4_loadu_storeu();
    test_f32x4_blend();
    
    test_f32x4_hadd();
    test_f32x4_abs();
    test_f32x4_neg();
    test_f32x4_mod();
    test_f32x4_trunc();
    test_f32x4_round();
    test_f32x4_floor();
    test_f32x4_ceil();
    test_f32x4_clamp();
    test_f32x4_mul_add();
    test_f32x4_mul_sub();
    test_f32x4_nmul_add();
    test_f32x4_nmul_sub();
    test_f32x4_is_nan();
    test_f32x4_is_infinite();
    test_f32x4_is_finite();

    test_report();

    return 0;
}