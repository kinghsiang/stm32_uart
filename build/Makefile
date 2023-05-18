RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include startup/subdir.mk
-include base/subdir.mk
-include User_HandsOn/subdir.mk
-include stm32f4xx_hal_driver/Src/subdir.mk
-include subdir.mk
-include objects.mk


OBJS += \
	$(C_SRCS:../%.c=%.o) $(S_UPPER_SRCS:../%.S=%.o)

C_DEPS += \
	$(C_SRCS:../%.c=%.d)

S_UPPER_DEPS += \
	$(S_UPPER_SRCS:../%.S=%.d)

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
endif

# Add inputs and outputs from these tool invocations to the build variables 
SECONDARY_FLASH += \
	main.hex \
	main.bin

SECONDARY_LIST += \
main.lst \

# All Target
all: main.elf secondary-outputs

# Tool invocations
main.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	arm-none-eabi-gcc \
		-T ../startup/STM32F429ZI_FLASH.ld \
		-nostartfiles -Xlinker --gc-sections \
		-Wl,-Map,main.map -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -o "main.elf" $(OBJS) $(USER_OBJS)
	@echo 'Finished building target: $@'
	@echo ' '

main.hex: main.elf
	arm-none-eabi-objcopy -O ihex main.elf  "main.hex"
	@echo 'Finished building: $@'
	@echo ' '

main.bin: main.elf
	arm-none-eabi-objcopy -O binary main.elf  "main.bin"
	@echo 'Finished building: $@'
	@echo ' '

main.lst: main.elf
	arm-none-eabi-objdump -h -S main.elf > "main.lst"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) \
		$(OBJS) $(C_DEPS) $(ASM_DEPS) \
		$(SECONDARY_FLASH) $(EXECUTABLES) $(SECONDARY_LIST) $(S_UPPER_DEPS) main.elf
	-@echo ' '
	find -name '*.lst' | xargs $(RM)
	$(RM) main.map

secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_LIST) $(SECONDARY_SIZE)

.PHONY: all clean dependents
.SECONDARY:
