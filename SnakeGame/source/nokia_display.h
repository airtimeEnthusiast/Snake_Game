/*
 * Austin Wright 4-25-21
 * Project 5 CSE 325: Snake Game
 * nokia_display.h
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
/* 	Select a bank based on y coordinate range
/* -----------------------------------------------------------------*/

int Bank_Select(int yCoord);
/* -----------------------------------------------------------------*/
/* 	Print the buffer within the display
/* -----------------------------------------------------------------*/
void Print_buffer();

/* -----------------------------------------------------------------*/
/*	Set an individual pixel
/* -----------------------------------------------------------------*/
void Set_Pixel(int x, int y, int enable);

/* -----------------------------------------------------------------*/
/* 	Returns 1 if a pixel is enabled and 0 if it is disabled
/* -----------------------------------------------------------------*/
int Get_Pixel(int x, int y);

/* -----------------------------------------------------------------*/
/* 	Clean the entire display
/* -----------------------------------------------------------------*/
void Clear_Entire_Display();

/* -----------------------------------------------------------------*/
/* 	Apply RES pulse 8.1 Figure 13
/* -----------------------------------------------------------------*/
void RES_Pulse();

/* -----------------------------------------------------------------*/
/* Apply RES pulse 8.1 Figure 12
/* -----------------------------------------------------------------*/
void Reset_Serial();

/* -----------------------------------------------------------------*/
/* Home the cursor
/* -----------------------------------------------------------------*/
void Zero_Cursor_Address();



#endif /* NOKIA_DISPLAY_H_ */
