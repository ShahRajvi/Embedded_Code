/*
 * led_effect.c
 *
 *  Created on: Aug 11, 2024
 *      Author: rajvi
 */


#include "main.h"

void led_effect_stop(void)
{
	for(int i = 0 ; i < 4 ; i++)
		xTimerStop(led_timer_handle[i],portMAX_DELAY);
}

void led_effect(int n )
{
	led_effect_stop();
	xTimerStart(led_timer_handle[n-1], portMAX_DELAY);

}


void LED_effect1(){
	// LED2 toggle at 1s
	HAL_GPIO_TogglePin(GPIOA, LED_GREEN_PIN);
	vTaskDelay(pdMS_TO_TICKS(1000));
}


void LED_effect2(){
	// LED2 toggle at 2s
	HAL_GPIO_TogglePin(GPIOA, LED_GREEN_PIN);
	vTaskDelay(pdMS_TO_TICKS(2000));
}

void LED_effect3(){
	// LED2 toggle at 3s
	HAL_GPIO_TogglePin(GPIOA, LED_GREEN_PIN);
	vTaskDelay(pdMS_TO_TICKS(3000));
}

void LED_effect4(){
	// LED2 toggle at 4s
	HAL_GPIO_TogglePin(GPIOA, LED_GREEN_PIN);
	vTaskDelay(pdMS_TO_TICKS(400));
}

