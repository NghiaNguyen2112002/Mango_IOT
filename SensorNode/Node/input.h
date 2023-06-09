#ifndef __INPUT_H__
#define __INPUT_H__

#include <SoftwareSerial.h>
#include <DHT.h>

#include "pin.h"

#define DHTTYPE       DHT11

void IN_Init(void);
float IN_ReadHumid(void);
float IN_ReadTemp(void);
unsigned char IN_ReadADC(void);
unsigned char IN_ReadNito(void);
unsigned char IN_ReadPhotpho(void);
unsigned char IN_ReadKali(void);


#endif