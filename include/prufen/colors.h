#ifndef _PRUF_COLORS_H_
#define _PRUF_COLORS_H_

#include "restrict_include.h"
#include "options.h"

#define PRUF_RED(x) "\033[31m" x "\033[0m"
#define PRUF_GREEN(x) "\033[32m" x "\033[0m"
#define PRUF_BLUE(x) "\033[34m" x "\033[0m"
#define PRUF_MAGENTA(x) "\033[35m" x "\033[0m"
#define PRUF_CYAN(x) "\033[36m" x "\033[0m"

#define PRUF_REDBOLD(x) "\033[1;31m" x "\033[0m"
#define PRUF_GREENBOLD(x) "\033[1;32m" x "\033[0m"
#define PRUF_YELLOWBOLD(x) "\033[1;33m" x "\033[0m"
#define PRUF_BLUEBOLD(x) "\033[1;34m" x "\033[0m"
#define PRUF_MAGENTABOLD(x) "\033[1;35m" x "\033[0m"
#define PRUF_CYANBOLD(x) "\033[1;36m" x "\033[0m"

#define PRUF_BOLD(x) "\033[1m" x "\033[0m"
#define PRUF_UNDERLINE(x) "\033[4m" x "\033[0m"

#define pruf_print_color(output, fmt, color, ...) fprintf(output, pruf_options__.flags & PRUF_OPTIONS_COLOR_ON ? color(fmt) : fmt , ##__VA_ARGS__)
#define pruf_write_color(output, fmt, color, ...) sprintf(output, pruf_options__.flags & PRUF_OPTIONS_COLOR_ON ? color(fmt) : fmt , ##__VA_ARGS__)

#endif
