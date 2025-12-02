################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/Encoder/encoder.c 

OBJS += \
./Drivers/Encoder/encoder.o 

C_DEPS += \
./Drivers/Encoder/encoder.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/Encoder/%.o Drivers/Encoder/%.su Drivers/Encoder/%.cyclo: ../Drivers/Encoder/%.c Drivers/Encoder/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F429xx -c -I../Core/Inc -I"C:/Users/ADMIN/Desktop/FOC/Drivers/Encoder" -I"C:/Users/ADMIN/Desktop/FOC/Drivers/FOC" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-Encoder

clean-Drivers-2f-Encoder:
	-$(RM) ./Drivers/Encoder/encoder.cyclo ./Drivers/Encoder/encoder.d ./Drivers/Encoder/encoder.o ./Drivers/Encoder/encoder.su

.PHONY: clean-Drivers-2f-Encoder

