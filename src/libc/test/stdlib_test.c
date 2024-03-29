
#include <stddef.h>
#include <stdlib.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>

#include "test_harness.h"

TEST_GROUP(stdlib)

TEST(stdlib, strtol)
{
    long (* volatile STRTOL)(const char *restrict nptr, char **restrict endptr, int base) = strtol;

    ASSERT_EQ(LONG_MIN, STRTOL("-18446744073709551616", NULL, 10));
    ASSERT_EQ(LONG_MIN, STRTOL("-18446744073709551615", NULL, 10));
    ASSERT_EQ(LONG_MIN, STRTOL("-18446744073709551614", NULL, 10));
    ASSERT_EQ(LONG_MIN, STRTOL("-9223372036854775810", NULL, 10));
    ASSERT_EQ(LONG_MIN, STRTOL("-9223372036854775809", NULL, 10));
    ASSERT_EQ(LONG_MIN, STRTOL("-9223372036854775808", NULL, 10));
    ASSERT_EQ(LONG_MIN, STRTOL("-9223372036854775807", NULL, 10));
    ASSERT_EQ(LONG_MIN, STRTOL("-9223372036854775806", NULL, 10));
    ASSERT_EQ(LONG_MIN, STRTOL("-9223372036854775805", NULL, 10));
    ASSERT_EQ(LONG_MIN, STRTOL("-9223372036854775804", NULL, 10));
    ASSERT_EQ(LONG_MIN, STRTOL("-2147483649", NULL, 10));
    ASSERT_EQ(LONG_MIN, STRTOL("-2147483648", NULL, 10));
    ASSERT_EQ(-2147483647, STRTOL("-2147483647", NULL, 10));
    ASSERT_EQ(-2147483646, STRTOL("-2147483646", NULL, 10));
    ASSERT_EQ(-2147483645, STRTOL("-2147483645", NULL, 10));
    ASSERT_EQ(-3, STRTOL("-3", NULL, 10));
    ASSERT_EQ(-2, STRTOL("-2", NULL, 10));
    ASSERT_EQ(-1, STRTOL("-1", NULL, 10));
    ASSERT_EQ(0, STRTOL("0", NULL, 10));
    ASSERT_EQ(1, STRTOL("1", NULL, 10));
    ASSERT_EQ(2, STRTOL("2", NULL, 10));
    ASSERT_EQ(3, STRTOL("3", NULL, 10));
    ASSERT_EQ(2147483645, STRTOL("2147483645", NULL, 10));
    ASSERT_EQ(2147483646, STRTOL("2147483646", NULL, 10));
    ASSERT_EQ(LONG_MAX, STRTOL("2147483647", NULL, 10));
    ASSERT_EQ(LONG_MAX, STRTOL("2147483648", NULL, 10));
    ASSERT_EQ(LONG_MAX, STRTOL("2147483649", NULL, 10));
    ASSERT_EQ(LONG_MAX, STRTOL("9223372036854775804", NULL, 10));
    ASSERT_EQ(LONG_MAX, STRTOL("9223372036854775805", NULL, 10));
    ASSERT_EQ(LONG_MAX, STRTOL("9223372036854775806", NULL, 10));
    ASSERT_EQ(LONG_MAX, STRTOL("9223372036854775807", NULL, 10));
    ASSERT_EQ(LONG_MAX, STRTOL("9223372036854775808", NULL, 10));
    ASSERT_EQ(LONG_MAX, STRTOL("9223372036854775809", NULL, 10));
    ASSERT_EQ(LONG_MAX, STRTOL("9223372036854775810", NULL, 10));
    ASSERT_EQ(LONG_MAX, STRTOL("18446744073709551614", NULL, 10));
    ASSERT_EQ(LONG_MAX, STRTOL("18446744073709551615", NULL, 10));
    ASSERT_EQ(LONG_MAX, STRTOL("18446744073709551616", NULL, 10));

    END_TEST(stdlib);
}

