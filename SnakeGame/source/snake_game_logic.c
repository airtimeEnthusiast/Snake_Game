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
#include "snake_game_logic.h"
#include "nokia_display.h"
#include "frdm_general_peripherals.h"
#include "snake_buffer.h"
/* snake directions */
uint8_t UP  = -1;
uint8_t RIGHT = -1;
uint8_t DOWN  = -1;
uint8_t LEFT  = -1;


/* -----------------------------------------------------------------*/
/* 	Interrupt function Port A (button switches interupt)
/* -----------------------------------------------------------------*/
void playGame(){

	while(1){

	//Grow the snake inside the display

	//Add the first new fruit

	}
}
/* -----------------------------------------------------------------*/
/* 	Interrupt function Port A (button switches interupt)
/* -----------------------------------------------------------------*/
void Add_fruit(){

}
/* -----------------------------------------------------------------*/
/* 	Interrupt function Port A (button switches interupt)
/* -----------------------------------------------------------------*/
void init_Snake(){
	//Intialize snake head
	Set_Pixel(42,24,1);
}
/* -----------------------------------------------------------------*/
/* 	Interrupt function Port A (button switches interupt)
/* -----------------------------------------------------------------*/
void Grow_snake(){

}
/* -----------------------------------------------------------------*/
/* 	Interrupt function Port A (button switches interupt)
/* -----------------------------------------------------------------*/
void Direction(int d){
	 /*switch(d) {
	    case UP:    { left=FALSE; right=FALSE; up=TRUE ; down=FALSE; dr = -1; dc =  0;} break;
	    case RIGHT: { left=FALSE; right=TRUE ; up=FALSE; down=FALSE; dr =  0; dc =  1;} break;
	    case DOWN:  { left=FALSE; right=FALSE; up=FALSE; down=TRUE ; dr =  1; dc =  0;} break;
	    case LEFT:  { left=TRUE ; right=FALSE; up=FALSE; down=FALSE; dr =  0; dc = -1;} break;
	 }*/
}

/* -----------------------------------------------------------------*/
/* 	Interrupt function Port A (button switches interupt)
/* -----------------------------------------------------------------*/
void dummy_move(){

}

