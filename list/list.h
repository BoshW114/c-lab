#ifndef LIST_H
#define LIST_H

#include <stddef.h>
typedef struct List List;
List *list_create(void);
void list_destroy(List *l);
int list_push_front(List *l, int value);
int list_push_back(List *l, int value);
int list_get(const List *l, size_t i, int *out);
size_t list_size(const List *l);

#endif