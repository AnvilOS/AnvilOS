
#ifndef LIBC_TEST_H
#define LIBC_TEST_H

#include "test_harness.h"

int libc_test();

int string_test();
int ctype_test();
int stdlib_test();
int stdlib_strtod_test();
int stdio_printf_test();
int stdlib_malloc_test();
int time_test();
int stdio_io_test();
int setjmp_test();
int threads_test();

#endif /* _LIBC_TEST_H_INCLUDED */
