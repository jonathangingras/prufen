#ifndef _SWEETGREEN_EXPECT_MACROS_H_
#define _SWEETGREEN_EXPECT_MACROS_H_

#include "restrict_include.h"
#include "operands.h"
#include "assertion.h"

#define sweetgreen_expect_equal(l, r) \
	sweetgreen_test_append(_ZKItestvarname, \
		sweetgreen_assertion_new( \
			#l, #r, __LINE__, "equality", &sweetgreen_operands_equality, l, r, 0, &sweetgreen_comparable_format_integer \
	))

#define sweetgreen_expect_not_equal(l, r) \
	sweetgreen_test_append(_ZKItestvarname, \
		sweetgreen_assertion_new( \
			#l, #r, __LINE__, "inequality", &sweetgreen_operands_inequality, l, r, 0, &sweetgreen_comparable_format_integer \
	))

#define sweetgreen_expect_non_zero(l) \
	sweetgreen_test_append(_ZKItestvarname, \
		sweetgreen_assertion_new( \
			#l, NULL, __LINE__, "non-zero expression", &sweetgreen_operands_inequality, 0, l, 0, &sweetgreen_comparable_format_integer \
	))

#define sweetgreen_expect_true(l) \
	sweetgreen_test_append(_ZKItestvarname, \
		sweetgreen_assertion_new( \
			#l, NULL, __LINE__, "true expression", &sweetgreen_operands_equality, 1, l, 0, &sweetgreen_comparable_format_boolean \
	))

#define sweetgreen_expect_zero(l) \
	sweetgreen_test_append(_ZKItestvarname, \
		sweetgreen_assertion_new( \
			#l, NULL, __LINE__, "zero expression", &sweetgreen_operands_equality, 0, l, 0, &sweetgreen_comparable_format_integer \
	))

#define sweetgreen_expect_false(l) \
	sweetgreen_test_append(_ZKItestvarname, \
		sweetgreen_assertion_new( \
			#l, NULL, __LINE__, "false expression", &sweetgreen_operands_equality, 0, l, 0, &sweetgreen_comparable_format_boolean \
	))

#define sweetgreen_expect_same_address(l, r) \
	sweetgreen_test_append(_ZKItestvarname, \
		sweetgreen_assertion_new( \
			#l, #r, __LINE__, "pointer equality", &sweetgreen_operands_equality, (long)(l), (long)(r), 0, &sweetgreen_comparable_format_pointer \
	))

#define sweetgreen_expect_not_same_address(l, r) \
	sweetgreen_test_append(_ZKItestvarname, \
		sweetgreen_assertion_new( \
			#l, #r, __LINE__, "pointer inequality", &sweetgreen_operands_inequality, (long)(l), (long)(r), 0, &sweetgreen_comparable_format_pointer \
	))

#define sweetgreen_expect_equal_memory(l, r, len) \
	sweetgreen_test_append(_ZKItestvarname, \
		sweetgreen_assertion_new( \
			#l, #r, __LINE__, "memory equality", &sweetgreen_operands_memory_equality, (long)(l), (long)(r), len, &sweetgreen_comparable_format_boolean \
	))

#define sweetgreen_expect_not_equal_memory(l, r, len) \
	sweetgreen_test_append(_ZKItestvarname, \
		sweetgreen_assertion_new( \
			#l, #r, __LINE__, "memory inequality", &sweetgreen_operands_memory_inequality, (long)(l), (long)(r), len, &sweetgreen_comparable_format_boolean \
	))

#define sweetgreen_expect_equal_string(l, r) \
	sweetgreen_test_append(_ZKItestvarname, \
		sweetgreen_assertion_new( \
			#l, #r, __LINE__, "string equality", &sweetgreen_operands_string_equality, (long)(l), (long)(r), 0, &sweetgreen_comparable_format_string \
	))

#define sweetgreen_expect_not_equal_string(l, r) \
	sweetgreen_test_append(_ZKItestvarname, \
		sweetgreen_assertion_new( \
			#l, #r, __LINE__, "string inequality", &sweetgreen_operands_string_inequality, (long)(l), (long)(r), 0, &sweetgreen_comparable_format_string \
	))

#define sweetgreen_expect_null(l) \
	sweetgreen_test_append(_ZKItestvarname, \
		sweetgreen_assertion_new( \
			#l, NULL, __LINE__, "is NULL", &sweetgreen_operands_equality, 0, (long)(l), 0, &sweetgreen_comparable_format_pointer \
	))

#define sweetgreen_expect_not_null(l) \
	sweetgreen_test_append(_ZKItestvarname, \
		sweetgreen_assertion_new( \
			#l, NULL, __LINE__, "is not NULL", &sweetgreen_operands_inequality, 0, (long)(l), 0, &sweetgreen_comparable_format_pointer \
	))

#endif