
#ifndef _ERRNO_H_INCLUDED
#define _ERRNO_H_INCLUDED

#ifndef _SYS_ANVIL_INTERNAL_H_INCLUDED
#include <sys/anvil_internal.h>
#endif

#define EDOM        1
#define EILSEQ      2
#define ERANGE      3

#define EINVAL      4
#define ENOSYS      5

#define ENOMEM      6

#define EDEADLK     7
#define ESRCH       8
#define EAGAIN      9

#define errno _Errno

#endif /* _ERRNO_H_INCLUDED */
