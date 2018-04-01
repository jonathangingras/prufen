#ifndef _PRUF_MAIN_H_
#define _PRUF_MAIN_H_

#include "restrict_include.h"
#include "testcase.h"
#include "testcase_set.h"
#include "pre_main.h"
#include "format.h"
#include "options.h"

#include <signal.h>

struct pruf_testcase_set* pruf_testcase_set_global() {
	static struct pruf_testcase_set set;
	return &set;
}
PRUF_PRE_MAIN(pruf_testcase_set_global_init) {
	pruf_testcase_set_init(pruf_testcase_set_global());
}

struct pruf_testcase* pruf_testcase_static_get(const char* name) {
	return pruf_testcase_set_find_or_create_by_name(pruf_testcase_set_global(), name);
}

void pruf_sigchld(int sig) {
        while(waitpid(-1, 0, WNOHANG) > 0);
}

#define pruf_main \
int main(int argc, char** argv) { \
	int ret = 0; \
	signal(SIGCHLD, &pruf_sigchld); \
        if(pruf_options_parse(&pruf_options__, argc, (const char **)argv)) { return 1; } \
	pruf_print_title(pruf_options__.output_file, pruf_testcase_set_global()->size); \
	ret = pruf_testcase_set_run(pruf_options__.output_file, pruf_testcase_set_global()); \
	pruf_options_destroy(&pruf_options__); \
	return ret; \
}
#endif
