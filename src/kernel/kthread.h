
#ifndef THREAD_H_INCLUDED
#define THREAD_H_INCLUDED

#include "arm.h"
#include "dlist.h"

#include <stddef.h>
#include <stdint.h>

enum
{
    THR_ST_RUNNING,
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
};

void thread_init();

#endif /* THREAD_H_INCLUDED */
