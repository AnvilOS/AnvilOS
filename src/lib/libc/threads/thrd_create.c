
#include <threads.h>
#include <sys/anvil.h>

#include <errno.h>

int thrd_create(thrd_t *thr, thrd_start_t func, void *arg)
{
    int tid = _Anvil_thread_create(func, arg);
    if (tid < 0)
    {
    	if (tid == -ENOMEM)
    	{
    		return thrd_nomem;
    	}
   		return thrd_error;
    }
    if (thr)
    {
        *thr = tid;
    }
    return thrd_success;
}
