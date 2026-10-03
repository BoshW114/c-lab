#include <stdio.h>
#include "dynarray.h"
#include "test_util.h"

static void test_create_destroy(void)
{
    printf("[test] create / destroy\n");

    DynArray *a = da_create();
    CHECK(a != NULL);
    CHECK_EQ_INT(da_size(a), 0);
    da_destroy(a);

    da_destroy(NULL);
    CHECK(1);
}

static void test_push_get(void)
{
    printf("[test] push / get\n");

    DynArray *a = da_create();
    CHECK(a != NULL);

    CHECK_EQ_INT(da_push(a, 100), 0);
    CHECK_EQ_INT(da_size(a), 1);

    int v = -1;
    CHECK_EQ_INT(da_get(a, 0, &v), 0);
    CHECK_EQ_INT(v, 100);

    CHECK_EQ_INT(da_push(a, -1), 0);
    CHECK_EQ_INT(da_get(a, 1, &v), 0);
    CHECK_EQ_INT(v, -1);

    da_destroy(a);
}

static void test_out_of_range(void)
{
    printf("[test] out of range\n");

    DynArray *a = da_create();
    for (int i = 0; i < 5; i++) da_push(a, i);

    int v = -999;

    CHECK_EQ_INT(da_get(a, 5, &v), -1);
    CHECK_EQ_INT(v, -999);

    CHECK_EQ_INT(da_get(a, 99999, &v), -1);
    CHECK_EQ_INT(v, -999);

    CHECK_EQ_INT(da_get(a, 4, &v), 0);
    CHECK_EQ_INT(v, 4);

    CHECK_EQ_INT(da_get(a, 0, NULL), -1);

    da_destroy(a);
}

static void test_empty(void)
{
    printf("[test] empty array\n");

    DynArray *a = da_create();

    int v = -999;
    CHECK_EQ_INT(da_get(a, 0, &v), -1);
    CHECK_EQ_INT(v, -999);
    CHECK_EQ_INT(da_size(a), 0);

    da_destroy(a);
}

static void test_null_args(void)
{
    printf("[test] NULL args\n");

    int v = -999;
    CHECK_EQ_INT(da_get(NULL, 0, &v), -1);
    CHECK_EQ_INT(v, -999);
    CHECK_EQ_INT(da_push(NULL, 1), -1);
    CHECK_EQ_INT(da_size(NULL), 0);
}

static void test_grow(void)
{
    printf("[test] grow\n");

    DynArray *a = da_create();

    for (int i = 0; i < 100; i++) {
        CHECK_EQ_INT(da_push(a, i), 0);
    }
    CHECK_EQ_INT(da_size(a), 100);

    for (int i = 0; i < 100; i++) {
        int v = -1;
        CHECK_EQ_INT(da_get(a, (size_t)i, &v), 0);
        CHECK_EQ_INT(v, i);
    }

    da_destroy(a);
}

static void test_stress(void)
{
    printf("[test] stress (100000)\n");

    const int N = 100000;
    DynArray *a = da_create();
    CHECK(a != NULL);

    for (int i = 0; i < N; i++) {
        if (da_push(a, i) != 0) {
            printf("  push failed at element %d\n", i);
            break;
        }
    }
    CHECK_EQ_INT(da_size(a), (size_t)N);

    int v = -1;
    CHECK_EQ_INT(da_get(a, 0, &v), 0);
    CHECK_EQ_INT(v, 0);
    CHECK_EQ_INT(da_get(a, (size_t)N - 1, &v), 0);
    CHECK_EQ_INT(v, N - 1);
    CHECK_EQ_INT(da_get(a, (size_t)N, &v), -1);

    da_destroy(a);
}

static void test_repeat(void)
{
    printf("[test] repeat create/destroy x10000\n");

    for (int i = 0; i < 10000; i++) {
        DynArray *a = da_create();
        if (a == NULL) { CHECK(0); return; }
        da_push(a, i);
        da_destroy(a);
    }
    CHECK(1);
}

int main(void)
{
    printf("===== dynarray tests =====\n\n");

    test_create_destroy();
    test_push_get();
    test_out_of_range();
    test_empty();
    test_null_args();
    test_grow();
    test_stress();
    test_repeat();

    TEST_SUMMARY();

    return g_fail == 0 ? 0 : 1;
}
