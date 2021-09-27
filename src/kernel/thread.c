
#include "thread.h"
#include "syscall.h"
#include "sched.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>

struct thread_obj thread_1;
#define THREAD_1_STACK_SIZE (64)

uint64_t stk1[THREAD_1_STACK_SIZE];

void thread_init()
{
    thread_1.id = 1;
    thread_1.stk_sz = THREAD_1_STACK_SIZE * sizeof(uint64_t);
    thread_1.stk = stk1;
    thread_1.psp = (uint32_t)(thread_1.stk + THREAD_1_STACK_SIZE);
    thread_1.tls_ptr = NULL;

    /* Point the psp at the thread 1 stack */
    psp_set((uint32_t)thread_1.psp);
}

int kcall_threadcreate(struct thread_obj *currt)
{
    printf("kcall_threadcreate\n");

    struct thread_obj *p_thr;
    p_thr = (struct thread_obj *)malloc(sizeof (struct thread_obj));
    p_thr->stk_sz = 256;
    p_thr->stk = (uint64_t *)malloc(p_thr->stk_sz);
    p_thr->id = 2;
    p_thr->psp = (uint32_t)(p_thr->stk + p_thr->stk_sz - sizeof(struct regpack));
    p_thr->tls_ptr = NULL;

    struct regpack *preg = (struct regpack *)(p_thr->stk + p_thr->stk_sz - sizeof(struct regpack));
    preg->psr = 0x01000000;
    preg->pc = (unsigned long)PARM2;

    sched_add(p_thr, 0);

    return 0;
}
