/*
 * fsm.c
 *
 *  Created on: Apr 7, 2023
 *      Author: user
 */


#include "fsm.h"

uint8_t mode_lcd, mode_data;
uint8_t node_turn;

uint8_t flag_config_wf, flag_connect_wf, flag_display;

uint8_t* msg;


void ProcessMsg(char* msg){
	uint8_t i = 0, node_id;
	char* token;

/*
  	 {"ID":1,"TEMP":30.4,"HUMID":50.5,"ADC":30,"N":40,"P":30,"K":40}
	    0     "ID"
		1     1
		2     "TEMP"
		3     30.4
		4     "HUMID"
		5     50.5
		6     "ADC"
		7     30
		8     "N"
		9     40
		10    "P"
		11    30
		12    "K"
		13    40
*/
	token = strtok(msg, ":,{}");

	for(i = 0; (i < 100) && (token != NULL); i++){
		if(i == 1) {
			node_id = atoi(token);
			_Data_node[node_id].node_id = node_id;
			_Data_node[node_id].is_connected = 1;
		}
		else if(i == 3) _Data_node[node_id].temp = atoff(token);
		else if(i == 5) _Data_node[node_id].humid = atoff(token);
		else if(i == 7) _Data_node[node_id].adc = atoi(token);
		else if(i == 9) _Data_node[node_id].nito = atoi(token);
		else if(i == 11) _Data_node[node_id].photpho = atoi(token);
		else if(i == 13) _Data_node[node_id].kali = atoi(token);
		token = strtok(NULL, ":,{}");
	}
}

//==================HIGH LEVEL FUNCTION==================//
void FSM_Init(void){
	mode_data = INIT;
	mode_lcd = INIT;

	node_turn = 0;
	_time_screen = 50;

}

