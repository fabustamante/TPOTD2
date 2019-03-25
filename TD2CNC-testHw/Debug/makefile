################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: TD2CNC-testHw.axf

# Tool invocations
TD2CNC-testHw.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -L"C:\Users\PCHome\Documents\CNC\Ejs_TPS\TD2-r06\TD2CNC-r00\Debug" -L"C:\Users\PCHome\Documents\CNC\Ejs_TPS\TD2-r06\LPC_BaseBoardBB1769_R02\Debug" -L"C:\Users\PCHome\Documents\CNC\Ejs_TPS\TD2-r06\LibFreeRTOS_8.2.3\Debug" -L"C:\Users\PCHome\Documents\CNC\Ejs_TPS\TD2-r06\lpc_chip_175x_6x\Debug" -Xlinker -Map="TD2CNC-testHw.map" -Xlinker --gc-sections -mcpu=cortex-m3 -mthumb -T "TD2CNC-testHW2_Debug.ld" -o "TD2CNC-testHw.axf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS)$(C_DEPS) TD2CNC-testHw.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size "TD2CNC-testHw.axf"; # arm-none-eabi-objcopy -v -O binary "TD2CNC-testHw.axf" "TD2CNC-testHw.bin" ; # checksum -p LPC1769 -d "TD2CNC-testHw.bin";
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY: post-build

-include ../makefile.targets
