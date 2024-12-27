
#include "ksyscall.h"
#include "ksched.h"

#include <errno.h>
#include <sys/syscalls.h>
#include <stdio.h>

#include "stm32u5xx_hal.h"

/*
 * This creates an array of function pointers to the syscall handlers
 */
#define SYSCALL(func) func,
int (*(SysCall[]))(struct thread_obj *t) =
{
#include <sys/_syscall_list.h>
};
#undef SYSCALL

#define SYSCALL(func)     #func,
char *syscall_name[] =
{
#include <sys/_syscall_list.h>
};
#undef SYSCALL

int kcall_nop(struct thread_obj *t)
{
    printf("kcall_nop %p", (void *)t);
    return 0;
}

void SVC_Handler()
{
    /*
     * Syscalls use the std ARM abi to pass parameters
     *
     * parm   : r0 - the system call number
     * parm 1 : r1
     * parm 2 : r2
     * parm 3 : r3
     *
     * Additionally r0 holds the return value.
     */
    struct thread_obj *currt = ksched_get_currt();
    currt->psp = __get_PSP();
    currt->reg = (struct syscall_regs *)(currt->psp);
    int syscall = PARM0;
    /* Check that the syscall number is valid */
    if (syscall > __enum_kcall_nop)
    {
        RETVAL = -ENOSYS;
        return;
    }
    RETVAL = SysCall[syscall](currt);
}
