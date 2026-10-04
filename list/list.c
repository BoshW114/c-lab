#include <stdlib.h>
#include "list.h"

/* Internal layout. Not visible to callers, so it can change freely. */
typedef struct ListNode
{
    int              value;
    struct ListNode *next;
} ListNode;

struct List
{
    ListNode *head;   /* first node, or NULL when empty          */
    ListNode *tail;   /* last node, or NULL when empty           */
    size_t    size;   /* cached count, so list_size is O(1)      */
};

static ListNode *node_new(int value)
{
    ListNode *n = malloc(sizeof(ListNode));
    if (n == NULL)
    {
        return NULL;
    }
    n->value = value;
    n->next = NULL;
    return n;
}

List *list_create(void)
{
    List *l = malloc(sizeof(List));
    if (l == NULL)
    {
        return NULL;
    }
    l->head = NULL;
    l->tail = NULL;
    l->size = 0;
    return l;
}

void list_destroy(List *l)
{
    if (l == NULL)
    {
        return;
    }

    /* Grab next before freeing the current node: after free the
     * node's fields must not be read. */
    ListNode *cur = l->head;
    while (cur != NULL)
    {
        ListNode *next = cur->next;
        free(cur);
        cur = next;
    }

    free(l);
}

int list_push_front(List *l, int value)
{
    if (l == NULL)
    {
        return -1;
    }

    ListNode *n = node_new(value);
    if (n == NULL)
    {
        return -1;
    }

    n->next = l->head;
    l->head = n;
    if (l->tail == NULL)
    {
        l->tail = n;   /* first element becomes the tail too */
    }
    l->size++;
    return 0;
}

int list_push_back(List *l, int value)
{
    if (l == NULL)
    {
        return -1;
    }

    ListNode *n = node_new(value);
    if (n == NULL)
    {
        return -1;
    }

    if (l->tail == NULL)
    {
        l->head = n;
        l->tail = n;
    }
    else
    {
        l->tail->next = n;
        l->tail = n;
    }
    l->size++;
    return 0;
}

int list_get(const List *l, size_t i, int *out)
{
    if (l == NULL || out == NULL)
    {
        return -1;
    }
    if (i >= l->size)
    {
        return -1;
    }

    const ListNode *cur = l->head;
    for (size_t k = 0; k < i; k++)
    {
        cur = cur->next;
    }
    *out = cur->value;
    return 0;
}

size_t list_size(const List *l)
{
    if (l == NULL)
    {
        return 0;
    }
    return l->size;
}