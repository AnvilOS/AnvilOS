
#include <sys/anvil.h>
#include <sys/syscall_funcs.h>
#include <sys/syscalls.h>

int _Anvil_thread_join(int tid, void **value_ptr)
{
    return _Syscall2(__enum_kcall_thread_join, (long)tid, (long)value_ptr);
}
