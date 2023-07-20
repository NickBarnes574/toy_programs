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
