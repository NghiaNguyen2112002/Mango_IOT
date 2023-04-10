#ifndef __INC_WIFI_CONNECTION_H__
#define __INC_WIFI_CONNECTION_H__


#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <EEPROM.h>

#include "global.h"
#include "MQTT_server.h"

#define WIFI_NAME                 "Holmes211"
#define WIFI_PASSWORD             "0906631096"

#define WIFI_GATEWAY_NAME                   "GATEWAY"
#define WIFI_GATEWAY_PASS                   "123456789"

#define TIME_CHECK_WF       300       //3s

void WF_Init(void);
bool WF_IsConnected(void);
void WF_Connect(String wifi_name, String wifi_pass);
void WF_Disconnect(void);
void WF_CreateWebserver(void);

#endif