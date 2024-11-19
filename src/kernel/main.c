
#include "debug.h"
#include "timer.h"

//#include "stm32u5xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
//#include "b_u585i_iot02a.h"
//#include "b_u585i_iot02a_bus.h"

extern int libc_test();

int main()
{
    debug_init();
    printf("Hello, world\n\r");
////    sys_tick_init();
//    libc_test();
    int i = 0;
    while (1)
    {
    	printf("<%d>\n\r", ++i);
    }
}

void __libc_init_array()
{
}

void debug_putc(int ch)
{
	__io_putchar(ch);
}