TEST(stdlib, strtoul)
{
    unsigned long (* volatile STRTOUL)(const char *restrict nptr, char **restrict endptr, int base) = strtoul;

    ASSERT_EQ(-ULONG_MAX, STRTOUL("-18446744073709551616", NULL, 10));
    ASSERT_EQ(-ULONG_MAX, STRTOUL("-18446744073709551615", NULL, 10));
    ASSERT_EQ(-ULONG_MAX, STRTOUL("-18446744073709551614", NULL, 10));
    ASSERT_EQ(-ULONG_MAX, STRTOUL("-9223372036854775810", NULL, 10));
    ASSERT_EQ(-ULONG_MAX, STRTOUL("-9223372036854775809", NULL, 10));
    ASSERT_EQ(-ULONG_MAX, STRTOUL("-9223372036854775808", NULL, 10));
    ASSERT_EQ(-ULONG_MAX, STRTOUL("-9223372036854775807", NULL, 10));
    ASSERT_EQ(-ULONG_MAX, STRTOUL("-9223372036854775806", NULL, 10));
    ASSERT_EQ(-ULONG_MAX, STRTOUL("-9223372036854775805", NULL, 10));
    ASSERT_EQ(-ULONG_MAX, STRTOUL("-9223372036854775804", NULL, 10));
    ASSERT_EQ(-ULONG_MAX, STRTOUL("-4294967297", NULL, 10));
    ASSERT_EQ(-ULONG_MAX, STRTOUL("-4294967296", NULL, 10));
    ASSERT_EQ(1, STRTOUL("-4294967295", NULL, 10));
    ASSERT_EQ(2, STRTOUL("-4294967294", NULL, 10));
    ASSERT_EQ(3, STRTOUL("-4294967293", NULL, 10));
    ASSERT_EQ(2147483647, STRTOUL("-2147483649", NULL, 10));
    ASSERT_EQ(2147483648, STRTOUL("-2147483648", NULL, 10));
    ASSERT_EQ(2147483649, STRTOUL("-2147483647", NULL, 10));
    ASSERT_EQ(2147483650, STRTOUL("-2147483646", NULL, 10));
    ASSERT_EQ(2147483651, STRTOUL("-2147483645", NULL, 10));
    ASSERT_EQ(4294967293, STRTOUL("-3", NULL, 10));
    ASSERT_EQ(4294967294, STRTOUL("-2", NULL, 10));
    ASSERT_EQ(4294967295, STRTOUL("-1", NULL, 10));
    ASSERT_EQ(0, STRTOUL("0", NULL, 10));
    ASSERT_EQ(1, STRTOUL("1", NULL, 10));
    ASSERT_EQ(2, STRTOUL("2", NULL, 10));
    ASSERT_EQ(3, STRTOUL("3", NULL, 10));
    ASSERT_EQ(2147483645, STRTOUL("2147483645", NULL, 10));
    ASSERT_EQ(2147483646, STRTOUL("2147483646", NULL, 10));
    ASSERT_EQ(2147483647, STRTOUL("2147483647", NULL, 10));
    ASSERT_EQ(2147483648, STRTOUL("2147483648", NULL, 10));
    ASSERT_EQ(2147483649, STRTOUL("2147483649", NULL, 10));
    ASSERT_EQ(4294967293, STRTOUL("4294967293", NULL, 10));
    ASSERT_EQ(4294967294, STRTOUL("4294967294", NULL, 10));
    ASSERT_EQ(ULONG_MAX, STRTOUL("4294967295", NULL, 10));
    ASSERT_EQ(ULONG_MAX, STRTOUL("4294967296", NULL, 10));
    ASSERT_EQ(ULONG_MAX, STRTOUL("4294967297", NULL, 10));
    ASSERT_EQ(ULONG_MAX, STRTOUL("9223372036854775804", NULL, 10));
    ASSERT_EQ(ULONG_MAX, STRTOUL("9223372036854775805", NULL, 10));
    ASSERT_EQ(ULONG_MAX, STRTOUL("9223372036854775806", NULL, 10));
    ASSERT_EQ(ULONG_MAX, STRTOUL("9223372036854775807", NULL, 10));
    ASSERT_EQ(ULONG_MAX, STRTOUL("9223372036854775808", NULL, 10));
    ASSERT_EQ(ULONG_MAX, STRTOUL("9223372036854775809", NULL, 10));
    ASSERT_EQ(ULONG_MAX, STRTOUL("9223372036854775810", NULL, 10));
    ASSERT_EQ(ULONG_MAX, STRTOUL("18446744073709551614", NULL, 10));
    ASSERT_EQ(ULONG_MAX, STRTOUL("18446744073709551615", NULL, 10));
    ASSERT_EQ(ULONG_MAX, STRTOUL("18446744073709551616", NULL, 10));

    END_TEST(stdlib);
}

