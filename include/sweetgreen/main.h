#ifndef _SWEETGREEN_MAIN_H_
#define _SWEETGREEN_MAIN_H_

#include "restrict_include.h"
#include "testcase.h"
#include "testcase_set.h"
#include "pre_main.h"
#include "format.h"
#include "options.h"

#include <signal.h>

struct sweetgreen_testcase_set* sweetgreen_testcase_set_global() {
	static struct sweetgreen_testcase_set set;
	return &set;
}
SWEETGREEN_PRE_MAIN(sweetgreen_testcase_set_global_init) {
	sweetgreen_testcase_set_init(sweetgreen_testcase_set_global());
}

struct sweetgreen_testcase* sweetgreen_testcase_static_get(const char* name) {
	return sweetgreen_testcase_set_find_or_create_by_name(sweetgreen_testcase_set_global(), name);
}

void sweetgreen_sigchld(int sig) {
        while(waitpid(-1, 0, WNOHANG) > 0);
}

#define sweetgreen_main \
int main(int argc, char** argv) { \
	int ret; \
	signal(SIGCHLD, &sweetgreen_sigchld); \
        if(sweetgreen_options_parse(&sweetgreen_options__, argc, (const char **)argv)) { return 1; } \
	sweetgreen_print_title(sweetgreen_options__.output_file, sweetgreen_testcase_set_global()->size); \
	ret = sweetgreen_testcase_set_run(sweetgreen_options__.output_file, sweetgreen_testcase_set_global()); \
	sweetgreen_options_destroy(&sweetgreen_options__); \
	return ret; \
}
#endif
