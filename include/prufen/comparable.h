#ifndef _PRUF_COMPARABLE_H_
#define _PRUF_COMPARABLE_H_

union pruf_comparable_t {
	void* address;
	long integral_type;
};

typedef void (* pruf_comparable_formatter)(char*, union pruf_comparable_t);

void pruf_comparable_format_boolean(char* string_output, union pruf_comparable_t comparable) {
	sprintf(string_output, "%s", comparable.integral_type ? "true": "false");
}

void pruf_comparable_format_integer(char* string_output, union pruf_comparable_t comparable) {
	sprintf(string_output, "%ld", comparable.integral_type);
}

void pruf_comparable_format_pointer(char* string_output, union pruf_comparable_t comparable) {
	if(comparable.address) {
		sprintf(string_output, "%p", comparable.address);
	} else {
		sprintf(string_output, "NULL");
	}
}

void pruf_comparable_format_string(char* string_output, union pruf_comparable_t comparable) {
	sprintf(string_output, "\"%s\"", (const char*)comparable.address);
}

#endif
