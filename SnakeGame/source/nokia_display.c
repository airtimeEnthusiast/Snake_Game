/*
 * nokia_display.c
 *
 *  Created on: Mar 19, 2021
 *      Author: austinwright
 *
 *      NOTES:
 *
		//SPI_transmit(0x14);	//Recommended Bias of 0x04
 */
#include "nokia_display.h"
#include "frdm_spi.h"


#define LCDWIDTH 84
#define LCDHEIGHT 48

#ifndef _BV
#define _BV(x) (1 << (x)) ///< Mask for bit position x
#endif

/** the memory buffer for the LCD */
uint8_t d_buffer[LCDWIDTH * LCDHEIGHT] = {
//Banks 0
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//Banks 1
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//Banks 2
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//Banks 3
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//Banks 4
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
//Banks 5
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};

/* -----------------------------------------------------------------
 * Initialize this bad@$$ Nokia display
/* -----------------------------------------------------------------*/
void init_5110(){

	RES_Pulse();

	//Command mode (Setup for transmission)
	GPIOD->PDOR &= ~(1<<7);

    //Set function set for extended instructions
    SPI_transmit(0x21);
    delay_ms(1);

	//Set Bias to 0x04
	SPI_transmit(0x14);
	delay_ms(1);

	//Set VOP contrast
	SPI_transmit(0x10);
	delay_ms(1);

	//Set normal instruction mode
	SPI_transmit(0x20);
	delay_ms(1);

	//Display to normal mode
	SPI_transmit(0xC);
	delay_ms(1);

	//Turn off all pixels
	Clear_Entire_Display();
}
/* -----------------------------------------------------------------*/
/* 	Select a bank based on y coordinate range!
/* -----------------------------------------------------------------*/
int Bank_Select(int yCoord){
	if(yCoord < 8  && yCoord >= 0) { 	 return 0; }
	else if(yCoord < 16 && yCoord >= 8) { return 1; }
	else if(yCoord < 24 && yCoord >= 16){ return 2; }
	else if(yCoord < 32 && yCoord >= 24){ return 3; }
	else if(yCoord < 40 && yCoord >= 32){ return 4; }
	else if(yCoord < 48 && yCoord >= 40){ return 5; }
}
/* -----------------------------------------------------------------*/
/* 	Select a bank based on y coordinate range!
/* -----------------------------------------------------------------*/
void print_buffer(){
	for(int j = 0 ; j < 6 ; j++){
		for(int i = 0 ; i < 83 ; i++){
			printf("%d,",d_buffer[(j * 84) + i]);
	   	}
	   	printf("\n");
	}
}
/* -----------------------------------------------------------------*/
/* 	Set a pixel man!
/* -----------------------------------------------------------------*/
void Set_Pixel(int x, int y,int enable){

	//if pixel value is not within a legal display address
	if ((x < 0) || (x >= LCDWIDTH) || (y < 0) || (y >= LCDHEIGHT)){
		return;
	}

	//enable bit map buffer value
	uint8_t bitValue = _BV(y % 8) | d_buffer[x + (y / 8) * LCDWIDTH]; //Bank value OR buffer
	d_buffer[x + (y / 8) * LCDWIDTH] = bitValue;

	//printf("buffer offset: %d       bit value: %d\n", x + (y / 8) * LCDWIDTH,bitValue);

	//Command mode
	GPIOD->PDOR &= ~(1<<7);

	//Given the pixel value calculate the cursor address
	SPI_transmit(0x80 + x);					//offset x address
	SPI_transmit(0x40 + Bank_Select(y));	//offset y address

	//write pixel into display
	GPIOD->PDOR |= (1<<7);
	SPI_transmit(bitValue);

}
/* -----------------------------------------------------------------*/
/* 	Clean them artifacts man
/* -----------------------------------------------------------------*/
void Clear_Entire_Display(){

	GPIOD->PDOR &= ~(1<<7);			//Go to command mode
	SPI_transmit(0x80);				//reset x address
	SPI_transmit(0x40);				//reset y address

	GPIOD->PDOR |= (1<<7);			//Go to data mode
	for(int i = 0 ; i < 504 ; i++){
		SPI_transmit(0x0); 			//clear next column
	}
	GPIOD->PDOR &= ~(1<<7);			//Go back to command mode
	SPI_transmit(0x80);				//reset x address
	SPI_transmit(0x40);				//reset y address

	delay_ms(1);
}
/* -----------------------------------------------------------------*/
/* 	Apply RES pulse 8.1 Figure 13
/* -----------------------------------------------------------------*/
void RES_Pulse(){
	GPIOD->PDOR |= (1<<2);	//SCE high
	delay_ms(1);

	GPIOD->PDOR &= ~(1<<2); //SCE LOW (listen for transmission)
	delay_ms(500);

	GPIOD->PDOR &= ~(1<<4); //RST (RES) Low
	delay_ms(500);

	GPIOD->PDOR |= (1<<4); 	//RST (RES) High
	delay_ms(1);
}
/* -----------------------------------------------------------------*/
/* 	Apply RES pulse 8.1 Figure 13
/* -----------------------------------------------------------------*/
void Reset_Serial(){
	//Reset Serial Bus
    GPIOD->PDOR &= ~(1<<2); //SCE LOW (listen for transmission)
    delay_ms(500);
	GPIOD->PDOR &= ~(1<<4); //RST (RES) High
	delay_ms(1);
    GPIOD->PDOR |= (1<<4); 	//RST (RES) High
    delay_ms(1);
}

void Zero_Cursor_Address(){
	//Reset Cursor Address to (0,0)
	GPIOD->PDOR &= ~(1<<7);
	SPI_transmit(0x80);
	SPI_transmit(0x40);
}



