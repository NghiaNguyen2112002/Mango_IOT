#include "SoftwareSerial.h"
#include "Arduino.h"
#include "input.h"

// Modbus RTU requests for reading NPK values
const char request_nito[] =    {0x01, 0x03, 0x00, 0x1e, 0x00, 0x01, 0xe4, 0x0c};
const char request_photpho[] =  {0x01, 0x03, 0x00, 0x1f, 0x00, 0x01, 0xb5, 0xcc};
const char request_kali[] =     {0x01, 0x03, 0x00, 0x20, 0x00, 0x01, 0x85, 0xc0};

DHT dht(DHT_PIN, DHTTYPE);
SoftwareSerial rs485_serial(NPK_TX_PIN, NPK_RX_PIN);

float temp, humid;

void IN_Init(void){
  dht.begin();
  rs485_serial.begin(9600);
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
  return map(analogRead(ADC_PIN), 0, 1023, 0, 100);      //convert to percentage
}

unsigned char IN_ReadNito(void){
  char value[7];
  if(rs485_serial.write(request_nito, sizeof(request_nito)) == 8){
    for(unsigned char i = 0; i < 7; i++){
      value[i] = rs485_serial.read();
    }
  }
  return value[4];
}

unsigned char IN_ReadPhotpho(void){
  char value[7];
  if(rs485_serial.write(request_photpho, sizeof(request_photpho)) == 8){
    for(unsigned char i = 0; i < 7; i++){
      value[i] = rs485_serial.read();
    }
  }
  return value[4];
}
unsigned char IN_ReadKali(void){
  char value[7];
  if(rs485_serial.write(request_kali, sizeof(request_kali)) == 8){
    for(unsigned char i = 0; i < 7; i++){
      value[i] = rs485_serial.read();
    }
  }
  return value[4];
}