void FSM_LcdDisplay(void){
	switch(mode_lcd){
	case INIT:
		CLCD_PrintStringBuffer(0, 0, SCREEN_INIT_0);
		CLCD_PrintStringBuffer(1, 0, SCREEN_INIT_1);

		if(_time_screen < 5){
			CLCD_PrintStringBuffer(0, 0, SCREEN_WIFI_CONNECTING_0);
			CLCD_PrintStringBuffer(1, 0, SCREEN_WIFI_CONNECTING_1);

			UESP_SendMsg(CMD_CONNECT_WF);

//			mode_lcd = DISPLAY_CONNECT_WF;
			mode_lcd = READY_DISPLAY;
		}
		break;
	case READY_DISPLAY:

//		if(_Data_node[node_turn].is_connected > 0){
		if(strcmp(UESP_GetMsg(), DISCONNECT_WF) == 0){
			CLCD_PrintStringBuffer(0, 0, SCREEN_WIFI_CONNECTING_0);
			CLCD_PrintStringBuffer(1, 0, SCREEN_WIFI_CONNECTING_1);

			UESP_SendMsg(CMD_CONNECT_WF);

			mode_lcd = DISPLAY_CONNECT_WF;
		}
		else if(IN_IsPressed_ms(BT_CONFIG, 2000)){
			CLCD_PrintStringBuffer(0, 0, SCREEN_CONFIG_WIFI_0);
			CLCD_PrintStringBuffer(1, 0, SCREEN_CONFIG_WIFI_1);

//			UESP_SendMsg(CONFIG_WF);

			mode_lcd = DISPLAY_CONFIG_WF;
		}
		else if(_Data_node[node_turn].is_connected){
			_time_screen = TIME_SCREEN;
			CLCD_PrintStringBuffer(0, 0, SCREEN_TEMP_HUMI_0);
			CLCD_PrintStringBuffer(1, 0, SCREEN_TEMP_HUMI_1);
			CLCD_PrintCharBuffer(0, INDEX_LCD_CEL_SYMBOL, 0xDF);

			CLCD_PrintCharBuffer(0, 0, _Data_node[node_turn].node_id + '0');
			CLCD_PrintCharBuffer(1, 0, _Data_node[node_turn].node_id + '0');

			mode_lcd = DISPLAY_DHT;
		}
		else{
			mode_lcd = TURN_NEXT_NODE;
		}
		break;
	case DISPLAY_DHT:
		CLCD_PrintFloatBuffer(0, INDEX_LCD_TEMP, _Data_node[node_turn].temp);
		CLCD_PrintFloatBuffer(1, INDEX_LCD_HUMI, _Data_node[node_turn].humid);

		if(strcmp(UESP_GetMsg(), DISCONNECT_WF) == 0){
			CLCD_PrintStringBuffer(0, 0, SCREEN_WIFI_CONNECTING_0);
			CLCD_PrintStringBuffer(1, 0, SCREEN_WIFI_CONNECTING_1);
			mode_lcd = DISPLAY_CONNECT_WF;
		}
		else if(IN_IsPressed_ms(BT_CONFIG, 2000)){
			CLCD_PrintStringBuffer(0, 0, SCREEN_CONFIG_WIFI_0);
			CLCD_PrintStringBuffer(1, 0, SCREEN_CONFIG_WIFI_1);

			UESP_SendMsg(CMD_CONFIG_WF);

			mode_lcd = DISPLAY_CONFIG_WF;
		}
		else if(_time_screen < 5){
			_time_screen = TIME_SCREEN;
			CLCD_PrintStringBuffer(0, 0, SCREEN_SOILHUMID_NITO_0);
			CLCD_PrintStringBuffer(1, 0, SCREEN_SOILHUMID_NITO_1);

			CLCD_PrintCharBuffer(0, 0, _Data_node[node_turn].node_id + '0');
			CLCD_PrintCharBuffer(1, 0, _Data_node[node_turn].node_id + '0');

			mode_lcd = DISPLAY_SOILHUMID_NITO;
		}
		break;
	case DISPLAY_SOILHUMID_NITO:
		CLCD_PrintNumBuffer(0, INDEX_LCD_SHUMI, _Data_node[node_turn].adc);
		CLCD_PrintNumBuffer(1, INDEX_LCD_N, _Data_node[node_turn].nito);

		if(strcmp(UESP_GetMsg(), DISCONNECT_WF) == 0){
			CLCD_PrintStringBuffer(0, 0, SCREEN_WIFI_CONNECTING_0);
			CLCD_PrintStringBuffer(1, 0, SCREEN_WIFI_CONNECTING_1);
			mode_lcd = DISPLAY_CONNECT_WF;
		}
		else if(IN_IsPressed_ms(BT_CONFIG, 2000)){
			CLCD_PrintStringBuffer(0, 0, SCREEN_CONFIG_WIFI_0);
			CLCD_PrintStringBuffer(1, 0, SCREEN_CONFIG_WIFI_1);

			UESP_SendMsg(CMD_CONFIG_WF);

			mode_lcd = DISPLAY_CONFIG_WF;
		}
		else if(_time_screen < 5){
			_time_screen = TIME_SCREEN;
			CLCD_PrintStringBuffer(0, 0, SCREEN_PHOTPHO_KALI_0);
			CLCD_PrintStringBuffer(1, 0, SCREEN_PHOTPHO_KALI_1);

			CLCD_PrintCharBuffer(0, 0, _Data_node[node_turn].node_id + '0');
			CLCD_PrintCharBuffer(1, 0, _Data_node[node_turn].node_id + '0');

			mode_lcd = DISPLAY_PHOTPHO_KALI;
		}
		break;
	case DISPLAY_PHOTPHO_KALI:
		CLCD_PrintNumBuffer(0, INDEX_LCD_P, _Data_node[node_turn].photpho);
		CLCD_PrintNumBuffer(1, INDEX_LCD_K, _Data_node[node_turn].kali);

		if(_time_screen < 5){
			_time_screen = TIME_SCREEN;
			CLCD_PrintStringBuffer(0, 0, SCREEN_RELAY_CUR_0);
			CLCD_PrintStringBuffer(1, 0, SCREEN_RELAY_CUR_1);

			mode_lcd = DISPLAY_RELAY_CUR;
		}
		break;
	case DISPLAY_RELAY_CUR:
		CLCD_PrintStringBuffer(0, INDEX_LCD_RELAY, RELAYSTATESTR(_Data_gateway.relay));
		CLCD_PrintFloatBuffer(1, INDEX_LCD_CUR, _Data_gateway.cur);
		if(_time_screen < 5){
			_time_screen = TIME_SCREEN;
			mode_lcd = TURN_NEXT_NODE;
		}
		break;
	case TURN_NEXT_NODE:

		node_turn = (node_turn + 1) % NO_OF_NODES;

		mode_lcd = READY_DISPLAY;
		break;
	case DISPLAY_CONFIG_WF:

		if((strcmp(UESP_GetMsg(), CONFIG_WF_SUCCESS) == 0) || IN_IsPressed(BT_CONFIG)) {
			CLCD_PrintStringBuffer(0, 0, SCREEN_WIFI_CONNECTING_0);
			CLCD_PrintStringBuffer(1, 0, SCREEN_WIFI_CONNECTING_1);

			UESP_SendMsg(CMD_CONNECT_WF);

			mode_lcd = DISPLAY_CONNECT_WF;
		}
		break;
	case DISPLAY_CONNECT_WF:
		//every 500ms print a '.'
		CLCD_PrintCharBuffer(1, 6 + (_counter_time_elapsed/10) % 5, '.');
		if((_counter_time_elapsed/10) % 5 == 4) CLCD_PrintStringBuffer(1, 0, SCREEN_WIFI_CONNECTING_1);

		if(IN_IsPressed_ms(BT_CONFIG, 2000)){
			CLCD_PrintStringBuffer(0, 0, SCREEN_CONFIG_WIFI_0);
			CLCD_PrintStringBuffer(1, 0, SCREEN_CONFIG_WIFI_1);

			UESP_SendMsg(CMD_CONFIG_WF);

			mode_lcd = DISPLAY_CONFIG_WF;
		}
		else if(strcmp(UESP_GetMsg(), CONNECT_WF_SUCCESS) == 0) {
			UESP_SendMsg(CMD_TRANSMIT_DATA);
			mode_lcd = READY_DISPLAY;
		}
		break;
	default:
		mode_lcd = INIT;
	}

}

void FSM_DataTransfer(void){
	switch(mode_data){
	case INIT:

		_time_read_data = TIME_READ_DATA;
		mode_data = TRANSMIT_DATA;
		break;
	case READ_DATA:

		mode_data = TRANSMIT_DATA;
		break;
	case TRANSMIT_DATA:
//		if(ULORA_IsReceivedMsg()) {
		if(UESP_IsReceivedMsg()){
			//	process data received from lora
			//	=> stm32 send to esp => esp send to server
//			msg = ULORA_GetMsg();
			msg = UESP_GetMsg();
			ProcessMsg(msg);

			UESP_SendMsg(msg);
		}

		if(_time_read_data < 5) {
			_time_read_data = TIME_READ_DATA;
			mode_data = READ_DATA;
		}
		break;
	default:
		mode_data = INIT;
	}

}
