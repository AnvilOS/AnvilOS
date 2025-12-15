
#ifndef _PTHREAD_H_INCLUDED
#define _PTHREAD_H_INCLUDED

#ifndef _SYS_ANVIL_INTERNAL_H_INCLUDED
#include <sys/anvil_internal.h>
#endif

#include <sched.h>
#include <time.h>

typedef int pthread_t;
typedef int pthread_key_t;
typedef struct { int a; } pthread_attr_t;
typedef struct { int a; } pthread_mutexattr_t;
typedef struct { int a; } pthread_mutex_t;
typedef struct { int a; } pthread_cond_t;
typedef struct { int a; } pthread_once_t;

#define PTHREAD_MUTEX_RECURSIVE         1

#define PTHREAD_MUTEX_INITIALIZER       { 0 }
#define PTHREAD_ONCE_INIT               { 0 }

int   pthread_cond_broadcast(pthread_cond_t *);
int   pthread_cond_destroy(pthread_cond_t *);
int   pthread_cond_signal(pthread_cond_t *);
int   pthread_cond_timedwait(pthread_cond_t *restrict, pthread_mutex_t *restrict, const struct timespec *restrict);
int   pthread_cond_wait(pthread_cond_t *restrict, pthread_mutex_t *restrict);
int   pthread_create(pthread_t *restrict, const pthread_attr_t *restrict, void *(*)(void*), void *restrict);
int   pthread_detach(pthread_t);
int   pthread_equal(pthread_t, pthread_t);
void  *pthread_getspecific(pthread_key_t);
int   pthread_join(pthread_t, void **);
int   pthread_key_create(pthread_key_t *, void (*)(void*));
int   pthread_key_delete(pthread_key_t);
int   pthread_mutex_destroy(pthread_mutex_t *);
int   pthread_mutex_init(pthread_mutex_t *restrict, const pthread_mutexattr_t *restrict);
int   pthread_mutex_lock(pthread_mutex_t *);
int   pthread_mutex_trylock(pthread_mutex_t *);
int   pthread_mutex_unlock(pthread_mutex_t *);
int   pthread_mutexattr_destroy(pthread_mutexattr_t *);
int   pthread_mutexattr_init(pthread_mutexattr_t *);
int   pthread_mutexattr_settype(pthread_mutexattr_t *, int );
int   pthread_once(pthread_once_t *, void (*)(void));
pthread_t pthread_self(void);
int   pthread_setspecific(pthread_key_t, const void *);

#define GTHREAD_USE_WEAK 0
#define _GLIBCXX_GTHREAD_USE_WEAK 0

#endif /* _PTHREAD_H_INCLUDED */

