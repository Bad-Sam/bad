#ifndef BAD_TEST_MASK128_H
#define BAD_TEST_MASK128_H

#include <bad/bad.h>

BAD_NAMESPACE_START

void test_mask128_load_store();
void test_mask128_loadu_storeu();
void test_mask128_set();
void test_mask128_set_all();
void test_mask128_zero();
void test_mask128_all1();
void test_mask128_value32();
void test_mask128_highbit32();
void test_mask128_lowbit32();
void test_mask128_exponent32();
void test_mask128_eq();
void test_mask128_neq();
void test_mask128_and();
void test_mask128_and_not();
void test_mask128_or();
void test_mask128_xor();
void test_mask128_not();

BAD_NAMESPACE_END

#endif