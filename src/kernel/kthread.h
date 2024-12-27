
#ifndef THREAD_H_INCLUDED
#define THREAD_H_INCLUDED

#include "arm.h"
#include "dlist.h"

#include <stddef.h>
#include <stdint.h>

enum
{
    THR_ST_RUNNING,
    THR_ST_JOINING,
    THR_ST_ZOMBIE,
    THR_ST_DEAD,
};

struct thread_obj
{
    dlist_chain_t chain;
    int id;
    int state;
    struct syscall_regs *reg;
    void *stk;
    size_t stk_sz;
    void *tls_ptr;
    uint32_t psp;
    int joinable;
    struct thread_obj *joiner;

    union state_info
    {
        struct zombie
        {
            void *exit_val;
        } zombie;
        struct joining
        {
            void **value_ptr;
            struct thread_obj *joined_to;
        } joining;
    } state_info;
    int (*continuation_func)(struct thread_obj *);
};

void kthread_init();

extern struct thread_obj *g_currt;

#endif /* THREAD_H_INCLUDED */
