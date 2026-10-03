#include <stdio.h>
#include "dynarray.h"

int main(void)
{
    DynArray *a = da_create();
    if (a == NULL) 
    { 
        printf("create failed\n"); 
        return 1; 
    }
    for (int i = 0; i < 10; i++)
    {
        if (da_push(a, i * i) != 0)
        { 
            printf("push failed\n"); 
            return 1; 
        }
    }
    printf("size = %zu\n", da_size(a));
    for (size_t i=0;i<da_size(a);i++) 
    {
        int v = -1;
        if (da_get(a, i, &v) == 0) 
        {
            printf("%zu: %d\n", i, v);
        }
    }
    printf("out of range test: %d\n", da_get(a, 999, NULL));
    da_destroy(a);
    return 0;
}
