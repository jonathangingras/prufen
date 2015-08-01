#ifndef _SWEETGREEN_EXPECT_MACROS_H_
#define _SWEETGREEN_EXPECT_MACROS_H_

#include "restrict_include.h"

enum sweetgreen_result sweetgreen_result_from_boolean_t(long result) {
	enum sweetgreen_result returned_result = result ? PASSED : FAILED; 
	return returned_result;
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