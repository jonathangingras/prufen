#ifndef _SWEETGREEN_MAIN_H_
#define _SWEETGREEN_MAIN_H_

#include "restrict_include.h"

#define sweetgreen_main \
struct sweetgreen_testcase _ZKItestcasevarname;\
int main(int argc, char** argv) {\
	struct sweetgreen_testcase* testcase = &_ZKItestcasevarname;\
	return sweetgreen_testcase_test(stdout, testcase);\
}

#endif