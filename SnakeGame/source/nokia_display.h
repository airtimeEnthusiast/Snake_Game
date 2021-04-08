/*
 * frdm_accel.h
 *
 *  Created on: Mar 19, 2021
 *      Author: austinwright
 */

#ifndef NOKIA_DISPLAY_H_
#define NOKIA_DISPLAY_H_


/* -----------------------------------------------------------------*/
/* 	Initialize the PCD8544 on-board display chip. See the Nokia5110
 *  Data sheet for section and page reference
 *  See Page 15 of the Nokia data sheet for Intialization steps
/* -----------------------------------------------------------------*/
void init_5110();


/* -----------------------------------------------------------------*/
/* 	A reset function that
/* -----------------------------------------------------------------*/
void reset_5110();


/* -----------------------------------------------------------------*/
/* 	Initialize the PCD8544 on-board display chip. See the Nokia5110
 *  Data sheet for section and page reference
 *  See Page 15 of the Nokia data sheet for Intialization steps
/* -----------------------------------------------------------------*/
void RES_Pulse();

/* -----------------------------------------------------------------*/
/* 	Initialize the PCD8544 on-board display chip. See the Nokia5110
 *  Data sheet for section and page reference
 *  See Page 15 of the Nokia data sheet for Intialization steps
/* -----------------------------------------------------------------*/
void Function_Set();

/* -----------------------------------------------------------------*/
/* 	Initialize the PCD8544 on-board display chip. See the Nokia5110
 *  Data sheet for section and page reference
 *  See Page 15 of the Nokia data sheet for Intialization steps
/* -----------------------------------------------------------------*/
void Display_Control();

#endif /* NOKIA_DISPLAY_H_ */
