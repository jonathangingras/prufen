#ifndef _PRUF_EXPECT_MACROS_H_
#define _PRUF_EXPECT_MACROS_H_

#include "restrict_include.h"
#include "operands.h"
#include "assertion.h"

#define pruf_expect_equal(l, r) \
	pruf_test_append(pruf_this_test, \
		pruf_assertion_new( \
			#l, #r, __LINE__, \
			"equality", &pruf_operands_equality, PRUF_ASTNCB_NOF, \
			l, r, 0, &pruf_comparable_format_integer \
	))

#define pruf_expect_not_equal(l, r) \
	pruf_test_append(pruf_this_test, \
		pruf_assertion_new( \
			#l, #r, __LINE__, \
			"inequality", &pruf_operands_inequality, PRUF_ASTNCB_NEG, \
			l, r, 0, &pruf_comparable_format_integer \
	))

#define pruf_expect_zero(l) \
	pruf_test_append(pruf_this_test, \
		pruf_assertion_new( \
			#l, NULL, __LINE__, \
			"zero expression", &pruf_operands_equality, PRUF_ASTNCB_NOF, \
			0, l, 0, &pruf_comparable_format_integer \
	))

#define pruf_expect_non_zero(l) \
	pruf_test_append(pruf_this_test, \
		pruf_assertion_new( \
			#l, NULL, __LINE__, \
			"non-zero expression", &pruf_operands_inequality, PRUF_ASTNCB_NEG, \
			0, l, 0, &pruf_comparable_format_integer \
	))

#define pruf_expect_true(l) \
	pruf_test_append(pruf_this_test, \
		pruf_assertion_new( \
			#l, NULL, __LINE__, \
			"true expression", &pruf_operands_equality, PRUF_ASTNCB_NOF, \
			1, l, 0, &pruf_comparable_format_boolean \
	))

#define pruf_expect_false(l) \
	pruf_test_append(pruf_this_test, \
		pruf_assertion_new( \
			#l, NULL, __LINE__, \
			"false expression", &pruf_operands_equality, PRUF_ASTNCB_NOF, \
			0, l, 0, &pruf_comparable_format_boolean \
	))

#define pruf_expect_same_address(l, r) \
	pruf_test_append(pruf_this_test, \
		pruf_assertion_new( \
			#l, #r, __LINE__, \
			"pointer equality", &pruf_operands_equality, PRUF_ASTNCB_NOF, \
			(long)(l), (long)(r), 0, &pruf_comparable_format_pointer \
	))

#define pruf_expect_not_same_address(l, r) \
	pruf_test_append(pruf_this_test, \
		pruf_assertion_new( \
			#l, #r, __LINE__, \
			"pointer inequality", &pruf_operands_inequality, PRUF_ASTNCB_NEG, \
			(long)(l), (long)(r), 0, &pruf_comparable_format_pointer \
	))

#define pruf_expect_equal_memory(l, r, len) \
	pruf_test_append(pruf_this_test, \
		pruf_assertion_new( \
			#l, #r, __LINE__, \
			"memory equality", &pruf_operands_memory_equality, PRUF_ASTNCB_AVOIDEA | PRUF_ASTNCB_MEMDUP, \
			(long)(l), (long)(r), len, NULL \
	))

#define pruf_expect_not_equal_memory(l, r, len) \
	pruf_test_append(pruf_this_test, \
		pruf_assertion_new( \
			#l, #r, __LINE__, \
			"memory inequality", &pruf_operands_memory_inequality, PRUF_ASTNCB_AVOIDEA | PRUF_ASTNCB_MEMDUP, \
			(long)(l), (long)(r), len, NULL \
	))

#define pruf_expect_equal_string(l, r) \
	pruf_test_append(pruf_this_test, \
		pruf_assertion_new( \
			#l, #r, __LINE__, \
			"string equality", &pruf_operands_string_equality, PRUF_ASTNCB_STRDUP, \
			(long)(l), (long)(r), 0, &pruf_comparable_format_string \
	))

#define pruf_expect_not_equal_string(l, r) \
	pruf_test_append(pruf_this_test, \
		pruf_assertion_new( \
			#l, #r, __LINE__, \
			"string inequality", &pruf_operands_string_inequality, PRUF_ASTNCB_NEG | PRUF_ASTNCB_STRDUP, \
			(long)(l), (long)(r), 0, &pruf_comparable_format_string \
	))

#define pruf_expect_null(l) \
	pruf_test_append(pruf_this_test, \
		pruf_assertion_new( \
			#l, NULL, __LINE__, \
			"is NULL", &pruf_operands_equality, PRUF_ASTNCB_NOF, \
			0, (long)(l), 0, &pruf_comparable_format_pointer \
	))

#define pruf_expect_not_null(l) \
	pruf_test_append(pruf_this_test, \
		pruf_assertion_new( \
			#l, NULL, __LINE__, \
			"is not NULL", &pruf_operands_inequality, PRUF_ASTNCB_NEG, \
			0, (long)(l), 0, &pruf_comparable_format_pointer \
	))

#endif
