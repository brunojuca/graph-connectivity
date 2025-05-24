#include "utils.h"

#include <stdlib.h>
#include <stdio.h>

int throwInputError()
{
    fprintf(stderr, "Error reading input\n");
    exit(1);
}

int throwMallocError()
{
    fprintf(stderr, "Error in memory allocation\n");
    exit(1);
}
