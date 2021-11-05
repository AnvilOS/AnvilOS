
#include <stddef.h>
#include <stdlib.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "test_harness.h"
#include "double_test_data.h"

enum
{
    e_relative,
    e_absolute,
};

union double_bits
{
    double dbl;
    uint64_t uint;
    uint32_t uint32[2];
};

extern char *_Anvil_dtoa(double dd, int mode, int ndigits, int *decpt, int *sign, char **rve);
extern char *gdtoa_dtoa(double dd, int mode, int ndigits, int *decpt, int *sign, char **rve);

TEST_GROUP(stdlib_strtod)

TEST(stdlib_strtod, base_10_parser_data)
{
    double (* volatile STRTOD)(const char *restrict nptr, char **restrict endptr) = strtod;

    size_t i = 0;
    while (base_10_parser_data[i].str)
    {
        union double_bits res;
        //printf("---- %s ----\n", base_10_parser_data[i].str);
        res.dbl = STRTOD(base_10_parser_data[i].str, NULL);
        ASSERT_EQ(base_10_parser_data[i].low, res.uint32[0]);
        ASSERT_EQ(base_10_parser_data[i].high, res.uint32[1]);
        ++i;
    }

    END_TEST(stdlib_strtod);
}

TEST(stdlib_strtod, gdtoa_test_data)
{
    double (* volatile STRTOD)(const char *restrict nptr, char **restrict endptr) = strtod;

    size_t i = 0;
    while (gdtoa_test_data[i].str)
    {
        union double_bits res;
        //printf("---- %s ----\n", gdtoa_test_data[i].str);
        res.dbl = STRTOD(gdtoa_test_data[i].str, NULL);
        ASSERT_EQ(gdtoa_test_data[i].low, res.uint32[0]);
        ASSERT_EQ(gdtoa_test_data[i].high, res.uint32[1]);
        ++i;
    }

    END_TEST(stdlib_strtod);
}

int dtoa_test_one(double dd, int gdtoa_mode, int anvil_mode, int ndigits)
{
    int gdtoa_decpt;
    int dtoa_decpt;
    int sign;
    char *rve;

    char *gd_pstr = gdtoa_dtoa(dd, gdtoa_mode, ndigits, &gdtoa_decpt, &sign, &rve);
    char *pstr = _Anvil_dtoa(dd, anvil_mode, ndigits, &dtoa_decpt, &sign, &rve);
    if (!strcmp(pstr, gd_pstr) && (gdtoa_decpt == dtoa_decpt))
    {
        //printf("SAME %s %s\n", gd_pstr, pstr);
        //printf("%d %d\n", gdtoa_decpt, dtoa_decpt);
    }
    else
        {
        printf("DIFF %s %s\n", gd_pstr, pstr);
        printf("%d %d\n", gdtoa_decpt, dtoa_decpt);
        free(pstr);
        return -1;
    }
    freedtoa(gd_pstr);
    free(pstr);
    return 0;
}

//TEST(stdlib_strtod, dtoa_test_mode_0)
//{
//    int i = 0;
//    while (gdtoa_test_data[i].str)
//    {
//        union double_bits dd;
//        dd.uint = gdtoa_test_data[i].low;
//        dd.uint |= (uint64_t)gdtoa_test_data[i].high << 32;
//        if (dtoa_test_one(dd.dbl, 0, e_normal, 0) != 0)
//        {
//            printf("---- %s ----\n", gdtoa_test_data[i].str);
//        }
//        ++i;
//    }
//
//    END_TEST(stdlib_strtod);
//}

//TEST(stdlib_strtod, dtoa_test_mode_1)
//{
//    int i = 0;
//    while (gdtoa_test_data[i].str)
//    {
//        union double_bits dd;
//        dd.uint = gdtoa_test_data[i].low;
//        dd.uint |= (uint64_t)gdtoa_test_data[i].high << 32;
//        if (dtoa_test_one(dd.dbl, 1, e_normal, 0) != 0)
//        {
//            printf("---- %s ----\n", gdtoa_test_data[i].str);
//        }
//        ++i;
//    }
//
//    END_TEST(stdlib_strtod);
//}

