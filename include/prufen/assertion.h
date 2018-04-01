#ifndef _PRUF_ASSERTION_H_
#define _PRUF_ASSERTION_H_

#include "restrict_include.h"
#include "operands.h"
#include "format.h"

#define PRUF_ASTNCB_NOF 0
#define PRUF_ASTNCB_NEG 1
#define PRUF_ASTNCB_AVOIDEA 2
#define PRUF_ASTNCB_MEMDUP 4
#define PRUF_ASTNCB_STRDUP 8

#define pruf_assertion_callback_is_negation(callback_flags) (callback_flags & PRUF_ASTNCB_NEG)
#define pruf_assertion_callback_avoids_print(callback_flags) (callback_flags & PRUF_ASTNCB_AVOIDEA)

struct pruf_assertion {
	struct pruf_operands operands;

	enum pruf_result (*callback)(struct pruf_operands*);
	int callback_flags;

	int line;
	const char* expectation_hr;
	struct pruf_assertion* next;
};

void pruf_assertion_assign_operands(struct pruf_assertion* assertion, long l, long r, long len) {
  assertion->operands._3.integral_type = len;

  if(assertion->callback_flags & PRUF_ASTNCB_MEMDUP) {
    assertion->operands._1.address = calloc(len, sizeof(char));
    memcpy(assertion->operands._1.address, (void*)l, len);
    assertion->operands._2.address = calloc(len, sizeof(char));
    memcpy(assertion->operands._2.address, (void*)r, len);
  } else if(assertion->callback_flags & PRUF_ASTNCB_STRDUP) {
    assertion->operands._1.address = strdup((const char*)l);
    assertion->operands._2.address = strdup((const char*)r);
  } else {      
    assertion->operands._1.integral_type = l;
    assertion->operands._2.integral_type = r;
  }
}

struct pruf_assertion* pruf_assertion_new(const char* l_name, const char* r_name, int line, const char* expectation_hr, enum pruf_result (*callback)(struct pruf_operands*), int callback_flags, long l, long r, long len, void (* format)(char* string_output, union pruf_comparable_t)) {
	struct pruf_assertion* assertion = (struct pruf_assertion*)malloc(sizeof(struct pruf_assertion));
	assertion->next = NULL;
	
	assertion->line = line;
	assertion->expectation_hr = expectation_hr;
	assertion->callback = callback;
	assertion->callback_flags = callback_flags;

	assertion->operands.first_name = l_name;
	assertion->operands.second_name = r_name;
	assertion->operands._3.integral_type = len;
	assertion->operands.formatter = format;

        pruf_assertion_assign_operands(assertion, l, r, len);
	
	return assertion;
}

void pruf_assertion_destroy(struct pruf_assertion* assertion) {
  if((assertion->callback_flags & PRUF_ASTNCB_MEMDUP) || 
     (assertion->callback_flags & PRUF_ASTNCB_STRDUP)) {
    free(assertion->operands._1.address);
    free(assertion->operands._2.address);
  }
}

void pruf_assertion_print_expected_actual(FILE* output, struct pruf_assertion* assertion) {
	char expected[256], actual[256];
	assertion->operands.formatter(expected, assertion->operands._1);
	assertion->operands.formatter(actual, assertion->operands._2);

	pruf_print_color(output, "    %sexpected: %s", PRUF_MAGENTA,
		pruf_assertion_callback_is_negation(assertion->callback_flags) ? "un" : "",
		expected
	);

	pruf_print_color(output, ", actual: %s\n", PRUF_RED, actual);
}

void pruf_assertion_print_fail_information(FILE* output, struct pruf_assertion* assertion) {
	char line_str[48];
	memset(line_str, 0, 48);
	int offset = 0;
	
	offset += pruf_write_color(line_str, "(line: ", PRUF_MAGENTA);
	offset += pruf_write_color(line_str + offset, "%i", PRUF_MAGENTABOLD, assertion->line);
	pruf_write_color(line_str + offset, ")", PRUF_MAGENTA);
	
	fprintf(output, " -> ");
	pruf_print_color(output, "%s%s%s", PRUF_RED, 
		assertion->operands.first_name, 
		assertion->operands.second_name ? ", " : "", 
		assertion->operands.second_name ? assertion->operands.second_name : ""
	);
	fprintf(output, "%s\n", line_str);

	if(!pruf_assertion_callback_avoids_print(assertion->callback_flags)) {
		pruf_assertion_print_expected_actual(output, assertion);
	}
}

int pruf_assertion_test(FILE* output, struct pruf_assertion* assertion) {
	enum pruf_result result = assertion->callback(&assertion->operands);

	fprintf(output, "%s %s: ", 
		result == PASSED ? PRUF_PASS_SYMBOL : PRUF_FAIL_SYMBOL,
		assertion->expectation_hr
	);

	if(result) {
		pruf_print_color(output, "fail\n", PRUF_RED);
	} else {
		pruf_print_color(output, "ok\n", PRUF_GREEN);
	}
	
	if(result) { pruf_assertion_print_fail_information(output, assertion); }

	return result != PASSED;
}

#endif
