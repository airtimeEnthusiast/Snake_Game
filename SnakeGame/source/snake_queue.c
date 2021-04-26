/*
 * Austin Wright 4-25-21
 * Project 5 CSE 325: Snake Game
 * snake_queue.c
 */
#include "frdm_general_peripherals.h"
#include "snake_queue.h"

#define MAX 20

struct snakeSeg snake[MAX];
int itemCount = 0;
int front = 0;
int rear = -1;

/* -----------------------------------------------------------------*/
/* 	Determine if the snake queue is full
/* -----------------------------------------------------------------*/
bool isFull() {
   return itemCount == MAX;
}

/* -----------------------------------------------------------------*/
/* Initialize the queue to it's max size
/* -----------------------------------------------------------------*/
void intialize_queue(){
	for(int i = 0 ; i < MAX; i++){
		snake[i].x = -1;
		snake[i].y = -1;
	}
}

/* -----------------------------------------------------------------*/
/* 	Insert a new section into the queue
/* -----------------------------------------------------------------*/
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

/* -----------------------------------------------------------------*/
/* 	Remove the tail section
/* -----------------------------------------------------------------*/
void removeTail() {
	//insert queue in direction
	Draw_Segment(snake[front].x,snake[front].y,0);

	snake[front].x = -1;
	snake[front].y = -1;
	front++;

	if(front == MAX) {
		front = 0;
	}
   itemCount--;
}

/* -----------------------------------------------------------------*/
/* 	Print the sections
/* -----------------------------------------------------------------*/
void print(){
	printf("\nitems: %d", itemCount);
	int i = front;
	while(snake[i].x != 255 && snake[i].y != 255) {
		printf("\nx: %d \t y: %d", snake[i].x, snake[i].y);
		i++;
	}
}

/* -----------------------------------------------------------------*/
/* 	Get the current number of items
/* -----------------------------------------------------------------*/
int getItemCount(){
	return itemCount;
}


