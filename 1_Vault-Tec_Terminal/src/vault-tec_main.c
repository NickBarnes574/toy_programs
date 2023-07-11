#include "utilities.h"
#include "vault-tec_functions.h"

int main(int argc, char ** argv)
{
    int exit_code = E_FAILURE;

    (void)argc;
    (void)argv;

    exit_code = start_terminal();
    if (E_SUCCESS != exit_code)
    {
        print_error("failure.", __func__);
        goto END;
    }

    exit_code = E_SUCCESS;
END:
    return exit_code;
}

/*** end of file ***/
