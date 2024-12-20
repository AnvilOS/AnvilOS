
#include "sched.h"
#include "dlist.h"

extern struct thread_obj thread_1;

static dlist_t sched_list;
struct thread_obj *g_currt = &thread_1;

void sched_init()
{
    dlist_init(&sched_list);
}

struct thread_obj *sched_get_currt()
{
    return g_currt;
}

void sched_add(struct thread_obj *t, int head)
{
    if (head)
    {
        dlist_add_head(&sched_list, (dlist_item_t *)t);
    }
    else
    {
        dlist_add_tail(&sched_list, (dlist_item_t *)t);
    }
}

extern void *_Anvil_tls_tp;

void schedule()
{
    if (g_currt)
    {
        sched_add(g_currt, 0);
    }
    g_currt->tls_ptr = _Anvil_tls_tp;
    // Grab a new thread
    g_currt = (struct thread_obj *)dlist_rem_head(&sched_list);
    _Anvil_tls_tp = g_currt->tls_ptr;
}
