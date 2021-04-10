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
 * Steps
 * 1. Command mode (D/~C) low
 * 2. Briefly allow for extended instruction set
 * 3. Set the display contrast (VOP)
 * 4. Return to normal instruction mode
 * 5. Set the display to normal mode
/* -----------------------------------------------------------------*/
void init_5110();

/* -----------------------------------------------------------------*/
/* 	Initialize the PCD8544 on-board display chip. See the Nokia5110
 *  Data sheet for section and page reference
 *  See Page 15 of the Nokia data sheet for Intialization steps
/* -----------------------------------------------------------------*/
void Set_Pixel(int x, int y, int enable);

/* -----------------------------------------------------------------*/
/* 	Initialize the PCD8544 on-board display chip. See the Nokia5110
 *  Data sheet for section and page reference
 *  See Page 15 of the Nokia data sheet for Intialization steps
/* -----------------------------------------------------------------*/
void Clear_Entire_Display();

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
void Reset_Serial();

/* -----------------------------------------------------------------*/
/* 	Initialize the PCD8544 on-board display chip. See the Nokia5110
 *  Data sheet for section and page reference
 *  See Page 15 of the Nokia data sheet for Intialization steps
/* -----------------------------------------------------------------*/
void Zero_Cursor_Address();



#endif /* NOKIA_DISPLAY_H_ */
