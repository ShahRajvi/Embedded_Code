/*
 * stm32f446xx_gpio__driver.h
 *
 *  Created on: Jan 28, 2024
 *      Author: RShah23
 */

#ifndef INC_STM32F446XX_GPIO__DRIVER_H_
#define INC_STM32F446XX_GPIO__DRIVER_H_

#include "stm32f446xx.h"

typedef struct{
	uint8_t GPIO_PinNumber;			//Possible values from @GPIO_PIN_NO
	uint8_t GPIO_PinMode;			//Possible values from @GPIO_PIN_MODES
	uint8_t GPIO_PinSpeed;			//Possible values from @GPIO_PIN_SPEEDS
	uint8_t GPIO_PinPuPdControl;	//Possible values from @GPIO_PIN_PUPD
	uint8_t GPIO_PinOPType;			//Possible values from @GPIO_OP_TYPES
	uint8_t GPIO_PinAltFunMode;
}GPIO_PinConfig_t;


/*
 * This is a Handle structure for a GPIO pin
 */

typedef struct{
	//pointer to hold the base address of the GPIO peripheral
	GPIO_RegDef_t *pGPIOx; 				// This hold the base address of the GPIO port to which the pin belongs.
	GPIO_PinConfig_t GPIO_PinConfig; 	//This holds GPIO pin configuration settings.

}GPIO_Handle_t;

/***********************************************************************************************************
 * APIs supported by this driver
 * For more information check the function definition
 ***********************************************************************************************************/
/*
 * Init and De-Init Port
 */
void GPIO_Init(GPIO_Handle_t *pGPIOHandle);
void GPIO_DeInit(GPIO_RegDef_t *pGPIOx);

/*
 * Peripheral Clock Setup
 */

void GPIO_PeriClockControl(GPIO_RegDef_t *pGPIOx, uint8_t EnorDi);

/*
 * Data Read-Write
 */

uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber);
uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t *pGPIOx);

void GPIO_WriteToInputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber, uint8_t Value);
void GPIO_WriteToInputPort(GPIO_RegDef_t *pGPIOx, uint16_t Value);

void GPIO_ToggleOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber);

/*
 * IRQ Configuration and ISR Handling
 */

void GPIO_IRQConfig(uint8_t IRQNumber, uint8_t IRQPriority, uint8_t EnorDi);
void GPIO_IRQHandling(uint8_t PinNumber);

/*
 * @GPIO_PIN_NO
 * GPIO Pin Numbers
 */

#define GPIO_PIN_NO_0		0
#define GPIO_PIN_NO_1		1
#define GPIO_PIN_NO_2		2
#define GPIO_PIN_NO_3		3
#define GPIO_PIN_NO_4		4
#define GPIO_PIN_NO_5		5
#define GPIO_PIN_NO_6		6
#define GPIO_PIN_NO_7		7
#define GPIO_PIN_NO_8		8
#define GPIO_PIN_NO_9		9
#define GPIO_PIN_NO_10		10
#define GPIO_PIN_NO_11		11
#define GPIO_PIN_NO_12		12
#define GPIO_PIN_NO_13		13
#define GPIO_PIN_NO_14		14
#define GPIO_PIN_NO_15		15




/*
 * @GPIO_PIN_MODES
 * GPIO pin possible modes
 */

#define GPIO_MODE_IN 		0
#define GPIO_MODE_OUT		1
#define GPIO_MODE_ALTFN		2
#define GPIO_MODE_ANALOG 	3

#define GPIO_MODE_IT_FT		4  		//falling edge
#define GPIO_MODE_IT_RT		5		//rising edge
#define GPIO_MODE_IT_RFT	6		//trigger for rising/falling edge

/*
 * @GPIO_OP_TYPES
 * GPIO Pin possible output types
 */

#define GPIO_OP_TYPE_PP		0
#define GPIO_OP_TYPE_OD		1

/*
 * @GPIO_PIN_SPEEDS
 * GPIO pin possible speeds
 */

#define GPIO_SPEED_LOW 			0
#define GPIO_SPEED_MEDIUM		1
#define GPIO_SPEED_FAST			2
#define GPIO_SPEED_HIGH 		3

/*
 * @GPIO_PIN_PUPD
 * GPIO pin Pull up and Pull Down config macros
 */

#define GPIO_NO_PUPD 		0
#define GPIO_PIN_PU			1
#define GPIO_PIN_PD			2


#endif /* INC_STM32F446XX_GPIO__DRIVER_H_ */
