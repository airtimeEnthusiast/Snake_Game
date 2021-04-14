/*
 * frdm_general_peripherals.c
 *
 *  Created on: Mar 23, 2021
 *      Author: austinwright
 */
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL46Z4.h"
#include "fsl_debug_console.h"
#include "fsl_device_registers.h"
#include "frdm_general_peripherals.h"
#include "snake_game_logic.h"

/* -----------------------------------------------------------------*/
/* 	Setup LEDs
/* -----------------------------------------------------------------*/
void Enable_LEDS(){
	int blinkVal[4] = { 0, 4, 6, 7 };
	SIM->SCGC5 |= (1 << 11);
	for (int i = 0; i < 4; i++) {
		PORTC->PCR[blinkVal[i]] &= ~0x700;
		PORTC->PCR[blinkVal[i]] |= 0x700 & (1 << 8);
	}
}

/* -----------------------------------------------------------------*/
/* 	Setup switches
/* -----------------------------------------------------------------*/

void Inti_SW(){
	int switchVal[4] = { 4, 5, 12, 13 };
	SIM->SCGC5 |= (1 << 11);
	for (int i = 0; i < 4; i++) {
		PORTA->PCR[switchVal[i]] &= ~0xF0703;
		PORTA->PCR[switchVal[i]] |= 0xF0703 & ((0xA << 16) | (1 << 8) | 0x3);
	}
}

/* -----------------------------------------------------------------*/
/* 	Setup switches
/* -----------------------------------------------------------------*/
void Enable_PIT(){
	SIM->SCGC6 |= (1<<23);	//Clock gate the PIT

}



/* -----------------------------------------------------------------*/
/* 	Blink sequence when the player cannot orient the board in time
/* -----------------------------------------------------------------*/

void blinkLoseSequence() {
	GPIOC->PDOR |= (1 << 0) | (1 << 4) | (1 << 6) | (1 << 7);
	delay_ms(1000);
	GPIOC->PDOR &= ~(1 << 0) & ~(1 << 4) & ~(1 << 6) & ~(1 << 7);
	delay_ms(10);
}

/* -----------------------------------------------------------------*/
/* 	Blink sequence when the player orients the board in time
/* -----------------------------------------------------------------*/
void blinkWinSequence() {
	int count = 0;
	while (count < 3) {			//blink 3 times in a one second interval
		GPIOC->PDOR |= (1 << 0) | (1 << 4) | (1 << 6) | (1 << 7);
		delay_ms(167);
		GPIOC->PDOR &= ~(1 << 0) & ~(1 << 4) & ~(1 << 6) & ~(1 << 7);
		delay_ms(166);
		count++;
	}
}

/* -----------------------------------------------------------------*/
/* 	Blink LEDs based on a given angle
/* -----------------------------------------------------------------*/
void blinkAngleLEDs(int angle){
	for(int i = 0 ; i < 3 ; i++){
		if(angle == 90){
			blinkChoosenLED(1);
		}
		else if(angle == 60){
			blinkChoosenLED(1);
			blinkChoosenLED(2);
		}
		else if(angle == 30){
			blinkChoosenLED(2);
		}
		else if(angle == 0){
			blinkChoosenLED(2);
			blinkChoosenLED(3);
		}
		else if(angle == -30){
			blinkChoosenLED(3);
		}
		else if(angle == -60){
			blinkChoosenLED(3);
			blinkChoosenLED(4);
		}
		else if(angle == -90){
			blinkChoosenLED(4);
		}
	}
}

/* -----------------------------------------------------------------*/
/* 	Blink Chosen LED
/* -----------------------------------------------------------------*/
void blinkChoosenLED(int index) {
	switch (index) {
	//Blink LED 1
	case 1:
		GPIOC->PDOR |= (1 << 0);
		delay_ms(166);
		GPIOC->PDOR &= ~(1 << 0);
		break;
	//Blink LED 2
	case 2:
		GPIOC->PDOR |= (1 << 4);
		delay_ms(166);
		GPIOC->PDOR &= ~(1 << 4);
		break;
	//Blink LED 3
	case 3:
		GPIOC->PDOR |= (1 << 6);
		delay_ms(166);
		GPIOC->PDOR &= ~(1 << 6);
		break;
	//Blink LED 4
	case 4:
		GPIOC->PDOR |= (1 << 7);
		delay_ms(166);
		GPIOC->PDOR &= ~(1 << 7);
		break;
	default:
		printf("Error unassigned value: %d", index);
	}
	delay_ms(166);
}

/* -----------------------------------------------------------------*/
/* 	Interrupt function Port A (button switches interupt)
/* -----------------------------------------------------------------*/
void PORTA_IRQHandler(void) {
	printf("\nInterupt Called");
	int choosen = -1;
	// Clear ISF register bit (pg 194)
	PORTA->PCR[4] |= (1 << 24);
	PORTA->PCR[5] |= (1 << 24);
	PORTA->PCR[12] |= (1 << 24);
	PORTA->PCR[13] |= (1 << 24);
	// Return current switch values
	int S1 = GPIOA->PDIR & (1 << 4);
	int S2 = GPIOA->PDIR & (1 << 5);
	int S3 = GPIOA->PDIR & (1 << 12);
	int S4 = GPIOA->PDIR & (1 << 13);
	//Select chosen value
	if (S1 == 0 | S2 == 0 | S3 == 0 | S4 == 0) {
		//playGame();
	}
}

/* -----------------------------------------------------------------*/
/* 	Interrupt function Port A (button switches interupt)
/* -----------------------------------------------------------------*/
void PIT_IRQHandler(void){

}



