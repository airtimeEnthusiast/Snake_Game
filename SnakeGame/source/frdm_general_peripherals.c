/*
 * frdm_general_peripherals.c
 *
 *  Created on: Mar 23, 2021
 *      Author: austinwright
 */
#include "snake_game_logic.h"
#include "frdm_general_peripherals.h"
/* -----------------------------------------------------------------*/
/* 	Setup LEDs
 /* -----------------------------------------------------------------*/
void init_LEDS() {

	int blinkVal[4] = { 0, 4, 6, 7 };
	SIM->SCGC5 |= (1 << 11);
	for (int i = 0; i < 4; i++) {
		PORTC->PCR[blinkVal[i]] &= ~0x700;
		PORTC->PCR[blinkVal[i]] |= 0x700 & (1 << 8);
	}
	//Enable Port Data Direction Register for output
	GPIOC->PDDR |= (1 << 0) | (1 << 4) | (1 << 6) | (1 << 7);
	//Set a high bit into the LEDs Port Data Output
	GPIOC->PDOR |= (1 << 0) | (1 << 4) | (1 << 6) | (1 << 7);
	delay_ms(500);
	GPIOC->PDOR &= ~(1 << 0) & ~(1 << 4) & ~(1 << 6) & ~(1 << 7);
}
/* -----------------------------------------------------------------*/
/* 	Setup switches
 /* -----------------------------------------------------------------*/
void init_SW() {
	//Enable TL100E Switches as interrupts
	int switchVal[4] = { 4, 5, 12, 13 };
	for (int i = 0; i < 4; i++) {
		PORTA->PCR[switchVal[i]] &= ~0xF0703; //Safety Mask
		PORTA->PCR[switchVal[i]] |= 0xF0703 & ((0xA << 16) | (1 << 8) | 0x3);
	}
	//Set Port Data Direction for input
	GPIOA->PDDR &= ~(1 << 4) & ~(1 << 5) & ~(1 << 12) & ~(1 << 13);
	NVIC_EnableIRQ(30);	//Bit 30 Port A's IRQ
}
/* -----------------------------------------------------------------*/
/* 	Setup PIT
 /* -----------------------------------------------------------------*/
void init_PIT() {
	SIM->SCGC6 |= (1 << 23);	//Clock gate the PIT

}
/* -----------------------------------------------------------------*/
/* 	Stop PIT
 /* -----------------------------------------------------------------*/
void STOP_PIT() {
	//Disable Timer 0 and shun interrupts requests
	PIT->CHANNEL[0].TCTRL = 0x00;

}
/* -----------------------------------------------------------------*/
/* 	Start PIT
 /* -----------------------------------------------------------------*/
void START_PIT() {
	//Enable PIT Timers and debug mode
	PIT->MCR = 0x00;
	PIT->CHANNEL[0].LDVAL = 0xB71B00; //channel delay 12MHZ

	//Enable from Nested Vectored Interrupt Controller
	NVIC_EnableIRQ(22);	//Enable PIT interrupt vector
	//Enable Timer 0 and accept interrupts requests
	PIT->CHANNEL[0].TCTRL = 0x3; //12MHZ
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
void blinkAngleLEDs(int angle) {
	for (int i = 0; i < 3; i++) {
		if (angle == 90) {
			blinkChoosenLED(1);
		} else if (angle == 60) {
			blinkChoosenLED(1);
			blinkChoosenLED(2);
		} else if (angle == 30) {
			blinkChoosenLED(2);
		} else if (angle == 0) {
			blinkChoosenLED(2);
			blinkChoosenLED(3);
		} else if (angle == -30) {
			blinkChoosenLED(3);
		} else if (angle == -60) {
			blinkChoosenLED(3);
			blinkChoosenLED(4);
		} else if (angle == -90) {
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
	int delay_count = 0;
	while(buttonPressed() == -1 && delay_count < 10){
		delay_count++;
		delay_ms(8);
	}
	delay_ms(20);

	printf("\nInterupt Called");
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
	if (S1 == 0) {
		blinkChoosenLED(1);
		return 1;		//LED 1
	}
	if (S2 == 0) {
		blinkChoosenLED(2);
		return 2;		//LED 2
	}
	if (S3 == 0) {
		blinkChoosenLED(3);
		return 3;		//LED 3
	}
	if (S4 == 0) {
		blinkChoosenLED(4);
		return 4;		//LED 4
	} else {
		return -1;
	}
}
/* -----------------------------------------------------------------*/
/* 	Interrupt function Port A (button switches interupt)
 /* -----------------------------------------------------------------*/
void analogRandomSeed() {

}

/* -----------------------------------------------------------------*/
/* 	Interrupt function PIT (pixel timing interupt)
 /* -----------------------------------------------------------------*/
void PIT_IRQHandler(void) {
	if (PIT->CHANNEL[0].TFLG) { 		//Timer 0 triggered
		PIT->CHANNEL[0].TFLG = 1;	//Reset Flag

		blinkChoosenLED(1);
	}

}
/* -----------------------------------------------------------------*/
/* 	Interrupt function PIT (pixel timing interupt)
 /* -----------------------------------------------------------------*/
int buttonPressed() {
	// Return current switch values
	int S1 = GPIOA->PDIR & (1 << 4);
	int S2 = GPIOA->PDIR & (1 << 5);
	int S3 = GPIOA->PDIR & (1 << 12);
	int S4 = GPIOA->PDIR & (1 << 13);
	//Select chosen value
	if (S1 == 0 | S2 == 0 | S3 == 0 | S3 == 0 | S4 == 0) {
		return 1;
	} else {
		return -1;
	}
}

