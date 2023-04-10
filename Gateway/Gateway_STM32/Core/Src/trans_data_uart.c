/*
 * trans_data_uart.c
 *
 *  Created on: Apr 7, 2023
 *      Author: user
 */


#include "trans_data_uart.h"

UART_HandleTypeDef* u_esp;
UART_HandleTypeDef* u_lora;

uint8_t msg_esp[100], msg_lora[100];
uint8_t index_msg_esp, index_msg_lora;
uint8_t byte_esp_received, byte_lora_received;
uint8_t flag_esp_received_str, flag_lora_received_str;



void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
	if(huart->Instance == u_esp->Instance){
		if(byte_esp_received == '!'){
			index_msg_esp = 0;
			flag_esp_received_str = 0;
		}
		else if(byte_esp_received == '#'){
			msg_esp[index_msg_esp] = '\0';
			flag_esp_received_str = 1;
		}
		else {
			msg_esp[index_msg_esp++] = byte_esp_received;
		}

		HAL_UART_Receive_IT(u_esp, &byte_esp_received, 1);
	}

	if(huart->Instance == u_lora->Instance){
		if(byte_lora_received == '!'){
			index_msg_lora = 0;
			flag_lora_received_str = 0;
		}
		else if(byte_lora_received == '#'){
			msg_lora[index_msg_lora] = '\0';
			flag_lora_received_str = 1;
		}
		else {
			msg_lora[index_msg_lora++] = byte_lora_received;
		}

		HAL_UART_Receive_IT(u_lora, &byte_lora_received, 1);
	}
}




//==================HIGH LEVEL FUNCTION==================//
void UART_Init(UART_HandleTypeDef* uart_esp, UART_HandleTypeDef* uart_lora){
	u_esp = uart_esp;
	u_lora = uart_lora;
	index_msg_esp = index_msg_lora = 0;
	flag_esp_received_str = flag_lora_received_str = 0;

	HAL_UART_Receive_IT(u_esp, &byte_esp_received, 1);
	HAL_UART_Receive_IT(u_lora, &byte_lora_received, 1);
}

void UESP_SendMsg(char* msg, uint8_t size){
//	HAL_UART_Transmit(u_esp, msg, sizeof(msg), 1000);
	HAL_UART_Transmit(u_esp, msg, size, 1000);

}

uint8_t UESP_IsReceivedMsg(void){
	uint8_t temp = flag_esp_received_str;

	flag_esp_received_str = 0;
	return temp;
}

uint8_t* UESP_GetMsg(void){

	return msg_esp;
}

void ULORA_SendMsg(char* msg, uint8_t size){
	HAL_UART_Transmit(u_lora, msg, size, 1000);
}

uint8_t ULORA_IsReceivedMsg(void){
	uint8_t temp = flag_lora_received_str;

	flag_lora_received_str = 0;
	return temp;
}

uint8_t* ULORA_GetMsg(void){
//	if(!flag_lora_received_str) return "";

//	flag_lora_received_str = 0;

	return msg_lora;
}
