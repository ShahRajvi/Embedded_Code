/*
 * stm32f446xx_RCC_driver.h
 *
 *  Created on: Jul 13, 2024
 *      Author: RShah23
 */

#ifndef INC_STM32F446XX_RCC_DRIVER_H_
#define INC_STM32F446XX_RCC_DRIVER_H_

#include "stm32f446xx.h"
//Returns APB1 Clock value
uint32_t RCC_GetPCLK1Value(void);

// Returns APB2 Clock Value
uint32_t RCC_GetPCLK2Value(void);
uint32_t RCC_GetPLLOutputClock(void);

#endif /* INC_STM32F446XX_RCC_DRIVER_H_ */
