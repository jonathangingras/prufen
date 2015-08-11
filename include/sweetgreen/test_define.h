#ifndef _SWEETGREEN_TEST_DEFINE_H_
#define _SWEETGREEN_TEST_DEFINE_H_

#include "restrict_include.h"
#include "pre_main.h"

#define sweetgreen_test_define(testcase_name, name) \
void sweetgreen__##testcase_name##__##name(struct sweetgreen_test*);\
SWEETGREEN_PRE_MAIN(sweetgreen__##testcase_name##__##name##_add_to_testcase) {\
	struct sweetgreen_test* test = sweetgreen_test_new(&sweetgreen__##testcase_name##__##name, #testcase_name, #name);\
	sweetgreen_testcase_append(sweetgreen_testcase_static_get(#testcase_name), test);\
}\
void sweetgreen__##testcase_name##__##name(struct sweetgreen_test* _ZKItestvarname)

#endif