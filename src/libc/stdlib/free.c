
#include <stdlib.h>

void free(void *ptr)
{
    _Anvil_realloc(ptr, 0);
}