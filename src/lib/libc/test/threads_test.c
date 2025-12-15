
#include "test_harness.h"

#include <threads.h>
#include <stdio.h>

TEST_GROUP(threads)

int fast_func(void *arg)
{
    printf("fast_func()\n");
    while (1);
    thrd_exit(1000);
    return 0;
}

TEST(threads, create)
{
    int thr;
    printf("Creating\n");
    thrd_create(&thr, fast_func, (void *)0x12345678);
    printf("Creating done\n");
    //while (1);

    END_TEST(threads);
}

int threads_test()
{
    CALL_TEST(threads, create);

    END_TEST_GROUP(threads);
}
