#ifndef _SWEETGREEN_TEST_EXECUTERS_H_
#define _SWEETGREEN_TEST_EXECUTERS_H_

#include "restrict_include.h"

int sweetgreen_test_forked_execute(FILE* output, struct sweetgreen_test* test);
int sweetgreen_test_execute(FILE* output, struct sweetgreen_test* test);

#endif
