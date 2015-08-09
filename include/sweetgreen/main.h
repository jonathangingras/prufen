#ifndef _SWEETGREEN_MAIN_H_
#define _SWEETGREEN_MAIN_H_

#include "restrict_include.h"
#include "test_case.h"
#include "pre_main.h"

struct sweetgreen_testcase* sweetgreen_testcase_static_get(const char* testcase_name) {
	static struct sweetgreen_testcase testcase;
	return &testcase;
}

#define sweetgreen_main \
SWEETGREEN_PRE_MAIN(_ZKItestcasevarname_init) {\
	sweetgreen_testcase_init(sweetgreen_testcase_static_get("")); /* this must be the first function call of the entire program */ \
}\
int main(int argc, char** argv) {\
	struct sweetgreen_testcase* testcase = sweetgreen_testcase_static_get("");\
	return sweetgreen_testcase_test(stdout, testcase);\
}

#endif