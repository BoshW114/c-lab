#ifndef LIST_H
#define LIST_H

#include <stddef.h>

/* A singly linked list of int.
 * The List struct is opaque: callers only see a pointer, so the
 * internal node layout can change without breaking client code.
 */
typedef struct List List;

/* Create an empty list. Returns NULL on allocation failure. */
List *list_create(void);

/* Free every node and the list itself. Accepts NULL. */
void list_destroy(List *l);

/* Insert value at the front. Returns 0, or -1 on NULL list / allocation failure. */
int list_push_front(List *l, int value);

/* Insert value at the back. Returns 0, or -1 on NULL list / allocation failure. */
int list_push_back(List *l, int value);

/* Read element i (0-based) into *out.
 * Returns 0 on success, -1 if l or out is NULL or i is out of range.
 * Traverses from the head: O(i). On failure *out is not written. */
int list_get(const List *l, size_t i, int *out);

/* Number of elements. Returns 0 for a NULL list. O(n). */
size_t list_size(const List *l);

#endif /* LIST_H */