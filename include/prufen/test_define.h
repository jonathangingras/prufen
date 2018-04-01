#ifndef _PRUF_TEST_DEFINE_H_
#define _PRUF_TEST_DEFINE_H_

#include "restrict_include.h"
#include "pre_main.h"

#define pruf_test_define(testcase_name, name) \
void pruf__##testcase_name##__##name(struct pruf_test*);\
PRUF_PRE_MAIN(pruf__##testcase_name##__##name##_add_to_testcase) {\
	struct pruf_test* test = pruf_test_new(&pruf__##testcase_name##__##name, #testcase_name, #name);\
	pruf_testcase_append(pruf_testcase_static_get(#testcase_name), test);\
}\
void pruf__##testcase_name##__##name(struct pruf_test* pruf_this_test)

#endif
