#include <stdio.h>
#include <stdlib.h>

#include "utilities.h"

void print_error(const char * p_message, const char * p_func_name)
{

    const char * red    = "\x1b[31m";
    const char * yellow = "\x1b[33m";
    const char * reset  = "\x1b[0m";
    /* [ACTION]: Suppressing fprintf() error.
     * [JUSTIFICATION]: Result inconsequential to any further operations.
     */
    // NOLINTNEXTLINE
    fprintf(stderr,
            "%s[ERROR]%s %s%s()%s: %s\n",
            red,
            reset,
            yellow,
            p_func_name,
            reset,
            p_message);
}

void print_errno(const char * p_message, char * p_errno)
{
    /* [ACTION]: Suppressing fprintf() error.
     * [JUSTIFICATION]: Result inconsequential to any further operations.
     */
    // NOLINTNEXTLINE
    fprintf(stderr, "[ERROR]: %s\n[errno]: %s\n", p_message, p_errno);
}

/*** end of file ***/
