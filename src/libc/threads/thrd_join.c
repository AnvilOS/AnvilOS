
#include <threads.h>
#include <sys/anvil.h>

int thrd_join(thrd_t thr, int *res)
{
	void *ret_ptr;
	if (_Anvil_thread_join(thr, &ret_ptr) != 0)
	{
		return thrd_error;
	}
	*res = (int)ret_ptr;
	return thrd_success;
}
