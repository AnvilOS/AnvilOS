
#include "debug.h"
#include "timer.h"

extern int libc_test();

int main()
{
    debug_init();
    sys_tick_init();
    libc_test();
    while (1)
    {
    }
}
