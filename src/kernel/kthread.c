
#include "kthread.h"
#include "ksyscall.h"
#include "ksched.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <string.h>
#include <threads.h>
#include <errno.h>

#define STACK_SIZE (1024)           // In bytes

#define MAX_THREADS 16

#include "stm32u5xx_hal.h"

struct thread_obj *thr_tbl[MAX_THREADS];
struct thread_obj *g_currt;
extern char _estack;

static int find_thread_slot();

void kthread_init()
{
    __disable_irq();

    struct thread_obj *p_thr;
    p_thr = (struct thread_obj *)malloc(sizeof (struct thread_obj));
    p_thr->id = 1;
    p_thr->stk_sz = STACK_SIZE;
    p_thr->stk = malloc(p_thr->stk_sz);
    p_thr->psp = (uint32_t)((char *)p_thr->stk + STACK_SIZE);
    p_thr->tls_ptr = NULL;

    // Copy our current stack frame from the MSP (which from
    // now on will be used for interrupts) to thread 1's PSP
    void *s = (void *)__get_MSP();
    size_t n = &_estack - (char *)__get_MSP();
    void *d = (char *)p_thr->stk + STACK_SIZE - n;
    memcpy(d, s, n);

    // Point the psp at the thread 1 stack 
    __set_PSP((uint32_t)d);
    __set_MSP((uint32_t)&_estack);
    __set_CONTROL(__get_CONTROL() | 2);

    g_currt = p_thr;

    __enable_irq();

    // If we want to run threads unprivileged, uncomment this
    //__set_CONTROL(__get_CONTROL() | 1);
}

int kcall_thread_create(struct thread_obj *currt)
{
    printf("kcall_thread_create\n");

    struct thread_obj *p_thr;
    p_thr = (struct thread_obj *)malloc(sizeof (struct thread_obj));
    p_thr->id = find_thread_slot() + 1;
    p_thr->stk_sz = STACK_SIZE;
    p_thr->stk = malloc(p_thr->stk_sz);
    p_thr->psp = (uint32_t)((char *)p_thr->stk + p_thr->stk_sz - sizeof(struct all_regs));
    p_thr->tls_ptr = NULL;

    struct all_regs *preg = (struct all_regs *)p_thr->psp;
    preg->regpack.psr = 0x01000000;
    preg->regpack.pc = (unsigned long)PARM1;
    preg->regpack.lr = (unsigned long)thrd_exit;
    preg->regpack_manual.lr = (unsigned long)0xffffffac;
 
    ksched_add(p_thr, 0);

    return 0;
}

int kcall_thread_join(struct thread_obj *currt)
{
    printf("kcall_thread_join\n");
    return 0;
}

int kcall_thread_exit(struct thread_obj *currt)
{
    printf("kcall_thread_exit\n");
    return 0;
}

static int find_thread_slot()
{
    for (int i=0; i<MAX_THREADS; ++i)
    {
        if (thr_tbl[i] == NULL)
        {
            return i;
        }
    }
    return -1;
}
