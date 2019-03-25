################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/CncController.c \
../src/Display.c \
../src/GCodeDispatch.c \
../src/GCodeDispatchOLD.c \
../src/IRQHandlers.c \
../src/MatrixKeypad.c \
../src/Planner.c \
../src/Robot.c \
../src/Serial.c \
../src/Stepper.c \
../src/appinit.c \
../src/cr_startup_lpc175x_6x.c \
../src/crp.c \
../src/main.c \
../src/sysinit.c 

OBJS += \
./src/CncController.o \
./src/Display.o \
./src/GCodeDispatch.o \
./src/GCodeDispatchOLD.o \
./src/IRQHandlers.o \
./src/MatrixKeypad.o \
./src/Planner.o \
./src/Robot.o \
./src/Serial.o \
./src/Stepper.o \
./src/appinit.o \
./src/cr_startup_lpc175x_6x.o \
./src/crp.o \
./src/main.o \
./src/sysinit.o 

C_DEPS += \
./src/CncController.d \
./src/Display.d \
./src/GCodeDispatch.d \
./src/GCodeDispatchOLD.d \
./src/IRQHandlers.d \
./src/MatrixKeypad.d \
./src/Planner.d \
./src/Robot.d \
./src/Serial.d \
./src/Stepper.d \
./src/appinit.d \
./src/cr_startup_lpc175x_6x.d \
./src/crp.d \
./src/main.d \
./src/sysinit.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__CODE_RED -DCORE_M3 -D__USE_LPCOPEN -D__LPC17XX__ -D__REDLIB__ -I"C:\Users\PCHome\Documents\CNC\Ejs_TPS\TD2-r06\LPC_BaseBoardBB1769_R02\inc" -I"C:\Users\PCHome\Documents\CNC\Ejs_TPS\TD2-r06\LibFreeRTOS_8.2.3\src\demo_code" -I"C:\Users\PCHome\Documents\CNC\Ejs_TPS\TD2-r06\TD2CNC-r00\inc" -I"C:\Users\PCHome\Documents\CNC\Ejs_TPS\TD2-r06\LibFreeRTOS_8.2.3\src\portable\GCC\ARM_CM3" -I"C:\Users\PCHome\Documents\CNC\Ejs_TPS\TD2-r06\LibFreeRTOS_8.2.3\inc" -I"C:\Users\PCHome\Documents\CNC\Ejs_TPS\TD2-r06\lpc_chip_175x_6x\inc" -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


