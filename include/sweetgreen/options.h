#ifndef _SWEETGREEN_OPTIONS_H_
#define _SWEETGREEN_OPTIONS_H_

#include "restrict_include.h"
#include "format.h"

void sweetgreen_options_parse(int argc, char** argv) {
	int arg;
	for(arg = 0; arg < argc; ++arg) {
		if(!strcmp("--no-color", argv[arg])) {
			SWEETGREEN_COLOR_ON = 0;
		}
	}
}

#endif