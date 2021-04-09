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

/* -----------------------------------------------------------------*/
/* 	Initialize this bad@$$ Nokia display with the following steps
 * 1. Command mode (D/~C) low
 * 2. Briefly allow for extended instruction set
 * 3. Set the display contrast (VOP)
 * 4. Return to normal instruction mode
 * 5. Set the display to normal mode
 */
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

	clearDisplay();


	for(int j = 0 ; j < 83 ; j++){
		SPI_transmit(0x1F); //fill column
	}
		SPI_transmit(0x80);			//reset x address
		SPI_transmit(0x40);			//reset y address

	for(int k = 0 ; k <= 83 ; k++){
			SPI_transmit(0x0); //clear column
	}
	delay_ms(100);
}
/* -----------------------------------------------------------------*/
/* 	Set a pixel man!
/* -----------------------------------------------------------------*/
void setPixel(int x, int y){

}
/* -----------------------------------------------------------------*/
/* 	Clean them artifacts man
/* -----------------------------------------------------------------*/
void clearDisplay(){

	GPIOD->PDOR &= ~(1<<7);			//Go to command mode
	SPI_transmit(0x80);				//reset x address
	SPI_transmit(0x40);				//reset y address

	GPIOD->PDOR |= (1<<7);			//Go to data mode
	for(int i = 0 ; i < 504 ; i++){
		SPI_transmit(0x0); 			//clear next column
	}
	GPIOD->PDOR &= ~(1<<7);
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



