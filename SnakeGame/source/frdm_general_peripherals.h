/*
 * frdm_general_peripherals.h
 *
 *  Created on: Mar 23, 2021
 *      Author: austinwright
 */

#ifndef FRDM_GENERAL_PERIPHERALS_H_
#define FRDM_GENERAL_PERIPHERALS_H_

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
#include "fsl_common.h"

void init_LEDS();

void init_SW();

void init_PIT();

void STOP_PIT();

void START_PIT();

void blinkLoseSequence();

void blinkWinSequence();

void blinkAngleLEDs(int angle);

void blinkChoosenLED(int index);

void PORTA_IRQHandler(void);

void PIT_IRQHandler(void);

int buttonPressed();

#endif /* FRDM_GENERAL_PERIPHERALS_H_ */
