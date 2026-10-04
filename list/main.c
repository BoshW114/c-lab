#include<stdio.h>
#include<stdlib.h>
#include "list.h"
int main()
{
    List *l = list_create();
    list_push_back(l, 10);
    list_push_back(l, 20);
    list_push_front(l, 5);

    /* 应该是 5 10 20 */
    for (size_t i = 0; i < list_size(l); i++) {
        int v;
        if (list_get(l, i, &v) == 0) {
            printf("%d ", v);
        }
    }
    printf("\n");

    list_destroy(l);
}