#ifndef _SWEETGREEN_TEST_CASE_SET_H_
#define _SWEETGREEN_TEST_CASE_SET_H_

#include "restrict_include.h"
#include "testcase.h"
#include "append.h"
#include "format.h"

struct sweetgreen_testcase_node {
	struct sweetgreen_testcase* testcase;
	struct sweetgreen_testcase_node* next;
};

struct sweetgreen_testcase_node* sweetgreen_testcase_node_new(struct sweetgreen_testcase* testcase) {
	struct sweetgreen_testcase_node* node = (struct sweetgreen_testcase_node*)malloc(sizeof(struct sweetgreen_testcase_node));
	node->testcase = testcase;
	node->next = NULL;
	return node;
}

struct sweetgreen_testcase_set {
	struct sweetgreen_testcase_node* first;
	struct sweetgreen_testcase_node* last;
	size_t size;
};

sweetgreen_declare_append(testcase_set, struct sweetgreen_testcase_set*, struct sweetgreen_testcase_node*);

struct sweetgreen_testcase_set* sweetgreen_testcase_set_init(struct sweetgreen_testcase_set* set) {
	set->first = NULL;
	set->last = NULL;
	set->size = 0;
	return set;
}

struct sweetgreen_testcase* sweetgreen_testcase_set_create_node(struct sweetgreen_testcase_set* set, const char* name) {
	struct sweetgreen_testcase* testcase = sweetgreen_testcase_new(name);
	struct sweetgreen_testcase_node* node = sweetgreen_testcase_node_new(testcase);
	sweetgreen_testcase_set_append(set, node);
	return testcase;
}

struct sweetgreen_testcase* sweetgreen_testcase_set_find_or_create_by_name(struct sweetgreen_testcase_set* set, const char* name) {
	struct sweetgreen_testcase_node* set_iterator = set->first;
	while(set_iterator) {
		if(!strcmp(name, set_iterator->testcase->name)) {
			break;
		}
		set_iterator = set_iterator->next;
	}
	return set_iterator ? set_iterator->testcase : sweetgreen_testcase_set_create_node(set, name);
}

int sweetgreen_testcase_set_run(FILE* output, struct sweetgreen_testcase_set* set) {
	struct sweetgreen_testcase_node* set_iterator = set->first;
	int result = 0;
	while(set_iterator) {
		result += sweetgreen_testcase_test(output, set_iterator->testcase);
		struct sweetgreen_testcase_node* to_free = set_iterator;
		set_iterator = set_iterator->next;
		free(to_free);
		if(set_iterator) { sweetgreen_print_separating_line_strong(output); }
	}
	return result;
}

#endif
