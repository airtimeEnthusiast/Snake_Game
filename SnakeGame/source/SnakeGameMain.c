/*
 * Austin Wright 3-26-21
 * Project 4 CSE 325: Balance Game
 * FRDM project which uses the MMA845 on board accelerometer to measure the angle the MCU is held at
 * Unfortunately, I was unable to complete the project and get the I2C to work proporly. I have defined
 * auxiliary game functions as well as a way to read the accelerometer data

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


 */


/**
 * @file    StopLightGameMain.c
 * @brief   Application entry point.
 */
#include "frdm_general_peripherals.h"
#include "frdm_spi.h"
#include "nokia_display.h"
#include "snake_game_logic.h"
#include "snake_buffer.h"
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
    init_LEDS();
    init_SW();
    init_PIT();

    STOP_PIT();
    START_PIT();

    blinkChoosenLED(2);
    blinkChoosenLED(1);

    init_Snake();

    while(1){}

    return 0;

    //dummyPixel_Test();

    return 0;
}
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




