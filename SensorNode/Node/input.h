#ifndef __INPUT_H__
#define __INPUT_H__

#include <DHT.h>
#include "pin.h"

#define DHTTYPE       DHT22

void IN_Init(void);
float IN_ReadHumid(void);
float IN_ReadTemp(void);
unsigned char IN_ReadADC(void);



#endif