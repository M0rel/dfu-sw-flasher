#include <stdarg.h>
#include <stdio.h>

#include "logger.h"

void log_write(int verbosity, const char *fmt, ...)
{
        if (NULL == fmt) {
                return;
        }

        va_list args;
        va_start(args, fmt);

        if (VERBOSITY_LIMIT >= verbosity) {
                vfprintf(stdout, fmt, args);
        }

        va_end(args);
}
