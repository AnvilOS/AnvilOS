
#ifndef _SETJMP_H_INCLUDED
#define _SETJMP_H_INCLUDED

#ifndef _SYS_ANVIL_INTERNAL_H_INCLUDED
#include <sys/anvil_internal.h>
#endif

// Enough room for r4-r11, r13 and r14
typedef __UINT32_TYPE__ jmp_buf[10];

int setjmp(jmp_buf __env);
_Noreturn void longjmp(jmp_buf __env, int __val);

#endif /* _SETJMP_H_INCLUDED */
