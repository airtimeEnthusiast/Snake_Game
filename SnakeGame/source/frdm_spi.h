/*
 * frdm_i2c.h
 *
 *  Created on: Mar 18, 2021
 *      Author: austinwright
 */
#include "fsl_device_registers.h"


#ifndef FRDM_I2C_H_
#define FRDM_I2C_H_

void delay_ms(unsigned short delay_t);
void SPI_init(void);
void SPI_transmit(uint8_t byte);
int isTransmitFlagEmpty();


#endif /* FRDM_I2C_H_ */
