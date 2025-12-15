
BINARY := anvil

LIBS := ../bsp/libbsp.a

EXTRA_DEPS := ../lib/libc/libc.a arm/lnfile.ld

MODULE_LDFLAGS := \
    -nostartfiles \
    -fno-exceptions \
    -fno-unwind-tables \
    -fno-asynchronous-unwind-tables \
    -T $(SRCDIR)/$(ARCH)/lnfile.ld \
    -ffunction-sections \
    -fdata-sections \
    -fno-move-loop-invariants \
    -Wl,--gc-sections \
    -Wl,-Map,"armcpp.map"
 
MODULE_CPPFLAGS := \
	-I$(SRCDIR) \
	-I$(SRCDIR)/../bsp/stm32-u5/inc 										\
	-I$(SRCDIR)/../bsp/stm32-u5/CMSIS/Device/ST/STM32U5xx/Include 	\
	-I$(SRCDIR)/../bsp/stm32-u5/CMSIS/Include 					\
	-I$(SRCDIR)/../bsp/stm32-u5/BSP/Components/Common 			\
	-I$(SRCDIR)/../bsp/stm32-u5/BSP/B-U585I-IOT02A 			\
    -I$(SRCDIR)/../bsp \
    -I$(SRCDIR)/../bsp/stm32-u5/STM32U5xx_HAL_Driver/Inc \
    -nostartfiles \
    -fno-exceptions -fno-unwind-tables -fno-asynchronous-unwind-tables

include $(PROJECT_ROOT)/make/default.mk
