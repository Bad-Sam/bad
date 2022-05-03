#ifndef BAD_TEST_F32X8_CALC_H
#define BAD_TEST_F32X8_CALC_H

#include <bad/bad.h>

BAD_NAMESPACE_START

// =========== Arithmetic ===========
void test_f32x8_hadd();
void test_f32x8_sum();


// ====== Advanced arithmetic =======
void test_f32x8_abs();
void test_f32x8_sign();
void test_f32x8_neg();
void test_f32x8_frac();
void test_f32x8_mod();
void test_f32x8_trunc();
void test_f32x8_round();
void test_f32x8_floor();
void test_f32x8_ceil();
void test_f32x8_clamp();
void test_f32x8_lerp();
void test_f32x8_mul_add();
void test_f32x8_mul_sub();
void test_f32x8_nmul_add();
void test_f32x8_nmul_sub();


// ============ Comparison ============
void test_f32x8_neq();
void test_f32x8_eq();
void test_f32x8_ge();
void test_f32x8_gt();
void test_f32x8_le();
void test_f32x8_lt();


// ======= Selection & tests ========
void test_f32x8_is_nan();
void test_f32x8_is_infinite();
void test_f32x8_is_finite();

BAD_NAMESPACE_END

#endif