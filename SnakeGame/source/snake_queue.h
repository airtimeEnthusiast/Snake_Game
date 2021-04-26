/*
 * Austin Wright 4-25-21
 * Project 5 CSE 325: Snake Game
 * snake_queue.h
 */

#ifndef SNAKE_QUEUE_H_
#define SNAKE_QUEUE_H_
#include "frdm_general_peripherals.h"
struct snakeSeg{
	uint8_t x;
	uint8_t y;
};

/* -----------------------------------------------------------------*/
/* 	Determine if the snake queue is full
/* -----------------------------------------------------------------*/
bool isFull();

/* -----------------------------------------------------------------*/
/* Initialize the queue to it's max size
/* -----------------------------------------------------------------*/
void intialize_queue();

/* -----------------------------------------------------------------*/
/* 	Insert a new section into the queue
/* -----------------------------------------------------------------*/
void insert(int x, int y);

/* -----------------------------------------------------------------*/
/* 	Remove the tail section
/* -----------------------------------------------------------------*/
void removeTail();

/* -----------------------------------------------------------------*/
/* 	Print the sections
/* -----------------------------------------------------------------*/
void print();

/* -----------------------------------------------------------------*/
/* 	Get the current number of items
/* -----------------------------------------------------------------*/
int getItemCount();



#endif /* SNAKE_QUEUE_H_ */