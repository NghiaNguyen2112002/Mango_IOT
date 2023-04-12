#ifndef __DATA_PROCESSING__H__
#define __DATA_PROCESSING__H__

#include "input.h"
#include "pin.h"
#include "lora.h"
#include "global.h"

//===============MODE FOR FSM DATA PROCESSING===============//
#define INIT              0
#define IDLING            1
#define READ_DATA         2
#define SEND_DATA         3

//===============TIME===============//
#define TIME_IDLING       1000         //read data every 10000 ms


void DT_Init(void);
void DT_FsmForDataProcessing(void);

#endif