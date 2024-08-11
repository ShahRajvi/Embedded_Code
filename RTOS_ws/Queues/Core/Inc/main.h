/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <string.h>
#include <stdio.h>

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

#include "timers.h"
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */
/*
 * Command Structure definition
 */
typedef struct{
	uint8_t payload[10];
	uint8_t len;
}command_t;

/*
 * Application States
 */

typedef enum{
	sMainMenu = 0,
	sLEDEffect,
	sRTCMenu,
	sRTCTimeConfig,
	sRTCDateConfig,
	sRTCReport
}state_t;

extern TaskHandle_t menu_task_handle;
extern TaskHandle_t cmd_task_handle;
extern TaskHandle_t print_task_handle;
extern TaskHandle_t led_task_handle;
extern TaskHandle_t rtc_task_handle;

extern QueueHandle_t q_data;
extern QueueHandle_t q_print;

extern TimerHandle_t led_timer_handle[4];
extern TimerHandle_t rtc_timer;
extern state_t curr_state;


extern UART_HandleTypeDef huart2;
extern RTC_HandleTypeDef hrtc;
/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */
void menu_task_handler(void* parameters);
void cmd_task_handler(void* parameters);
void print_task_handler(void* parameters);
void led_task_handler(void* parameters);
void rtc_task_handler(void* parameters);

void led_effect_stop(void);
void led_effect(int n );
void fn_led_effect_callback(TimerHandle_t xTimer);
void LED_effect1();
void LED_effect2();
void LED_effect3();
void LED_effect4();


void show_time_date(void);
uint8_t getnumber(uint8_t *p , int len);
void rtc_configure_time(RTC_TimeTypeDef *time);
void rtc_configure_date(RTC_DateTypeDef *date);
int validate_rtc_information(RTC_TimeTypeDef *time, RTC_DateTypeDef *date);

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define B1_Pin GPIO_PIN_13
#define B1_GPIO_Port GPIOC
#define USART_TX_Pin GPIO_PIN_2
#define USART_TX_GPIO_Port GPIOA
#define USART_RX_Pin GPIO_PIN_3
#define USART_RX_GPIO_Port GPIOA
#define LD2_Pin GPIO_PIN_5
#define LD2_GPIO_Port GPIOA
#define TMS_Pin GPIO_PIN_13
#define TMS_GPIO_Port GPIOA
#define TCK_Pin GPIO_PIN_14
#define TCK_GPIO_Port GPIOA
#define SWO_Pin GPIO_PIN_3
#define SWO_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */
#define LED_GREEN_PIN LD2_Pin
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