TEST(stdlib_strtod, dtoa_test_mode_2)
{
    int item = 0;
    while (gdtoa_test_data[item].str)
    {
        union double_bits dd;
        dd.uint = gdtoa_test_data[item].low;
        dd.uint |= (uint64_t)gdtoa_test_data[item].high << 32;
//        for (int j=-300; j<300; j+=30)
        for (int j=-10; j<10; ++j)
        {
            if (dtoa_test_one(dd.dbl, 2, e_relative, j) != 0)
            {
                printf("---- %s ----\n", gdtoa_test_data[item].str);
            }
        }
        ++item;
    }

    END_TEST(stdlib_strtod);
}

TEST(stdlib_strtod, dtoa_test_mode_3)
{
    int item = 0;
    while (gdtoa_test_data[item].str)
    {
        union double_bits dd;
        dd.uint = gdtoa_test_data[item].low;
        dd.uint |= (uint64_t)gdtoa_test_data[item].high << 32;
//        for (int j=-300; j<300; j+=30)
        for (int j=-10; j<10; ++j)
        {
            if (dtoa_test_one(dd.dbl, 3, e_absolute, j) != 0)
            {
                printf("---- %s ----\n", gdtoa_test_data[item].str);
            }
        }
        ++item;
    }

    END_TEST(stdlib_strtod);
}

//TEST(stdlib_strtod, dtoa_test_mode_4)
//{
//    int item = 0;
//    while (gdtoa_test_data[item].str)
//    {
//        union double_bits dd;
//        dd.uint = gdtoa_test_data[item].low;
//        dd.uint |= (uint64_t)gdtoa_test_data[item].high << 32;
////        for (int j=-300; j<300; j+=30)
//        for (int j=-10; j<10; ++j)
//        {
//            if (dtoa_test_one(dd.dbl, 4, e_relative, j) != 0)
//            {
//                printf("---- %s ----\n", gdtoa_test_data[item].str);
//            }
//        }
//        ++item;
//    }
//
//    END_TEST(stdlib_strtod);
//}

//TEST(stdlib_strtod, dtoa_test_mode_5)
//{
//    int item = 0;
//    while (gdtoa_test_data[item].str)
//    {
//        union double_bits dd;
//        dd.uint = gdtoa_test_data[item].low;
//        dd.uint |= (uint64_t)gdtoa_test_data[item].high << 32;
////        for (int j=-300; j<300; j+=30)
//        for (int j=-10; j<10; ++j)
//        {
//            if (dtoa_test_one(dd.dbl, 5, e_absolute, j) != 0)
//            {
//                printf("---- %s ----\n", gdtoa_test_data[item].str);
//            }
//        }
//        ++item;
//    }
//
//    END_TEST(stdlib_strtod);
//}

int gg1;

int stdlib_strtod_test()
{
    CALL_TEST(stdlib_strtod, base_10_parser_data);
    CALL_TEST(stdlib_strtod, gdtoa_test_data);
//    CALL_TEST(stdlib_strtod, dtoa_test_mode_0);
//    CALL_TEST(stdlib_strtod, dtoa_test_mode_1);
    CALL_TEST(stdlib_strtod, dtoa_test_mode_2);
    CALL_TEST(stdlib_strtod, dtoa_test_mode_3);
//    CALL_TEST(stdlib_strtod, dtoa_test_mode_4);
//    CALL_TEST(stdlib_strtod, dtoa_test_mode_5);

    extern int cc0, cc1, cc2, cc3, cc4, cc5, cc6, qq1, qq2, smallest_div, biggest;
    extern int malloc_cnt, realloc_cnt, loops;
    printf("CC %d %d %d %d %d %d %d\n", cc0, cc1, cc2, cc3, cc4, cc5, cc6);
    printf("QQ %d %d %d\n", qq1, qq2, smallest_div);
    printf("GG=%d\n", gg1);
    printf("Malloc=%d %d\n", malloc_cnt, realloc_cnt);
    printf("BIGGEST=%d\n", biggest);
    printf("LOOPS=%d\n", loops);

    END_TEST_GROUP(stdlib_strtod);
}
