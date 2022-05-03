#ifndef BAD_TEST_F32X8_H
#define BAD_TEST_F32X8_H

#include <bad/bad.h>

BAD_NAMESPACE_START

// ============= Defaults =============
void test_f32x8_zero();
void test_f32x8_one();


// ========== Loads & stores ==========
void test_f32x8_load_store();
void test_f32x8_loadu_storeu();
void test_f32x8_set();
void test_f32x8_set_all();


// ======= Selection ========
void test_f32x8_blend();

// ============ Cast/reinterpret =============
void test_f32x8_as_mask256();

BAD_NAMESPACE_END

#endif