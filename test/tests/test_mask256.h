#ifndef BAD_TEST_MASK256_H
#define BAD_TEST_MASK256_H

#include <bad/bad.h>

BAD_NAMESPACE_START

void test_mask256_load_store();
void test_mask256_loadu_storeu();
void test_mask256_set();
void test_mask256_set1();
void test_mask256_zero();
void test_mask256_all1();
void test_mask256_value32();
void test_mask256_highbit32();
void test_mask256_lowbit32();
void test_mask256_exponent32();
void test_mask256_eq();
void test_mask256_neq();
void test_mask256_and();
void test_mask256_and_not();
void test_mask256_or();
void test_mask256_xor();
void test_mask256_not();

BAD_NAMESPACE_END

#endif