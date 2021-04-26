/*
 * Austin Wright 4-25-21
 * Project 5 CSE 325: Snake Game
 * frdm_general_peripherals.c
 */
#include "frdm_general_peripherals.h"
#include "snake_queue.h"

/* snake directions */
uint8_t DIRECTION  = 1;
uint8_t PREV_DIRECT = 1;

/* Current Position */
uint8_t xCur;
uint8_t yCur;

/* -----------------------------------------------------------------*/
/* 	Setup LEDs
/* -----------------------------------------------------------------*/
void init_LEDS() {

	int blinkVal[4] = { 0, 4, 6, 7 };	//Port C values
	SIM->SCGC5 |= (1 << 11);			//Enable Port C LEDs
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
	//SIM->SCGC5 |= (1 << 9);			//Enable Port A Switches
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
/* 	Draw a segment of the snake
/* -----------------------------------------------------------------*/
void Draw_Segment(uint8_t x, uint8_t y, uint8_t enable){

	Set_Pixel(x,y,enable); 				//	center
	Set_Pixel(x,y + 1,enable);			//	center bottom
	Set_Pixel(x,y - 1,enable); 			//	center top
	Set_Pixel(x - 1,y,enable);			//	center left
	Set_Pixel(x + 1,y,enable); 			//	center right
}
/* -----------------------------------------------------------------*/
/* 	Draw a 3 by 3 box at the center of x, and y, enable is 1 for write
/* -----------------------------------------------------------------*/
void move(){

	switch (getDirection()) {
	case 1:
		// Move Left
		printf("\nLeft");
		xCur--;
		break;
	case 2:
		// Move Up
		printf("\nUp");
		yCur--;
		break;
	case 3:
		// Move Down
		printf("\nDown");
		yCur++;
		break;
	case 4:
		// Move Right
		printf("\nRight");
		xCur++;
		break;
	default:
		printf("Error unassigned value: %d");
	}
}
/* -----------------------------------------------------------------*/
/* 	Interrupt function PIT (pixel timing interrupt)
/* -----------------------------------------------------------------*/
void PIT_IRQHandler(void) {
	if (PIT->CHANNEL[0].TFLG) { 		//Timer 0 triggered
		PIT->CHANNEL[0].TFLG = 1;		//Reset Flag

		//Check if snake eats a fruit
			//Grow snake
		//if(yCur < 0 | yCur > 47){
		//	yCur = 0;
		//}
		//if(xCur < 0 | xCur > 83){
		//	xCur = 0;
		//}

		insert(xCur,yCur);
		Draw_Segment(xCur,yCur,1);
		move();

		if(getItemCount() == 16){
			removeTail();
		}
	}
}
/* -----------------------------------------------------------------*/
/* Interrupt for the switches on Port A
/* -----------------------------------------------------------------*/
void PORTA_IRQHandler(void) {
	int delay_count = 0;
	while(buttonPressed() == -1 && delay_count < 10){
		delay_count++;
		delay_ms(8);
	}
	delay_ms(20);

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
	PREV_DIRECT = getDirection();
	//Select chosen value
	if (S1 == 0) {			// Move Left
		blinkChoosenLED(1);
		DIRECTION = 1;
	}
	if (S2 == 0) {			// Move Up
		blinkChoosenLED(2);
		DIRECTION = 2;
	}
	if (S3 == 0) {			// Move Down
		blinkChoosenLED(3);
		DIRECTION = 3;
	}
	if (S4 == 0) {			// Move Right
		blinkChoosenLED(4);
		DIRECTION = 4;
	}
}

/* -----------------------------------------------------------------*/
/* 	If a button is pressed
/* -----------------------------------------------------------------*/
int buttonPressed() {
	// Return current switch values
	int S1 = GPIOA->PDIR & (1 << 4);
	int S2 = GPIOA->PDIR & (1 << 5);
	int S3 = GPIOA->PDIR & (1 << 12);
	int S4 = GPIOA->PDIR & (1 << 13);
	//Select chosen value
	if (S1 == 0 | S2 == 0 | S3 == 0 | S3 == 0 | S4 == 0) {
		//printf("\nButton Pressed");
		return 1;
	} else {
		return -1;
	}
}
/* -----------------------------------------------------------------*/
/* 	Initialize the snake
/* -----------------------------------------------------------------*/
void init_Snake(int direction){
	//Initialize snake queue
	intialize_queue();
	xCur = 47;
	yCur = 24;
}
/* -----------------------------------------------------------------*/
/* 	get Direction
/* -----------------------------------------------------------------*/
int getDirection(){
	return DIRECTION;
}
