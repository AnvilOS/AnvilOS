
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
    printf("Hello, world\n\r");
    //sys_tick_init();
    libc_test();
    while (1)
    {

    }
}

void __libc_init_array()
{
    bsp_init();
}

void debug_putc(int ch)
{
	__io_putchar(ch);
}
