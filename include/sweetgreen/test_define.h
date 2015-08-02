#ifndef _SWEETGREEN_TEST_DEFINE_H_
#define _SWEETGREEN_TEST_DEFINE_H_

#include "restrict_include.h"
#include "pre_main.h"

#define sweetgreen_test_define(module, name) \
void sweetgreen__##module##__##name(struct sweetgreen_test*);\
SWEETGREEN_PRE_MAIN(sweetgreen__##module##__##name##_add_to_testcase) {\
	struct sweetgreen_test* test = sweetgreen_test_new(&sweetgreen__##module##__##name, #module, #name);\
	sweetgreen_testcase_append(&_ZKItestcasevarname, test);\
}\
void sweetgreen__##module##__##name(struct sweetgreen_test* _ZKItestvarname)

#endif