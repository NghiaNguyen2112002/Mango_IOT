#include <DHT.h>

#include "input.h"
#include "pin.h"
#include "lora.h"
#include "global.h"
#include "data_processing.h"

#define SERIAL_DEBUG_BAUD       9600

#define EXCECUTING_CYCLE        50        //50ms

unsigned long time_now = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(SERIAL_DEBUG_BAUD);
  LORA_Init();
  IN_Init();
  DT_Init();

  time_now = millis();
  Serial.println("begin");
  delay(500);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(millis() >= time_now + EXCECUTING_CYCLE){
    time_now = millis();

    if(_time_read >=5) _time_read -= 5;

    DT_FsmForDataProcessing();

    // if(Serial.available()) LORA_SendMsg(Serial.readString().c_str());

    // Serial.print(LORA_Listen());

  }
  // Serial.print(LORA_Listen());
  LORA_Listen();
}
