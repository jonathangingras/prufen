#ifndef _SWEETGREEN_FORMAT_H_
#define _SWEETGREEN_FORMAT_H_

#include <math.h>
#include "restrict_include.h"

#include "symbols.h"
#include "colors.h"

void sweetgreen_print_separating_line(FILE* output) {
	fprintf(output, "-------------------\n");
}

void sweetgreen_print_separating_line_strong(FILE* output) {
	fprintf(output, SWEETGREEN_YELLOWBOLD("*--------------------*\n"));
}

int sweetgreen_base10strlen(long integral) {
	if(integral) {
		long len = floor(log10(integral)) + 1;
		return integral < 0 ? len + 1 : len;
	}
	return 1;
}

void sweetgreen_fprinttimes(FILE* output, const char* seq, int times) {
	int i;
	for(i = times; i > 0; --i) {
		fprintf(output, "%s", seq);
	}
}

void sweetgreen_print_title(FILE* output, int testcases) {
	int intlen = sweetgreen_base10strlen(testcases);

	fprintf(output, SWEETGREEN_GREENBOLD("*")); sweetgreen_fprinttimes(output, "-", 35 + intlen); fprintf(output, SWEETGREEN_GREENBOLD("*") "\n");

	fprintf(output,
		"| " SWEETGREEN_GREENBOLD("SweetGreen") " - launching %d testcase%s |\n",
		testcases, testcases > 1 ? "s" : ""
	);

	fprintf(output, SWEETGREEN_GREENBOLD("*")); sweetgreen_fprinttimes(output, "-", 35 + intlen); fprintf(output, SWEETGREEN_GREENBOLD("*") "\n");
}

#endif