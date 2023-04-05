#include "Arduino.h"
#include "input.h"

DHT dht(DHT_PIN, DHTTYPE);     // Initialize DHT sensor

float temp, humid;

void IN_Init(void){
  dht.begin();
}

float IN_ReadHumid(void){
  humid = dht.readHumidity();

  if(isnan(humid)) {
    Serial.println("DHT Error!");
    return 0;
  }

  Serial.print("HUMI: "); Serial.println(humid);
  return humid;
}

float IN_ReadTemp(void){
  temp = dht.readTemperature();
  
  if(isnan(temp)) {
    Serial.println("DHT Error!");
    return 0;
  }

  Serial.print("TEMP: "); Serial.println(temp); 
  return temp;
}

unsigned char IN_ReadADC(void){
  return analogRead(ADC_PIN) * 100 / 1023;      //convert to percentage
}
