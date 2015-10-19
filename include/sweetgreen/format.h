#ifndef _SWEETGREEN_FORMAT_H_
#define _SWEETGREEN_FORMAT_H_

#include "restrict_include.h"
#include "symbols.h"
#include "colors.h"

void sweetgreen_print_separating_line(FILE* output) {
	fprintf(output, "-------------------\n");
}

void sweetgreen_print_separating_line_strong(FILE* output) {
	sweetgreen_print_color(output, "\n*--------------------*\n\n", SWEETGREEN_YELLOWBOLD);
}

void sweetgreen_fprinttimes(FILE* output, const char* seq, int times) {
	int i;
	for(i = times; i > 0; --i) {
		fprintf(output, "%s", seq);
	}
}

void sweetgreen_print_title_star(FILE* output) {
	sweetgreen_print_color(output, "%s", SWEETGREEN_GREENBOLD, "*");
}

void sweetgreen_print_title(FILE* output, int testcases) {
	int intlen = 35;

	sweetgreen_print_title_star(output); sweetgreen_fprinttimes(output, "-", intlen); sweetgreen_print_title_star(output);
	fprintf(output, "\n"); 
	sweetgreen_print_color(output, "  SweetGreen", SWEETGREEN_GREENBOLD);
	fprintf(output, " - launching %d testcase%s\n", testcases, testcases > 1 ? "s" : "");

	sweetgreen_print_title_star(output); sweetgreen_fprinttimes(output, "-", intlen); sweetgreen_print_title_star(output);
	fprintf(output, "\n\n");
}

#endif