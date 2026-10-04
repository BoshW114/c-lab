#include <stdio.h>
#include "list.h"
#include "../dynarray/test_util.h"

static void test_create_destroy(void)
{
    printf("[test] create / destroy\n");

    List *l = list_create();
    CHECK(l != NULL);
    CHECK_EQ_INT(list_size(l), 0);
    list_destroy(l);

    list_destroy(NULL);
    CHECK(1);
}

static void test_push_front(void)
{
    printf("[test] push_front\n");

    List *l = list_create();
    CHECK(l != NULL);

    CHECK_EQ_INT(list_push_front(l, 1), 0);
    CHECK_EQ_INT(list_size(l), 1);

    CHECK_EQ_INT(list_push_front(l, 2), 0);
    CHECK_EQ_INT(list_push_front(l, 3), 0);
    CHECK_EQ_INT(list_size(l), 3);

    int v = -1;
    CHECK_EQ_INT(list_get(l, 0, &v), 0);
    CHECK_EQ_INT(v, 3);
    CHECK_EQ_INT(list_get(l, 1, &v), 0);
    CHECK_EQ_INT(v, 2);
    CHECK_EQ_INT(list_get(l, 2, &v), 0);
    CHECK_EQ_INT(v, 1);

    list_destroy(l);
}

static void test_push_back(void)
{
    printf("[test] push_back\n");

    List *l = list_create();
    CHECK(l != NULL);

    for (int i = 1; i <= 5; i++) {
        CHECK_EQ_INT(list_push_back(l, i * 10), 0);
    }
    CHECK_EQ_INT(list_size(l), 5);

    for (int i = 0; i < 5; i++) {
        int v = -1;
        CHECK_EQ_INT(list_get(l, (size_t)i, &v), 0);
        CHECK_EQ_INT(v, (i + 1) * 10);
    }

    list_destroy(l);
}

static void test_mixed_order(void)
{
    printf("[test] mixed push_front / push_back\n");

    List *l = list_create();

    CHECK_EQ_INT(list_push_back(l, 2), 0);
    CHECK_EQ_INT(list_push_front(l, 1), 0);
    CHECK_EQ_INT(list_push_back(l, 3), 0);
    CHECK_EQ_INT(list_push_front(l, 0), 0);
    CHECK_EQ_INT(list_size(l), 4);

    for (int i = 0; i < 4; i++) {
        int v = -1;
        CHECK_EQ_INT(list_get(l, (size_t)i, &v), 0);
        CHECK_EQ_INT(v, i);
    }

    list_destroy(l);
}

static void test_single_element(void)
{
    printf("[test] single element (head == tail)\n");

    List *l = list_create();

    CHECK_EQ_INT(list_push_back(l, 42), 0);
    CHECK_EQ_INT(list_size(l), 1);

    int v = -1;
    CHECK_EQ_INT(list_get(l, 0, &v), 0);
    CHECK_EQ_INT(v, 42);
    CHECK_EQ_INT(list_get(l, 1, &v), -1);

    list_destroy(l);

    /* Same via push_front */
    l = list_create();
    CHECK_EQ_INT(list_push_front(l, 7), 0);
    CHECK_EQ_INT(list_get(l, 0, &v), 0);
    CHECK_EQ_INT(v, 7);

    /* Adding a second element must keep tail correct */
    CHECK_EQ_INT(list_push_back(l, 8), 0);
    CHECK_EQ_INT(list_size(l), 2);
    CHECK_EQ_INT(list_get(l, 1, &v), 0);
    CHECK_EQ_INT(v, 8);

    list_destroy(l);
}

static void test_out_of_range(void)
{
    printf("[test] out of range\n");

    List *l = list_create();
    for (int i = 0; i < 3; i++) list_push_back(l, i);

    int v = -999;

    CHECK_EQ_INT(list_get(l, 3, &v), -1);
    CHECK_EQ_INT(v, -999);

    CHECK_EQ_INT(list_get(l, 99999, &v), -1);
    CHECK_EQ_INT(v, -999);

    CHECK_EQ_INT(list_get(l, 2, &v), 0);
    CHECK_EQ_INT(v, 2);

    CHECK_EQ_INT(list_get(l, 0, NULL), -1);

    list_destroy(l);
}

static void test_empty(void)
{
    printf("[test] empty list\n");

    List *l = list_create();

    int v = -999;
    CHECK_EQ_INT(list_get(l, 0, &v), -1);
    CHECK_EQ_INT(v, -999);
    CHECK_EQ_INT(list_size(l), 0);

    list_destroy(l);
}

static void test_null_args(void)
{
    printf("[test] NULL args\n");

    int v = -999;
    CHECK_EQ_INT(list_get(NULL, 0, &v), -1);
    CHECK_EQ_INT(v, -999);
    CHECK_EQ_INT(list_push_front(NULL, 1), -1);
    CHECK_EQ_INT(list_push_back(NULL, 1), -1);
    CHECK_EQ_INT(list_size(NULL), 0);
}

static void test_stress(void)
{
    printf("[test] stress (100000)\n");

    const int N = 100000;
    List *l = list_create();
    CHECK(l != NULL);

    for (int i = 0; i < N; i++) {
        if (list_push_back(l, i) != 0) {
            printf("  push_back failed at %d\n", i);
            break;
        }
    }
    CHECK_EQ_INT(list_size(l), (size_t)N);

    int v = -1;
    CHECK_EQ_INT(list_get(l, 0, &v), 0);
    CHECK_EQ_INT(v, 0);
    CHECK_EQ_INT(list_get(l, (size_t)N - 1, &v), 0);
    CHECK_EQ_INT(v, N - 1);
    CHECK_EQ_INT(list_get(l, (size_t)N, &v), -1);

    list_destroy(l);
}

static void test_stress_front(void)
{
    printf("[test] stress push_front (100000)\n");

    const int N = 100000;
    List *l = list_create();
    CHECK(l != NULL);

    for (int i = 0; i < N; i++) {
        if (list_push_front(l, i) != 0) {
            printf("  push_front failed at %d\n", i);
            break;
        }
    }
    CHECK_EQ_INT(list_size(l), (size_t)N);

    /* push_front reverses order: element i is N-1-i */
    int v = -1;
    CHECK_EQ_INT(list_get(l, 0, &v), 0);
    CHECK_EQ_INT(v, N - 1);
    CHECK_EQ_INT(list_get(l, (size_t)N - 1, &v), 0);
    CHECK_EQ_INT(v, 0);

    list_destroy(l);
}

static void test_repeat(void)
{
    printf("[test] repeat create/destroy x10000\n");

    for (int i = 0; i < 10000; i++) {
        List *l = list_create();
        if (l == NULL) { CHECK(0); return; }
        list_push_back(l, i);
        list_push_front(l, i);
        list_destroy(l);
    }
    CHECK(1);
}

int main(void)
{
    printf("===== list tests =====\n\n");

    test_create_destroy();
    test_push_front();
    test_push_back();
    test_mixed_order();
    test_single_element();
    test_out_of_range();
    test_empty();
    test_null_args();
    test_stress();
    test_stress_front();
    test_repeat();

    TEST_SUMMARY();

    return g_fail == 0 ? 0 : 1;
}