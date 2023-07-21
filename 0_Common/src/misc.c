#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "misc.h"
#include "utilities.h"

int generate_random_int(int min, int max)
{
    // NOLINTNEXTLINE
    int random_int = min + rand() % (max - min + 1);

    return random_int;
}

int * random_int_list(int min, int max)
{
    int * number_list = NULL;
    int   range       = 0;
    int   idx_a       = 0;
    int   idx_b       = 0;
    int   temp        = 0;

    range = (max - min) + 1;

    number_list = calloc(range, sizeof(int));

    for (int idx = 0; idx < range; idx++)
    {
        number_list[idx] = min + idx;
    }

    for (idx_a = (range - 1); 0 < idx_a; idx_a--)
    {
        // Swap element with a random lower index
        idx_b              = rand() % (idx_a + 1);
        temp               = number_list[idx_a];
        number_list[idx_a] = number_list[idx_b];
        number_list[idx_b] = temp;
    }

    return number_list;
}
