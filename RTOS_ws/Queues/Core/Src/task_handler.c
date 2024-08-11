/*
 * task_handler.c
 *
 *  Created on: Aug 11, 2024
 *      Author: rajvi
 */

#include "main.h"

#define HR_conf  	0
#define MIN_conf 	1
#define SEC_conf 	2

#define DD_conf 	3
#define MM_conf 	4
#define YY_conf 	5
#define DAY_conf 	6


int extract_command(command_t *cmd);
void process_command(command_t *cmd);

const char* inv_msg = "Invalid Message \n";


void menu_task_handler(void* parameters){
	//BaseType_t ret;
	uint32_t cmd_addr;
	command_t *cmd;

	int option;

	const char* menu_msg =
			"**********************************\n"
			"                Menu              \n"
			"**********************************\n"
			"LED EFFECT                  ---> 0\n"
			"Date & Time                 ---> 1\n"
			"EXIT                        ---> 2\n"
			"Enter your choice here: ";




	while(1){

		xQueueSend(q_print, &menu_msg, portMAX_DELAY);
		// wait for menu commands
		xTaskNotifyWait(0, 0, &cmd_addr, portMAX_DELAY );
		cmd = (command_t*)cmd_addr;

		if(cmd->len == 1){
			// Valid command
			option = cmd->payload[0] - 48;	// ASCII to int conversion
			switch(option){
				case 0:
					curr_state = sLEDEffect;
					xTaskNotify(led_task_handle,0,eNoAction);
					break;
				case 1:
					curr_state = sRTCMenu;
					xTaskNotify(rtc_task_handle,0,eNoAction);
					break;
				case 2:
					break;
				default:
					xQueueSend(q_print,&inv_msg,portMAX_DELAY);
					continue;
			}
		}
		else{
			//invalid entry
			xQueueSend(q_print, &inv_msg, portMAX_DELAY);
			continue;
		}
		// Wait to run again when some other task notifies
		xTaskNotifyWait(0, 0, NULL, portMAX_DELAY );
	} // while super loop end
}


void cmd_task_handler(void* parameters){

	BaseType_t ret;
	command_t cmd;
		while(1){
			/* Notify Wait */
			ret = xTaskNotifyWait(0, 0, NULL, portMAX_DELAY);

			if(ret == pdTRUE){
				/* process the user data (command) stored in input data queue */
				process_command(&cmd);
			}
			/* Notify the command to relevant task */


	}
}

void print_task_handler(void* parameters){
	uint32_t *msg;
	while(1){
		xQueueReceive(q_print, &msg, portMAX_DELAY);
		HAL_UART_Transmit(&huart2, (uint8_t*)msg, strlen((char*)msg), HAL_MAX_DELAY);

	}
}

/*
 * Displays LED Menu
 */
void led_task_handler(void* parameters){
	uint32_t cmd_addr;
		command_t *cmd;
		const char* msg_led = "========================\n"
							  "|      LED Effect     |\n"
							  "========================\n"
							  "(none,e1,e2,e3,e4)\n"
							  "Enter your choice here : ";
		const char* inv_msg = "Invalid Message \n";
		while(1){
			/*Wait for notification (Notify wait) */
			xTaskNotifyWait(0,0,NULL,portMAX_DELAY);

			/*Print LED menu */
			xQueueSend(q_print,&msg_led,portMAX_DELAY);

			/*wait for LED command (Notify wait) */
			xTaskNotifyWait(0,0,&cmd_addr,portMAX_DELAY);
			cmd = (command_t*)cmd_addr;

			if(cmd->len <= 4)
			{
				if(! strcmp((char*)cmd->payload,"none"))
					led_effect_stop();
				else if (! strcmp((char*)cmd->payload,"e1"))
					led_effect(1);
				else if (! strcmp((char*)cmd->payload,"e2"))
					led_effect(2);
				else if (! strcmp((char*)cmd->payload,"e3"))
					led_effect(3);
				else if (! strcmp((char*)cmd->payload,"e4"))
					led_effect(4);
				else
					xQueueSend(q_print,&inv_msg,portMAX_DELAY); /*print invalid message */
			}else
				xQueueSend(q_print,&inv_msg,portMAX_DELAY);

			/* update state variable */
			curr_state = sMainMenu;

			/*Notify menu task */
			xTaskNotify(menu_task_handle,0,eNoAction);

		}
}

