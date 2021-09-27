
#include "libc_test.h"
#include <stdlib.h>

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
    setjmp_test();

    __test_harness_print_string("[ All tests done! ]\n");

    _Anvil_heap_check(1);

    return 0;
}
