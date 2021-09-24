
#include "debug.h"

#include "libc_test.h"

int libc_test()
{
    __test_harness_print_string("\n\n[ Beginning tests ]\n\n");

    string_test();
    ctype_test();
    stdlib_malloc_test();
    stdlib_test();
    stdlib_strtod_test();
    stdio_printf_test();
    time_test();
    stdio_io_test();

    __test_harness_print_string("[ All tests done! ]\n");

    return 0;
}
