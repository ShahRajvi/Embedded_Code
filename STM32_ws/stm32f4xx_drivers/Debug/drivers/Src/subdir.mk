################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../drivers/Src/stm32f446xx_I2C_drivers.c \
../drivers/Src/stm32f446xx_RCC_driver.c \
../drivers/Src/stm32f446xx_SPI_driver.c \
../drivers/Src/stm32f446xx_USART_driver.c \
../drivers/Src/stm32f446xx_gpio__driver.c 

OBJS += \
./drivers/Src/stm32f446xx_I2C_drivers.o \
./drivers/Src/stm32f446xx_RCC_driver.o \
./drivers/Src/stm32f446xx_SPI_driver.o \
./drivers/Src/stm32f446xx_USART_driver.o \
./drivers/Src/stm32f446xx_gpio__driver.o 

C_DEPS += \
./drivers/Src/stm32f446xx_I2C_drivers.d \
./drivers/Src/stm32f446xx_RCC_driver.d \
./drivers/Src/stm32f446xx_SPI_driver.d \
./drivers/Src/stm32f446xx_USART_driver.d \
./drivers/Src/stm32f446xx_gpio__driver.d 


# Each subdirectory must supply rules for building sources it contributes
drivers/Src/%.o drivers/Src/%.su drivers/Src/%.cyclo: ../drivers/Src/%.c drivers/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F446RETx -c -I../Inc -I"C:/Users/RShah23/Documents/R_ws/stm32f4xx_drivers/drivers/Inc" -I"C:/Users/RShah23/Documents/R_ws/stm32f4xx_drivers/drivers/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
drivers/Src/stm32f446xx_gpio__driver.o: ../drivers/Src/stm32f446xx_gpio__driver.c drivers/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F446RETx -c -I../Inc -I"C:/Users/RShah23/Documents/R_ws/stm32f4xx_drivers/drivers/Inc" -I"C:/Users/RShah23/Documents/R_ws/stm32f4xx_drivers/drivers/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-drivers-2f-Src

clean-drivers-2f-Src:
	-$(RM) ./drivers/Src/stm32f446xx_I2C_drivers.cyclo ./drivers/Src/stm32f446xx_I2C_drivers.d ./drivers/Src/stm32f446xx_I2C_drivers.o ./drivers/Src/stm32f446xx_I2C_drivers.su ./drivers/Src/stm32f446xx_RCC_driver.cyclo ./drivers/Src/stm32f446xx_RCC_driver.d ./drivers/Src/stm32f446xx_RCC_driver.o ./drivers/Src/stm32f446xx_RCC_driver.su ./drivers/Src/stm32f446xx_SPI_driver.cyclo ./drivers/Src/stm32f446xx_SPI_driver.d ./drivers/Src/stm32f446xx_SPI_driver.o ./drivers/Src/stm32f446xx_SPI_driver.su ./drivers/Src/stm32f446xx_USART_driver.cyclo ./drivers/Src/stm32f446xx_USART_driver.d ./drivers/Src/stm32f446xx_USART_driver.o ./drivers/Src/stm32f446xx_USART_driver.su ./drivers/Src/stm32f446xx_gpio__driver.cyclo ./drivers/Src/stm32f446xx_gpio__driver.d ./drivers/Src/stm32f446xx_gpio__driver.o ./drivers/Src/stm32f446xx_gpio__driver.su

.PHONY: clean-drivers-2f-Src

