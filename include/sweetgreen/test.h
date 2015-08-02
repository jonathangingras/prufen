#ifndef _SWEETGREEN_TEST_H_
#define _SWEETGREEN_TEST_H_

#include "restrict_include.h"
#include "append.h"
#include "format.h"

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

sweetgreen_declare_append(test, struct sweetgreen_test*, struct sweetgreen_assertion*);

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

int sweetgreen_test_test(FILE* output, struct sweetgreen_test* test) {
	fprintf(output, SWEETGREEN_CYANBOLD("%s") " - " SWEETGREEN_BLUEBOLD("%s") ":\n", test->module_name, test->name);

	fprintf(output, SWEETGREEN_MAGENTA("execution:") "\n");
	test->function(test);
	fprintf(output, SWEETGREEN_MAGENTA("<---- end") "\n");

	int result = 0;
	struct sweetgreen_assertion* assertion = test->first;
	fprintf(output, "launching " SWEETGREEN_BOLD("%zu") " assertion%s:\n", test->size, (test->size > 1 ? "s": ""));

	while(assertion) {
		result += sweetgreen_assertion_test(output, assertion);

		struct sweetgreen_assertion* last = assertion;
		assertion = assertion->next;
		free(last);
	}
	fprintf(output, SWEETGREEN_BOLD("=>")" ️test result: %s\n", result ? SWEETGREEN_RED("FAILED") : SWEETGREEN_GREEN("PASSED"));
	return result;
}

#endif