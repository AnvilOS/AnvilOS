
CROSS_PREFIX := $(PROJECT_ROOT)/../cross-tools/bin/arm-anvil-eabi
ARCH := arm
BSP := stm32-u5

GLOBAL_CFLAGS := -std=gnu11 -mcpu=cortex-m33 -DDEBUG     -DUSE_HAL_DRIVER -DSTM32U585xx -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb
GLOBAL_CXXFLAGS := -std=gnu11 -mcpu=cortex-m33 -DDEBUG   -DUSE_HAL_DRIVER -DSTM32U585xx -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb
GLOBAL_CPPFLAGS := -g -O2 -std=gnu11 -mcpu=cortex-m33 -DDEBUG -DUSE_HAL_DRIVER -DSTM32U585xx -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb
GLOBAL_LDFLAGS := -g -std=gnu11 -mcpu=cortex-m33 -DDEBUG -DUSE_HAL_DRIVER -DSTM32U585xx -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb
