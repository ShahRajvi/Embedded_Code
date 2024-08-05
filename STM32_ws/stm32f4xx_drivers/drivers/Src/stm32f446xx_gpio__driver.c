/*
 * stm32f446xx_gpio__driver.c
 *
 *  Created on: Jan 28, 2024
 *      Author: RShah23
 */


#include "stm32f446xx_gpio__driver.h"

/*
 * Init and De-Init Port
 */

/******************************************************************************
 *  @fn			GPIO_Init
 *  @brief		This function initializes the GPIO Port
 *
 *  @param[GPIO_Handle_t *pGPIOHandle]	Pointer to GPIO handle that
 *  @param[in]
 *  @param[in]
 *
 *  @return		None
 *
 *  @Note		See section 8.4.1 GPIO port mode register
 *
 ******************************************************************************/

void GPIO_Init(GPIO_Handle_t *pGPIOHandle){
	uint32_t temp = 0;

	// 1. configure the mode of the gpio pin
	if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode <= GPIO_MODE_ANALOG){
		//non-interrupt mode
		temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));			// each pin takes 2 bit fields. The value is left shifted by 2 to set to the corresponding pin Number bits

		pGPIOHandle->pGPIOx->MODER &= ~(0x3 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);								// Clearing the bits before setting a value. Else OR operator would give garbage results.

		pGPIOHandle->pGPIOx->MODER |= temp;																				//setting the GPIOx_MODER register value Bit wise OR to make sure we are only changing the register bits affected

	}
	else{
		// this part is for interrupt mode
	}
	temp = 0;

	// 2. configure the speed
	temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinSpeed << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));			// each pin takes 2 bit fields. The value is left shifted by 2 to set to the corresponding pin Number bits

	pGPIOHandle->pGPIOx->OSPEEDR &= ~(0x3 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);								// Clearing the bits before setting a value. Else OR operator would give garbage results.

	pGPIOHandle->pGPIOx->OSPEEDR |= temp;																			//setting the GPIOx_OSPEEDR register value

	temp = 0;
	// 3. configure the pull up pull down settings (pupd)
	temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinPuPdControl << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));			// each pin takes 2 bit fields. The value is left shifted by 2 to set to the corresponding pin Number bits

	pGPIOHandle->pGPIOx->PUPDR &= ~(0x3 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);								// Clearing the bits before setting a value. Else OR operator would give garbage results.

	pGPIOHandle->pGPIOx->PUPDR |= temp;																						//setting the GPIOx_PUPDR register value

	temp = 0;

	// 4. configure the optype
	temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinOPType << ( pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));					// each pin takes 1 bit fields. The value is left shifted by 1 to set to the corresponding pin Number bits

	pGPIOHandle->pGPIOx->OTYPER &= ~(0x1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);								// Clearing the bits before setting a value. Else OR operator would give garbage results.

	pGPIOHandle->pGPIOx->OTYPER |= temp;																						//setting the GPIOx_OTYPER register value

	temp = 0;

	// 5. configure the alt functionality
	if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode <= GPIO_MODE_ALTFN){		//if mode is in alternate function then use this part of codde.
		//configure the alternate function registers
		uint32_t temp1 = 0, temp2 = 0;
		temp1 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber / 8;
		temp2 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber % 8;

		pGPIOHandle->pGPIOx->AFR[temp1] &= ~(0xF <<  (4 * temp2));								// Clearing the bits before setting a value. Else OR operator would give garbage results.

		pGPIOHandle->pGPIOx->AFR[temp1] |= (pGPIOHandle->GPIO_PinConfig.GPIO_PinAltFunMode << (4 * temp2) );


	}




}


/******************************************************************************
 *  @fn			GPIO_DeInit
 *  @brief		This function de-initializes the GPIO Port
 *
 *  @param[GPIO_RegDef_t *pGPIOx]	base address of the gpio peripheral
 *  @param[in]
 *  @param[in]
 *
 *  @return		None
 *
 *  @Note		Refer to RCC_RHB1RSTR. Can't keep the register value set at all times otherwise the port will always be in reset mode. Need to clear this register. 1 -> 0
 *
 ******************************************************************************/

void GPIO_DeInit(GPIO_RegDef_t *pGPIOx){

	if(pGPIOx == GPIOA){
				GPIOA_REG_RESET();
	}

	if(pGPIOx == GPIOB){
				GPIOB_REG_RESET();
	}

	if(pGPIOx == GPIOC){
				GPIOC_REG_RESET();
	}
	if(pGPIOx == GPIOD){
				GPIOD_REG_RESET();
	}
	if(pGPIOx == GPIOE){
				GPIOE_REG_RESET();
	}
	if(pGPIOx == GPIOF){
				GPIOF_REG_RESET();
	}
	if(pGPIOx == GPIOG){
				GPIOG_REG_RESET();
	}
	if(pGPIOx == GPIOH){
				GPIOH_REG_RESET();
	}
	if(pGPIOx == GPIOI){
				GPIOI_REG_RESET();
	}



}

/******************************************************************************
 *  @fn			GPIO_PeriClockControl
 *  @brief		This function enables or disables the peripheral clock for the given GPIO Port
 *
 *  @param[GPIO_RegDef_t *pGPIOx]	base address of the GPIO peripheral
 *  @param[uint8_t EnorDi]			ENABLE or DISABLE macros
 *  @param[in]
 *
 *  @return		None
 *
 *  @Note		None
 *
 ******************************************************************************/

