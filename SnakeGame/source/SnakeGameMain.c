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
 */


/**
 * @file    StopLightGameMain.c
 * @brief   Application entry point.
 */

#include "frdm_spi.h"
#include "nokia_display.h"
/* -----------------------------------------------------------------*/
/* 	main function
/* -----------------------------------------------------------------*/
int main (void)
{
    BOARD_InitBootPins();
	BOARD_InitBootClocks();			//Negate clock signals to maintain a low clock
	BOARD_InitBootPeripherals();
	BOARD_InitDebugConsole();

    SPI_init();    	//Initialize SPI0
    init_5110(); 	//Initialize 5110

    //dummyData_Test();
    //dummyPixel_Test();
    Set_Pixel(83,47);



    return 0;
}


void dummyData_Test(){
	///Dummy Data Test
	int dummy = 1; //255 (fills the whole bank);
	for(int k = 0 ; k < 8 ; k++){
		printf("\nRow %d : dummy: %d",k,dummy);
		//Dummy Bar Write Test
		GPIOD->PDOR |= (1<<7);
		for(int j = 0 ; j < 84 ; j++){	//fill all column in next row
			SPI_transmit(dummy); //fill next column
			delay_ms(9);
		}

		//Reset Address
		GPIOD->PDOR &= ~(1<<7);
		SPI_transmit(0x80);
		SPI_transmit(0x40);
		dummy = dummy | (dummy<<1);
	}
	delay_ms(1000);
	//Clear_Entire_Display();
}

void dummyPixel_Test(){

	GPIOD->PDOR &= ~(1<<7);
	//Set X and Y address
	SPI_transmit(0xD3); //Set X address to 83 (last column (0xD3))
	SPI_transmit(0x45); // Set Y address to 5 (last row (0x45))

	GPIOD->PDOR |= (1<<7);
	SPI_transmit(0x80);	//Fill all of the rows in this column

	//Pixel 504 = 84 * 6

	//Lazy bone approach would be a counter value <= 504
	//Loop through each pixel till you get the counter value

}

/* -----------------------------------------------------------------*/
/* 	game function
/* -----------------------------------------------------------------*/
void playGame() {
}

/* -----------------------------------------------------------------*/
/* 	Interrupt function Port A
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
		playGame();
	}
}



