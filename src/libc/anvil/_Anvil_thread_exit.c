
#include <sys/anvil.h>
#include <sys/syscall_funcs.h>
#include <sys/syscalls.h>

_Noreturn void _Anvil_thread_exit(void *value_ptr)
{
    _Syscall1(__enum_kcall_thread_exit, (long)value_ptr);
    while (1)
    {
        // Stop the 'no return' warning
    }
}
