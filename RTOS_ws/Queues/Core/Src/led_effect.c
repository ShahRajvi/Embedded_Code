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
		xTimerStop(handle_led_timer[i],portMAX_DELAY);
}

void led_effect(int n )
{
	led_effect_stop();
	xTimerStart(handle_led_timer[n-1], portMAX_DELAY);

}
