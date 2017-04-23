#ifndef _SWEETGREEN_OPTIONS_H_
#define _SWEETGREEN_OPTIONS_H_

#include "restrict_include.h"
#include "test_executers.h"
#include "types.h"

#include <limits.h>
#include <string.h>

#include <unistd.h>
#include <sys/fcntl.h>
#include <sys/stat.h>

#define SWEETGREEN_OPTIONS_COLOR_ON 1

struct sweetgreen_options {
	int (*test_executer)(FILE* output, struct sweetgreen_test* test);
	unsigned long flags;
	FILE *output_file;
};

static struct sweetgreen_options sweetgreen_options__;

struct sweetgreen_option {
	int (*validate)(int argc, const char **argv, int index);
	void (*set)(struct sweetgreen_options* options, const char *arg_str);
};

//arguments

// no color
int sweetgreen_options_validate_nocolor(int argc, const char **argv, int index) {
  return !strcmp("--no-color", argv[index]) || !strcmp("-n", argv[index]);
}

void sweetgreen_options_set_nocolor(struct sweetgreen_options* options, const char *arg_str) {
	options->flags ^= SWEETGREEN_OPTIONS_COLOR_ON;
}

// output file
int sweetgreen_options_validate_output(int argc, const char **argv, int index) {
	return !strcmp("--output", argv[index]) || !strcmp("-o", argv[index]);
}

void sweetgreen_options_set_output(struct sweetgreen_options* options, const char *arg_str) {
	if(!arg_str || arg_str[0] == '-') {
		fprintf(stderr, "option: `-o': no filename provided!\n");
		return;
	}
	int output = open(arg_str, O_CREAT | O_TRUNC | O_WRONLY, S_IRUSR | S_IWUSR);
	dup2(output, STDOUT_FILENO);
}

// no fork
int sweetgreen_options_validate_nofork(int argc, const char **argv, int index) {
	return !strcmp("--no-fork", argv[index]) || !strcmp("-f", argv[index]);
}

void sweetgreen_options_set_nofork(struct sweetgreen_options* options, const char *arg_str) {
	options->test_executer = &sweetgreen_test_execute;
}


//iterating over arguments

int sweetgreen_options_consider_arg(int argc, const char **argv, int index) {
	return argv[index][0] == '-';
}

int sweetgreen_options_iterate(struct sweetgreen_options* options, int argc, const char **argv) {
	const static struct sweetgreen_option possible_options[] = {
		{ .validate = &sweetgreen_options_validate_nocolor, .set = &sweetgreen_options_set_nocolor },
		{ .validate = &sweetgreen_options_validate_output,  .set = &sweetgreen_options_set_output  },
                { .validate = &sweetgreen_options_validate_nofork,  .set = &sweetgreen_options_set_nofork  }
	};

	int argument_index, option_index;
	for(argument_index = 0; argument_index < argc; ++argument_index) {
		char arg_set = 0;
		for(option_index = 0; option_index < 3; ++option_index) {
			if(possible_options[option_index].validate(argc, argv, argument_index)) {
				possible_options[option_index].set(options, argument_index + 1 < argc ? argv[argument_index + 1] : NULL);
				arg_set = 1;
				break;
			}
		}
		if(!arg_set && sweetgreen_options_consider_arg(argc, argv, argument_index)) {
			fprintf(stderr, "option: `%s': no such option available!\n", argv[argument_index]);
		}
	}

	return 0;
}

// parsing

int sweetgreen_options_parse(struct sweetgreen_options* options, int argc, const char** argv) {
	options->output_file = stdout;
	options->flags = ULONG_MAX;
        options->test_executer = &sweetgreen_test_forked_execute;

	if(sweetgreen_options_iterate(options, argc, argv)) {
		return -1;
	}
	return 0;
}

void sweetgreen_options_destroy(struct sweetgreen_options *options) {
	fclose(options->output_file);
}

#endif
