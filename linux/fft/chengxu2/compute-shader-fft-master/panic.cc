#include <cstdio>
#include <cstdlib>
#include <cstdarg>

#include "panic.h"

void
panic(const char *fmt, ...)
{
    static char buf[16*1024];

    va_list ap;

    va_start(ap, fmt);
    vsprintf(buf, fmt, ap);
    va_end(ap);

    fprintf(stderr, "%s", buf);

    exit(1);
}
