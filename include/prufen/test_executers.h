#ifndef _PRUF_TEST_EXECUTERS_H_
#define _PRUF_TEST_EXECUTERS_H_

#include "restrict_include.h"

int pruf_test_forked_execute(FILE* output, struct pruf_test* test);
int pruf_test_execute(FILE* output, struct pruf_test* test);

#endif
