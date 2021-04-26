/*
 * snake_queue.c
 *
 *  Created on: Apr 19, 2021
 *      Author: austinwright
 */
#include "frdm_general_peripherals.h"
#include "snake_queue.h"

#define MAX 20

struct snakeSeg snake[MAX];
int itemCount = 0;
int front = 0;
int rear = -1;

uint8_t peekX() {
   return snake[front].x;
}

uint8_t peekY(){
	return snake[front].y;
}

bool isEmpty() {
   return itemCount == 0;
}

bool isFull() {
   return itemCount == MAX;
}

int size() {
   return itemCount;
}

void intialize_queue(){
	for(int i = 0 ; i < MAX; i++){
		snake[i].x = -1;
		snake[i].y = -1;
	}
}

void insert(int x, int y) {

   if(!isFull()) {

      if(rear == MAX-1) {
         rear = -1;
      }

      rear++;
      snake[rear].x = x;
      snake[rear].y = y;


      itemCount++;
   }
}

void removeTail() {
	//insert queue in direction
	Draw_Segment(snake[front].x,snake[front].y,0,getDirection());

	snake[front].x = -1;
	snake[front].y = -1;
	front++;

	if(front == MAX) {
		front = 0;
	}
   itemCount--;
}

void removeHead() {
	//remove "head" of the snake
	Draw_Segment(snake[rear].x,snake[rear].y,0,getDirection());

	snake[rear].x = -1;
	snake[rear].y = -1;
	if(itemCount == 0) {
		front = 0;
	}
	rear--;
	itemCount--;
}


void print(){
	printf("\nitems: %d", itemCount);
	int i = front;
	while(snake[i].x != 255 && snake[i].y != 255) {
		printf("\nx: %d \t y: %d", snake[i].x, snake[i].y);
		i++;
	}
}

int getItemCount(){
	return itemCount;
}


