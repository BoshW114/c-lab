#ifndef DYNARRAY_H
#define DYNARRAY_H

#include <stddef.h>

/* A dynamically growing array of int.
 * size     = number of elements currently stored
 * capacity = number of elements the allocated block can hold (size <= capacity)
 */
typedef struct
{
    int *data;
    size_t size;
    size_t capacity;
} DynArray;

/* Create an empty array. Returns NULL on allocation failure. */
DynArray *da_create(void);

/* Free the array and all memory it owns. Accepts NULL. */
void da_destroy(DynArray *a);

/* Append value. Returns 0 on success, -1 on failure
 * (NULL argument or realloc failure; the array is left unchanged). */
int da_push(DynArray *a, int value);

/* Read element i into *out.
 * Returns 0 on success, -1 if a is NULL, out is NULL, or i is out of range.
 * On failure *out is not written. */
int da_get(const DynArray *a, size_t i, int *out);

/* Number of stored elements. Returns 0 for a NULL array. */
size_t da_size(const DynArray *a);

#endif /* DYNARRAY_H */
