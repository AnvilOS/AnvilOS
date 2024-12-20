
BSP_INCLUDE_PATHS := \
	-I$(SRCDIR)/$(BSP)/inc \
	-I$(SRCDIR)/$(BSP)/STM32U5xx_HAL_Driver/Inc \
	-I$(SRCDIR)/$(BSP)/STM32U5xx_HAL_Driver/Inc/Legacy \
	-I$(SRCDIR)/$(BSP)/CMSIS/Device/ST/STM32U5xx/Include \
	-I$(SRCDIR)/$(BSP)/CMSIS/Include \
	-I$(SRCDIR)/$(BSP)/BSP/Components/Common \
	-I$(SRCDIR)/$(BSP)/BSP/B-U585I-IOT02A 			

BSP_SRCS := \
	Startup/startup_stm32u585aiixq.S \
	src/main.c \
	src/system_stm32u5xx.c \
	src/stm32u5xx_hal_msp.c \
	STM32U5xx_HAL_Driver/Src/stm32u5xx_hal_pwr_ex.c \
	STM32U5xx_HAL_Driver/Src/stm32u5xx_hal_rcc.c \
	STM32U5xx_HAL_Driver/Src/stm32u5xx_hal.c \
	BSP/B-U585I-IOT02A/b_u585i_iot02a.c \
	BSP/B-U585I-IOT02A/b_u585i_iot02a_bus.c \
	STM32U5xx_HAL_Driver/Src/stm32u5xx_hal_cortex.c \
	STM32U5xx_HAL_Driver/Src/stm32u5xx_hal_dma.c \
	STM32U5xx_HAL_Driver/Src/stm32u5xx_hal_dma_ex.c \
	STM32U5xx_HAL_Driver/Src/stm32u5xx_hal_exti.c \
	STM32U5xx_HAL_Driver/Src/stm32u5xx_hal_gpio.c \
	STM32U5xx_HAL_Driver/Src/stm32u5xx_hal_icache.c \
	STM32U5xx_HAL_Driver/Src/stm32u5xx_hal_mdf.c \
	STM32U5xx_HAL_Driver/Src/stm32u5xx_hal_pwr.c \
	STM32U5xx_HAL_Driver/Src/stm32u5xx_hal_rcc_ex.c \
	STM32U5xx_HAL_Driver/Src/stm32u5xx_hal_uart.c \
	STM32U5xx_HAL_Driver/Src/stm32u5xx_hal_uart_ex.c
