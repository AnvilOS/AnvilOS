
#include <threads.h>
#include <sys/anvil.h>

_Noreturn void thrd_exit(int res)
{
	// Todo: Call key destructors
	_Anvil_thread_exit((void *)res);
}