TEST(stdlib, strtoll)
{
    long long (* volatile STRTOLL)(const char *restrict nptr, char **restrict endptr, int base) = strtoll;

    ASSERT_EQ(LLONG_MIN, STRTOLL("-18446744073709551616", NULL, 10));
    ASSERT_EQ(LLONG_MIN, STRTOLL("-18446744073709551615", NULL, 10));
    ASSERT_EQ(LLONG_MIN, STRTOLL("-18446744073709551614", NULL, 10));
    ASSERT_EQ(LLONG_MIN, STRTOLL("-9223372036854775810", NULL, 10));
    ASSERT_EQ(LLONG_MIN, STRTOLL("-9223372036854775809", NULL, 10));
    ASSERT_EQ(LLONG_MIN, STRTOLL("-9223372036854775808", NULL, 10));
    ASSERT_EQ(-9223372036854775807LL, STRTOLL("-9223372036854775807", NULL, 10));
    ASSERT_EQ(-9223372036854775806LL, STRTOLL("-9223372036854775806", NULL, 10));
    ASSERT_EQ(-9223372036854775805LL, STRTOLL("-9223372036854775805", NULL, 10));
    ASSERT_EQ(-9223372036854775804LL, STRTOLL("-9223372036854775804", NULL, 10));
    ASSERT_EQ(-2147483649, STRTOLL("-2147483649", NULL, 10));
    ASSERT_EQ(-2147483648, STRTOLL("-2147483648", NULL, 10));
    ASSERT_EQ(-2147483647, STRTOLL("-2147483647", NULL, 10));
    ASSERT_EQ(-2147483646, STRTOLL("-2147483646", NULL, 10));
    ASSERT_EQ(-2147483645, STRTOLL("-2147483645", NULL, 10));
    ASSERT_EQ(-3, STRTOLL("-3", NULL, 10));
    ASSERT_EQ(-2, STRTOLL("-2", NULL, 10));
    ASSERT_EQ(-1, STRTOLL("-1", NULL, 10));
    ASSERT_EQ(0, STRTOLL("0", NULL, 10));
    ASSERT_EQ(1, STRTOLL("1", NULL, 10));
    ASSERT_EQ(2, STRTOLL("2", NULL, 10));
    ASSERT_EQ(3, STRTOLL("3", NULL, 10));
    ASSERT_EQ(2147483645, STRTOLL("2147483645", NULL, 10));
    ASSERT_EQ(2147483646, STRTOLL("2147483646", NULL, 10));
    ASSERT_EQ(2147483647, STRTOLL("2147483647", NULL, 10));
    ASSERT_EQ(2147483648, STRTOLL("2147483648", NULL, 10));
    ASSERT_EQ(2147483649, STRTOLL("2147483649", NULL, 10));
    ASSERT_EQ(9223372036854775804, STRTOLL("9223372036854775804", NULL, 10));
    ASSERT_EQ(9223372036854775805, STRTOLL("9223372036854775805", NULL, 10));
    ASSERT_EQ(9223372036854775806, STRTOLL("9223372036854775806", NULL, 10));
    ASSERT_EQ(9223372036854775807, STRTOLL("9223372036854775807", NULL, 10));
    ASSERT_EQ(LLONG_MAX, STRTOLL("9223372036854775808", NULL, 10));
    ASSERT_EQ(LLONG_MAX, STRTOLL("9223372036854775809", NULL, 10));
    ASSERT_EQ(LLONG_MAX, STRTOLL("9223372036854775810", NULL, 10));
    ASSERT_EQ(LLONG_MAX, STRTOLL("18446744073709551614", NULL, 10));
    ASSERT_EQ(LLONG_MAX, STRTOLL("18446744073709551615", NULL, 10));
    ASSERT_EQ(LLONG_MAX, STRTOLL("18446744073709551616", NULL, 10));

    END_TEST(stdlib);
}

