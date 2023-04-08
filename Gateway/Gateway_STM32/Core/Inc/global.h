/*
 * global.h
 *
 *  Created on: Apr 7, 2023
 *      Author: user
 */

#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_

#include "stdio.h"

#define NO_OF_NODES					2
typedef struct Data_Node{
	uint8_t node_id;
	float temp;
	float humid;
	uint8_t adc;
	uint8_t nito;
	uint8_t photpho;
	uint8_t kali;
	uint8_t is_connected;
}Data_Node;

typedef struct Data_Gateway{
	uint8_t relay;
	float cur;
}Data_Gateway;


// Create a buffer to store data of all node
extern Data_Node _Data_node[];

extern Data_Gateway _Data_gateway;

extern uint16_t _time_screen, _time_read_data;

extern uint16_t _counter_time_elapsed;

#endif /* INC_GLOBAL_H_ */
