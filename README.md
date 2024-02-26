# MCU Snake Game
This simple snake game runs on an [FDRM KL46Z MCU](https://home.agh.edu.pl/~ostrowsk/teksty/manual.pdf) that communicates with a Nokia 5510 LCD to display the game. Timing is handled by the internal periodic interupt vector (PIT).  
## Game Movement Controls
FSM101 push button switches were configured for active high, use the internal pull-down resistors and connected to these IO signals
#### Switch 1 - PTA4 (Left)
#### Switch 2 - PTA5 (Up)
#### Switch 3 - PTA12 (Down)
#### Switch 4 - PTA13 (Right)

## Display Connectivity
[Nokia 5110](https://www.sparkfun.com/datasheets/LCD/Monochrome/Nokia5110.pdf) communicates using the MCU's SPI protocol interface. 
 |  LCD Pin |FDRM Pin |
| --- | --- |
| VCC | 3.3V (P3V3)|
| GND | GND |
| VCC | 3.3V (P3V3)|
| RST or RES | PTD4 |
| D/C | PTD7)|
| DN(MOSI) | PTD6 |

## Video Link
[Demo Video](https://youtu.be/EmfKIQFfCK4) 
