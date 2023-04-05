#include <DHT.h>

#include "input.h"
#include "pin.h"

#define SERIAL_DEBUG_BAUD   9600

void setup() {
  // put your setup code here, to run once:
  Serial.begin(SERIAL_DEBUG_BAUD);

  IN_Init();
}

void loop() {
  // put your main code here, to run repeatedly:
  IN_ReadHumid();
  IN_ReadTemp();
  delay(3000);
}
