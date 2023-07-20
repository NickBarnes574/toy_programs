#include "sdl_functions.h"
#include "utilities.h"

SDL_Window * new_window(const char * name, int width, int height)
{
    SDL_Window * window = NULL;

    if (NULL == name)
    {
        print_error("No name provided.");
        goto END;
    }

    if ((1 > width) || (1 > height))
    {
        print_error("Width and height must be greater than 0.");
        goto END;
    }

    window = SDL_CreateWindow(name,
                              SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED,
                              width,
                              height,
                              SDL_WINDOW_RESIZABLE);

    if (NULL == window)
    {
        fprintf(stderr,
                "Unable to initialize window.\nSDL ERROR: %s\n",
                SDL_GetError());
        goto END;
    }

END:
    return window;
}
