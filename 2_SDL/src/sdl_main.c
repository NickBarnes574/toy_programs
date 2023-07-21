#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "comparisons.h"
#include "linked_list.h"
#include "misc.h"
#include "sdl_functions.h"
#include "utilities.h"

#define WINDOW_WIDTH  400
#define WINDOW_HEIGHT 200
#define MAX_LIST_SIZE 100
#define MIN_RAND      1
#define MAX_RAND      99
#define SCALE_X       10
#define SCALE_Y       10

void draw_state(list_t *       list,
                SDL_Renderer * renderer,
                uint32_t       idx_a,
                uint32_t       idx_b)
{
    int           index   = 0;
    list_node_t * current = list->head;
    for (u_int32_t idx = 0; idx < list->size; idx++)
    {
        if (index == idx_a)
        {
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        }
        else if (index == idx_b)
        {
            SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
        }
        else
        {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        }
        SDL_RenderDrawLine(
            renderer, index, MAX_LIST_SIZE, index, *(int *)current->data);
        current = current->next;
        index += 1;
    }
}

int main(int argc, char ** argv)
{
    (void)argc;
    (void)argv;
    int            exit_code       = E_FAILURE;
    SDL_Window *   window          = NULL;
    SDL_Renderer * renderer        = NULL;
    SDL_Event      event           = { 0 };
    bool           program_running = true;
    list_t *       list            = NULL;
    int *          number_list     = NULL;
    list_node_t *  node_a          = NULL;
    list_node_t *  node_b          = NULL;
    list_node_t *  print_node      = NULL;

    SDL_Init(SDL_INIT_EVERYTHING);

    // window = new_window("hello world!", WINDOW_WIDTH, WINDOW_HEIGHT);
    SDL_CreateWindowAndRenderer(
        100 * 10, 100 * 10, SDL_WINDOW_RESIZABLE, &window, &renderer);
    SDL_RenderSetScale(renderer, SCALE_X, SCALE_Y);

    number_list = calloc(MAX_LIST_SIZE, sizeof(int));
    if (NULL == number_list)
    {
        print_error("CMR Failure.");
        goto END;
    }

    number_list = random_int_list(MIN_RAND, MAX_RAND);
    for (int idx = 0; idx < MAX_LIST_SIZE; idx++)
    {
        printf("%d ", number_list[idx]);
    }
    printf("---------------------\n");

    list = list_new(NULL, int_comp);
    for (int idx = 0; idx < MAX_LIST_SIZE; idx++)
    {
        number_list[idx] = idx + 1;
        exit_code        = list_push_tail(list, &number_list[idx]);
        if (E_SUCCESS != exit_code)
        {
            print_error("Unable to insert number into list.");
            goto END;
        }
    }

    for (uint32_t idx_a = 1; idx_a < list->size + 1; idx_a++)
    {
        for (uint32_t idx_b = 1; idx_b < list->size + 1; idx_b++)
        {
            node_a = list_peek_position(list, idx_a);
            node_b = list_peek_position(list, idx_b);
            if ((NULL == node_a) || (NULL == node_b))
            {
                print_error("NULL node.");
                goto END;
            }

            if (ONE == list->compare_function(&node_a->data, &node_b->data))
            {
                exit_code = list_swap_nodes(list, idx_a, idx_b);
                if (E_SUCCESS != exit_code)
                {
                    print_error("Unable to swap nodes.");
                    goto END;
                }
            }

            // Clear screen
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderClear(renderer);

            // Draw the state of the sort
            draw_state(list, renderer, idx_a, idx_b);

            // Show to window
            SDL_RenderPresent(renderer);
            SDL_Delay(10);
        }
    }

    for (uint32_t idx = 1; idx < list->size + 1; idx++)
    {
        print_node = list_peek_position(list, idx);
        if (NULL == print_node)
        {
            print_error("NULL node.");
            goto END;
        }

        printf("%d ", *(int *)print_node->data);
    }

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
    SDL_DestroyRenderer(renderer);

    exit_code = E_SUCCESS;
END:
    free(number_list);
    list_delete(&list);
    SDL_Quit();
    return exit_code;
}

/*** end of file ***/
