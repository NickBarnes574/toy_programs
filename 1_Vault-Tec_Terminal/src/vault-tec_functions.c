#define _POSIX_C_SOURCE 199309L

#include <stdio.h>
#include <time.h>

#include "utilities.h"
#include "vault-tec_functions.h"
#include "vault-tec_messages.h"

#define SLEEP_LENGTH 20000000

int start_terminal(void)
{
    int exit_code = E_FAILURE;

    struct timespec ts;
    ts.tv_sec  = 0;
    ts.tv_nsec = SLEEP_LENGTH;

    for (int idx = 0; message[idx] != '\0'; idx++)
    {
        putchar(message[idx]); // Print one character to 'stdout'
        fflush(stdout);        // Write immediately and clear the output buffer
        nanosleep(&ts, NULL);
    }
    putchar('\n');

    exit_code = E_SUCCESS;
    return exit_code;
}

/*** end of file ***/
