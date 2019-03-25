################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/FreeRTOSCommonHooks.c \
../src/croutine.c \
../src/event_groups.c \
../src/list.c \
../src/queue.c \
../src/tasks.c \
../src/timers.c 

OBJS += \
./src/FreeRTOSCommonHooks.o \
./src/croutine.o \
./src/event_groups.o \
./src/list.o \
./src/queue.o \
./src/tasks.o \
./src/timers.o 

C_DEPS += \
./src/FreeRTOSCommonHooks.d \
./src/croutine.d \
./src/event_groups.d \
./src/list.d \
./src/queue.d \
./src/tasks.d \
./src/timers.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DDEBUG -D__CODE_RED -DCORE_M3 -D__LPC17XX__ -I"C:\Users\PCHome\Documents\CNC\Ejs_TPS\TD2-r06\LibFreeRTOS_8.2.3\inc" -I"C:\Users\PCHome\Documents\CNC\Ejs_TPS\TD2-r06\LPC_BaseBoardBB1769_R02\inc" -I"C:\Users\PCHome\Documents\CNC\Ejs_TPS\TD2-r06\LibFreeRTOS_8.2.3\src\demo_code" -I"C:\Users\PCHome\Documents\CNC\Ejs_TPS\TD2-r06\LibFreeRTOS_8.2.3\src\portable\GCC\ARM_CM3" -I"C:\Users\PCHome\Documents\CNC\Ejs_TPS\TD2-r06\lpc_chip_175x_6x\inc" -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


