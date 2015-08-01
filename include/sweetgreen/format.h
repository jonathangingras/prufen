#ifndef _SWEETGREEN_FORMAT_H_
#define _SWEETGREEN_FORMAT_H_

#include "restrict_include.h"

#include "symbols.h"
#include "colors.h"

void sweetgreen_print_separating_line(FILE* output) {
	fprintf(output, "-------------------\n");
}

#endif