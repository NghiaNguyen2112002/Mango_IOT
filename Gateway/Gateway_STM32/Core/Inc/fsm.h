/*
 * fsm.h
 *
 *  Created on: Apr 7, 2023
 *      Author: user
 */

#ifndef INC_FSM_H_
#define INC_FSM_H_

#include "string.h"

#include "lcd_i2c.h"
#include "trans_data_uart.h"
#include "input.h"
#include "global.h"
#include "screen_lcd.h"

//==================MODE FSM LCD DISPLAY==================//
#define INIT						0
#define READY_DISPLAY				1
#define DISPLAY_DHT					2
#define DISPLAY_SOILHUMID_NITO		3
#define DISPLAY_PHOTPHO_KALI		4
#define DISPLAY_RELAY_CUR			5
#define TURN_NEXT_NODE				6
#define DISPLAY_CONFIG_WF			7
#define DISPLAY_CONNECT_WF			8


//==================MODE FSM DATA PROCESSING==================//
//#define INIT						0
#define READ_DATA					1
#define TRANSMIT_DATA				2


//==================TIME==================//
#define TIME_SCREEN						300
#define TIME_READ_DATA					500

//==================MSG FROM ESP==================//
#define ONRELAY							"ONRELAY"
#define OFFRELAY						"OFRELAY"
#define CONFIG_WF_SUCCESS				"CONFIG_SUCCESS"
#define CONNECT_WF_SUCCESS				"CONNECT_SUCCESS"
#define DISCONNECT_WF					"DISCONNECT"

//==================CMD TO ESP==================//
#define CMD_CONNECT_WF					"CONNECT"
#define CMD_CONFIG_WF					"CONFIG"
#define CMD_TRANSMIT_DATA				"TRANSMIT"

void FSM_Init(void);
void FSM_LcdDisplay(void);
void FSM_DataTransfer(void);

#endif /* INC_FSM_H_ */