void GPIO_PeriClockControl(GPIO_RegDef_t *pGPIOx, uint8_t EnorDi){

	/*
	 * Add exception handling here
	 */

	if(EnorDi == ENABLE){

		if(pGPIOx == GPIOA){
			GPIOA_PCLK_EN();
		}
		else if (pGPIOx == GPIOB){
			GPIOB_PCLK_EN();
		}

		else if (pGPIOx == GPIOC){
			GPIOC_PCLK_EN();
		}
		else if (pGPIOx == GPIOD){
			GPIOD_PCLK_EN();
		}
		else if (pGPIOx == GPIOE){
			GPIOE_PCLK_EN();
		}
		else if (pGPIOx == GPIOF){
			GPIOF_PCLK_EN();
		}
		else if (pGPIOx == GPIOG){
			GPIOG_PCLK_EN();
		}
		else if (pGPIOx == GPIOH){
			GPIOH_PCLK_EN();
		}
		else if (pGPIOx == GPIOI){
			GPIOI_PCLK_EN();
		}


	}
	else{ //Disable GPIO PCLKS

		if(pGPIOx == GPIOA){
				GPIOA_PCLK_DI();
			}
			else if (pGPIOx == GPIOB){
				GPIOB_PCLK_DI();
			}

			else if (pGPIOx == GPIOC){
				GPIOC_PCLK_DI();
			}
			else if (pGPIOx == GPIOD){
				GPIOD_PCLK_DI();
			}
			else if (pGPIOx == GPIOE){
				GPIOE_PCLK_DI();
			}
			else if (pGPIOx == GPIOF){
				GPIOF_PCLK_DI();
			}
			else if (pGPIOx == GPIOG){
				GPIOG_PCLK_DI();
			}
			else if (pGPIOx == GPIOH){
				GPIOH_PCLK_DI();
			}
			else if (pGPIOx == GPIOI){
				GPIOI_PCLK_DI();
			}

	}
}

/*
 * Data Read-Write
 */

/******************************************************************************
 *  @fn			GPIO_ReadFromInputPin
 *  @brief		This function reads the GPIO pin (1 bit)
 *
 *  @param[GPIO_RegDef_t *pGPIOx]	base address of the GPIO peripheral
 *  @param[uint8_t PinNumber]			Pin Number macros
 *  @param[in]
 *
 *  @return		uint8_t value of the pin
 *
 *  @Note		None
 *
 ******************************************************************************/

uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber){
	uint8_t value;
	value = ((pGPIOx->IDR >> PinNumber) & 0x00000001);  // Shift the data value to the least significant bit position and return the last bit.
	return value;
}

/******************************************************************************
 *  @fn			GPIO_ReadFromInputPort
 *  @brief		This function reads the GPIO pin (1 bit)
 *
 *  @param[GPIO_RegDef_t *pGPIOx]	base address of the GPIO peripheral
 *  @param[in]
 *  @param[in]
 *
 *  @return		uint16_t value of the port (all 16 pins)
 *
 *  @Note		None
 *
 ******************************************************************************/

uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t *pGPIOx){
	uint16_t value;
	value = (uint16_t)pGPIOx->IDR;
	return value;
}

/******************************************************************************
 *  @fn			GPIO_ReadFromInputPin
 *  @brief		This function reads the GPIO pin (1 bit)
 *
 *  @param[GPIO_RegDef_t *pGPIOx]	base address of the GPIO peripheral
 *  @param[uint8_t PinNumber]		Pin Number macros
 *  @param[uint8_t Value]			Value to be written to the ODR
 *
 *  @return		None
 *
 *  @Note		None
 *
 ******************************************************************************/

void GPIO_WriteToInputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber, uint8_t Value){
	if(Value == GPIO_PIN_SET){
		//write 1 to the output data register at the bit field corresponding to the pin number
		pGPIOx->ODR |= (1 << PinNumber);

	}
	else {
		//write 0 to the output data register at the bit field corresponding to the pin number

		pGPIOx->ODR &= ~(1 << PinNumber);

	}
}

/******************************************************************************
 *  @fn			GPIO_ReadFromInputPort
 *  @brief		This function reads the GPIO pin (1 bit)
 *
 *  @param[GPIO_RegDef_t *pGPIOx]	base address of the GPIO peripheral
 *  @param[uint16_t Value]			Value to be written to the port
 *  @param[in]
 *
 *  @return		None
 *
 *  @Note		None
 *
 ******************************************************************************/
void GPIO_WriteToInputPort(GPIO_RegDef_t *pGPIOx, uint16_t Value){
	pGPIOx->ODR = Value;

}

/******************************************************************************
 *  @fn			GPIO_ToggleOutputPin
 *  @brief		This function reads the GPIO pin (1 bit)
 *
 *  @param[GPIO_RegDef_t *pGPIOx]	base address of the GPIO peripheral
 *  @param[uint8_t PinNumber]		Pin Number macros
 *  @param[in]
 *
 *  @return		None
 *
 *  @Note		None
 *
 ******************************************************************************/

void GPIO_ToggleOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber){
	pGPIOx->ODR = (pGPIOx->ODR ^ (1 << PinNumber));		//XOR operation to toggle the required bit field.
}

/*
 * IRQ Configuration and ISR Handling
 */

void GPIO_IRQConfig(uint8_t IRQNumber, uint8_t IRQPriority, uint8_t EnorDi){

}
void GPIO_IRQHandling(uint8_t PinNumber){

}
