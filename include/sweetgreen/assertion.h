#ifndef _SWEETGREEN_ASSERTION_H_
#define _SWEETGREEN_ASSERTION_H_

#include "restrict_include.h"
#include "operands.h"
#include "format.h"

struct sweetgreen_assertion {
	struct sweetgreen_operands operands;
	int line;
	const char* expectation_hr;
	struct sweetgreen_assertion* next;
};

struct sweetgreen_assertion* sweetgreen_assertion_new(const char* l_name, const char* r_name, int line, const char* expectation_hr, enum sweetgreen_result (*assertion_callback)(struct sweetgreen_operands*), long l, long r, long len, void (* format)(char* string_output, union sweetgreen_comparable_t)) {
	struct sweetgreen_assertion* assertion = (struct sweetgreen_assertion*)malloc(sizeof(struct sweetgreen_assertion));
	assertion->next = NULL;
	
	assertion->operands.first_name = l_name;
	assertion->operands.second_name = r_name;
	assertion->operands.assert = assertion_callback;
	assertion->operands._1.integral_type = l;
	assertion->operands._2.integral_type = r;
	assertion->operands._3.integral_type = len;
	assertion->operands.formatter = format;

	assertion->line = line;
	assertion->expectation_hr = expectation_hr;
	return assertion;
}

void sweetgreen_assertion_print_fail_information(struct sweetgreen_assertion* assertion, FILE* output) {
	char line_str[48];
	memset(line_str, 0, 48);
	sprintf(line_str, SWEETGREEN_MAGENTA("(line: ") SWEETGREEN_MAGENTABOLD("%i") SWEETGREEN_MAGENTA(")"), assertion->line);
	fprintf(output, " -> " SWEETGREEN_RED("%s%s%s") " %s\n",
		assertion->operands.first_name,
		assertion->operands.second_name ? ", " : "",
		assertion->operands.second_name ? assertion->operands.second_name : "",
		line_str
	);

	char expected[256], actual[256];
	assertion->operands.formatter(expected, assertion->operands._1);
	assertion->operands.formatter(actual, assertion->operands._2);

	fprintf(output, SWEETGREEN_MAGENTA("    expected: %s") SWEETGREEN_RED(", actual: %s\n"), expected, actual);
}

int sweetgreen_assertion_test(FILE* output, struct sweetgreen_assertion* assertion) {
	enum sweetgreen_result result = assertion->operands.assert(&assertion->operands);

	fprintf(output, "%s %s: %s\n", 
		result == PASSED ? SWEETGREEN_PASS_SYMBOL : SWEETGREEN_FAIL_SYMBOL,
		assertion->expectation_hr,
		result ? SWEETGREEN_RED("fail") : SWEETGREEN_GREEN("ok")
	);
	
	if(result) { sweetgreen_assertion_print_fail_information(assertion, output); }

	return result != PASSED;
}

#endif