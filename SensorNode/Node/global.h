#ifndef __GLOBAL_H__
#define __GLOBAL_H__

#define NODE_ID         1

typedef struct Data_Pack{
  unsigned char node_id;
  float temp;
  float humid;
  unsigned char adc;
  unsigned char nito;
  unsigned char photpho;
  unsigned char kali;
}Data_Pack;

extern Data_Pack _data;

extern unsigned int _time_read;
#endif