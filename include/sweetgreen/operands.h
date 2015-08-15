#ifndef _SWEETGREEN_OPERANDS_H_
#define _SWEETGREEN_OPERANDS_H_

#include "restrict_include.h"
#include "result.h"
#include "comparable.h"

struct sweetgreen_operands {
	union sweetgreen_comparable_t _1, _2, _3;

	sweetgreen_comparable_formatter formatter;

	const char* first_name;
	const char* second_name;
};

enum sweetgreen_result sweetgreen_result_from_boolean_t(long result) {
	enum sweetgreen_result returned_result = result ? PASSED : FAILED; 
	return returned_result;
}

enum sweetgreen_result sweetgreen_operands_equality(struct sweetgreen_operands* operands) {
	return sweetgreen_result_from_boolean_t(operands->_1.integral_type == operands->_2.integral_type);
}

enum sweetgreen_result sweetgreen_operands_inequality(struct sweetgreen_operands* operands) {
	return sweetgreen_result_from_boolean_t(operands->_1.integral_type != operands->_2.integral_type);
}

enum sweetgreen_result sweetgreen_operands_memory_equality(struct sweetgreen_operands* operands) {
	return sweetgreen_result_from_boolean_t(!memcmp(operands->_1.address, operands->_2.address, operands->_3.integral_type));
}

enum sweetgreen_result sweetgreen_operands_memory_inequality(struct sweetgreen_operands* operands) {
	return sweetgreen_result_from_boolean_t(memcmp(operands->_1.address, operands->_2.address, operands->_3.integral_type));
}

enum sweetgreen_result sweetgreen_operands_string_equality(struct sweetgreen_operands* operands) {
	return sweetgreen_result_from_boolean_t(!strcmp(operands->_1.address, operands->_2.address));
}

enum sweetgreen_result sweetgreen_operands_string_inequality(struct sweetgreen_operands* operands) {
	return sweetgreen_result_from_boolean_t(strcmp(operands->_1.address, operands->_2.address));
}

#endif