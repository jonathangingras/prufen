#ifndef _SWEETGREEN_MAIN_H_
#define _SWEETGREEN_MAIN_H_

#include "restrict_include.h"
#include "testcase.h"
#include "testcase_set.h"
#include "pre_main.h"

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

#define sweetgreen_main \
int main(int argc, char** argv) { \
	return sweetgreen_testcase_set_run(stdout, sweetgreen_testcase_set_global()); \
}
#endif