#ifndef _PRUF_TEST_H_
#define _PRUF_TEST_H_

#include "restrict_include.h"
#include "append.h"
#include "format.h"

#include <unistd.h>
#include <signal.h>
#include <sys/fcntl.h>
#include <sys/wait.h>

typedef void (*pruf_test_function)(struct pruf_test*);

struct pruf_test {
	const char* module_name;
	const char* name;
	
	struct pruf_assertion* first;
	struct pruf_assertion* last;
	size_t size;
	pruf_test_function function;
	struct pruf_test* next;
};

pruf_declare_append(test, struct pruf_test*, struct pruf_assertion*);

struct pruf_test* pruf_test_new(pruf_test_function function, const char* module_name, const char* name) {
	struct pruf_test* test = (struct pruf_test*)malloc(sizeof(struct pruf_test));
	test->module_name = module_name;
	test->name = name;
	test->first = NULL;
	test->last = NULL;
	test->size = 0;
	test->function = function;
	test->next = NULL;
	return test;
}

int pruf_test_dispatch(FILE* output, struct pruf_test* test, int result_in) {
        int result = 1, read_code;
        
        /* read in a blocking way, we cannot use wait here, because we must nohang (see main.h) 
         * in order to keep a text file output away from the scheduler concurrency */
        read_code = read(result_in, &result, sizeof(int)); 
        close(result_in);

        if(read_code <= 0) {
                pruf_print_color(output, "COULD NOT READ RESULT: ", PRUF_BOLD);
                pruf_print_color(output, "possible SEGFAULT!\n", PRUF_REDBOLD);
        }

        return result;
}

int pruf_test_execute(FILE* output, struct pruf_test* test) {
	int result = 0;

        pruf_print_color(output, "execution:\n", PRUF_MAGENTA);
	test->function(test);
        pruf_print_color(output, " <---- end\n", PRUF_MAGENTA);

	struct pruf_assertion* assertion = test->first;
	fprintf(output, "launching ");
	pruf_print_color(output, "%zu", PRUF_BOLD, test->size);
	fprintf(output, " assertion%s:\n", (test->size > 1 ? "s": ""));
	
	while(assertion) {
		result += pruf_assertion_test(output, assertion);
	
		struct pruf_assertion* last = assertion;
		assertion = assertion->next;
		pruf_assertion_destroy(last);
                free(last);
	}

	return result;
}

int pruf_test_forked_execute(FILE* output, struct pruf_test* test) {
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

                child_result = pruf_test_execute(output, test);
                fflush(output);
                fflush(stderr);
                
                write(result_pipe[1], &child_result, sizeof(int));
                close(result_pipe[1]);

                _exit(child_result);
	}

	return pruf_test_dispatch(output, test, result_pipe[0]);
}

int pruf_test_test(FILE* output, struct pruf_test* test) {
	int result;

	pruf_print_color(output, "%s", PRUF_CYANBOLD, test->module_name);
	fprintf(output, " - ");
	pruf_print_color(output, "%s", PRUF_BLUEBOLD, test->name);
	fprintf(output, ":\n");

	result = pruf_options__.test_executer(output, test);
        
	pruf_print_color(output, "=>", PRUF_BOLD);
	fprintf(output, " ️test result: ");
	if(result) {
		pruf_print_color(output, "FAILED\n", PRUF_REDBOLD);
	} else {
		pruf_print_color(output, "PASSED\n", PRUF_GREENBOLD);
	}

	return result;
}

#endif
