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


//==================LCD SCREEN==================//
#define SCREEN_INIT_0                   "      MANGO     "
#define SCREEN_INIT_1                   "                "

#define SCREEN_TEMP_HUMI_0             	" .ATEMP:      *C"        //"1.ATEMP: 30.3 *C"
#define SCREEN_TEMP_HUMI_1             	" .AHUMI:      % "        //"1.AHUMI: 50.0 % "

#define SCREEN_SOILHUMID_NITO_0			" .SHUMI:      % "
#define SCREEN_SOILHUMID_NITO_1			" .N:       mg/kg"

#define SCREEN_PHOTPHO_KALI_0			" .P:       mg/kg"
#define SCREEN_PHOTPHO_KALI_1			" .K:       mg/kg"

#define SCREEN_RELAY_CUR_0              "RELAY:          "        //" RELAY:     ON  "
#define SCREEN_RELAY_CUR_1              "CUR:          A "

#define SCREEN_CONFIG_WIFI_0            "  CONFIG  WIFI  "
#define SCREEN_CONFIG_WIFI_1            "                "

#define SCREEN_WIFI_CONNECTING_0        "CONNECTING  WIFI"
#define SCREEN_WIFI_CONNECTING_1        "                "

#define RELAYSTATESTR(state)         	state ? "ON " : "OFF"

//==================INDEX DISPLAY ON SCREEN==================//
#define INDEX_LCD_CEL_SYMBOL				14
#define INDEX_LCD_TEMP						9
#define INDEX_LCD_HUMI						9
#define INDEX_LCD_SHUMI						9
#define INDEX_LCD_N							5
#define INDEX_LCD_P							5
#define INDEX_LCD_K							5
#define INDEX_LCD_RELAY						7
#define INDEX_LCD_CUR						5

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
