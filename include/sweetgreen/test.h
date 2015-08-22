#ifndef _SWEETGREEN_TEST_H_
#define _SWEETGREEN_TEST_H_

#include "restrict_include.h"
#include "append.h"
#include "format.h"

typedef void (*sweetgreen_test_function)(struct sweetgreen_test*);

struct sweetgreen_test {
	const char* module_name;
	const char* name;
	
	struct sweetgreen_assertion* first;
	struct sweetgreen_assertion* last;
	size_t size;
	sweetgreen_test_function function;
	struct sweetgreen_test* next;
};

sweetgreen_declare_append(test, struct sweetgreen_test*, struct sweetgreen_assertion*);

struct sweetgreen_test* sweetgreen_test_new(sweetgreen_test_function function, const char* module_name, const char* name) {
	struct sweetgreen_test* test = (struct sweetgreen_test*)malloc(sizeof(struct sweetgreen_test));
	test->module_name = module_name;
	test->name = name;
	test->first = NULL;
	test->last = NULL;
	test->size = 0;
	test->function = function;
	test->next = NULL;
	return test;
}

int sweetgreen_test_test(FILE* output, struct sweetgreen_test* test) {
	sweetgreen_print_color(output, "%s", SWEETGREEN_CYANBOLD, test->module_name);
	fprintf(output, " - ");
	sweetgreen_print_color(output, "%s", SWEETGREEN_BLUEBOLD, test->name);
	fprintf(output, ":\n");

	sweetgreen_print_color(output, "execution:\n", SWEETGREEN_MAGENTA);
	test->function(test);
	sweetgreen_print_color(output, " <---- end\n", SWEETGREEN_MAGENTA);

	int result = 0;
	struct sweetgreen_assertion* assertion = test->first;
	fprintf(output, "launching ");
	sweetgreen_print_color(output, "%zu", SWEETGREEN_BOLD, test->size);
	fprintf(output, " assertion%s:\n", (test->size > 1 ? "s": ""));

	while(assertion) {
		result += sweetgreen_assertion_test(output, assertion);

		struct sweetgreen_assertion* last = assertion;
		assertion = assertion->next;
		free(last);
	}
	sweetgreen_print_color(output, "=>", SWEETGREEN_BOLD);
	fprintf(output, " ️test result: ");
	
	if(result) {
		sweetgreen_print_color(output, "FAILED\n", SWEETGREEN_REDBOLD);
	} else {
		sweetgreen_print_color(output, "PASSED\n", SWEETGREEN_GREENBOLD);
	}

	return result;
}

#endif