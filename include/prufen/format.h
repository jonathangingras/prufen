#ifndef _PRUF_FORMAT_H_
#define _PRUF_FORMAT_H_

#include "restrict_include.h"
#include "symbols.h"
#include "colors.h"

void pruf_print_separating_line(FILE* output) {
	fprintf(output, "-------------------\n");
}

void pruf_print_separating_line_strong(FILE* output) {
	pruf_print_color(output, "\n*--------------------*\n\n", PRUF_YELLOWBOLD);
}

void pruf_fprinttimes(FILE* output, const char* seq, int times) {
	int i;
	for(i = times; i > 0; --i) {
		fprintf(output, "%s", seq);
	}
}

void pruf_print_title_star(FILE* output) {
	pruf_print_color(output, "%s", PRUF_GREENBOLD, "*");
}

void pruf_print_title(FILE* output, int testcases) {
	int intlen = 32;

	pruf_print_title_star(output); pruf_fprinttimes(output, "-", intlen); pruf_print_title_star(output);
	fprintf(output, "\n"); 
	pruf_print_color(output, "  Prüfen", PRUF_GREENBOLD);
	fprintf(output, " - launching %d testcase%s\n", testcases, testcases > 1 ? "s" : "");

	pruf_print_title_star(output); pruf_fprinttimes(output, "-", intlen); pruf_print_title_star(output);
	fprintf(output, "\n\n");
}

#endif
