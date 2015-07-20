#ifndef _SWEETGREEN_H_
#define _SWEETGREEN_H_

#include <stdlib.h>
#include <string.h>

#include "symbols.h"
#include "expect_macros.h"
#include "colors.h"

#ifdef __cplusplus
extern "C" {
#endif

struct sweetgreen_operands {
	void* first;
	const char* first_name;
	void* second;
	const char* second_name;
	void* third;
	const char* third_name;
};

enum sweetgreen_result {
	PASSED = 0,
	FAILED,
	UNSTABLE
};

struct sweetgreen_assertion {
	struct sweetgreen_operands operands;
	enum sweetgreen_result result;
	int line;
	char expectation[32];
	struct sweetgreen_assertion* next;
};

typedef void (*sweetgreen_test_function)(struct sweetgreen_test*);

struct sweetgreen_test {
	struct sweetgreen_assertion* first;
	struct sweetgreen_assertion* last;
	size_t size;
	sweetgreen_test_function function;
	struct sweetgreen_test* next;
	char module_name[128];
	char name[256];
};

struct sweetgreen_testcase {
	struct sweetgreen_test* first;
	struct sweetgreen_test* last;
	size_t size;
};

struct sweetgreen_test* sweetgreen_test_new(sweetgreen_test_function function, const char* module_name, const char* name) {
	struct sweetgreen_test* test = (struct sweetgreen_test*)malloc(sizeof(struct sweetgreen_test));
	test->first = NULL;
	test->last = NULL;
	test->size = 0;
	test->function = function;
	test->next = NULL;
	test->module_name[0] = 0;
	strcat(test->module_name, module_name);
	test->name[0] = 0;
	strcat(test->name, name);
	return test;
}

void sweetgreen_print_separating_line(FILE* output) {
	fprintf(output, "-------------------\n");
}

#define sweetgreen_declare_append(declare_name, container_type, element_type)\
void sweetgreen_##declare_name##_append(container_type container, element_type element) {\
	if(!container->first) {\
		container->first = element;\
	}\
	\
	if(!container->last) {\
		container->last = element;\
	} else {\
		container->last->next = element;\
		container->last = element;\
	}\
	\
	container->size++;\
}
sweetgreen_declare_append(testcase, struct sweetgreen_testcase*, struct sweetgreen_test*);
sweetgreen_declare_append(test, struct sweetgreen_test*, struct sweetgreen_assertion*);

int sweetgreen_assertion_test(FILE* output, struct sweetgreen_assertion* assertion) {
	char line_str[48];
	memset(line_str, 0, 48);
	sprintf(line_str, SWEETGREEN_MAGENTA("(line: ")SWEETGREEN_MAGENTABOLD("%i")SWEETGREEN_MAGENTA(")"), assertion->line);
	fprintf(output, "%s %s: %s", 
		assertion->result == PASSED ? SWEETGREEN_PASS_SYMBOL : SWEETGREEN_FAIL_SYMBOL,
		assertion->expectation,
		assertion->result ? SWEETGREEN_RED("fail") : SWEETGREEN_GREEN("ok")
	);

	if(assertion->result) {
		fprintf(output, " -> ["SWEETGREEN_RED("%s%s%s")"] %s",
			assertion->operands.first_name,
			assertion->operands.second_name ? ", " : "",
			assertion->operands.second_name ? assertion->operands.second_name : "",
			line_str
		);
	}

	fprintf(output, "\n");
	return assertion->result != PASSED;
}

int sweetgreen_test_test(FILE* output, struct sweetgreen_test* test) {
	test->function(test);
	int result = 0;
	struct sweetgreen_assertion* assertion = test->first;
	fprintf(output, SWEETGREEN_CYANBOLD("%s")" - "SWEETGREEN_BLUEBOLD("%s")":\nlaunching %zu assertion%s:\n", test->module_name, test->name, test->size, (test->size > 1 ? "s": ""));
	while(assertion) {
		result += sweetgreen_assertion_test(output, assertion);

		struct sweetgreen_assertion* last = assertion;
		assertion = assertion->next;
		free(last);
	}
	fprintf(output, SWEETGREEN_BOLD("=>")" ️test result: %s\n", result ? SWEETGREEN_RED("FAILED") : SWEETGREEN_GREEN("PASSED"));
	return result;
}

#define sweetgreen_testcase_iterate_over(node) \
while(node) {\
	result += sweetgreen_test_test(output, node);\
	sweetgreen_print_separating_line(output);\
	\
	struct sweetgreen_test* last = node;\
	node = node->next;\
	free(last);\
}

int sweetgreen_testcase_test(FILE* output, struct sweetgreen_testcase* testcase) {
	struct sweetgreen_test* test = testcase->first;
	int result = 0;
	fprintf(output, SWEETGREEN_YELLOWBOLD("*--------------------*\n|")SWEETGREEN_BLUEBOLD(" Launching %zu test%s: ")SWEETGREEN_YELLOWBOLD("|\n*--------------------*\n"), testcase->size, testcase->size > 1 ? "s": "");
	sweetgreen_print_separating_line(output);
	
	sweetgreen_testcase_iterate_over(test);

	fprintf(output, "tearing down...\ntestcase result: %s\n", result ? SWEETGREEN_UNDERLINE(SWEETGREEN_REDBOLD("FAILED")) : SWEETGREEN_GREENBOLD("PASSED"));
	return result;
}

enum sweetgreen_result sweetgreen_result_from_boolean_t(long result) {
	enum sweetgreen_result returned_result = result ? PASSED : FAILED; 
	return returned_result;
}

struct sweetgreen_assertion* sweetgreen_assertion_new(const char* l_name, const char* r_name, int line, const char* expectation, enum sweetgreen_result result) {
	struct sweetgreen_assertion* assertion = (struct sweetgreen_assertion*)malloc(sizeof(struct sweetgreen_assertion));
	assertion->next = NULL;
	assertion->operands.first_name = l_name;
	assertion->operands.second_name = r_name;
	assertion->line = line;
	assertion->result = result;
	assertion->expectation[0] = 0;
	strcat(assertion->expectation, expectation);
	return assertion;
}

#define sweetgreen_test_define(module, name) \
void sweetgreen__##module##__##name(struct sweetgreen_test*);\
__attribute__((constructor)) void sweetgreen__##module##__##name##_add_to_testcase(void) {\
	struct sweetgreen_test* test = sweetgreen_test_new(&sweetgreen__##module##__##name, #module, #name);\
	sweetgreen_testcase_append(&_ZKItestcasevarname, test);\
}\
void sweetgreen__##module##__##name(struct sweetgreen_test* _ZKItestvarname)

sweetgreen_main;

#ifdef __cplusplus
}
#endif

#endif