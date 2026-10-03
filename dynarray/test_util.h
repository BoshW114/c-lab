#ifndef TEST_UTIL_H
#define TEST_UTIL_H

#include <stdio.h>

static int g_pass = 0;
static int g_fail = 0;

#define CHECK(cond)                                                     \
    do {                                                                \
        if (cond) {                                                     \
            g_pass++;                                                   \
        } else {                                                        \
            g_fail++;                                                   \
            printf("  FAIL  %s:%d  %s\n", __FILE__, __LINE__, #cond);   \
        }                                                               \
    } while (0)

#define CHECK_EQ_INT(actual, expect)                                    \
    do {                                                                \
        long _a = (long)(actual);                                       \
        long _e = (long)(expect);                                       \
        if (_a == _e) {                                                 \
            g_pass++;                                                   \
        } else {                                                        \
            g_fail++;                                                   \
            printf("  FAIL  %s:%d  expected %ld, got %ld\n",            \
                   __FILE__, __LINE__, _e, _a);                         \
        }                                                               \
    } while (0)

#define TEST_SUMMARY()                                                  \
    do {                                                                \
        printf("\n===== passed %d, failed %d =====\n", g_pass, g_fail); \
    } while (0)

#endif /* TEST_UTIL_H */
