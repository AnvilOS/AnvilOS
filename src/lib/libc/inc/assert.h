
#ifndef _ASSERT_H_INCLUDED
#define _ASSERT_H_INCLUDED

#ifndef _SYS_ANVIL_INTERNAL_H_INCLUDED
#include <sys/anvil_internal.h>
#endif

#if defined (NDEBUG)
#define assert(__a)     ((void)0)
#else
#define assert(__a)     ( (void)((__a) ? \
                        (void)0 : \
                        __assert(#__a, __FILE__, __LINE__, __func__)) )
#endif

void __assert(const char *__expr, const char *__file, int __line, const char *__func);

#endif /* _ASSERT_H_INCLUDED */