TEST(stdlib, strtoull)
{
    unsigned long long (* volatile STRTOULL)(const char *restrict nptr, char **restrict endptr, int base) = strtoull;

    ASSERT_EQ(1, STRTOULL("-18446744073709551618", NULL, 10));
    ASSERT_EQ(1, STRTOULL("-18446744073709551617", NULL, 10));
    ASSERT_EQ(1, STRTOULL("-18446744073709551616", NULL, 10));
    ASSERT_EQ(1, STRTOULL("-18446744073709551615", NULL, 10));
    ASSERT_EQ(2, STRTOULL("-18446744073709551614", NULL, 10));
    ASSERT_EQ(9223372036854775806U, STRTOULL("-9223372036854775810", NULL, 10));
    ASSERT_EQ(9223372036854775807U, STRTOULL("-9223372036854775809", NULL, 10));
    ASSERT_EQ(9223372036854775808U, STRTOULL("-9223372036854775808", NULL, 10));
    ASSERT_EQ(9223372036854775809U, STRTOULL("-9223372036854775807", NULL, 10));
    ASSERT_EQ(9223372036854775810U, STRTOULL("-9223372036854775806", NULL, 10));
    ASSERT_EQ(9223372036854775811U, STRTOULL("-9223372036854775805", NULL, 10));
    ASSERT_EQ(9223372036854775812U, STRTOULL("-9223372036854775804", NULL, 10));
    ASSERT_EQ(18446744069414584319U, STRTOULL("-4294967297", NULL, 10));
    ASSERT_EQ(18446744069414584320U, STRTOULL("-4294967296", NULL, 10));
    ASSERT_EQ(18446744069414584321U, STRTOULL("-4294967295", NULL, 10));
    ASSERT_EQ(18446744069414584322U, STRTOULL("-4294967294", NULL, 10));
    ASSERT_EQ(18446744069414584323U, STRTOULL("-4294967293", NULL, 10));
    ASSERT_EQ(18446744071562067967U, STRTOULL("-2147483649", NULL, 10));
    ASSERT_EQ(18446744071562067968U, STRTOULL("-2147483648", NULL, 10));
    ASSERT_EQ(18446744071562067969U, STRTOULL("-2147483647", NULL, 10));
    ASSERT_EQ(18446744071562067970U, STRTOULL("-2147483646", NULL, 10));
    ASSERT_EQ(18446744071562067971U, STRTOULL("-2147483645", NULL, 10));
    ASSERT_EQ(18446744073709551613U, STRTOULL("-3", NULL, 10));
    ASSERT_EQ(18446744073709551614U, STRTOULL("-2", NULL, 10));
    ASSERT_EQ(18446744073709551615U, STRTOULL("-1", NULL, 10));
    ASSERT_EQ(0, STRTOULL("0", NULL, 10));
    ASSERT_EQ(1, STRTOULL("1", NULL, 10));
    ASSERT_EQ(2, STRTOULL("2", NULL, 10));
    ASSERT_EQ(3, STRTOULL("3", NULL, 10));
    ASSERT_EQ(2147483645, STRTOULL("2147483645", NULL, 10));
    ASSERT_EQ(2147483646, STRTOULL("2147483646", NULL, 10));
    ASSERT_EQ(2147483647, STRTOULL("2147483647", NULL, 10));
    ASSERT_EQ(2147483648, STRTOULL("2147483648", NULL, 10));
    ASSERT_EQ(2147483649, STRTOULL("2147483649", NULL, 10));
    ASSERT_EQ(4294967293, STRTOULL("4294967293", NULL, 10));
    ASSERT_EQ(4294967294, STRTOULL("4294967294", NULL, 10));
    ASSERT_EQ(4294967295, STRTOULL("4294967295", NULL, 10));
    ASSERT_EQ(4294967296, STRTOULL("4294967296", NULL, 10));
    ASSERT_EQ(4294967297, STRTOULL("4294967297", NULL, 10));
    ASSERT_EQ(9223372036854775804, STRTOULL("9223372036854775804", NULL, 10));
    ASSERT_EQ(9223372036854775805, STRTOULL("9223372036854775805", NULL, 10));
    ASSERT_EQ(9223372036854775806, STRTOULL("9223372036854775806", NULL, 10));
    ASSERT_EQ(9223372036854775807, STRTOULL("9223372036854775807", NULL, 10));
    ASSERT_EQ(9223372036854775808U, STRTOULL("9223372036854775808", NULL, 10));
    ASSERT_EQ(9223372036854775809U, STRTOULL("9223372036854775809", NULL, 10));
    ASSERT_EQ(9223372036854775810U, STRTOULL("9223372036854775810", NULL, 10));
    ASSERT_EQ(18446744073709551614U, STRTOULL("18446744073709551614", NULL, 10));
    ASSERT_EQ(18446744073709551615U, STRTOULL("18446744073709551615", NULL, 10));
    ASSERT_EQ(ULLONG_MAX, STRTOULL("18446744073709551616", NULL, 10));
    ASSERT_EQ(ULLONG_MAX, STRTOULL("18446744073709551617", NULL, 10));
    ASSERT_EQ(ULLONG_MAX, STRTOULL("18446744073709551618", NULL, 10));

    END_TEST(stdlib);
}

