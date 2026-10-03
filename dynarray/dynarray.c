#include <stdlib.h>
#include "dynarray.h"

/* Initial capacity. Small enough to be cheap, large enough that the
 * first few pushes do not trigger a reallocation. */
#define DA_INIT_CAPACITY 4

DynArray *da_create(void)
{
    DynArray *a = malloc(sizeof(DynArray));
    if (a == NULL)
    {
        return NULL;
    }

    a->capacity = DA_INIT_CAPACITY;
    a->size = 0;
    a->data = malloc(a->capacity * sizeof(int));
    if (a->data == NULL)
    {
        /* Roll back: the struct was already allocated. */
        free(a);
        return NULL;
    }
    return a;
}

void da_destroy(DynArray *a)
{
    if (a == NULL)
    {
        return;
    }
    /* Order matters: free the buffer before the struct that points to it. */
    free(a->data);
    free(a);
}

int da_push(DynArray *a, int value)
{
    if (a == NULL)
    {
        return -1;
    }

    if (a->size == a->capacity)
    {
        /* Grow geometrically; doubling gives amortised O(1) per push. */
        size_t new_cap = 2 * a->capacity;
        /* Keep the result in a temporary: on failure the original
         * pointer must stay valid so the array is not corrupted. */
        int *new_data = realloc(a->data, new_cap * sizeof(int));
        if (new_data == NULL)
        {
            return -1;
        }
        a->data = new_data;
        a->capacity = new_cap;
    }

    a->data[a->size] = value;
    a->size++;
    return 0;
}

int da_get(const DynArray *a, size_t i, int *out)
{
    if (a == NULL || out == NULL)
    {
        return -1;
    }
    if (i >= a->size)
    {
        return -1;
    }
    *out = a->data[i];
    return 0;
}

size_t da_size(const DynArray *a)
{
    if (a == NULL)
    {
        return 0;
    }
    return a->size;
}
