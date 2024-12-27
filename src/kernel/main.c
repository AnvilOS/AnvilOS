
#include "debug.h"
#include "timer.h"

#include "ksched.h"
#include "kthread.h"

#include <stdio.h>
#include <stdlib.h>
#include <threads.h>

#include "stm32u5xx_hal.h"

extern int libc_test();

int func_a(void *arg)
{
    int cnt = 0;
    while (1)
    {
        if (++cnt > 1000000)
        {
            debug_putc('A');
            cnt = 0;
        }
    }
}

int func_b(void *arg)
{
   int cnt = 0;
    while (1)
    {
        if (++cnt > 1000000)
        {
            debug_putc('B');
            cnt = 0;
        }
    }
}

int main()
{
    printf("Hello, world\n\r");

    int tid1;
    int err1 = thrd_create(&tid1, func_a, 1);

    int tid2;
    int err2 = thrd_create(&tid2, func_b, 1);

    int cnt = 0;
    while (1)
    {
        if (++cnt > 1000000)
        {
            debug_putc('M');
            cnt = 0;
        }
    }
}

void __libc_init_array()
{
    bsp_init();

    NVIC_SetPriority(SysTick_IRQn, 14);
    NVIC_SetPriority(PendSV_IRQn, 15);

    ksched_init();
    kthread_init();
}

int debug_putc(int ch)
{
	__io_putchar(ch);
}
