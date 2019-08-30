
#include "debug.h"

#include <string.h>
#include <stdio.h>

#include "arm.h"
#include "thread.h"

extern char __etext__;
extern char __sdata__;
extern char __edata__;
extern char __sbss__;
extern char __ebss__;
extern char __erom__;

int main();
void SystemInit();

int counter;
int curr_thread;
unsigned long psp1;
unsigned long psp2;
unsigned long psp3;

void start_func()
{
    /* Copy data from ROM to RAM */
    memcpy(&__sdata__, &__erom__, &__edata__ - &__sdata__);

    /* Clear the BSS */
    memset(&__sbss__, 0, &__ebss__ - &__sbss__);

    SystemInit();

    thread_init();

    /* Branch to main and it effectively becomes thread 1 */
    __asm__ __volatile__ ("b main");
}

void NMI_Handler()
{
    printf("NMI_Handler\n");
    while (1);
}

void HardFault_Handler()
{
    printf("HardFault_Handler\n");
    while (1);
}

void MemManage_Handler()
{
    printf("MemManage_Handler\n");
    while (1);
}

void BusFault_Handler()
{
    printf("BusFault_Handler\n");
    while (1);
}

void UsageFault_Handler()
{
    printf("UsageFault_Handler\n");
    while (1);
}

void DebugMon_Handler()
{
    printf("DebugMon_Handler\n");
    while (1);
}

void PendSV_Handler()
{
    printf("PendSV_Handler\n");
    while (1);
}

void SysTick_Handler1()
{
    if (++counter > 1000)
    {
        printf("SysTick_Handler %d\n", curr_thread);
        counter = 0;
    }
    if (curr_thread == 1)
    {
        printf("To 2\n");
        psp1 = psp_get();
        psp_set(psp2);
        curr_thread = 2;
    }
    else if (curr_thread == 2)
    {
        printf("To 3\n");
        psp2 = psp_get();
        psp_set(psp3);
        curr_thread = 3;
    }
    else if (curr_thread == 3)
    {
        printf("To 1\n");
        psp3 = psp_get();
        psp_set(psp1);
        curr_thread = 1;
    }
}
