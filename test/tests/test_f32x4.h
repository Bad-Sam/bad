#ifndef BAD_TEST_F32X4_H
#define BAD_TEST_F32X4_H

#include <bad/bad.h>

BAD_NAMESPACE_START

// ============= Defaults =============
//void test_f32x4_any();
//void test_f32x4_zero();
void test_f32x4_one();


// ========== Loads & stores ==========
void test_f32x4_load_store();
void test_f32x4_loadu_storeu();


// ======= Selection & tests ========
void test_f32x4_blend();

BAD_NAMESPACE_END

#endif