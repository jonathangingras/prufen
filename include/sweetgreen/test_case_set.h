#ifndef _SWEETGREEN_TEST_CASE_SET_H_
#define _SWEETGREEN_TEST_CASE_SET_H_

#include "restrict_include.h"
#include "test_case.h"
#include "append.h"

struct sweetgreen_testcase_node {
	char* name;
	struct sweetgreen_testcase* testcase;
	struct sweetgreen_testcase_node* next;
};

struct sweetgreen_testcase_set {
	struct sweetgreen_testcase_node* first;
	struct sweetgreen_testcase_node* last;
	size_t size;
};

sweetgreen_declare_append(testcase_set, struct sweetgreen_testcase_set, struct sweetgreen_testcase_node);



#endif