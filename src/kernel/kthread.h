
#ifndef THREAD_H_INCLUDED
#define THREAD_H_INCLUDED

#include "arm.h"
#include "dlist.h"

#include <stddef.h>
#include <stdint.h>

enum
{
    THR_ST_RUNNING,
    THR_ST_ZOMBIE,
    THR_ST_DEAD,
};

struct thread_obj
{
    dlist_chain_t chain;
    int id;
    int state;
    struct syscall_regs *reg;
    uint64_t *stk;
    size_t stk_sz;
    void *tls_ptr;
    uint32_t psp;
    int joinable;
    struct thread_obj *joiner;
    void *exit_val;
};

void kthread_init();

extern struct thread_obj *g_currt;

#endif /* THREAD_H_INCLUDED */
