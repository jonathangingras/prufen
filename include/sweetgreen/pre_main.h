#ifndef _SWEETGREEN_PRE_MAIN_H_
#define _SWEETGREEN_PRE_MAIN_H_

#if defined(__GNUC__)
	#define SWEETGREEN_PRE_MAIN(function_name)\
		__attribute__((constructor)) void function_name()
#elif defined(_MSC_VER)
	#define SWEETGREEN_PRE_MAIN(function_name)\
		static void __cdecl function_name();\
		__declspec(allocate(".CRT$XCU")) void (__cdecl * function_name##_)() = function_name;\
		static void __cdecl function_name()
#endif

#endif