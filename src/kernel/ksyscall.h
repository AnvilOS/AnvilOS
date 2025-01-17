
#ifndef SYSCALL_H_INCLUDED
#define SYSCALL_H_INCLUDED

#include "kthread.h"

/* This creates a list of function prototypes for the syscall handlers */
#define SYSCALL(func) int func (struct thread_obj *t);
#include <sys/_syscall_list.h>
#undef SYSCALL

#define PARM0 (currt->reg->regpack.r0)
#define PARM1 (currt->reg->regpack.r1)
#define PARM2 (currt->reg->regpack.r2)
#define PARM3 (currt->reg->regpack.r3)
#define RETVAL (currt->reg->regpack.r0)

#endif /* SYSCALL_H_INCLUDED */
