/*
 * stm32f446xx_I2C_drivers.c
 *
 *  Created on: Jul 15, 2024
 *      Author: RShah23
 */

#include "stm32f446xx_I2C_drivers.h"
uint16_t AHB_PreScaler[8] = {2, 4, 8, 16, 64, 128, 256, 512};
uint16_t APB1_PreScaler[8] = {2, 4, 8, 16};

/*********************************************************************
 * @fn      		  - I2C_PeriClockControl
 *
 * @brief             -	This function is for peripheral clock setup
 *
 * @param[in]         - *pI2Cx // Base address of the I2C bus
 * @param[in]         - ENABLE or DISABLE
 *
 * @return      - None
 *
 * @Note        - None

 */

void I2C_PeriClockControl(I2C_RegDef_t *pI2Cx, uint8_t EnorDi){
	if(EnorDi == ENABLE){
				if(pI2Cx == I2C1){
							I2C1_PCLK_EN();
						}
				if(pI2Cx == I2C2){
							I2C2_PCLK_EN();
						}
				if(pI2Cx == I2C3){
							I2C3_PCLK_EN();
						}
			}

			if(EnorDi == DISABLE){
					if(pI2Cx == I2C1){
								I2C1_PCLK_DI();
							}
					if(pI2Cx == I2C2){
								I2C2_PCLK_DI();
							}
					if(pI2Cx == I2C3){
								I2C3_PCLK_DI();
							}

				}
}

/*********************************************************************
 * @fn      		  - SPI_Init
 *
 * @brief             -	This function is for peripheral clock setup
 *
 * @param[in]         - *pSPIx // Base address of the SPI bus
 * @param[in]         - ENABLE or DISABLE
 *
 * @return      - None
 *
 * @Note        - None

 */

void I2C_Init(I2C_Handle_t *pI2CHandle){

	uint32_t tempreg = 0;

	tempreg |= (pI2CHandle->I2C_Config->I2C_ACKControl << I2C_CR1_ACK);
	// Setting the CR1 register
	pI2CHandle->pI2Cx->I2C_CR1 = tempreg;

	// CR2 Register config.
	tempreg = 0;
	tempreg |= RCC_GetPCLK1Value()/1000000U;

	pI2CHandle->pI2Cx->I2C_CR2 |= (tempreg & 0x3F); //Only 6 bits are being stored.


	tempreg = 0;

	// program the device own address

	tempreg |= pI2CHandle->I2C_Config->I2C_DeviceAddress << 1;
	tempreg |= (1 << 14);
	pI2CHandle->pI2Cx->I2C_OAR1 |= tempreg;

	// CCR register config:
	uint16_t ccr_value = 0;
	tempreg = 0;

	if(pI2CHandle->I2C_Config->I2C_SCLSpeed <= I2C_SCL_SPEED_SM){
		// mode is standard mode
		ccr_vlaue = RCC_GetPCLK1Value()/(2*pI2CHandle->I2C_Config->I2C_SCLSpeed);
		tempreg |= (ccr_value & 0x0FFF);
	}
	else{
		// fast mode
		tempreg |= (1 << I2C_CCR_FS);
		tempreg |= (pI2CHandle->I2C_Config->I2C_FMDutyCycle << I2C_CCR_DUTY);
		if(pI2CHandle->I2C_Config->I2C_FMDutyCycle == I2C_FM_DUTY_2){
			ccr_vlaue = RCC_GetPCLK1Value()/(3*pI2CHandle->I2C_Config->I2C_SCLSpeed);
		}
		else{
			ccr_vlaue = RCC_GetPCLK1Value()/(25*pI2CHandle->I2C_Config->I2C_SCLSpeed);
		}
		tempreg |= (ccr_value & 0x0FFF);
		pI2CHandle->pI2Cx->I2C_CCR |= tempreg;
	}



	// Enable clock for I2C
	I2C_PeriClockControl(pI2CHandle->pI2Cx, ENABLE);





}

/*
 * Function: RCC_GetPLLOutputClock()
 */

uint32_t RCC_GetPLLOutputClock(void){
	return 0;
}

/*
 * Function: RCC_GetPCLK1Value()
 */


uint32_t RCC_GetPCLK1Value(void){
	uint32_t pclk1, SystemClk;
	uint8_t clksrc, scaler_temp;
	uint16_t ahbp, apb1;

	// Read bits 2 and 3 of the RCC CFGR Register to get the clock source information.
	clksrc = ((RCC->RCC_CFGR >> 2) & 0x3);

	if(clksrc == 0){
		// System clock = 16MHz
		SystemClk = 16000000;
	}
	else if (clksrc == 1){
		// HSE = 8MHz
		SystemClk = 8000000;
	}
	else if (clksrc == 2){
		// PLL clock
		SystemClk = RCC_GetPLLOutputClock();
	}

	// AHB Prescaler: ECC_CFGR bits 4-7
	scaler_temp = ((RCC->RCC_CFGR >> 4) & 0xF);

	if(scaler_temp >= 8){
		ahbp = AHB_PreScaler[scaler_temp - 8];
	}
	else{
		ahbp = 1;
	}

	//APB1 Prescaler:
	scaler_temp = ((RCC->RCC_CFGR >> 10) & 0x7);

		if(scaler_temp >= 8){
			apb1 = APB1_PreScaler[scaler_temp - 4];
		}
		else{
			apb1 = 1;
		}

	pclk1 = SystemClk / (apb1*ahbp);

	return pclk1;
}

/*****************************************************************
 * @fn          - I2C_DeInit
 *
 * @brief       - This function de-initialize I2C peripherals
 *
 * @param[in]   - I2C_RegDef_t *pI2Cx - pointer to the Base address of the I2C peripheral
 *
 * @return      - None
 *
 * @Note        - None
 *
 *****************************************************************/
void I2C_DeInit(I2C_RegDef_t *pI2Cx)
{
    if(pI2Cx == I2C1)
    {
    	I2C1_REG_RESET();
    }
    else if(pI2Cx == I2C2)
    {
        I2C2_REG_RESET();
    }
    else if(pI2Cx == I2C3)
    {
        I2C3_REG_RESET();
    }
}

/*****************************************************************
 * @fn          - I2C_PeripheralControl
 *
 * @brief       - This function sets I2C peripheral control
 *
 * @param[in]   - Base address of the I2C peripheral
 * @param[in]   - Enable or Disable command
 *
 * @return      - None
 *
 * @Note        - None
 *
 *****************************************************************/
void I2C_PeripheralControl(I2C_RegDef_t *pI2Cx, uint8_t EnorDi)
{
    if(EnorDi == ENABLE)
    {
        pI2Cx->I2C_CR1 |= (1 << I2C_CR1_PE);
    }
    else
    {
        pI2Cx->I2C_CR1 &= ~(1 << I2C_CR1_PE);
    }
}

/*****************************************************************
 * @fn          - I2C_GetFlagStatus
 *
 * @brief       - This function check if flag is set in the status register.
 * 				  returns if bit in register is set or not
 *
 * @param[in]   - Base address of the I2C peripheral
 * @param[in]   - Name of flag
 *
 * @return      - Flag status bool (True/False)
 *
 * @Note        - None
 *
 *****************************************************************/
uint8_t I2C_GetFlagStatus(I2C_RegDef_t *pI2Cx, uint32_t FlagName){
    if((pI2Cx->I2C_SR1 & FlagName) || (pI2Cx->I2C_SR2 & FlagName))
    {
        return FLAG_SET;
    }
    return FLAG_RESET;
}
