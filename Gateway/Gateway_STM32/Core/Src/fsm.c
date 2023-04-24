/*
 * fsm.c
 *
 *  Created on: Apr 7, 2023
 *      Author: user
 */


#include "fsm.h"

uint8_t mode_lcd, mode_data, mode_sys;
uint8_t node_turn;

uint8_t flag_config_mode, flag_connect_mode, flag_display_data_mode;

char msg[100];
char msg_json[30];


char* ConvertMessageToJsonString(void){
	strcpy(msg_json, "{\"ID\":100,\"RELAY\":");
	msg_json[18] = _Data_gateway.relay + '0';
	strcpy(msg_json + 19,"}\n");

	return msg_json;
}

void ProcessMsg(char* msg){
	uint8_t i = 0, node_id;
	char* token;


/*
	!{"ID":1,"T":0.00,"H":0.00,"A":20,"N":0,"P":0,"K":0}#
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

uint8_t SystemMode(void){
	return mode_sys;
}
//==================HIGH LEVEL FUNCTION==================//
void FSM_Init(void){
	mode_data = INIT;
	mode_lcd = INIT;
	mode_sys = INIT;

	node_turn = 0;
	_time_screen = 50;

}

void FSM_LcdDisplay(void){
	switch(mode_lcd){
	case INIT:
		CLCD_PrintStringBuffer(0, 0, SCREEN_INIT_0);
		CLCD_PrintStringBuffer(1, 0, SCREEN_INIT_1);

		if(_time_screen < 5){
			mode_lcd = READY_DISPLAY;
		}
		break;
	case READY_DISPLAY:

		CLCD_PrintCharBuffer(1, 12 + (_counter_time_elapsed/10) % 4, '.');
		if((_counter_time_elapsed/10) % 4 == 3) CLCD_PrintStringBuffer(1, 0, SCREEN_READY_DISPLAY_1);

		if(SystemMode() == SYS_CONNECT_WF){
			CLCD_PrintStringBuffer(0, 0, SCREEN_WIFI_CONNECTING_0);
			CLCD_PrintStringBuffer(1, 0, SCREEN_WIFI_CONNECTING_1);

			mode_lcd = DISPLAY_CONNECT_WF;
		}
		else if(SystemMode() == SYS_CONFIG_WF){
			CLCD_PrintStringBuffer(0, 0, SCREEN_CONFIG_WIFI_0);
			CLCD_PrintStringBuffer(1, 0, SCREEN_CONFIG_WIFI_1);

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

		if(SystemMode() == SYS_CONNECT_WF){
			CLCD_PrintStringBuffer(0, 0, SCREEN_WIFI_CONNECTING_0);
			CLCD_PrintStringBuffer(1, 0, SCREEN_WIFI_CONNECTING_1);
			mode_lcd = DISPLAY_CONNECT_WF;
		}
		else if(SystemMode() == SYS_CONFIG_WF){
			CLCD_PrintStringBuffer(0, 0, SCREEN_CONFIG_WIFI_0);
			CLCD_PrintStringBuffer(1, 0, SCREEN_CONFIG_WIFI_1);

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

		if(SystemMode() == SYS_CONNECT_WF){
			CLCD_PrintStringBuffer(0, 0, SCREEN_WIFI_CONNECTING_0);
			CLCD_PrintStringBuffer(1, 0, SCREEN_WIFI_CONNECTING_1);
			mode_lcd = DISPLAY_CONNECT_WF;
		}
		else if(SystemMode() == SYS_CONFIG_WF){
			CLCD_PrintStringBuffer(0, 0, SCREEN_CONFIG_WIFI_0);
			CLCD_PrintStringBuffer(1, 0, SCREEN_CONFIG_WIFI_1);

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

		if(SystemMode() == SYS_CONNECT_WF){
			CLCD_PrintStringBuffer(0, 0, SCREEN_WIFI_CONNECTING_0);
			CLCD_PrintStringBuffer(1, 0, SCREEN_WIFI_CONNECTING_1);
			mode_lcd = DISPLAY_CONNECT_WF;
		}
		else if(SystemMode() == SYS_CONFIG_WF){
			CLCD_PrintStringBuffer(0, 0, SCREEN_CONFIG_WIFI_0);
			CLCD_PrintStringBuffer(1, 0, SCREEN_CONFIG_WIFI_1);

			mode_lcd = DISPLAY_CONFIG_WF;
		}
		else if(_time_screen < 5){
			_time_screen = TIME_SCREEN;
			CLCD_PrintStringBuffer(0, 0, SCREEN_RELAY_CUR_0);
			CLCD_PrintStringBuffer(1, 0, SCREEN_RELAY_CUR_1);

			mode_lcd = DISPLAY_RELAY_CUR;
		}
		break;
	case DISPLAY_RELAY_CUR:
		CLCD_PrintStringBuffer(0, INDEX_LCD_RELAY, RELAYSTATESTR(_Data_gateway.relay));
		CLCD_PrintFloatBuffer(1, INDEX_LCD_CUR, _Data_gateway.cur);

		if(SystemMode() == SYS_CONNECT_WF){
			CLCD_PrintStringBuffer(0, 0, SCREEN_WIFI_CONNECTING_0);
			CLCD_PrintStringBuffer(1, 0, SCREEN_WIFI_CONNECTING_1);
			mode_lcd = DISPLAY_CONNECT_WF;
		}
		else if(SystemMode() == SYS_CONFIG_WF){
			CLCD_PrintStringBuffer(0, 0, SCREEN_CONFIG_WIFI_0);
			CLCD_PrintStringBuffer(1, 0, SCREEN_CONFIG_WIFI_1);

			mode_lcd = DISPLAY_CONFIG_WF;
		}
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

		if(SystemMode() == SYS_CONNECT_WF) {
			CLCD_PrintStringBuffer(0, 0, SCREEN_WIFI_CONNECTING_0);
			CLCD_PrintStringBuffer(1, 0, SCREEN_WIFI_CONNECTING_1);

			mode_lcd = DISPLAY_CONNECT_WF;
		}
		break;
	case DISPLAY_CONNECT_WF:
		//every 500ms print a '.'
		CLCD_PrintCharBuffer(1, 6 + (_counter_time_elapsed/10) % 5, '.');

		if((_counter_time_elapsed/10) % 5 == 4) CLCD_PrintStringBuffer(1, 0, SCREEN_WIFI_CONNECTING_1);

		if(SystemMode() == SYS_CONFIG_WF){
			CLCD_PrintStringBuffer(0, 0, SCREEN_CONFIG_WIFI_0);
			CLCD_PrintStringBuffer(1, 0, SCREEN_CONFIG_WIFI_1);

			mode_lcd = DISPLAY_CONFIG_WF;
		}
		else if(SystemMode() == SYS_PROCESS_DATA) {
			CLCD_PrintStringBuffer(0, 0, SCREEN_READY_DISPLAY_0);
			CLCD_PrintStringBuffer(1, 0, SCREEN_READY_DISPLAY_1);

			mode_lcd = READY_DISPLAY;
		}
		break;
	default:
		mode_lcd = INIT;
	}

}

void FSM_SystemControl(void){
	switch(mode_sys){
	case INIT:
//		send CMD to ESP after 2000ms
		if(_counter_time_elapsed % 40 == 39){
			UESP_SendMsg(CMD_CONNECT_WF, sizeof(CMD_CONNECT_WF));
			mode_sys = SYS_CONNECT_WF;
		}
		break;
	case SYS_CONNECT_WF:

		if(IN_IsPressed_ms(BT_CONFIG, 2000)){
			UESP_SendMsg(CMD_CONFIG_WF, sizeof(CMD_CONFIG_WF));

			mode_sys = SYS_CONFIG_WF;
		}
		else if(UESP_IsReceivedMsg()){
			if(strcmp(UESP_GetMsg(), CONNECT_WF_SUCCESS) == 0){

			UESP_SendMsg(CMD_TRANSMIT_DATA, sizeof(CMD_TRANSMIT_DATA));

			mode_sys = SYS_PROCESS_DATA;
			}
		}
		break;
	case SYS_CONFIG_WF:

		if(UESP_IsReceivedMsg()){
			if((strcmp(UESP_GetMsg(), CONFIG_WF_SUCCESS == 0))) {
				UESP_SendMsg(CMD_CONNECT_WF, sizeof(CMD_CONNECT_WF));

				mode_sys = SYS_CONNECT_WF;
			}
		}
		else if(IN_IsPressed(BT_CONFIG)) {
			UESP_SendMsg(CMD_CONNECT_WF, sizeof(CMD_CONNECT_WF));

			mode_sys = SYS_CONNECT_WF;
		}
		break;
	case SYS_PROCESS_DATA:

		if(_time_read_data < 5) {
			_time_read_data = TIME_READ_DATA;
//			ACS712 5A => 185 mV/A
			_Data_gateway.cur = (IN_ReadADC() * 3.3 / 4095.0 - 2500.0) / 185.0;

			UESP_SendMsg(ConvertMessageToJsonString(), 25);
		}

		else if(ULORA_IsReceivedMsg()) {
//			process data received from lora
//			=> stm32 send to esp => esp send to server


			UESP_SendMsg(msg, sprintf(msg, "%s", ULORA_GetMsg()));

			ProcessMsg(msg);
		}


		else if(UESP_IsReceivedMsg()){
			if(strcmp(UESP_GetMsg(), DISCONNECT_WF) == 0){
				UESP_SendMsg(CMD_CONNECT_WF, sizeof(CMD_CONNECT_WF));

				mode_sys = SYS_CONNECT_WF;
			}
			else if(strcmp(UESP_GetMsg(), ONRELAY) == 0){
				HAL_GPIO_WritePin(RELAY_GPIO_Port, RELAY_Pin, SET);
				_Data_gateway.relay = 1;
				UESP_SendMsg(ConvertMessageToJsonString(), 25);
			}
			else if(strcmp(UESP_GetMsg(), OFFRELAY) == 0){
				HAL_GPIO_WritePin(RELAY_GPIO_Port, RELAY_Pin, RESET);
				_Data_gateway.relay = 0;
				UESP_SendMsg(ConvertMessageToJsonString(), 25);
			}
		}

		else if(IN_IsPressed_ms(BT_CONFIG, 2000)){
			UESP_SendMsg(CMD_CONFIG_WF, sizeof(CMD_CONFIG_WF));

			mode_sys = SYS_CONFIG_WF;
		}
		break;
	default:
		mode_sys = INIT;
	}
}
