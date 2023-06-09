#ifndef __LORA_H__
#define __LORA_H__

#include <SoftwareSerial.h>
#include "pin.h"
#include "global.h"
//======MODE======//
#define MODE_NORMAL           0
#define MODE_WAKEUP           1
#define MODE_PWSAVING         2
#define MODE_SLEEP            3

// adress and channel lora of gateway
#define DES_ADDRESS_H           0x00
#define DES_ADDRESS_L           0x01
#define DES_CHANNEL             0x04

#if defined(NODE_0)
// NODE 0: 
#define SELF_ADDRESS_H          0x00
#define SELF_ADDRESS_L          0x02
#define SELF_CHANNEL            0x04
#endif

#if defined(NODE_1)
// NODE 1: 
#define SELF_ADDRESS_H          0x00
#define SELF_ADDRESS_L          0x03
#define SELF_CHANNEL            0x04

#endif


void LORA_Init(void);
void LORA_SetMode(unsigned char mode);
void LORA_SendMsg(char* msg);
String LORA_Listen(void);

#endif