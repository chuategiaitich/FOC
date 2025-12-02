################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/FOC/FOC.c \
../Drivers/FOC/FOC_Math.c \
../Drivers/FOC/FOC_PID.c \
../Drivers/FOC/FOC_fast_sincos.c 

OBJS += \
./Drivers/FOC/FOC.o \
./Drivers/FOC/FOC_Math.o \
./Drivers/FOC/FOC_PID.o \
./Drivers/FOC/FOC_fast_sincos.o 

C_DEPS += \
./Drivers/FOC/FOC.d \
./Drivers/FOC/FOC_Math.d \
./Drivers/FOC/FOC_PID.d \
./Drivers/FOC/FOC_fast_sincos.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/FOC/%.o Drivers/FOC/%.su Drivers/FOC/%.cyclo: ../Drivers/FOC/%.c Drivers/FOC/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F429xx -c -I../Core/Inc -I"C:/Users/ADMIN/Desktop/FOC/Drivers/Encoder" -I"C:/Users/ADMIN/Desktop/FOC/Drivers/FOC" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-FOC

clean-Drivers-2f-FOC:
	-$(RM) ./Drivers/FOC/FOC.cyclo ./Drivers/FOC/FOC.d ./Drivers/FOC/FOC.o ./Drivers/FOC/FOC.su ./Drivers/FOC/FOC_Math.cyclo ./Drivers/FOC/FOC_Math.d ./Drivers/FOC/FOC_Math.o ./Drivers/FOC/FOC_Math.su ./Drivers/FOC/FOC_PID.cyclo ./Drivers/FOC/FOC_PID.d ./Drivers/FOC/FOC_PID.o ./Drivers/FOC/FOC_PID.su ./Drivers/FOC/FOC_fast_sincos.cyclo ./Drivers/FOC/FOC_fast_sincos.d ./Drivers/FOC/FOC_fast_sincos.o ./Drivers/FOC/FOC_fast_sincos.su

.PHONY: clean-Drivers-2f-FOC

