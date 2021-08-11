#include "core.h"

void *OOM_GUARD(void *object)
{
    if (object == NULL)
    {
        fprintf(stderr, "Out of memory.\n");
        exit(EXIT_FAILURE);
    }
    return object;
}
