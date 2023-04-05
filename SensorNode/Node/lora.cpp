#include "Arduino.h"
#include "lora.h"


SoftwareSerial lora_serial(LORA_TX_PIN, LORA_RX_PIN);

void Config(uint16_t address, uint8_t channel){
  digitalWrite(LORA_M0_PIN, 1);
  digitalWrite(LORA_M1_PIN, 1);

  
}

//============HIGH LEVEL FUNCTION============//
void LORA_Init(void){
  self_addressL = (uint8_t)SELF_ADDRESS;
  self_addressH = (uint8_t)SELF_ADDRESS >> 8;
  
  des_addressL = (uint8_t)DES_ADDRESS;
  des_addressH = (uint8_t)DES_ADDRESS >> 8;

  lora_serial.begin(9600);
  LORA_SetMode(MODE_NORMAL);
}

void SetMode(unsigned char mode){
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
  lora_serial.write(DES_ADDRESS_H);
  lora_serial.write(DES_ADDRESS_L);
  lora_serial.write(DES_CHANNEL);

  while(*msg){
    lora_serial.write(*msg++);
  }
}
