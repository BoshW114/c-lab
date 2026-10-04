#include<stdio.h>
#include<stdlib.h>
#include "list.h"
typedef struct ListNode
{
    int val;
    struct ListNode* next;
} ListNode;
typedef struct List
{
    ListNode* head;
    ListNode* tail;
    size_t size;
}List;
List *list_create(void)
{
    List *l = malloc(sizeof(List));
    if(l == NULL)
    {
        return NULL;
    }
    l->head = NULL;
    l->tail = NULL;
    l->size = 0;
    return l;
}
int list_push_front(List *l, int value)
{
    if(l == NULL)
    {
        return -1;
    }
    ListNode* n = malloc(sizeof(ListNode));
    if(n == NULL)
    {
        return -1;
    }
    n->val = value;
    n->next = l->head;
    l->head = n;
    if(l->tail == NULL)
    {
        l->tail = n;
    }
    l->size ++;
    return 0;
}
int list_push_back(List *l, int value)
{
    if(l == NULL)
    {
        return -1;
    }
    ListNode *n = malloc(sizeof(ListNode));
    if(n == NULL)
    {
        return -1;
    }
    n->val = value;
    n->next = NULL;
    if(l->tail == NULL)
    {
        l->head = n;
        l->tail = n;
    }
    else
    {
    l->tail->next = n;
    l->tail = n;
    }
    l->size ++;
    return 0;
}
int list_get (const List *l, size_t i, int *out)
{
    if(l == NULL || out == NULL)
    {
        return -1;
    }
    if(i >= l->size)
    {
        return -1;
    }
    const ListNode* cur = l->head;
    for(size_t k=0;k<i;k++)
    {
        cur = cur->next;
    }
    *out = cur->val;
    return 0;
}
size_t list_size(const List *l)
{
    if(l == NULL)
    {
        return 0;
    }
    return l->size;
}
void list_destroy(List *l)
{
    if(l == NULL)
    {
        return;
    }
    ListNode *cur = l->head;
    while(cur != NULL)
    {
        ListNode* next = cur->next;
        free(cur);
        cur = next;
    }
    free(l);
}