/*
 * Displays RTC Task Menu
 */
void rtc_task_handler(void* parameters){
	const char* msg_rtc1 = "========================\n"
						   "           RTC          \n"
						   "========================\n";

		const char* msg_rtc2 =  "Configure Time            ----> 0\n"
								"Configure Date            ----> 1\n"
								"Enable reporting          ----> 2\n"
								"Exit                      ----> 3\n"
								"Enter your choice here : ";


		const char *msg_rtc_hh = "Enter hour(1-12):";
		const char *msg_rtc_mm = "Enter minutes(0-59):";
		const char *msg_rtc_ss = "Enter seconds(0-59):";

		const char *msg_rtc_dd  = "Enter date(1-31):";
		const char *msg_rtc_mo  = "Enter month(1-12):";
		const char *msg_rtc_dow = "Enter day(1-7 sun:1):";
		const char *msg_rtc_yr  = "Enter year(0-99):";

		const char *msg_conf = "Configuration successful\n";
		const char *msg_rtc_report = "Enable time&date reporting(y/n)?: ";

		static int rtc_state = 0;
		uint32_t cmd_addr;
		command_t *cmd;
		int menu_code;
		RTC_DateTypeDef date;
		RTC_TimeTypeDef time;

		while(1){
			/* Notify wait (wait till someone notifies)*/
			xTaskNotifyWait(0, 0, NULL, portMAX_DELAY );
			/* Print the menu and show current date and time information */
			xQueueSend(q_print, &msg_rtc1, portMAX_DELAY);
			show_time_date();
			xQueueSend(q_print,&msg_rtc2,portMAX_DELAY);

			while(curr_state != sMainMenu){

				/* Wait for command notification (Notify wait) */
				xTaskNotifyWait(0, 0, &cmd_addr, portMAX_DELAY );
				cmd = (command_t*)cmd_addr;

				switch(curr_state)
				{
					case sRTCMenu:{
						/* process RTC menu commands */
						if(cmd->len == 1){
							menu_code = cmd->payload[0] - 48;
							switch(menu_code){
							case 0:
								curr_state = sRTCTimeConfig;
								xQueueSend(q_print, &msg_rtc_hh , portMAX_DELAY);
								break;
							case 1:
								curr_state = sRTCDateConfig;
								xQueueSend(q_print, &msg_rtc_dd , portMAX_DELAY);
								break;
							case 2:
								curr_state = sRTCReport;
								xQueueSend(q_print, &msg_rtc_report , portMAX_DELAY);
								break;
							case 3:
								curr_state = sMainMenu;
								break;
							default:
								curr_state = sMainMenu;
								xQueueSend(q_print, &inv_msg , portMAX_DELAY);
							}

						}else{
							curr_state = sMainMenu;
							xQueueSend(q_print, &inv_msg, portMAX_DELAY);
						}

						break;}

					case sRTCTimeConfig:{
						/* get hh, mm, ss infor and configure RTC */
						switch(rtc_state){
							case HR_conf:
								uint8_t hour = getnumber(cmd->payload, cmd->len);
								time.Hours = hour;
								rtc_state = MIN_conf;
								xQueueSend(q_print, &msg_rtc_mm , portMAX_DELAY);
								break;
							case MIN_conf:
								uint8_t min = getnumber(cmd->payload, cmd->len);
								time.Minutes = min;
								xQueueSend(q_print, &msg_rtc_ss , portMAX_DELAY);
								rtc_state = SEC_conf;
								break;
							case SEC_conf:
								uint8_t ss = getnumber(cmd->payload, cmd->len);
								time.Seconds = ss;
								if(!validate_rtc_information(&time, NULL)){
									rtc_configure_time(&time);
									xQueueSend(q_print, &msg_conf, portMAX_DELAY);
									show_time_date();
								}else{
									xQueueSend(q_print, &inv_msg, portMAX_DELAY);
								}

								rtc_state = 0;
								curr_state = sMainMenu;
								break;
						}

						/* take care of invalid entries */
						break;}

					case sRTCDateConfig:{

						/* get date, month, day , year info and configure RTC */
						switch(rtc_state){
							case DD_conf:
								uint8_t dd = getnumber(cmd->payload, cmd->len);
								date.Date = dd;
								xQueueSend(q_print, &msg_rtc_mo, portMAX_DELAY);
								rtc_state = MM_conf;
								break;
							case MM_conf:
								uint8_t mm = getnumber(cmd->payload, cmd->len);
								date.Month = mm;
								xQueueSend(q_print, &msg_rtc_yr, portMAX_DELAY);
								rtc_state = YY_conf;
								break;
							case YY_conf:
								uint8_t yr = getnumber(cmd->payload, cmd->len);
								date.Year = yr;
								xQueueSend(q_print, &msg_rtc_dow, portMAX_DELAY);
								rtc_state = DAY_conf;
								break;
							case DAY_conf:
								uint8_t day = getnumber(cmd->payload, cmd->len);
								date.WeekDay = day;
								xQueueSend(q_print, &msg_rtc_yr, portMAX_DELAY);
								if(!validate_rtc_information(NULL, &date)){
									rtc_configure_date(&date);
									xQueueSend(q_print, &msg_conf, portMAX_DELAY);
									show_time_date();
								}else{
									xQueueSend(q_print, &inv_msg, portMAX_DELAY);
								}
								curr_state = sMainMenu;
								rtc_state = 0;
								break;
						/* take care of invalid entries */

						break;}
					}

					case sRTCReport:{
						/* enable or disable RTC current time reporting over ITM printf */
						if(cmd->len == 1){
							if(cmd->payload[0] == 'y'){
								if(xTimerIsTimerActive(rtc_timer) == pdFALSE)
								xTimerStart(rtc_timer,portMAX_DELAY);
							}else if(cmd->payload[0] == 'n'){
								xTimerStop(rtc_timer,portMAX_DELAY);
							}else {
								xQueueSend(q_print, &inv_msg, portMAX_DELAY);
							}
						}
						curr_state = sMainMenu;
						break;}

				}// switch end

			} //while end

			   /* Notify menu task */
				xTaskNotify(menu_task_handle,0, eNoAction);


		}//while super loop end
}


