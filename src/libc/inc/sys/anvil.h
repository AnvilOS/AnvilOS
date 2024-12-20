
#ifndef _SYS_ANVIL_H_INCLUDED
#define _SYS_ANVIL_H_INCLUDED

#ifndef _SYS_ANVIL_INTERNAL_H_INCLUDED
#include <sys/anvil_internal.h>
#endif

int _Anvil_thread_create(int (*__start_routine)(void *), void *__arg);
int _Anvil_thread_join(int __tid, void **__value_ptr);
_Noreturn void _Anvil_thread_exit(void *__value_ptr);

#endif /* _SYS_ANVIL_H_INCLUDED */
