#ifndef _SWEETGREEN_TEST_CASE_H_
#define _SWEETGREEN_TEST_CASE_H_

#include "restrict_include.h"
#include "append.h"
#include "format.h"

typedef void (*sweetgreen_testcase_around_function)();

struct sweetgreen_testcase {
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

#define sweetgreen_call_if_non_null(function) if(function) { function(); }

#define sweetgreen_testcase_test_each(stream_output, test) \
while(test) {\
	sweetgreen_call_if_non_null(testcase->setup);\
	result += sweetgreen_test_test(stream_output, test);\
	sweetgreen_call_if_non_null(testcase->teardown);\
	\
	sweetgreen_print_separating_line(stream_output);\
	\
	struct sweetgreen_test* last = test;\
	test = test->next;\
	free(last);\
}

int sweetgreen_testcase_test(FILE* output, struct sweetgreen_testcase* testcase) {
	struct sweetgreen_test* test = testcase->first;
	int result = 0;
	fprintf(output, SWEETGREEN_YELLOWBOLD("*--------------------*\n") SWEETGREEN_BLUEBOLD("  Launching %zu test%s: ") SWEETGREEN_YELLOWBOLD("\n*--------------------*\n"), testcase->size, testcase->size > 1 ? "s": "");
	sweetgreen_print_separating_line(output);
	
	sweetgreen_testcase_test_each(output, test);

	fprintf(output, "tearing down %zu test%s...\ntestcase result: %s\n", testcase->size, (testcase->size > 1 ? "s" : ""), result ? SWEETGREEN_UNDERLINE(SWEETGREEN_REDBOLD("FAILED")) : SWEETGREEN_GREENBOLD("PASSED"));
	return result;
}

#endif