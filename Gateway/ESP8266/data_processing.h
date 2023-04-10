#ifndef __INC_DATA_PROCESSING_H__
#define __INC_DATA_PROCESSING_H__

#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>
#include <EEPROM.h>

#include "global.h"
#include "MQTT_server.h"
#include "wifi.h"
#include "pin.h"

//==================MODE FSM==================//
#define INIT                0
#define IDLING              1
#define CONNECT_WF          2
#define CONFIG_WF           3
#define TRANSMIT_DATA       4

//==================MSG FROM ESP TO STM==================//
#define ONRELAY							"!ONRELAY#"
#define OFFRELAY						"!OFRELAY#"
#define CONFIG_WF_SUCCESS		"!CONFIG_SUCCESS#"
#define CONNECT_WF_SUCCESS	"!CONNECT_SUCCESS#"
#define DISCONNECT_WF				"!DISCONNECT#"

//==================CMD FROM STM TO ESP==================//
#define CMD_CONNECT_WF					"CONNECT"
#define CMD_CONFIG_WF					  "CONFIG"
#define CMD_TRANSMIT_DATA				"TRANSMIT"

void DT_Init(void);
void DT_FsmForProcess(void);

#endif