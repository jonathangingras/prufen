#ifndef _SWEETGREEN_TEST_CASE_H_
#define _SWEETGREEN_TEST_CASE_H_

#include "restrict_include.h"
#include "append.h"
#include "format.h"

typedef void (*sweetgreen_testcase_around_function)();

struct sweetgreen_testcase {
	const char* name;

	struct sweetgreen_test* first;
	struct sweetgreen_test* last;
	size_t size;

	sweetgreen_testcase_around_function setup, teardown;
};

sweetgreen_declare_append(testcase, struct sweetgreen_testcase*, struct sweetgreen_test*);

struct sweetgreen_testcase* sweetgreen_testcase_init(struct sweetgreen_testcase* testcase) {
	testcase->setup = NULL;
	testcase->teardown = NULL;
	return testcase;
}

struct sweetgreen_testcase* sweetgreen_testcase_new(const char* name) {
	struct sweetgreen_testcase* testcase = (struct sweetgreen_testcase*)malloc(sizeof(struct sweetgreen_testcase));
	testcase->name = name;
	testcase->setup = NULL;
	testcase->teardown = NULL;
	return testcase;
}

#define sweetgreen_call_if_non_null(function) if(function) { function(); }

#define sweetgreen_testcase_test_each(stream_output, result_output, testcase) \
sweetgreen_print_separating_line(stream_output);\
struct sweetgreen_test* test = testcase->first;\
while(test) {\
	sweetgreen_call_if_non_null((testcase)->setup);\
	*result_output += sweetgreen_test_test(stream_output, test);\
	sweetgreen_call_if_non_null((testcase)->teardown);\
	\
	sweetgreen_print_separating_line(stream_output);\
	\
	struct sweetgreen_test* last = test;\
	test = (test)->next;\
	free(last);\
}

void sweetgreen_testcase_print_header(FILE* output, struct sweetgreen_testcase* testcase) {
	fprintf(output, 
		"\nTestcase: " SWEETGREEN_CYANBOLD("%s\n") " -> launching %zu test%s:\n\n",
		testcase->name, testcase->size, testcase->size > 1 ? "s": ""
	);
}

void sweetgreen_testcase_print_result(FILE* output, struct sweetgreen_testcase* testcase, int result) {
	fprintf(output, "\ntearing down %zu test%s...\ntestcase result: %s\n\n", 
		testcase->size, (testcase->size > 1 ? "s" : ""), 
		result ? SWEETGREEN_UNDERLINE(SWEETGREEN_REDBOLD("FAILED")) : SWEETGREEN_GREENBOLD("PASSED")
	);
}

int sweetgreen_testcase_test(FILE* output, struct sweetgreen_testcase* testcase) {
	int result = 0;
	
	sweetgreen_testcase_print_header(output, testcase);
	sweetgreen_testcase_test_each(output, &result, testcase);
	sweetgreen_testcase_print_result(output, testcase, result);

	return result;
}

#endif