#ifndef _SWEETGREEN_AROUND_H_
#define _SWEETGREEN_AROUND_H_

#include "restrict_include.h"
#include "pre_main.h"

#define sweetgreen_setup \
	void sweetgreen_setup_function();\
	SWEETGREEN_PRE_MAIN(sweetgreen_setup_function_insert) {\
		_ZKItestcasevarname.setup = &sweetgreen_setup_function;\
	}\
	void sweetgreen_setup_function()

#define sweetgreen_teardown \
	void sweetgreen_teardown_function();\
	SWEETGREEN_PRE_MAIN(sweetgreen_teardown_function_insert) {\
		_ZKItestcasevarname.teardown = &sweetgreen_teardown_function;\
	}\
	void sweetgreen_teardown_function()

#endif