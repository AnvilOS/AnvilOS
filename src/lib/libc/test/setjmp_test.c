
#include "test_harness.h"

#include <setjmp.h>

TEST_GROUP(setjmp)

jmp_buf testjmpbuf;
static int test_num;

static void func()
{
	// Only the first multiply will be called
	test_num *= 2;
	longjmp(testjmpbuf, 333);
	test_num *= 2;
}

TEST(setjmp, setjmp)
{
	test_num = 55;
	int ret_val = setjmp(testjmpbuf);
	if (ret_val == 0)
	{
		func();
		// This test will never be reached
		ASSERT_EQ(0, 1);
	}

    ASSERT_EQ(333, ret_val);
    ASSERT_EQ(110, test_num);

    END_TEST(setjmp);
}

int setjmp_test()
{
    CALL_TEST(setjmp, setjmp);

    END_TEST_GROUP(setjmp);
}
