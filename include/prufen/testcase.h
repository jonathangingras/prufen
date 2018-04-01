#ifndef _PRUF_TEST_CASE_H_
#define _PRUF_TEST_CASE_H_

#include "restrict_include.h"
#include "append.h"
#include "format.h"

typedef void (*pruf_testcase_around_function)();

struct pruf_testcase {
	const char* name;

	struct pruf_test* first;
	struct pruf_test* last;
	size_t size;

	pruf_testcase_around_function setup, teardown;
};

pruf_declare_append(testcase, struct pruf_testcase*, struct pruf_test*);

struct pruf_testcase* pruf_testcase_init(struct pruf_testcase* testcase) {
	testcase->setup = NULL;
	testcase->teardown = NULL;
	return testcase;
}

struct pruf_testcase* pruf_testcase_new(const char* name) {
	struct pruf_testcase* testcase = (struct pruf_testcase*)malloc(sizeof(struct pruf_testcase));
	testcase->name = name;
	testcase->setup = NULL;
	testcase->teardown = NULL;
	return testcase;
}

#define pruf_call_if_non_null(function) if(function) { function(); }

#define pruf_testcase_test_each(stream_output, result_output, testcase) \
pruf_print_separating_line(stream_output);\
struct pruf_test* test = testcase->first;\
while(test) {\
	pruf_call_if_non_null((testcase)->setup);\
	*result_output += pruf_test_test(stream_output, test);\
	pruf_call_if_non_null((testcase)->teardown);\
	\
	pruf_print_separating_line(stream_output);\
	\
	struct pruf_test* last = test;\
	test = (test)->next;\
	free(last);\
}

void pruf_testcase_print_header(FILE* output, struct pruf_testcase* testcase) {
	fprintf(output, "Testcase: "); 
	pruf_print_color(output, "%s\n", PRUF_CYANBOLD, testcase->name);
	fprintf(output, " -> launching %zu test%s:\n", testcase->size, testcase->size > 1 ? "s": "");
}

void pruf_testcase_print_result(FILE* output, struct pruf_testcase* testcase, int result) {
	fprintf(output, "tearing down %zu test%s...\ntestcase result: ", 
		testcase->size, testcase->size > 1 ? "s" : ""
	);
	if(result) {
		pruf_print_color(output, "FAILED\n", PRUF_REDBOLD);
	} else {
		pruf_print_color(output, "PASSED\n", PRUF_GREENBOLD);
	}
}

int pruf_testcase_test(FILE* output, struct pruf_testcase* testcase) {
	int result = 0;
	
	pruf_testcase_print_header(output, testcase);
	pruf_testcase_test_each(output, &result, testcase);
	pruf_testcase_print_result(output, testcase, result);

	return result;
}

#endif
