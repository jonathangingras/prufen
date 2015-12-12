#ifndef _SWEETGREEN_TEST_H_
#define _SWEETGREEN_TEST_H_

#include "restrict_include.h"
#include "append.h"
#include "format.h"

#include <unistd.h>
#include <signal.h>
#include <sys/fcntl.h>
#include <sys/wait.h>

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

int sweetgreen_test_dispatch(FILE* output, struct sweetgreen_test* test, pid_t pid, int data_in) {
	int status = 0;
	waitpid(pid, &status, 0);

	if(WIFSIGNALED(status)) {
		sweetgreen_print_color(output, "SIGNAL ENDED PROCESS: ", SWEETGREEN_MAGENTA);
                
                if(WTERMSIG(status) == SIGSEGV) {
                    sweetgreen_print_color(output, "SEGFAULT!\n", SWEETGREEN_REDBOLD);
                }
                return -1;
	}

	char buffer[256];
	int len;
	memset(buffer, 0, 256);
	while((len = read(data_in, buffer, 256))) {
		fwrite(buffer, sizeof(char), len, output);
	}

	close(data_in);

        return WEXITSTATUS(status);
}

int sweetgreen_test_patch(struct sweetgreen_test* test, int data_out) {
	FILE* data_output = fdopen(data_out, "w");
	int result = 0;

	sweetgreen_print_color(data_output, "execution:\n", SWEETGREEN_MAGENTA);
	test->function(test);
	sweetgreen_print_color(data_output, " <---- end\n", SWEETGREEN_MAGENTA);

	struct sweetgreen_assertion* assertion = test->first;
	fprintf(data_output, "launching ");
	sweetgreen_print_color(data_output, "%zu", SWEETGREEN_BOLD, test->size);
	fprintf(data_output, " assertion%s:\n", (test->size > 1 ? "s": ""));
	
	while(assertion) {
		result += sweetgreen_assertion_test(data_output, assertion);
	
		struct sweetgreen_assertion* last = assertion;
		assertion = assertion->next;
		free(last);
	}

	fflush(data_output);

	fclose(data_output);
	close(data_out);

	return result;
}

int sweetgreen_test_execute(FILE* output, struct sweetgreen_test* test) {
	int data[2];
        pid_t pid;

	if(pipe(data)) {
		exit(1);
	}

	if((pid = fork())) {
		close(data[1]);
        } else {
		close(data[0]);
		_exit(sweetgreen_test_patch(test, data[1]));
	}

	return sweetgreen_test_dispatch(output, test, pid, data[0]);
}

int sweetgreen_test_test(FILE* output, struct sweetgreen_test* test) {
	int result;

	sweetgreen_print_color(output, "%s", SWEETGREEN_CYANBOLD, test->module_name);
	fprintf(output, " - ");
	sweetgreen_print_color(output, "%s", SWEETGREEN_BLUEBOLD, test->name);
	fprintf(output, ":\n");

	result = sweetgreen_test_execute(output, test);
        
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
