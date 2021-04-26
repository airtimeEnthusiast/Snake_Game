/*
 * Austin Wright 4-25-21
 * Project 5 CSE 325: Snake Game
 * frdm_spi.h
 */
#include "fsl_device_registers.h"


#ifndef FRDM_I2C_H_
#define FRDM_I2C_H_

/* -----------------------------------------------------------------*/
/* 	Initialize the Serial Peripheral Interface
 *  1. Enable Port D
 *  2. Enable SPI clock
 *  3. Set Port Mux to enable Nokia display ports:
 * 	Alt 1 to enable ~SCE at Port D2
 *  Alt 1 to enable ~RST at Port D4
 *  Alt 1 to enable ~D/C at Port D7
 *  Alt 2 to enable DN (MOSI) at Port D6
 *	Alt 2 to enable SCLK at Port D5
 */
/* -----------------------------------------------------------------*/
void init_SPI(void);

/* -----------------------------------------------------------------*/
/* 	Return the SPI Transmit Buffer Empty Flag
/* -----------------------------------------------------------------*/
int isTransmitFlagEmpty();

/* -----------------------------------------------------------------*/
/* 	Send a byte the display through the SPI data low register
/* -----------------------------------------------------------------*/
void SPI_transmit(uint8_t byte);

/* -----------------------------------------------------------------*/
/* 	Delay function
/* -----------------------------------------------------------------*/
void delay_ms(unsigned short delay_t);

#endif /* FRDM_I2C_H_ */
