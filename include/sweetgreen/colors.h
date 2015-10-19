#ifndef _SWEETGREEN_COLORS_H_
#define _SWEETGREEN_COLORS_H_

#include "restrict_include.h"
#include "options.h"

#define SWEETGREEN_RED(x) "\033[31m" x "\033[0m"
#define SWEETGREEN_GREEN(x) "\033[32m" x "\033[0m"
#define SWEETGREEN_BLUE(x) "\033[34m" x "\033[0m"
#define SWEETGREEN_MAGENTA(x) "\033[35m" x "\033[0m"
#define SWEETGREEN_CYAN(x) "\033[36m" x "\033[0m"

#define SWEETGREEN_REDBOLD(x) "\033[1;31m" x "\033[0m"
#define SWEETGREEN_GREENBOLD(x) "\033[1;32m" x "\033[0m"
#define SWEETGREEN_YELLOWBOLD(x) "\033[1;33m" x "\033[0m"
#define SWEETGREEN_BLUEBOLD(x) "\033[1;34m" x "\033[0m"
#define SWEETGREEN_MAGENTABOLD(x) "\033[1;35m" x "\033[0m"
#define SWEETGREEN_CYANBOLD(x) "\033[1;36m" x "\033[0m"

#define SWEETGREEN_BOLD(x) "\033[1m" x "\033[0m"
#define SWEETGREEN_UNDERLINE(x) "\033[4m" x "\033[0m"

#define sweetgreen_print_color(output, fmt, color, ...) fprintf(output, sweetgreen_options__.flags & SWEETGREEN_OPTIONS_COLOR_ON ? color(fmt) : fmt , ##__VA_ARGS__)
#define sweetgreen_write_color(output, fmt, color, ...) sprintf(output, sweetgreen_options__.flags & SWEETGREEN_OPTIONS_COLOR_ON ? color(fmt) : fmt , ##__VA_ARGS__)

#endif