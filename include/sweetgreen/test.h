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

int sweetgreen_test_dispatch(FILE* output, struct sweetgreen_test* test, int result_in) {
        int result = 1, read_code;
        
        /* read in a blocking way, we cannot use wait here, because we must nohang (see main.h) 
         * in order to keep a text file output away from the scheduler concurrency */
        read_code = read(result_in, &result, sizeof(int)); 
        close(result_in);

        if(read_code <= 0) {
                sweetgreen_print_color(output, "COULD NOT READ RESULT: ", SWEETGREEN_BOLD);
                sweetgreen_print_color(output, "possible SEGFAULT!\n", SWEETGREEN_REDBOLD);
        }

        return result;
}

int sweetgreen_test_execute(FILE* output, struct sweetgreen_test* test) {
	int result = 0;

        sweetgreen_print_color(output, "execution:\n", SWEETGREEN_MAGENTA);
	test->function(test);
        sweetgreen_print_color(output, " <---- end\n", SWEETGREEN_MAGENTA);

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

	return result;
}

int sweetgreen_test_forked_execute(FILE* output, struct sweetgreen_test* test) {
	int result_pipe[2];
        pid_t pid;

        fflush(output);

	if(pipe(result_pipe)) {
                fprintf(output, "Could not pipe, aborting.\n");
		fprintf(stderr, "Could not pipe, aborting.\n");
                exit(1);
	}

	if((pid = fork())) {
	        close(result_pipe[1]);
        } else {
		int child_result = 0;

                close(result_pipe[0]);

                child_result = sweetgreen_test_execute(output, test);
                fflush(output);
                fflush(stderr);
                
                write(result_pipe[1], &child_result, sizeof(int));
                close(result_pipe[1]);

                _exit(child_result);
	}

	return sweetgreen_test_dispatch(output, test, result_pipe[0]);
}

int sweetgreen_test_test(FILE* output, struct sweetgreen_test* test) {
	int result;

	sweetgreen_print_color(output, "%s", SWEETGREEN_CYANBOLD, test->module_name);
	fprintf(output, " - ");
	sweetgreen_print_color(output, "%s", SWEETGREEN_BLUEBOLD, test->name);
	fprintf(output, ":\n");

	result = sweetgreen_options__.test_executer(output, test);
        
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
