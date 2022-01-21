#ifndef BAD_TEST_MASK128_H
#define BAD_TEST_MASK128_H

#include <bad/bad.h>

BAD_NAMESPACE_START

void test_mask128_load_store();
void test_mask128_loadu_storeu();
void test_mask128_all1();
void test_mask128_value32();
void test_mask128_highbit32();
void test_mask128_lowbit32();
void test_mask128_exponent32();

BAD_NAMESPACE_END

#endif