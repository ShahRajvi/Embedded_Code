/*
 * task_handler.c
 *
 *  Created on: Aug 11, 2024
 *      Author: rajvi
 */

#include "main.h"

int extract_command(command_t *cmd);
void process_command(command_t *cmd);





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
	const char* inv_msg = "Invalid Message \n";



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
		}
		// Wait to run agian when som other task notifies
		xTaskNotifyWait(0, 0, NULL, portMAX_DELAY );
	} // while super loop end
}


//state_t curr_state = sMainMenu;


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
	BaseType_t ret;
	extract_command(cmd);

	switch(curr_state){
	case sMainMenu:
		ret = xTaskNotify(menu_task_handle, (uint32_t)cmd, eSetValueWithOverwrite);
		break;

	case sLEDEffect:
		ret = xTaskNotify(led_task_handle, (uint32_t)cmd, eSetValueWithOverwrite);
		break;

	case sRTCMenu:

	case sRTCTimeConfig:

	case sRTCDateConfig:

	case sRTCReport:
		ret = xTaskNotify(rtc_task_handle, (uint32_t)cmd, eSetValueWithOverwrite);
		break;
	}
}

void print_task_handler(void* parameters){

	while(1){


	}
}
/*
 * Toggle orange led on the board
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
			xTaskNotify(handle_menu_task,0,eNoAction);

		}
}
/*
 * Toggle red led on the board.
 */

void rtc_task_handler(void* parameters){
	TickType_t last_wakeup_time;
	last_wakeup_time = xTaskGetTickCount();
	while(1){

		vTaskDelayUntil(&last_wakeup_time, pdMS_TO_TICKS(1000)); // Making all our tasks periodic
	}
}
