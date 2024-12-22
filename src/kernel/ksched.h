
#ifndef SCHED_H_INCLUDED
#define SCHED_H_INCLUDED

#include "kthread.h"

void sched_init();
struct thread_obj *sched_get_currt();
void sched_add(struct thread_obj *t, int head);
void schedule();

extern struct thread_obj *g_currt; 

#endif /* SCHED_H_INCLUDED */
