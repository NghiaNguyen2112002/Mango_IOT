#include "HardwareSerial.h"
#include "Arduino.h"
#include "lora.h"

SoftwareSerial lora_serial(LORA_RX_PIN, LORA_TX_PIN);

void Config(uint16_t address, uint8_t channel){
  digitalWrite(LORA_M0_PIN, 1);
  digitalWrite(LORA_M1_PIN, 1);
}

//============HIGH LEVEL FUNCTION============//
void LORA_Init(void){
  pinMode(LORA_M0_PIN, OUTPUT);
  pinMode(LORA_M1_PIN, OUTPUT);
  lora_serial.begin(9600);
  LORA_SetMode(MODE_NORMAL);
}

void LORA_SetMode(unsigned char mode){
  switch(mode){
    case MODE_NORMAL:
      digitalWrite(LORA_M0_PIN, 0);
      digitalWrite(LORA_M1_PIN, 0);
    break;
    case MODE_WAKEUP:
      digitalWrite(LORA_M0_PIN, 1);
      digitalWrite(LORA_M1_PIN, 0);
    break;
    case MODE_PWSAVING:
      digitalWrite(LORA_M0_PIN, 0);
      digitalWrite(LORA_M1_PIN, 1);
    break;
    case MODE_SLEEP:
      digitalWrite(LORA_M0_PIN, 1);
      digitalWrite(LORA_M1_PIN, 1);
    break;
  }
}

void LORA_SendMsg(char* msg){
  lora_serial.write((char)DES_ADDRESS_H);
  lora_serial.write((char)DES_ADDRESS_L);
  lora_serial.write((char)DES_CHANNEL);
  lora_serial.print(msg);
  Serial.println(msg);
}

String LORA_Listen(void){
  if(lora_serial.available() > 0){
     Serial.println(lora_serial.readString());
  }
  return "";
}