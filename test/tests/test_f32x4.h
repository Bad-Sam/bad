#ifndef BAD_TEST_F32X4_H
#define BAD_TEST_F32X4_H

#include <bad/bad.h>

BAD_NAMESPACE_START

// ============= Defaults =============
void test_f32x4_one();


// ========== Loads & stores ==========
void test_f32x4_load_store();
void test_f32x4_loadu_storeu();


// =========== Arithmetic ===========
void test_f32x4_hadd();


// ====== Advanced arithmetic =======
void test_f32x4_abs();
void test_f32x4_neg();
void test_f32x4_mod();
void test_f32x4_trunc();
void test_f32x4_round();
void test_f32x4_floor();
void test_f32x4_ceil();
void test_f32x4_clamp();

void test_f32x4_mul_add();
void test_f32x4_mul_sub();
void test_f32x4_nmul_add();
void test_f32x4_nmul_sub();


// ======= Selection & tests ========
void test_f32x4_blend();
void test_f32x4_is_nan();
void test_f32x4_is_infinite();
void test_f32x4_is_finite();

BAD_NAMESPACE_END

#endif