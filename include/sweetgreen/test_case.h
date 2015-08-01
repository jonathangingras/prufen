#ifndef _SWEETGREEN_TEST_CASE_H_
#define _SWEETGREEN_TEST_CASE_H_

#include "restrict_include.h"
#include "append.h"
#include "format.h"

struct sweetgreen_testcase {
	struct sweetgreen_test* first;
	struct sweetgreen_test* last;
	size_t size;
};

sweetgreen_declare_append(testcase, struct sweetgreen_testcase*, struct sweetgreen_test*);

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
	fprintf(output, SWEETGREEN_YELLOWBOLD("*--------------------*\n")SWEETGREEN_BLUEBOLD("  Launching %zu test%s: ")SWEETGREEN_YELLOWBOLD("\n*--------------------*\n"), testcase->size, testcase->size > 1 ? "s": "");
	sweetgreen_print_separating_line(output);
	
	sweetgreen_testcase_iterate_over(test);

	fprintf(output, "tearing down %zu test%s...\ntestcase result: %s\n", testcase->size, (testcase->size > 1 ? "s" : ""), result ? SWEETGREEN_UNDERLINE(SWEETGREEN_REDBOLD("FAILED")) : SWEETGREEN_GREENBOLD("PASSED"));
	return result;
}

#endif