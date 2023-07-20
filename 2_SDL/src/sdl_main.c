#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "sdl_functions.h"
#include "utilities.h"

#define WINDOW_WIDTH  400
#define WINDOW_HEIGHT 200

int main(int argc, char ** argv)
{
    (void)argc;
    (void)argv;
    int          exit_code       = E_FAILURE;
    SDL_Window * window          = NULL;
    SDL_Event    event           = { 0 };
    bool         program_running = true;

    SDL_Init(SDL_INIT_EVERYTHING);

    window = new_window("hello world!", WINDOW_WIDTH, WINDOW_HEIGHT);

    while (true == program_running)
    {
        while (SDL_PollEvent(&event))
        {
            if (SDL_QUIT == event.type)
            {
                program_running = false;
                break;
            }
        }
    }

    SDL_DestroyWindow(window);

    exit_code = E_SUCCESS;
END:
    SDL_Quit();
    return exit_code;
}

/*** end of file ***/
