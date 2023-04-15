#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
#include <PubSubClient.h>
#include <SoftwareSerial.h>
#include <EEPROM.h>

#include "global.h"
#include "MQTT_server.h"
#include "wifi.h"
#include "data_processing.h"

#define SERIAL_DEBUG_BAUD       9600
#define EXCECUTING_CYCLE        50        //50ms

unsigned long time_now = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(SERIAL_DEBUG_BAUD);
  EEPROM.begin(512);
  WF_Init();
  SV_Init();
  DT_Init();

}

void loop() {
  // put your main code here, to run repeatedly:
  if(millis() >= time_now + EXCECUTING_CYCLE){
    time_now = millis();
    DT_FsmForProcess();
  }
  
  client.loop();
  WebServer.handleClient();
}
