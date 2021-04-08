/*
 * nokia_display.c
 *
 *  Created on: Mar 19, 2021
 *      Author: austinwright
 *
 *
 *
 *
 *
 *      NOTES:
 *
		//SPI_transmit(0x14);	//Recommended Bias of 0x04
 */
#include "nokia_display.h"
#include "frdm_spi.h"


/* -----------------------------------------------------------------*/
/* 	Initialize this bad@$$ Nokia display
/* -----------------------------------------------------------------*/
void init_5110(){

	//RES_Pulse();
    GPIOD->PDOR |= ~(1<<2);	//SCE high
    delay_ms(1);

    GPIOD->PDOR &= ~(1<<4); //RST Low
    delay_ms(500);

    GPIOD->PDOR |= (1<<4); //RST High
    delay_ms(1);

    GPIOD->PDOR &= ~(1<<2); //SCE is going LOW



	//Command mode
	GPIOD->PDOR &= ~(1<<7);

    //Set function set for extended instructions
    SPI_transmit(0x21);
    delay_ms(1);

	//Set Bias to 0x04
	SPI_transmit(0x14);
	delay_ms(1);

	//Set VOP contrast
	SPI_transmit(0x90);
	delay_ms(1);

	//Set normal instruction mode
	SPI_transmit(0x20);
	delay_ms(1);

	//Display to normal mode
	SPI_transmit(0xC);
	delay_ms(1);

	//Data mode
	GPIOD->PDOR |= (1<<7);

	//Write dummy data
	SPI_transmit(0x1F);

	//Reset_Function();
    //Function_Set();

}

/* -----------------------------------------------------------------*/
/* 	//Apply RES pulse 8.1
/* -----------------------------------------------------------------*/
void RES_Pulse(){
	GPIOD->PDOR &= ~(1<<2);	//SCE low
	GPIOD->PDOR &= ~(1<<4);	//RST low
	delay_ms(10);
	GPIOD->PDOR |= (1<<4);	//RST high
	delay_ms(10);
}

void Reset_Function(){
//RESET function (Step 8.2)

	//Command mode
	GPIOD->PDOR &= ~(1<<7);

	//Power-down high: Entry mode and Set control low
	SPI_transmit(0x24);	//Horizontal addressing, normal instruction set

	//Display blank
	SPI_transmit(0x8);	//bit E = D = 0

	// Zero out Address counters
	SPI_transmit(0x40);	//y address set to 0
	SPI_transmit(0x80);	//x address set to 0 and shut off HV generator

	//Temperature control mode
	SPI_transmit(0x4);	//TC1 and TC0 =0

	//Zero out bias system
	SPI_transmit(0x10);	//BS0 to BS2 = 0

	//Power on PCD844 "Chip"
	SPI_transmit(0x20);
}
void Function_Set(){
	//Function set (Step 8.4-8.8)

	//Display Control set to normal
	SPI_transmit(0xC);

	//Set VOP contrast
	SPI_transmit(0x90);


	SPI_transmit(0x40);	//y address set to 0
	SPI_transmit(0x80);	//x address set to 0


}



