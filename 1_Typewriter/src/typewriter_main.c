#include "typewriter_functions.h"
#include "utilities.h"

int main(int argc, char ** argv)
{
    int exit_code = E_FAILURE;

    (void)argc;
    (void)argv;

    exit_code = typewriter();
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
