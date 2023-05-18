# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
	../User_HandsOn/main.c \

# Each subdirectory must supply rules for building sources it contributes
User_HandsOn/%.o: ../User_HandsOn/%.c
	@echo 'Building file: $<'
	arm-none-eabi-gcc \
		-D STM32F429_439xx -D STM32F429xx -D __VFP_FP__ \
		-I ../base \
		-I ../User_HandsOn \
		-I ../startup \
		-I ../stm32f4xx_hal_driver/Inc \
		-O0 -ffunction-sections -fdata-sections \
		-Wall -std=gnu99 -Wa,-adhlns="$@.lst" -c -fmessage-length=0 \
		-MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '