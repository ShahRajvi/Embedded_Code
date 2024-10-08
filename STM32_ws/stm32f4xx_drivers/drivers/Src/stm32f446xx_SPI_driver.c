/*
 * stm32f446xx_SPI_driver.c
 *
 *  Created on: Jul 15, 2024
 *      Author: RShah23
 */

#include "stm32f446xx_SPI_driver.h"


/*********************************************************************
 * @fn      		  - SPI_PeriClockControl
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

void SPI_PeriClockControl(SPI_RegDef_t *pSPIx, uint8_t EnorDi){
	if(EnorDi == ENABLE){
				if(pSPIx == SPI1){
							SPI1_PCLK_EN();
						}
				if(pSPIx == SPI2){
							SPI2_PCLK_EN();
						}
				if(pSPIx == SPI3){
							SPI3_PCLK_EN();
						}
				if(pSPIx == SPI4){
							SPI4_PCLK_EN();
						}
				if(pSPIx == SPI5){
							SPI5_PCLK_EN();
						}
				if(pSPIx == SPI6){
							SPI6_PCLK_EN();
						}
			}

			if(EnorDi == DISABLE){
					if(pSPIx == SPI1){
								SPI1_PCLK_DI();
							}
					if(pSPIx == SPI2){
								SPI2_PCLK_DI();
							}
					if(pSPIx == SPI3){
								SPI3_PCLK_DI();
							}
					if(pSPIx == SPI4){
								SPI4_PCLK_DI();
							}
					if(pSPIx == SPI5){
								SPI5_PCLK_DI();
							}
					if(pSPIx == SPI6){
								SPI6_PCLK_DI();
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

void SPI_Init(SPI_Handle_t *pSPIHandle){
	uint32_t tempreg = 0;

	// Configuring device mode. MSTR bit of CR1
	tempreg |= (pSPIHandle->SPI_Config.SPI_DeviceMode << SPI_CR1_MSTR);

	// Configuring Bus Config. Bit 15 and 14
	if(pSPIHandle->SPI_Config.SPI_BusConfig == SPI_BUS_CONFIG_FullDuplex){
		// Bidi Mode should be cleared (Bit 15)
		tempreg &= ~(1 << SPI_CR1_BIDI_MODE);

	}
	else if(pSPIHandle->SPI_Config.SPI_BusConfig == SPI_BUS_CONFIG_HalfDuplex){
		// Bidi Mode (bit 15) should be set.

		tempreg |= (1 << SPI_CR1_BIDI_MODE);

	}
	else if(pSPIHandle->SPI_Config.SPI_BusConfig == SPI_BUS_CONFIG_Simplex_RXONLY){
		// Bidi Mode (bit 15) should be cleared.
		// Bit 10: 0 for Rx only mode
		tempreg &= ~(1 << SPI_CR1_BIDI_MODE);
		tempreg |= (1 << SPI_CR1_RXONLY);
	}

	// Configuring SPI SCLK Speed bits 3 to 5 of CR1 register
	tempreg |= (pSPIHandle->SPI_Config.SPI_SclkSpeed << SPI_CR1_BR);

	// Configuring DFF bit 11 of CR1 register
	tempreg |= (pSPIHandle->SPI_Config.SPI_DFF << SPI_CR1_DFF);

	// Configuring CPOL bit 1 of CR1 register
	tempreg |= (pSPIHandle->SPI_Config.SPI_CPOL << SPI_CR1_CPOL);

	// Configuring CPHA bit 0 of CR1 register
	tempreg |= (pSPIHandle->SPI_Config.SPI_CPHA << SPI_CR1_CPHA);

	// Configuring SSM bit 9 of CR1 register
	tempreg |= (pSPIHandle->SPI_Config.SPI_SSM << SPI_CR1_SSM);

	pSPIHandle->pSPIx->SPI_CR1 = tempreg;

}


/*****************************************************************
 * @fn          - SPI_DeInit
 *
 * @brief       - This function de-initialize SPI peripherals
 *
 * @param[in]   - SPI_RegDef_t *pSPIx - pointer to the Base address of the SPI peripheral
 *
 * @return      - None
 *
 * @Note        - None
 *
 *****************************************************************/
