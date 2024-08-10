################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ThirdParty/Segger_v3.54/OS/SEGGER_SYSVIEW_FreeRTOS.c 

OBJS += \
./ThirdParty/Segger_v3.54/OS/SEGGER_SYSVIEW_FreeRTOS.o 

C_DEPS += \
./ThirdParty/Segger_v3.54/OS/SEGGER_SYSVIEW_FreeRTOS.d 


# Each subdirectory must supply rules for building sources it contributes
ThirdParty/Segger_v3.54/OS/%.o ThirdParty/Segger_v3.54/OS/%.su ThirdParty/Segger_v3.54/OS/%.cyclo: ../ThirdParty/Segger_v3.54/OS/%.c ThirdParty/Segger_v3.54/OS/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I../Core/Inc -I"C:/Users/rajvi/OneDrive/Documents/00_Projects/Embedded_Code/RTOS_ws/FreeRTOS_Project/ThirdParty/Segger/Config" -I"C:/Users/rajvi/OneDrive/Documents/00_Projects/Embedded_Code/RTOS_ws/FreeRTOS_Project/ThirdParty/Segger/OS" -I"C:/Users/rajvi/OneDrive/Documents/00_Projects/Embedded_Code/RTOS_ws/FreeRTOS_Project/ThirdParty/Segger/SEGGER" -I"C:/Users/rajvi/OneDrive/Documents/00_Projects/Embedded_Code/RTOS_ws/FreeRTOS_Project/ThirdParty/FreeRTOS" -I"C:/Users/rajvi/OneDrive/Documents/00_Projects/Embedded_Code/RTOS_ws/FreeRTOS_Project/ThirdParty/FreeRTOS/include" -I"C:/Users/rajvi/OneDrive/Documents/00_Projects/Embedded_Code/RTOS_ws/FreeRTOS_Project/ThirdParty/FreeRTOS/portable/GCC/ARM_CM4F" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-ThirdParty-2f-Segger_v3-2e-54-2f-OS

clean-ThirdParty-2f-Segger_v3-2e-54-2f-OS:
	-$(RM) ./ThirdParty/Segger_v3.54/OS/SEGGER_SYSVIEW_FreeRTOS.cyclo ./ThirdParty/Segger_v3.54/OS/SEGGER_SYSVIEW_FreeRTOS.d ./ThirdParty/Segger_v3.54/OS/SEGGER_SYSVIEW_FreeRTOS.o ./ThirdParty/Segger_v3.54/OS/SEGGER_SYSVIEW_FreeRTOS.su

.PHONY: clean-ThirdParty-2f-Segger_v3-2e-54-2f-OS

