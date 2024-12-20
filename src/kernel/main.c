
#include "debug.h"
#include "timer.h"

#include <sched.h>
#include <thread.h>

#include <stdio.h>
#include <stdlib.h>
#include <threads.h>

#include "stm32u5xx_hal.h"


/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
//#include "b_u585i_iot02a.h"
//#include "b_u585i_iot02a_bus.h"

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
    int i = 0;
    printf("Hello, world\n\r");
    //sys_tick_init();
    //libc_test();

    int x1 = NVIC_GetPriority(SysTick_IRQn);
    int x2 = NVIC_GetPriority(PendSV_IRQn);
    printf("PRIO %d %d\n", x1, x2);

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
    int x1 = NVIC_GetPriority(SysTick_IRQn);
    int x2 = NVIC_GetPriority(PendSV_IRQn);
 
    bsp_init();

    NVIC_SetPriority(SysTick_IRQn, 14);
    NVIC_SetPriority(PendSV_IRQn, 15);

    int x3 = NVIC_GetPriority(SysTick_IRQn);
    int x4 = NVIC_GetPriority(PendSV_IRQn);

    printf("PRIO %d %d\n", x1, x2);
    printf("PRIO %d %d\n", x3, x4);

    x3 = NVIC_GetPriority(SysTick_IRQn);
    x4 = NVIC_GetPriority(PendSV_IRQn);
    printf("PRIO %d %d\n", x3, x4);

    sched_init();
    thread_init();
}

int debug_putc(int ch)
{
	__io_putchar(ch);
}
