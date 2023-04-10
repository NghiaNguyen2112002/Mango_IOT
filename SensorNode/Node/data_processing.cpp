#include "data_processing.h"

unsigned char mode;

String ConvertDataToJsonString(void){
  String s = "!{\"ID\":" + String(_data.node_id);
        s += ",\"T\":" + String(_data.temp);
        s += ",\"H\":" + String(_data.humid);
        s += ",\"A\":" + String(_data.adc);
        s += ",\"N\":" + String(_data.nito);
        s += ",\"P\":" + String(_data.photpho);
        s += ",\"K\":" + String(_data.kali);   
        s += "}#";

  return s; 
}


void DT_Init(void){
  mode = INIT;
}
void DT_FsmForDataProcessing(void){
  switch(mode){
    case INIT:
      _time_read = 0;
      mode = IDLING;

    break;
    case IDLING:
      if(_time_read < 5) mode = READ_DATA;

    break;
    case READ_DATA:
      _data.temp = IN_ReadTemp();
      _data.humid = IN_ReadHumid();
      _data.adc = IN_ReadADC();
      // _data.nito = IN_ReadNito();
      // _data.photpho = IN_ReadPhotpho();
      // _data.kali = IN_ReadKali();
      mode = SEND_DATA;
    break;
    case SEND_DATA:
      LORA_SendMsg(ConvertDataToJsonString().c_str());

      //sending data, back to idling and wait a while before the next reading time
      _time_read = TIME_IDLING;
      mode = IDLING;
    break;
    default:
    mode = INIT;
  }
}