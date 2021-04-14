
/* -----------------------------------------------------------------*/
/* 	Intialize SPI0
/* -----------------------------------------------------------------*/

#include "frdm_spi.h"
/********************************************************************/


void init_SPI(void){

	//Enable Clock gating
    SIM->SCGC5 |= (1<<12);     	//Enable Port D clock
    SIM->SCGC4 |= (1<<23);     	//Enable SPI1 clock

    //Set PCR multiplexers
    PORTD->PCR[2] |= 0x100;		//Alt 1 to enable ~SCE at Port D2
    PORTD->PCR[4] |= 0x100;		//Alt 1 to enable ~RST at Port D4
    PORTD->PCR[7] |= 0x100;  	//Alt 1 to enable ~D/C at Port D7
    PORTD->PCR[6] |= 0x200;  	//Alt 2 to enable DN (MOSI) at Port D6
	PORTD->PCR[5] |= 0x200; 	//Alt 2 to enable SCLK at Port D5

	//Set output mode for SCE, RST and ~D/C
    GPIOD->PDDR |= (1<<2) | (1<<4) | (1<<7);

    //Set SCLK to input
    GPIOD->PDDR |= (0<<5);

    //Set Control Register 1
    SPI1->C1 = (1<<2) | (1<<3) | (1<<4) | (1<<6); //phase 1 clock (start high), clock polarity (active low), configure as a master, SPI system enable

    //Zero out Control Register 2
    SPI1->C2 = 0;

    //Set baud rate
    SPI1->BR = (8<<4) | (2<<0); 	//6.67 KHZ

}
int isTransmitFlagEmpty(){
	return (SPI1->S && (1<<5));
}

void SPI_transmit(uint8_t byte){
   while(!isTransmitFlagEmpty()){
	   printf("\nBRUHH u stuck");
   }
   SPI1->DL = byte;
   delay_ms(1);	//wait for byte to set in
}

/* -----------------------------------------------------------------*/
/* 	Delay function
/* -----------------------------------------------------------------*/
void delay_ms(unsigned short delay_t) {
	SIM->SCGC6 |= (1 << 24); 		//Clock enable TPM0 (bit 24)
	SIM->SOPT2 |= (0x2 << 24);		//TMP clock source OSCERCLK
	TPM0->CONF |= (0x1 << 17); 		//Stop Counter On Overflow (CSOO)
	TPM0->SC = (1 << 7) | (0x7);   	//Prescaler of 128
	TPM0->MOD = delay_t * 62 + delay_t / 2 - 1;
	TPM0->SC |= 0x01 << 3;
	while (!(TPM0->SC & 0x80)) {
		__asm volatile ("nop");
	}
	return;
}
