/*
 * screen_lcd.h
 *
 *  Created on: Apr 9, 2023
 *      Author: user
 */

#ifndef INC_SCREEN_LCD_H_
#define INC_SCREEN_LCD_H_


//==================LCD SCREEN==================//
#define SCREEN_INIT_0                   "      MANGO     "
#define SCREEN_INIT_1                   "                "

#define SCREEN_READY_DISPLAY_0			"  WAITING NODE  "
#define SCREEN_READY_DISPLAY_1			" TO CONNECT     "

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


#endif /* INC_SCREEN_LCD_H_ */
