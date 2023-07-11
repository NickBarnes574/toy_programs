#define _POSIX_C_SOURCE 199309L

#include <stdio.h>
#include <time.h>

#include "utilities.h"
#include "vault-tec_functions.h"

#define SLEEP_LENGTH 20000000

int start_terminal(void)
{
    int exit_code = E_FAILURE;

    char message[] =
        "Please enter your username:\n\
    Dogmeat\n\
\n\
Please enter your password:\n\
\n\
Access granted. Welcome, Dogmeat.\n\
\n\
ROBCO INDUSTRIES (TM) TERMLINK PROTOCOL\n\
ENTER PASSWORD NOW\n\
\n\
Accessing mainframe...\n\
\n\
Welcome to Vault-Tec Terminal!\n\
\n\
    list vaults\n\
\n\
Vault ID Location Status\n\
101 Washington, D.C. Operational\n\
106 California Sealed\n\
112 Maryland Abandoned\n\
118 New York Experimental\n\
122 Texas Operational\n\
\n\
    open vault 101\n\
\n\
Vault 101 Information\n\
\n\
Status: Operational\n\
Population: 1000\n\
Overseer: Alphonse Almodovar\n\
Location: Washington, D.C.\n\
\n\
    view security logs\n\
\n\
Security Logs\n\
Entry Date Event\n\
07/03/2277 Intrusion detected in sector B\n\
07/06/2277 Security breach in armory\n\
07/09/2277 Suspicious activity in the atrium\n\
\n\
    exit\n\
\n\
Logging out...\n\
\n\
Thank you for using the Vault-Tec Terminal System.\n\
ROBCO INDUSTRIES (TM) TERMLINK PROTOCOL\n\
TERMINAL LOGGED OFF";

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
