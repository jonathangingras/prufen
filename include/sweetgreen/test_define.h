#ifndef _SWEETGREEN_TEST_DEFINE_H_
#define _SWEETGREEN_TEST_DEFINE_H_

#include "restrict_include.h"

#if defined(__GNUC__)
	#define SWEETGREEN_BEFORE_MAIN(function_name)\
		__attribute__((constructor)) void function_name()
#elif defined(_MSC_VER)
	#define SWEETGREEN_BEFORE_MAIN(function_name)\
		static void __cdecl function_name();\
		__declspec(allocate(".CRT$XCU")) void (__cdecl * function_name##_)() = function_name;\
		static void __cdecl function_name()
#endif

#define sweetgreen_test_define(module, name) \
void sweetgreen__##module##__##name(struct sweetgreen_test*);\
SWEETGREEN_BEFORE_MAIN(sweetgreen__##module##__##name##_add_to_testcase) {\
	struct sweetgreen_test* test = sweetgreen_test_new(&sweetgreen__##module##__##name, #module, #name);\
	sweetgreen_testcase_append(&_ZKItestcasevarname, test);\
}\
void sweetgreen__##module##__##name(struct sweetgreen_test* _ZKItestvarname)

#endif