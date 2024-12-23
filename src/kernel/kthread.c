
#include "kthread.h"
#include "ksyscall.h"
#include "ksched.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <string.h>
#include <threads.h>

#include "stm32u5xx_hal.h"

struct thread_obj thread_1;
#define THREAD_1_STACK_SIZE (1024)

uint64_t stk1[THREAD_1_STACK_SIZE];
extern uint64_t _estack;

void thread_init()
{
    thread_1.id = 1;
    thread_1.stk_sz = THREAD_1_STACK_SIZE * sizeof(uint64_t);
    thread_1.stk = stk1;
    thread_1.psp = (uint32_t)(thread_1.stk + THREAD_1_STACK_SIZE);
    thread_1.tls_ptr = NULL;

    __disable_irq();

    // Copy our current stack frame from the MSP (which from
    // now on will be used for interrupts) to thread1's PSP
    uint64_t *s = (uint64_t *)__get_MSP();
    size_t n = &_estack - (uint64_t *)__get_MSP();
    uint64_t *d = stk1 + THREAD_1_STACK_SIZE - n;
    memcpy(d, s, n * sizeof(uint64_t));

    // Point the psp at the thread 1 stack 
    __set_PSP((uint32_t)d);
    __set_MSP((uint32_t)&_estack);
    __set_CONTROL(__get_CONTROL() | 2);

    g_currt = &thread_1;

    __enable_irq();

    // If we want to run threads unprivileged, uncomment this
    //__set_CONTROL(__get_CONTROL() | 1);
}

int kcall_thread_create(struct thread_obj *currt)
{
    printf("kcall_thread_create\n");

    struct thread_obj *p_thr;
    p_thr = (struct thread_obj *)malloc(sizeof (struct thread_obj));
    p_thr->stk_sz = 256;
    p_thr->stk = (uint64_t *)malloc(p_thr->stk_sz);
    p_thr->id = 2;
    p_thr->psp = (uint32_t)((struct regpack *)(p_thr->stk + p_thr->stk_sz - sizeof(struct all_regs)));
    p_thr->tls_ptr = NULL;

    struct all_regs *preg = p_thr->psp;
    preg->regpack.psr = 0x01000000;
    preg->regpack.pc = (unsigned long)PARM1;
    preg->regpack.lr = (unsigned long)thrd_exit;
    preg->regpack_manual.lr = (unsigned long)0xffffffac;
 
    sched_add(p_thr, 0);

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

    // p_thr->psp = (uint32_t)((struct regpack *)(p_thr->stk + p_thr->stk_sz - sizeof(struct regpack)));
    // p_thr->tls_ptr = NULL;

    // struct regpack *preg = p_thr->psp;
    // //preg->psr = 0x01000000;
    // // *((uint32_t *)(p_thr->psp)+15) = 0x01000000;
    // // *((uint32_t *)(p_thr->psp)+14) = (unsigned long)PARM1;

    // preg->psr = 0x01000000;
    // preg->pc = (unsigned long)PARM1;

    // printf("%08lx %08lx\n", *((uint32_t *)p_thr->psp+15), *((uint32_t *)p_thr->psp+14));

    // p_thr->pc = (unsigned long)0xffffffac;
