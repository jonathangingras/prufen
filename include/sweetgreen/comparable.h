#ifndef _SWEETGREEN_COMPARABLE_H_
#define _SWEETGREEN_COMPARABLE_H_

union sweetgreen_comparable_t {
	void* address;
	long integral_type;
};

typedef void (* sweetgreen_comparable_formatter)(char*, union sweetgreen_comparable_t);

void sweetgreen_comparable_format_boolean(char* string_output, union sweetgreen_comparable_t comparable) {
	sprintf(string_output, "%s", comparable.integral_type ? "true": "false");
}

void sweetgreen_comparable_format_integer(char* string_output, union sweetgreen_comparable_t comparable) {
	sprintf(string_output, "%ld", comparable.integral_type);
}

void sweetgreen_comparable_format_pointer(char* string_output, union sweetgreen_comparable_t comparable) {
	if(comparable.address) {
		sprintf(string_output, "%p", comparable.address);
	} else {
		sprintf(string_output, "NULL");
	}
}

void sweetgreen_comparable_format_string(char* string_output, union sweetgreen_comparable_t comparable) {
	sprintf(string_output, "\"%s\"", (const char*)comparable.address);
}

#endif
