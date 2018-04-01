#ifndef _PRUF_AROUND_H_
#define _PRUF_AROUND_H_

#include "restrict_include.h"
#include "pre_main.h"

#define pruf_setup(testcase_name) \
	void pruf_setup_function_##testcase_name ();\
	PRUF_PRE_MAIN(pruf_setup_function_##testcase_name##_insert) {\
		pruf_testcase_static_get(#testcase_name)->setup = &pruf_setup_function_##testcase_name ;\
	}\
	void pruf_setup_function_##testcase_name ()

#define pruf_teardown(testcase_name) \
	void pruf_teardown_function_##testcase_name ();\
	PRUF_PRE_MAIN(pruf_teardown_function_##testcase_name##_insert) {\
		pruf_testcase_static_get(#testcase_name)->teardown = &pruf_teardown_function_##testcase_name ;\
	}\
	void pruf_teardown_function_##testcase_name ()

#endif