TEST(stdlib, div)
{
    div_t res;

    //  I got this table from stack overflow
    //
    //     n     |  d     |  q     |  r
    //    -------|--------|--------|--------
    //     7     |  3     |  2     |  1
    //    -7     |  3     | -2     | -1
    //     7     | -3     | -2     |  1
    //    -7     | -3     |  2     | -1

    res = div(7, 3);
    ASSERT_EQ(2, res.quot);
    ASSERT_EQ(1, res.rem);

    res = div(-7, 3);
    ASSERT_EQ(-2, res.quot);
    ASSERT_EQ(-1, res.rem);

    res = div(7, -3);
    ASSERT_EQ(-2, res.quot);
    ASSERT_EQ(1, res.rem);

    res = div(-7, -3);
    ASSERT_EQ(2, res.quot);
    ASSERT_EQ(-1, res.rem);

    END_TEST(stdlib);
}

int qsort_compare(const void *p1, const void *p2)
{
    const short *sh1 = p1;
    const short *sh2 = p2;
    return *sh1 - *sh2;
}

static const int array_sz = 2048;

TEST(stdlib, qsort_limits)
{
    short array[] = { 2, 1 };

    qsort(array, 0, 2, qsort_compare);
    ASSERT_EQ(2, array[0]);
    ASSERT_EQ(1, array[1]);

    qsort(array, 1, 2, qsort_compare);
    ASSERT_EQ(2, array[0]);
    ASSERT_EQ(1, array[1]);

    qsort(array+1, 1, 2, qsort_compare);
    ASSERT_EQ(2, array[0]);
    ASSERT_EQ(1, array[1]);

    qsort(array, 2, 2, qsort_compare);
    ASSERT_EQ(1, array[0]);
    ASSERT_EQ(2, array[1]);

    END_TEST(stdlib)
}

