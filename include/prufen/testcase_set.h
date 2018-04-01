#ifndef _PRUF_TEST_CASE_SET_H_
#define _PRUF_TEST_CASE_SET_H_

#include "restrict_include.h"
#include "testcase.h"
#include "append.h"
#include "format.h"

struct pruf_testcase_node {
	struct pruf_testcase* testcase;
	struct pruf_testcase_node* next;
};

struct pruf_testcase_node* pruf_testcase_node_new(struct pruf_testcase* testcase) {
	struct pruf_testcase_node* node = (struct pruf_testcase_node*)malloc(sizeof(struct pruf_testcase_node));
	node->testcase = testcase;
	node->next = NULL;
	return node;
}

struct pruf_testcase_set {
	struct pruf_testcase_node* first;
	struct pruf_testcase_node* last;
	size_t size;
};

pruf_declare_append(testcase_set, struct pruf_testcase_set*, struct pruf_testcase_node*);

struct pruf_testcase_set* pruf_testcase_set_init(struct pruf_testcase_set* set) {
	set->first = NULL;
	set->last = NULL;
	set->size = 0;
	return set;
}

struct pruf_testcase* pruf_testcase_set_create_node(struct pruf_testcase_set* set, const char* name) {
	struct pruf_testcase* testcase = pruf_testcase_new(name);
	struct pruf_testcase_node* node = pruf_testcase_node_new(testcase);
	pruf_testcase_set_append(set, node);
	return testcase;
}

struct pruf_testcase* pruf_testcase_set_find_or_create_by_name(struct pruf_testcase_set* set, const char* name) {
	struct pruf_testcase_node* set_iterator = set->first;
	while(set_iterator) {
		if(!strcmp(name, set_iterator->testcase->name)) {
			break;
		}
		set_iterator = set_iterator->next;
	}
	return set_iterator ? set_iterator->testcase : pruf_testcase_set_create_node(set, name);
}

int pruf_testcase_set_run(FILE* output, struct pruf_testcase_set* set) {
	struct pruf_testcase_node* set_iterator = set->first;
	int result = 0;
	while(set_iterator) {
		result += pruf_testcase_test(output, set_iterator->testcase);
		struct pruf_testcase_node* to_free = set_iterator;
		set_iterator = set_iterator->next;
		free(to_free);
		if(set_iterator) { pruf_print_separating_line_strong(output); }
	}
	return result;
}

#endif
