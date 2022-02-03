#ifndef BAD_TEST_F32X4_H
#define BAD_TEST_F32X4_H

#include <bad/bad.h>

BAD_NAMESPACE_START

// ============= Defaults =============
void test_f32x4_zero();
void test_f32x4_one();


// ========== Loads & stores ==========
void test_f32x4_load_store();
void test_f32x4_loadu_storeu();
void test_f32x4_set();
void test_f32x4_set1();


// ======= Selection ========
void test_f32x4_blend();

// ============ Cast/reinterpret =============
void test_f32x4_cast_mask128();

BAD_NAMESPACE_END

#endif