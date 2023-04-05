#ifndef __LORA_H__
#define __LORA_H__

#include <SoftwareSerial.h>
#include "pin.h"

//======MODE======//
#define MODE_NORMAL           0
#define MODE_WAKEUP           1
#define MODE_PWSAVING         2
#define MODE_SLEEP            3

#define SELF_ADDRESS_H          0x00
#define SELF_ADDRESS_L          0x00
#define SELF_CHANNEL          0x00

#define DES_ADDRESS_H           0x00
#define DES_ADDRESS_L           0x00
#define DES_CHANNEL           0x00

void LORA_Init(void);
void LORA_SetMode(unsigned char mode);
void LORA_SendMsg(char* msg);

#endif