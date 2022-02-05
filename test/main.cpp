#include "test.h"
#include "tests/test_mask128.h"
#include "tests/test_mask256.h"
#include "tests/test_f32x4.h"
#include "tests/test_f32x8.h"
#include "tests/test_f32x4_calc.h"
#include "tests/test_f32x8_calc.h"


#if defined(__cplusplus)
using namespace bad;
#endif

int main()
{
    fprintf(stderr, "========== mask128.h ==========");
    test_mask128_load_store();
    test_mask128_loadu_storeu();
    test_mask128_set();
    test_mask128_set1();
    test_mask128_zero();
    test_mask128_all1();
    test_mask128_value32();
    test_mask128_highbit32();
    test_mask128_lowbit32();
    test_mask128_exponent32();
    test_mask128_eq();
    test_mask128_neq();
    test_mask128_and();
    test_mask128_and_not();
    test_mask128_or();
    test_mask128_xor();
    test_mask128_not();

    fprintf(stderr, "\n\n========== mask256.h ==========");
    test_mask256_load_store();
    test_mask256_loadu_storeu();
    test_mask256_set();
    test_mask256_set1();
    test_mask256_zero();
    test_mask256_all1();
    test_mask256_value32();
    test_mask256_highbit32();
    test_mask256_lowbit32();
    test_mask256_exponent32();
    test_mask256_eq();
    test_mask256_neq();
    test_mask256_and();
    test_mask256_and_not();
    test_mask256_or();
    test_mask256_xor();
    test_mask256_not();

    fprintf(stderr, "\n\n========== f32x4.h ==========");
    test_f32x4_zero();
    test_f32x4_one();
    test_f32x4_load_store();
    test_f32x4_loadu_storeu();
    test_f32x4_set();
    test_f32x4_set1();
    test_f32x4_blend();
    test_f32x4_cast_mask128();

    fprintf(stderr, "\n\n========== f32x8.h ==========");
    test_f32x8_zero();
    test_f32x8_one();
    test_f32x8_load_store();
    test_f32x8_loadu_storeu();
    test_f32x8_set();
    test_f32x8_set1();
    test_f32x8_blend();
    test_f32x8_cast_mask256();
    
    fprintf(stderr, "\n\n========== f32x4_calc.h ==========");
    test_f32x4_hadd();
    test_f32x4_abs();
    test_f32x4_sign();
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
    test_f32x4_neq();
    test_f32x4_eq();
    test_f32x4_ge();
    test_f32x4_gt();
    test_f32x4_le();
    test_f32x4_lt();
    test_f32x4_is_nan();
    test_f32x4_is_infinite();
    test_f32x4_is_finite();

    fprintf(stderr, "\n\n========== f32x8_calc.h ==========");
    test_f32x8_hadd();
    test_f32x8_abs();
    test_f32x8_sign();
    test_f32x8_neg();
    test_f32x8_mod();
    test_f32x8_trunc();
    test_f32x8_round();
    test_f32x8_floor();
    test_f32x8_ceil();
    test_f32x8_clamp();
    test_f32x8_mul_add();
    test_f32x8_mul_sub();
    test_f32x8_nmul_add();
    test_f32x8_nmul_sub();
    test_f32x8_neq();
    test_f32x8_eq();
    test_f32x8_ge();
    test_f32x8_gt();
    test_f32x8_le();
    test_f32x8_lt();
    test_f32x8_is_nan();
    test_f32x8_is_infinite();
    test_f32x8_is_finite();

    test_report();

    return 0;
}