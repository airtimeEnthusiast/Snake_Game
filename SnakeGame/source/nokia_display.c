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
uint8_t display_buffer[LCDWIDTH * LCDHEIGHT / 8] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
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
/* 	Set a pixel man!
/* -----------------------------------------------------------------*/
void Set_Pixel(int x, int y,int enable){

	if ((x < 0) || (x >= LCDWIDTH) || (y < 0) || (y >= LCDHEIGHT)){
		return;
	}

	//Getting the pixel value
	printf("\nPixel %d\n", x + (y / 8) * LCDWIDTH);

	display_buffer[x + (y / 8) * LCDWIDTH] = enable;


	//Command mode
	GPIOD->PDOR &= ~(1<<7);
	//Given the pixel value calculate the address
	SPI_transmit(0x80 + x);		//offset x address

	//y offset calc
	// (y_coord / 6)

	// transmit value: (y_coord % 8) or smt



	/*int count = 0;
	int buffer = 1;
	//Each Bank
	for(int i = 0 ; i < 6 ; i++){
		//Every bank row
		for(int k = 0 ; k < 8 ; k++){
			//Every bank column
			for(int j = 0 ; j < 84 ; j++){
				buffer = (buffer<<1);
				count++;
				SPI_transmit(0);
				printf("\ncount: %d\nbuffer: %d\n\n",count);
				if(count == (x + (y / 8) * LCDWIDTH)){
					GPIOD->PDOR |= (1<<7);
					SPI_transmit(1);
					printf("\ntransmit buffer");
					return;
				}
			}
			buffer = 1;
			//Reset Address
			GPIOD->PDOR &= ~(1<<7);
			SPI_transmit(0x80);
			SPI_transmit(0x40 + i);
		}
	}*


	Zero_Cursor_Address();	// Zero out address

	GPIOD->PDOR |= (1<<7); // Command mode


	GPIOD->PDOR |= (1<<7); // Data mode*/

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

	GPIOD->PDOR |= (1<<4); //RST (RES) High
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



