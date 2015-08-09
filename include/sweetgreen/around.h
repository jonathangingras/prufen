#ifndef _SWEETGREEN_AROUND_H_
#define _SWEETGREEN_AROUND_H_

#include "restrict_include.h"
#include "pre_main.h"

#define sweetgreen_setup(testcase_name) \
	void sweetgreen_setup_function_##testcase_name ();\
	SWEETGREEN_PRE_MAIN(sweetgreen_setup_function_##testcase_name##_insert) {\
		sweetgreen_testcase_static_get(#testcase_name)->setup = &sweetgreen_setup_function_##testcase_name ;\
	}\
	void sweetgreen_setup_function_##testcase_name ()

#define sweetgreen_teardown(testcase_name) \
	void sweetgreen_teardown_function_##testcase_name ();\
	SWEETGREEN_PRE_MAIN(sweetgreen_teardown_function_##testcase_name##_insert) {\
		sweetgreen_testcase_static_get(#testcase_name)->teardown = &sweetgreen_teardown_function_##testcase_name ;\
	}\
	void sweetgreen_teardown_function_##testcase_name ()

#endif