################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/portable/MemMang/heap_1.c \
../src/portable/MemMang/heap_2.c \
../src/portable/MemMang/heap_3.c \
../src/portable/MemMang/heap_4.c \
../src/portable/MemMang/heap_5.c 

OBJS += \
./src/portable/MemMang/heap_1.o \
./src/portable/MemMang/heap_2.o \
./src/portable/MemMang/heap_3.o \
./src/portable/MemMang/heap_4.o \
./src/portable/MemMang/heap_5.o 

C_DEPS += \
./src/portable/MemMang/heap_1.d \
./src/portable/MemMang/heap_2.d \
./src/portable/MemMang/heap_3.d \
./src/portable/MemMang/heap_4.d \
./src/portable/MemMang/heap_5.d 


# Each subdirectory must supply rules for building sources it contributes
src/portable/MemMang/%.o: ../src/portable/MemMang/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DDEBUG -D__CODE_RED -DCORE_M3 -D__LPC17XX__ -I"C:\Users\PCHome\Documents\CNC\Ejs_TPS\TD2-r06\LibFreeRTOS_8.2.3\inc" -I"C:\Users\PCHome\Documents\CNC\Ejs_TPS\TD2-r06\LPC_BaseBoardBB1769_R02\inc" -I"C:\Users\PCHome\Documents\CNC\Ejs_TPS\TD2-r06\LibFreeRTOS_8.2.3\src\demo_code" -I"C:\Users\PCHome\Documents\CNC\Ejs_TPS\TD2-r06\LibFreeRTOS_8.2.3\src\portable\GCC\ARM_CM3" -I"C:\Users\PCHome\Documents\CNC\Ejs_TPS\TD2-r06\lpc_chip_175x_6x\inc" -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


