#ifndef __GLOBAL_H__
#define __GLOBAL_H__

#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
#include <PubSubClient.h> 


// Create WF client
extern WiFiClient espClient;
// Create MQTT instance
extern PubSubClient client;

// Create web server
extern ESP8266WebServer WebServer;

extern String _wifi_name, _wifi_pass;

extern String _cmd;
extern bool _flag_config_success, _flag_received_cmd_from_sv;
#endif