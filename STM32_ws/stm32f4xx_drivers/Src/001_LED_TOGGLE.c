/*
 * 001_LED_TOGGLE.c
 *
 *  Created on: Feb 4, 2024
 *      Author: RShah23
 */

#include "stm32f446xx.h"

void delay(void){ 		// Implementing software delay
	//
	for(uint32_t i = 0; i<500000; i++);
}


int main(void)
{

	GPIO_Handle_t GPIOLed; 			//Creating a variable of type GPIO_Handle_t to configure the GPIO pin to toggle led 2 in push-pull mode.

	GPIOLed.pGPIOx = GPIOA;			// Using GPIO port A PA5 or D13 to toggle LED2
	GPIOLed.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_5;		// Pin Number set to Pin 5
	GPIOLed.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;		// Pin Mode set to output mode
	GPIOLed.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;		// Pin Speed set to FAST


	//GPIOLed.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_OD; 	// Open Drain configuration. Do not use OD unless its a special application.
	//GPIOLed.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PU;


	// Pull up pull down config.
	 GPIOLed.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;	// Output type set to push pull
	 GPIOLed.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;	// No additional Push pull resistor activation required

	// Enabling Peripheral clock to use with the GPIO port

	GPIO_PeriClockControl(GPIOA, ENABLE);		// Enable clock for GPIO port A

	GPIO_Init(&GPIOLed);


	while(1){
		GPIO_ToggleOutputPin(GPIOA,  GPIO_PIN_NO_5); 	// Toggle output at pin 5 of GPIO port A
		//GPIO_WriteToInputPin(GPIOA, GPIO_PIN_NO_5, DISABLE);
		delay();
	}

	return 0;
}
