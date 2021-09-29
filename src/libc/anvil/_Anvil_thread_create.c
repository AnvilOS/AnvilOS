
#include <sys/anvil.h>
#include <sys/syscall_funcs.h>
#include <sys/syscalls.h>

int _Anvil_thread_create(int (*start_routine)(void*), void *arg)
{
    return _Syscall2(__enum_kcall_thread_create, (long)start_routine, (long)arg);
}
