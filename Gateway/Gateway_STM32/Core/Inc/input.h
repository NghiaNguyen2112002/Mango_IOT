/*
 * input.h
 *
 *  Created on: Apr 7, 2023
 *      Author: user
 */

#ifndef INC_INPUT_H_
#define INC_INPUT_H_

#include <stdlib.h>
#include "stm32f1xx_hal.h"
#include "main.h"

#define NO_OF_BUTTONS						1
#define MAX_COUNTER        					200   //10s

#define BUTTON_IS_PRESSED                   0
#define BUTTON_IS_RELEASED                  1

//==================INDEX BUTTON==================//
#define BT_CONFIG							0


void IN_Init(void);
void IN_ReadButton(void);
uint8_t IN_IsPressed(uint8_t index);
uint8_t IN_IsPressed_ms(uint8_t index, uint16_t duration);

#endif /* INC_INPUT_H_ */
