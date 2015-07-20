#include "restrict_include.h"

#ifndef _SWEETGREEN_EXPECT_MACROS_H_
#define _SWEETGREEN_EXPECT_MACROS_H_

#define sweetgreen_main \
struct sweetgreen_testcase _ZKItestcasevarname;\
int main(int argc, char** argv) {\
	struct sweetgreen_testcase* testcase = &_ZKItestcasevarname;\
	return sweetgreen_testcase_test(stdout, testcase);\
}

#define sweetgreen_expect_equal(l, r) \
	sweetgreen_test_append(_ZKItestvarname, \
		sweetgreen_assertion_new( \
			#l, #r, __LINE__, "equality", sweetgreen_result_from_boolean_t((l) == (r)) \
	))

#define sweetgreen_expect_not_equal(l, r) \
	sweetgreen_test_append(_ZKItestvarname, \
		sweetgreen_assertion_new( \
			#l, #r, __LINE__, "inequality", sweetgreen_result_from_boolean_t((l) != (r)) \
	))

#define sweetgreen_expect_non_zero(l) \
	sweetgreen_test_append(_ZKItestvarname, \
		sweetgreen_assertion_new( \
			#l, NULL, __LINE__, "non-zero expression", sweetgreen_result_from_boolean_t((l)) \
	))

#define sweetgreen_expect_true sweetgreen_expect_non_zero

#define sweetgreen_expect_zero(l) \
	sweetgreen_test_append(_ZKItestvarname, \
		sweetgreen_assertion_new( \
			#l, NULL, __LINE__, "zero expression", sweetgreen_result_from_boolean_t(!(l)) \
	))

#define sweetgreen_expect_false sweetgreen_expect_zero

#endif