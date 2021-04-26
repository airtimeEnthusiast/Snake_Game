/*
 * Austin Wright 4-25-21
 * Project 5 CSE 325: Snake Game
 * frdm_general_peripherals.h
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

/* -----------------------------------------------------------------*/
/* Initialize the LEDs connected at Port C
 * LED 1: PortC 0
 * LED 2: PortC 4
 * LED 3: PortC 6
 * LED 4: PortC 7
/* -----------------------------------------------------------------*/
void init_LEDS();

/* -----------------------------------------------------------------*/
/* Initialize the switches connected at Port A
 * SW 1: PortC 4
 * SW 2: PortC 5
 * SW 3: PortC 12
 * SW 4: PortC 13
/* -----------------------------------------------------------------*/
void init_SW();

/* -----------------------------------------------------------------*/
/* 	Initialize the periodic interrupt vector module for snake movement
 *  and timing in this case
/* -----------------------------------------------------------------*/
void init_PIT();

/* -----------------------------------------------------------------*/
/* 	Stop PIT by zero-ing channel 0 Timer Control Register see page 592
 *  See section 32.3.6
/* -----------------------------------------------------------------*/
void STOP_PIT();

/* -----------------------------------------------------------------*/
/* 	Start PIT by setting 0x3 into the Timer Control Register
 *  See section 32.3.6
/* -----------------------------------------------------------------*/
void START_PIT();

/* -----------------------------------------------------------------*/
/* Blink one of the GPIO LEDs from an index 1-4
/* -----------------------------------------------------------------*/
void blinkChoosenLED(int index);

/* -----------------------------------------------------------------*/
/* Draw a segment of the snake. enable is 1 for a write and enable is
 * 0 for an erase of a pixel
/* -----------------------------------------------------------------*/
void Draw_Segment(uint8_t x, uint8_t y, uint8_t enable);

/* -----------------------------------------------------------------*/
/* 	Move a snake segment in the latest specified direction
/* -----------------------------------------------------------------*/
void move();

/* -----------------------------------------------------------------*/
/* Periodic Interrupt handler for moving the snake around
/* -----------------------------------------------------------------*/
void PIT_IRQHandler(void);

/* -----------------------------------------------------------------*/
/* Interrupt for the switches on Port A
/* -----------------------------------------------------------------*/
void PORTA_IRQHandler(void);

/* -----------------------------------------------------------------*/
/* Determine if a button was pressed by the user
/* -----------------------------------------------------------------*/
int buttonPressed();

/* -----------------------------------------------------------------*/
/* 	Initialize the snake
/* -----------------------------------------------------------------*/
void init_Snake(int direction);

/* -----------------------------------------------------------------*/
/* 	Return the latest direction value
/* -----------------------------------------------------------------*/
int getDirection();
#endif /* FRDM_GENERAL_PERIPHERALS_H_ */
