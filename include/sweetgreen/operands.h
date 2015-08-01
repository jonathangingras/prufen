#ifndef _SWEETGREEN_OPERANDS_H_
#define _SWEETGREEN_OPERANDS_H_

#include "restrict_include.h"

struct sweetgreen_operands {
	void* first;
	const char* first_name;
	void* second;
	const char* second_name;
	void* third;
	const char* third_name;
};

#endif