TEST(stdlib, qsort_algorithm)
{
    short *array = (short *)malloc(array_sz * sizeof(short));
    ASSERT_PTR_NE(NULL, array);

    for (int i=0; i<array_sz; ++i)
    {
        array[i] = rand() * array_sz / RAND_MAX;
    }
    qsort(array, array_sz, 2, qsort_compare);

    for (unsigned i=0; i<array_sz-1; ++i)
    {
        ASSERT_EQ(0, array[i] > array[i+1]);
    }

    // Try sorting an array that's already sorted
    for (int i=0; i<array_sz; ++i)
    {
        array[i] = i;
    }
    qsort(array, array_sz, 2, qsort_compare);
    for (unsigned i=0; i<array_sz-1; ++i)
    {
        ASSERT_EQ(0, array[i] > array[i+1]);
    }

    // Now one in reverse
    for (int i=0; i<array_sz; ++i)
    {
        array[i] = array_sz - i - 1;
    }
    qsort(array, array_sz, 2, qsort_compare);
    for (unsigned i=0; i<array_sz-1; ++i)
    {
        ASSERT_EQ(0, array[i] > array[i+1]);
    }

    // Now sort an array of identical items
    for (int i=0; i<array_sz; ++i)
    {
        array[i] = 1000;
    }
    qsort(array, array_sz, 2, qsort_compare);
    for (unsigned i=0; i<array_sz-1; ++i)
    {
        ASSERT_EQ(0, array[i] > array[i+1]);
    }

    free(array);

    END_TEST(stdlib)
}

int bsearch_compare(const void *p1, const void *p2)
{
    const char *sh1 = p1;
    const char *sh2 = p2;
    return *sh1 - *sh2;
}

TEST(stdlib, bsearch)
{
    const char array[] = { 1, 2, 3, 3, 4, 4, 6, 7, 8, 9 };
    char key;

    key = 0;
    ASSERT_PTR_EQ(NULL, bsearch(&key, array, 10, 1, bsearch_compare));

    key = 1;
    ASSERT_PTR_EQ(&array[0], bsearch(&key, array, 10, 1, bsearch_compare));

    key = 2;
    ASSERT_PTR_EQ(&array[1], bsearch(&key, array, 10, 1, bsearch_compare));

    key = 4;
    char *key4 = bsearch(&key, array, 10, 1, bsearch_compare);
    ASSERT_EQ(1, key4 == &array[4] || key4 == &array[5]);

    key = 5;
    ASSERT_PTR_EQ(NULL, bsearch(&key, array, 10, 1, bsearch_compare));

    key = 6;
    ASSERT_PTR_EQ(&array[6], bsearch(&key, array, 10, 1, bsearch_compare));

    key = 9;
    ASSERT_PTR_EQ(&array[9], bsearch(&key, array, 10, 1, bsearch_compare));

    key = 11;
    ASSERT_PTR_EQ(NULL, bsearch(&key, array, 10, 1, bsearch_compare));

    END_TEST(stdlib)
}

int stdlib_test()
{
    CALL_TEST(stdlib, strtol);
    CALL_TEST(stdlib, strtoul);
    CALL_TEST(stdlib, strtoll);
    CALL_TEST(stdlib, strtoull);

    CALL_TEST(stdlib, div);

    CALL_TEST(stdlib, qsort_limits);
    CALL_TEST(stdlib, qsort_algorithm);
    CALL_TEST(stdlib, bsearch);

    END_TEST_GROUP(stdlib);
}
