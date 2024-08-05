################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ThirdParty/Segger/SEGGER/SEGGER_RTT.c \
../ThirdParty/Segger/SEGGER/SEGGER_RTT_printf.c \
../ThirdParty/Segger/SEGGER/SEGGER_SYSVIEW.c 

S_UPPER_SRCS += \
../ThirdParty/Segger/SEGGER/SEGGER_RTT_ASM_ARMv7M.S 

OBJS += \
./ThirdParty/Segger/SEGGER/SEGGER_RTT.o \
./ThirdParty/Segger/SEGGER/SEGGER_RTT_ASM_ARMv7M.o \
./ThirdParty/Segger/SEGGER/SEGGER_RTT_printf.o \
./ThirdParty/Segger/SEGGER/SEGGER_SYSVIEW.o 

S_UPPER_DEPS += \
./ThirdParty/Segger/SEGGER/SEGGER_RTT_ASM_ARMv7M.d 

C_DEPS += \
./ThirdParty/Segger/SEGGER/SEGGER_RTT.d \
./ThirdParty/Segger/SEGGER/SEGGER_RTT_printf.d \
./ThirdParty/Segger/SEGGER/SEGGER_SYSVIEW.d 


# Each subdirectory must supply rules for building sources it contributes
ThirdParty/Segger/SEGGER/%.o ThirdParty/Segger/SEGGER/%.su ThirdParty/Segger/SEGGER/%.cyclo: ../ThirdParty/Segger/SEGGER/%.c ThirdParty/Segger/SEGGER/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I../Core/Inc -I"C:/Users/rajvi/OneDrive/Documents/00_Projects/Embedded_Code/RTOS_ws/FreeRTOS_Project/ThirdParty/Segger/Config" -I"C:/Users/rajvi/OneDrive/Documents/00_Projects/Embedded_Code/RTOS_ws/FreeRTOS_Project/ThirdParty/Segger/OS" -I"C:/Users/rajvi/OneDrive/Documents/00_Projects/Embedded_Code/RTOS_ws/FreeRTOS_Project/ThirdParty/Segger/SEGGER" -I"C:/Users/rajvi/OneDrive/Documents/00_Projects/Embedded_Code/RTOS_ws/FreeRTOS_Project/ThirdParty/FreeRTOS" -I"C:/Users/rajvi/OneDrive/Documents/00_Projects/Embedded_Code/RTOS_ws/FreeRTOS_Project/ThirdParty/FreeRTOS/include" -I"C:/Users/rajvi/OneDrive/Documents/00_Projects/Embedded_Code/RTOS_ws/FreeRTOS_Project/ThirdParty/FreeRTOS/portable/GCC/ARM_CM4F" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
ThirdParty/Segger/SEGGER/%.o: ../ThirdParty/Segger/SEGGER/%.S ThirdParty/Segger/SEGGER/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m4 -g3 -DDEBUG -c -I"C:/Users/rajvi/OneDrive/Documents/00_Projects/Embedded_Code/RTOS_ws/FreeRTOS_Project/ThirdParty/Segger/SEGGER" -I"C:/Users/rajvi/OneDrive/Documents/00_Projects/Embedded_Code/RTOS_ws/FreeRTOS_Project/ThirdParty/Segger/Config" -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"

clean: clean-ThirdParty-2f-Segger-2f-SEGGER

clean-ThirdParty-2f-Segger-2f-SEGGER:
	-$(RM) ./ThirdParty/Segger/SEGGER/SEGGER_RTT.cyclo ./ThirdParty/Segger/SEGGER/SEGGER_RTT.d ./ThirdParty/Segger/SEGGER/SEGGER_RTT.o ./ThirdParty/Segger/SEGGER/SEGGER_RTT.su ./ThirdParty/Segger/SEGGER/SEGGER_RTT_ASM_ARMv7M.d ./ThirdParty/Segger/SEGGER/SEGGER_RTT_ASM_ARMv7M.o ./ThirdParty/Segger/SEGGER/SEGGER_RTT_printf.cyclo ./ThirdParty/Segger/SEGGER/SEGGER_RTT_printf.d ./ThirdParty/Segger/SEGGER/SEGGER_RTT_printf.o ./ThirdParty/Segger/SEGGER/SEGGER_RTT_printf.su ./ThirdParty/Segger/SEGGER/SEGGER_SYSVIEW.cyclo ./ThirdParty/Segger/SEGGER/SEGGER_SYSVIEW.d ./ThirdParty/Segger/SEGGER/SEGGER_SYSVIEW.o ./ThirdParty/Segger/SEGGER/SEGGER_SYSVIEW.su

.PHONY: clean-ThirdParty-2f-Segger-2f-SEGGER

