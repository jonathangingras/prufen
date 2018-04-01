#ifndef _PRUF_OPERANDS_H_
#define _PRUF_OPERANDS_H_

#include "restrict_include.h"
#include "result.h"
#include "comparable.h"

struct pruf_operands {
	union pruf_comparable_t _1, _2, _3;

	pruf_comparable_formatter formatter;

	const char* first_name;
	const char* second_name;
};

enum pruf_result pruf_result_from_boolean_t(long result) {
	enum pruf_result returned_result = result ? PASSED : FAILED; 
	return returned_result;
}

enum pruf_result pruf_operands_equality(struct pruf_operands* operands) {
	return pruf_result_from_boolean_t(operands->_1.integral_type == operands->_2.integral_type);
}

enum pruf_result pruf_operands_inequality(struct pruf_operands* operands) {
	return pruf_result_from_boolean_t(operands->_1.integral_type != operands->_2.integral_type);
}

enum pruf_result pruf_operands_memory_equality(struct pruf_operands* operands) {
	return pruf_result_from_boolean_t(!memcmp(operands->_1.address, operands->_2.address, operands->_3.integral_type));
}

enum pruf_result pruf_operands_memory_inequality(struct pruf_operands* operands) {
	return pruf_result_from_boolean_t(memcmp(operands->_1.address, operands->_2.address, operands->_3.integral_type));
}

enum pruf_result pruf_operands_string_equality(struct pruf_operands* operands) {
	return pruf_result_from_boolean_t(!strcmp(operands->_1.address, operands->_2.address));
}

enum pruf_result pruf_operands_string_inequality(struct pruf_operands* operands) {
	return pruf_result_from_boolean_t(strcmp(operands->_1.address, operands->_2.address));
}

#endif
