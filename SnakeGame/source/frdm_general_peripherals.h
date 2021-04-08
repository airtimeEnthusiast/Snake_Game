/*
 * frdm_general_peripherals.h
 *
 *  Created on: Mar 23, 2021
 *      Author: austinwright
 */

#ifndef FRDM_GENERAL_PERIPHERALS_H_
#define FRDM_GENERAL_PERIPHERALS_H_


void Enable_LEDS();

void Enable_SW();

void blinkLoseSequence();

void blinkWinSequence();

void blinkAngleLEDs(int angle);

void blinkChoosenLED(int index);


#endif /* FRDM_GENERAL_PERIPHERALS_H_ */
