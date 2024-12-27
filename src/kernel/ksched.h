
#ifndef SCHED_H_INCLUDED
#define SCHED_H_INCLUDED

#include "kthread.h"

void ksched_init();
struct thread_obj *ksched_get_currt();
void ksched_add(struct thread_obj *t, int head);
void ksched_block(int state);
void kschedule();

extern struct thread_obj *g_currt; 

#endif /* SCHED_H_INCLUDED */
