################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ThirdParty/Segger/Config/SEGGER_SYSVIEW_Config_FreeRTOS.c 

OBJS += \
./ThirdParty/Segger/Config/SEGGER_SYSVIEW_Config_FreeRTOS.o 

C_DEPS += \
./ThirdParty/Segger/Config/SEGGER_SYSVIEW_Config_FreeRTOS.d 


# Each subdirectory must supply rules for building sources it contributes
ThirdParty/Segger/Config/%.o ThirdParty/Segger/Config/%.su ThirdParty/Segger/Config/%.cyclo: ../ThirdParty/Segger/Config/%.c ThirdParty/Segger/Config/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I"C:/Users/rajvi/OneDrive/Documents/00_Projects/Embedded_Code/RTOS_ws/FreeRTOS_Project/ThirdParty/Segger/Config" -I"C:/Users/rajvi/OneDrive/Documents/00_Projects/Embedded_Code/RTOS_ws/FreeRTOS_Project/ThirdParty/Segger/OS" -I"C:/Users/rajvi/OneDrive/Documents/00_Projects/Embedded_Code/RTOS_ws/FreeRTOS_Project/ThirdParty/Segger/SEGGER" -I../Core/Inc -I"C:/Users/rajvi/OneDrive/Documents/00_Projects/Embedded_Code/RTOS_ws/FreeRTOS_Project/ThirdParty/FreeRTOS" -I"C:/Users/rajvi/OneDrive/Documents/00_Projects/Embedded_Code/RTOS_ws/FreeRTOS_Project/ThirdParty/FreeRTOS/include" -I"C:/Users/rajvi/OneDrive/Documents/00_Projects/Embedded_Code/RTOS_ws/FreeRTOS_Project/ThirdParty/FreeRTOS/portable/GCC/ARM_CM4F" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-ThirdParty-2f-Segger-2f-Config

clean-ThirdParty-2f-Segger-2f-Config:
	-$(RM) ./ThirdParty/Segger/Config/SEGGER_SYSVIEW_Config_FreeRTOS.cyclo ./ThirdParty/Segger/Config/SEGGER_SYSVIEW_Config_FreeRTOS.d ./ThirdParty/Segger/Config/SEGGER_SYSVIEW_Config_FreeRTOS.o ./ThirdParty/Segger/Config/SEGGER_SYSVIEW_Config_FreeRTOS.su

.PHONY: clean-ThirdParty-2f-Segger-2f-Config

