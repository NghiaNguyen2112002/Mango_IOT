/*
 * trans_data_uart.h
 *
 *  Created on: Apr 7, 2023
 *      Author: user
 */

#ifndef INC_TRANS_DATA_UART_H_
#define INC_TRANS_DATA_UART_H_

#include <stdlib.h>
#include <stdio.h>
#include "stm32f1xx_hal.h"
#include "main.h"
#include "lcd_i2c.h"

void UART_Init(UART_HandleTypeDef* uart_esp, UART_HandleTypeDef* uart_lora);

void UESP_SendMsg(char* msg, uint8_t size);
uint8_t UESP_IsReceivedMsg(void);
uint8_t* UESP_GetMsg(void);

void ULORA_SendMsg(char* msg, uint8_t size);
uint8_t ULORA_IsReceivedMsg(void);
uint8_t* ULORA_GetMsg(void);

#endif /* INC_TRANS_DATA_UART_H_ */
