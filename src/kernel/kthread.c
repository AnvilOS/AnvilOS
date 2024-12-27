
#include "kthread.h"
#include "ksyscall.h"
#include "ksched.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <string.h>
#include <threads.h>
#include <errno.h>
#include <assert.h>

#define STACK_SIZE (1024)           // In bytes

#define MAX_THREADS 16

#include "stm32u5xx_hal.h"

struct thread_obj *thr_tbl[MAX_THREADS];
struct thread_obj *g_currt;
extern char _estack;

static int find_thread_slot();
static struct thread_obj *thread_new();
static void thread_delete(struct thread_obj *t);
static int thread_join_cont(struct thread_obj *currt);

void kthread_init()
{
    __disable_irq();

    struct thread_obj *p_thr = thread_new();
    p_thr->psp = (uint32_t)((char *)p_thr->stk + STACK_SIZE);

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

    struct thread_obj *p_thr = thread_new();
    p_thr->psp = (uint32_t)((char *)p_thr->stk + p_thr->stk_sz - sizeof(struct all_regs));

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
    // Join a thread and return its exit value
    // PARM1  : tid
    // PARM2  : ptr to void*
    // RETVAL : 0 or -ERRNO

    printf("kcall_thread_join\n");

    struct thread_obj *exiter;
    //int err;

    if (currt->id == (int)PARM1)
    {
        // Posix recommends we detect this
        printf("kcall_threadjoin EDEADLK\n");
        return -EDEADLK;
    }

    if ((exiter = thr_tbl[PARM1]) == NULL)
    {
        printf("kcall_threadjoin ESRCH %d\n", (int)PARM1);
        return -ESRCH;
    }

    if (!exiter->joinable || exiter->joiner != NULL)
    {
        // Someone is already joining him
        printf("kcall_threadjoin not joinable or already joined\n");
        return -EINVAL;
    }

    // Join the thread
    exiter->joiner = currt;
    currt->state_info.joining.joined_to = exiter;
    currt->state_info.joining.value_ptr = (void **)PARM2;
    currt->continuation_func = thread_join_cont;

    if (exiter->state != THR_ST_ZOMBIE)
    {
        // We need to wait for him
        ksched_block(THR_ST_JOINING);
    }

    return 0;
}

static int thread_join_cont(struct thread_obj *currt)
{
    // This runs when we wake-up after waiting for another
    // thread to exit
    // We need to untangle them and dispose of the zombie thread but we do that
    // only if the kcopy to user succeeds.

    struct thread_obj *zombie;

    printf("kthreadjoin_cont %d\n", currt->id);

    // Unhook ourselves from the zombie thread
    zombie = currt->state_info.joining.joined_to;

    assert(zombie);

    currt->state_info.joining.joined_to = NULL;

    zombie->joiner = NULL;

    // XXX: If this fails, we return an error from threadjoin and leave the
    // zombie as a zombie
    *currt->state_info.joining.value_ptr = zombie->state_info.zombie.exit_val;

    zombie->state = THR_ST_DEAD;
    thread_delete(zombie);

    return 0;
}

int kcall_thread_exit(struct thread_obj *currt)
{
    printf("kcall_thread_exit\n");

    if (!currt->joinable)
    {
        // We cannot be joined so we die immediately
        printf("kcall_thread_exit DEAD\n");
        ksched_block(THR_ST_DEAD);
        thread_delete(currt);
        return 0;
    }

    if (currt->joiner != NULL)
    {
        // Someone is waiting for us so make him ready.
        ksched_add(currt->joiner, 0);
    }

    currt->state_info.zombie.exit_val = (void *)PARM1;
    ksched_block(THR_ST_ZOMBIE);

    return 0;
}

static int find_thread_slot()
{
    for (int i=1; i<MAX_THREADS; ++i)
    {
        if (thr_tbl[i] == NULL)
        {
            return i;
        }
    }
    return -1;
}

static struct thread_obj *thread_new()
{
    struct thread_obj *t;
    int id;
    
    if ((id = find_thread_slot()) == -1)
    {
        return NULL;
    }
    if ((t = (struct thread_obj *)malloc(sizeof (struct thread_obj))) == NULL)
    {
        return NULL;
    }
    t->stk_sz = STACK_SIZE;
    if ((t->stk = malloc(t->stk_sz)) == NULL)
    {
        free(t);
        return NULL;
    }
    t->id = id;
    t->psp = (uint32_t)((char *)t->stk + STACK_SIZE);
    t->tls_ptr = NULL;
    thr_tbl[t->id] = t;

    return t;
}

static void thread_delete(struct thread_obj *t)
{
    thr_tbl[t->id] = NULL;
    if (t->stk)
    {
        free(t->stk);
    }
    free(t);
}
