
#include "ksched.h"
#include "dlist.h"

static dlist_t sched_list = { &sched_list, &sched_list };

void ksched_init()
{
    dlist_init(&sched_list);
}

struct thread_obj *ksched_get_currt()
{
    return g_currt;
}

void ksched_add(struct thread_obj *t, int head)
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

void ksched_block(int state)
{
    g_currt->state = state;
    if (state != THR_ST_RUNNING)
    {
        g_currt = NULL;
    }
}

extern void *_Anvil_tls_tp;

void kschedule()
{
    if (dlist_is_empty(&sched_list))
    {
        return;
    }
    if (g_currt)
    {
        ksched_add(g_currt, 0);
    }
    g_currt->tls_ptr = _Anvil_tls_tp;
    // Grab a new thread
    g_currt = (struct thread_obj *)dlist_rem_head(&sched_list);
    _Anvil_tls_tp = g_currt->tls_ptr;
}
