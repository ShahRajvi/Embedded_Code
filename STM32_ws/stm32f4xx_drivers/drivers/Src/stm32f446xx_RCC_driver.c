/*
 * stm32f446xx_RCC_driver.c
 *
 *  Created on: July 13, 2024
 *      Author: RShah23
 */

#include "stm32f446xx_RCC_driver.h"

uint16_t AHB_Prescaler[8] = {2,4, 8, 16, 64, 128, 256, 512};
uint8_t APBx_Prescaler[4] = {2, 4, 8, 16};


/*****************************************************************
 * @fn          - RCC_GetPCLK1Value
 *
 * @brief       - This function returns PClock 1 value
 *
 *
 * @return      - PClock 1 value
 *
 * @Note        - None
 *
 *****************************************************************/

uint32_t RCC_GetPCLK1Value(void){
	uint32_t PCLK1, SystemClk;

	uint8_t clksrc, temp, ahbp, apb1p;

	clksrc = ((RCC->RCC_CFGR >> 2) & 0x03);

	if(clksrc == 0){
		SystemClk = 16000000;
	}
	else if(clksrc == 1){
		SystemClk = 8000000;
	}
	else if(clksrc == 2){
		SystemClk = RCC_GetPLLOutputClock();
	}

	// AHBP

	temp = ((RCC->RCC_CFGR >> 4) & 0x0F);
	if(temp < 8){
		ahbp = 1;
	}
	else{
		ahbp = AHB_Prescaler[temp-8];
	}

	// APB1
	temp = ((RCC->RCC_CFGR >> 10) & 0x07);
		if(temp < 4){
			apb1p = 1;
		}
		else{
			apb1p = APBx_Prescaler[temp-4];
		}
		// Calculate pclk
		PCLK1 = (SystemClk / ahbp) / apb1p;

		return PCLK1;
}


/*****************************************************************
 * @fn          - RCC_GetPCLK2Value
 *
 * @brief       - This function returns PClock 2 value
 *
 *
 * @return      - PClock 2 value
 *
 * @Note        - None
 *
 *****************************************************************/
uint32_t RCC_GetPCLK2Value(void){
	uint32_t PCLK2, SystemClk;

	uint8_t clksrc, temp, ahbp, apb2p;

	clksrc = ((RCC->RCC_CFGR >> 2) & 0x03);

	if(clksrc == 0){
		SystemClk = 16000000;
	}
	else if(clksrc == 1){
		SystemClk = 8000000;
	}
	else if(clksrc == 2){
		SystemClk = RCC_GetPLLOutputClock();
	}

	// AHBP

	temp = ((RCC->RCC_CFGR >> 4) & 0x0F);
	if(temp < 8){
		ahbp = 1;
	}
	else{
		ahbp = AHB_Prescaler[temp-8];
	}

	// APB1
	temp = ((RCC->RCC_CFGR >> 10) & 0x07);
		if(temp < 4){
			apb2p = 1;
		}
		else{
			apb2p = APBx_Prescaler[temp-4];
		}
		// Calculate pclk
		PCLK2 = (SystemClk / ahbp) / apb2p;

		return PCLK2;
}

/*****************************************************************
 * @fn          - RCC_GetPLLOutputClock
 *
 * @brief       - This function returns PLL output value
 *
 *
 * @return      - PLL output value
 *
 * @Note        - None
 *
 *****************************************************************/
uint32_t RCC_GetPLLOutputClock(void)
{
    /* Not used for now */
    return 0;
}
