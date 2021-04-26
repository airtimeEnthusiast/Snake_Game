/*
 * Austin Wright 4-25-21
 * Project 5 CSE 325: Snake Game
 * FRDM project uses the SPI interface to communicate with the Nokia 5110 to display a simple snake game.

 The buttons and LEDs are configured with GPIO with the following register bits:
 LED1: Port A bit 4
 LED2: Port A bit 5
 LED3: Port A bit 12
 LED4: Port A bit 13

 BUTTON1: Port C bit 0
 BUTTON2: Port C bit 4
 BUTTON3: Port C bit 6
 BUTTON4: Port C bit 7

When integrating system modules
  *Enable CLockGating
  *Enable from system integration module
  *Enable Port mode such as mux operation
  *Enable Port Data Direction
  *Enable Enable System Module

/**
 * @file    SnakeGameMain.c
 * @brief   Application entry point.
 */
#include "frdm_general_peripherals.h"
#include "frdm_spi.h"
#include "nokia_display.h"
#include "snake_queue.h"
/* -----------------------------------------------------------------*/
/* 	main function
/* -----------------------------------------------------------------*/
int main (void)
{
    BOARD_InitBootPins();
	BOARD_InitBootClocks();			//Negate clock signals to maintain a low clock
	BOARD_InitBootPeripherals();
	BOARD_InitDebugConsole();

	init_SPI();    	//Initialize SPI0
    init_5110(); 	//Initialize 5110 display
    init_LEDS();	//Initialize LEDs
    init_SW();		//Initialize Buttons
    init_PIT();		//Initialize Periodic Interrupt Timer

    STOP_PIT();		//Stop PIT for clean setup
    START_PIT();	//Enable PIT functionality

    init_Snake(1);	//Place snake into the display

    while(1){}

    return 0;
}
/* -----------------------------------------------------------------*/
/* 	Dummy pixel test
/* -----------------------------------------------------------------*/
void dummyPixel_Test(){
	for (int j = 0; j < 12; j++) {
		for (int i = 0; i < 83; i++) {
			Set_Pixel(i, j, 1);
		}
	}
	printf("\npixel val %d",Get_Pixel(0,0));
	printf("\npixel val %d",Get_Pixel(1,1));
	printf("\npixel val %d",Get_Pixel(2,2));
	printf("\npixel val %d",Get_Pixel(83,11));
	for (int j = 0; j < 12; j++) {
		for (int i = 0; i < 83; i++) {
			Set_Pixel(i, j, 0);
		}
	}
	printf("\npixel val %d",Get_Pixel(0,0));
	printf("\npixel val %d",Get_Pixel(1,1));
	printf("\npixel val %d",Get_Pixel(2,2));
	printf("\npixel val %d",Get_Pixel(83,11));
}
/* -----------------------------------------------------------------*/
/* 	Dummy queue test
/* -----------------------------------------------------------------*/
void dummyQueue_Test(){
	intialize_queue();
	insert(2,3);
	insert(2,4);
	insert(2,5);
	insert(2,6);
	insert(2,7);
	print();
	removeTail();
	print();
	removeTail();
	print();
	removeTail();
	print();
	removeTail();
	print();
	removeTail();
	print();
}