void SPI_DeInit(SPI_RegDef_t *pSPIx)
{
    if(pSPIx == SPI1)
    {
    	SPI1_REG_RESET();
    }
    else if(pSPIx == SPI2)
    {
        SPI2_REG_RESET();
    }
    else if(pSPIx == SPI3)
    {
        SPI3_REG_RESET();
    }
    else if(pSPIx == SPI4)
    {
        SPI4_REG_RESET();
    }
    else if(pSPIx == SPI5)
    {
        SPI5_REG_RESET();
    }
    else if(pSPIx == SPI6)
    {
        SPI6_REG_RESET();
    }
}

/*****************************************************************
 * @fn          - SPI_SendData
 *
 * @brief       - This function sends data over SPI bus.
 *
 * @param[in]   - Base address of the SPI peripheral
 * @param[in]   - Transmit buffer
 * @param[in]   - Length of data to be sent
 *
 * @return      - None
 *
 * @Note        - Blocking call. or polling type function.
 *
 *****************************************************************/

void SPI_SendData(SPI_RegDef_t *pSPIx, uint8_t *pTxBuffer, uint32_t Len){
	// Check if length of data > 0
	while(Len > 0){
		// Check if Transmit buffer is empty => TXE bit is SET
		//while(!((pSPIx->SPI_SR) & (1 << SPI_SR_TXE)));
		while((SPI_GetFlagStatus(pSPIx, SPI_SR_TXE_FLAG)) == (uint8_t) FLAG_RESET);

		// TX Buffer is now empty. Transmit either 8 or 16 bit of data
		if((pSPIx->SPI_CR1) & (1 << SPI_CR1_DFF)){
			// 16 bit data frame
			pSPIx->SPI_DR = *(uint16_t *)pTxBuffer;
			// Transmitting 2 bytes
			Len--;
			Len--;
			// Incrementing pTXbuffer byte address by 2
			(uint16_t *)pTxBuffer++;

		}
		else{
			pSPIx->SPI_DR = *(uint8_t *)pTxBuffer;
			Len--;
			pTxBuffer++;
		}

	}

}


/*****************************************************************
 * @fn          - SPI_ReceivedData
 *
 * @brief       - This function receives data over SPI
 *                peripheral
 *
 * @param[in]   - Base address of the SPI peripheral
 * @param[in]   - Transmit buffer
 * @param[in]   - Length of transmit buffer
 *
 * @return      - None
 *
 * @Note        - None
 *
 *****************************************************************/
void SPI_ReceiveData(SPI_RegDef_t *pSPIx, uint8_t *pRxBuffer, uint32_t Len){
	// Check if length of data > 0
		while(Len > 0){
			// Check if Receiving buffer is empty => RXNE bit is SET
			//while(!((pSPIx->SPI_SR) & (1 << SPI_SR_RXNE)));
			while((SPI_GetFlagStatus(pSPIx, SPI_SR_RXNE_FLAG)) == (uint8_t) FLAG_RESET);

			// Receiving either 8 or 16 bit of data
			if((pSPIx->SPI_CR1) & (1 << SPI_CR1_DFF)){
				// 16 bit data frame
				*(uint16_t *)pRxBuffer = pSPIx->SPI_DR;
				// Receiving 2 bytes
				Len--;
				Len--;
				// Incrementing pRXbuffer byte address by 2
				(uint16_t *)pRxBuffer++;

			}
			else{
				*(uint8_t *)pRxBuffer = pSPIx->SPI_DR;
				Len--;
				pRxBuffer++;
			}

		}
}

/*****************************************************************
 * @fn          - SPI_GetFlagStatus
 *
 * @brief       - This function check if flag is set in the status register.
 * 				  returns if bit in register is set or not
 *
 * @param[in]   - Base address of the SPI peripheral
 * @param[in]   - Name of flag
 *
 * @return      - Flag status bool (True/False)
 *
 * @Note        - None
 *
 *****************************************************************/
uint8_t SPI_GetFlagStatus(SPI_RegDef_t *pSPIx, uint32_t FlagName){
    if(pSPIx->SPI_SR & FlagName)
    {
        return FLAG_SET;
    }
    return FLAG_RESET;
}




