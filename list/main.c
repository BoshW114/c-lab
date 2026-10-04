#include <stdio.h>
#include "list.h"

static void print_list(const List *l)
{
    printf("size=%zu: ", list_size(l));
    for (size_t i = 0; i < list_size(l); i++)
    {
        int v = 0;
        if (list_get(l, i, &v) == 0)
        {
            printf("%d -> ", v);
        }
    }
    printf("NULL\n");
}

int main(void)
{
    List *l = list_create();
    if (l == NULL)
    {
        printf("create failed\n");
        return 1;
    }

    printf("=== push_back 1..5 ===\n");
    for (int i = 1; i <= 5; i++)
    {
        if (list_push_back(l, i) != 0)
        {
            printf("push_back failed\n");
            list_destroy(l);
            return 1;
        }
    }
    print_list(l);

    printf("\n=== push_front 0 ===\n");
    list_push_front(l, 0);
    print_list(l);

    printf("\n=== out of range ===\n");
    int v = -999;
    printf("get(100) = %d, v unchanged = %d\n", list_get(l, 100, &v), v);

    list_destroy(l);
    printf("\ndone\n");
    return 0;
}