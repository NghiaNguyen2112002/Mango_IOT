#include "data_processing.h"

SoftwareSerial mySerial(STM32_TX_PIN, STM32_RX_PIN);

bool flag_config_wf, flag_send_data;
String msg;
unsigned char mode;

//================HIGH LEVEL FUNCTION================//
void DT_Init(void){
  mySerial.begin(9600);

  msg = "";

  flag_config_wf = false;
  mode = INIT;
}


void DT_FsmForProcess(void){
  switch(mode){
    case INIT:
      mode = IDLING;
    break;
    case IDLING:
      if(mySerial.available()){
        msg = mySerial.readString();
        Serial.println(msg);

        if(strcmp(msg.c_str(), CMD_CONNECT_WF) == 0){
//      READ WIFI NAME + WIFI PASS FROM  EEPROM
          if (EEPROM.read(0) != 0) {      
            _wifi_name = "";
            _wifi_pass = "";   
            for (int i = 0; i < 32; i++) {                //32 o nho dau tieu la chua ten mang wifi SSID
              _wifi_name += char(EEPROM.read(i));
            }
            for (int i = 32; i < 96; ++i) {               //o nho tu 32 den 96 la chua PASSWORD
              _wifi_pass += char(EEPROM.read(i));
            }
          }
          Serial.println(_wifi_name + "  " + _wifi_pass);
          WF_Connect(_wifi_name, _wifi_pass);
          Serial.println("ESP CONNECT WF");
          mode = CONNECT_WF;
        }
        else if(strcmp(msg.c_str(), CMD_CONFIG_WF) == 0){
          WF_Disconnect();
          WF_CreateWebserver();
          Serial.println("ESP CONFIG WF");
          mode = CONFIG_WF;
        }
        else if(strcmp(msg.c_str(), CMD_TRANSMIT_DATA) == 0){
          flag_send_data = true;
          Serial.println("ESP TRANSMIT");
          mode = TRANSMIT_DATA;
        }
        else Serial.println("ERROR CMD");
      }
    break;
    case CONNECT_WF:
      if(WF_IsConnected()) {
        mySerial.print(CONNECT_WF_SUCCESS);
        mode = IDLING;
      }
      else if(mySerial.available()){
        msg = mySerial.readString();
        Serial.println(msg);

        if(strcmp(msg.c_str(), CMD_CONFIG_WF) == 0){
          WF_Disconnect();
          WF_CreateWebserver();
          Serial.println("ESP CONFIG WF");
          mode = CONFIG_WF;
        }
      }
    break;
    case CONFIG_WF:
      if(_flag_config_success){
        _flag_config_success = false;

//      SAVE WIFI NAME + WIFI PASS TO EEPROM
        for (int i = 0; i < 96; i++) {
          EEPROM.write(i, 0);               //Clear EEPROM
        }
        for (int i = 0; i < _wifi_name.length(); i++) {
          EEPROM.write(i, _wifi_name[i]);
        }
        for (int i = 0; i < _wifi_pass.length(); i++) {
          EEPROM.write(32 + i, _wifi_pass[i]);
        }
        EEPROM.commit();

        mySerial.print(CONFIG_WF_SUCCESS);
        mode = IDLING;
      }
      else if(mySerial.available()){
        msg = mySerial.readString();
        Serial.println(msg);
  
        if(strcmp(msg.c_str(), CMD_CONNECT_WF) == 0){
          WF_Connect(_wifi_name, _wifi_pass);
          Serial.println("ESP CONNECT WF");
          mode = CONNECT_WF;
        }
      }
    break;
    case TRANSMIT_DATA:
      SV_Connect();

      if(mySerial.available() && SV_IsConnected()){
        msg = mySerial.readString();
        Serial.println(msg);

        if(strcmp(msg.c_str(), CMD_CONFIG_WF) == 0){
          WF_Disconnect();
          WF_CreateWebserver();
          mode = CONFIG_WF;
        }
        else if(strcmp(msg.c_str(), CMD_CONNECT_WF) == 0){
          WF_Connect(_wifi_name, _wifi_pass);
          Serial.println("ESP CONNECT WF");
          mode = CONNECT_WF;
        }
        else {
          Serial.println("Sent to SV");
          SV_SendData(CHANNEL_DATA, (char*)msg.c_str());
        }
      }

      if(_flag_received_cmd_from_sv){
        _flag_received_cmd_from_sv = false;
        mySerial.print(_cmd);
      }

      if(WF_IsConnected() == false){
        mySerial.print(DISCONNECT_WF);
        mode = IDLING;
      }
      else if(flag_config_wf){
        flag_config_wf = false;

      }

    break;
  }
}