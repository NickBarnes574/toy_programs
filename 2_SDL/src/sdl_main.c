#include <stdio.h>
#include <stdlib.h>

#include "sdl_functions.h"
#include "utilities.h"

#define WINDOW_WIDTH  400
#define WINDOW_HEIGHT 200
#define MS_DELAY      10000

int main(int argc, char ** argv)
{
    (void)argc;
    (void)argv;
    int          exit_code = E_FAILURE;
    SDL_Window * window    = NULL;

    SDL_Init(SDL_INIT_EVERYTHING);

    window = SDL_CreateWindow("HELLO WORLD!",
                              SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED,
                              WINDOW_WIDTH,
                              WINDOW_HEIGHT,
                              SDL_WINDOW_RESIZABLE);

    if (NULL == window)
    {
        fprintf(stderr,
                "Unable to initialize window.\nSDL ERROR: %s\n",
                SDL_GetError());
        goto END;
    }

    SDL_Delay(MS_DELAY);
    SDL_DestroyWindow(window);
    exit_code = E_SUCCESS;
END:
    SDL_Quit();
    return exit_code;
}

/*** end of file ***/
