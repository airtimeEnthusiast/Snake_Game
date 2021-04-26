/*
 * snake_queue.h
 *
 *  Created on: Apr 19, 2021
 *      Author: austinwright
 */

#ifndef SNAKE_QUEUE_H_
#define SNAKE_QUEUE_H_
#include "frdm_general_peripherals.h"
struct snakeSeg{
	uint8_t x;
	uint8_t y;
};


uint8_t peekX();

uint8_t peekY();

bool isEmpty();

bool isFull();

int size();

void intialize_queue();

void insert(int x, int y);

void removeQueue();

void print();



#endif /* SNAKE_QUEUE_H_ */