int extract_command(command_t *cmd){
	uint8_t item;
	BaseType_t status;

	/* Check if there are any messages waiting in the queue	 */
	status = uxQueueMessagesWaiting(q_data);
	if(!status) return -1;	// Return since there are no messages in the queue

	uint8_t i = 0;

	do{
		status = xQueueReceive(q_data, &item, 0);
		if(status == pdTRUE) cmd->payload[i++] = item;
	}while(item != '\n');

	/* When \n is received 	 */

	cmd->payload[i-1] = '\0';
	cmd->len = i-1;
	return 0;
}

void process_command(command_t *cmd){
	// Extract the data bytes from the input data queue and create a command

	extract_command(cmd);

	switch(curr_state){
	case sMainMenu:
		xTaskNotify(menu_task_handle, (uint32_t)cmd, eSetValueWithOverwrite);
		break;

	case sLEDEffect:
		xTaskNotify(led_task_handle, (uint32_t)cmd, eSetValueWithOverwrite);
		break;

	case sRTCMenu:

	case sRTCTimeConfig:

	case sRTCDateConfig:

	case sRTCReport:
		xTaskNotify(rtc_task_handle, (uint32_t)cmd, eSetValueWithOverwrite);
		break;
	}
}



/*
 * Converts ASCII characters to uint8_t number
 */
uint8_t getnumber(uint8_t *p , int len){
	int value;

	if(len>1){
		value = (((p[0] - 48)*10) + (p[1] - 48));
	}
	else{
		value = (p[0] - 48);
	}
	return value;
}
