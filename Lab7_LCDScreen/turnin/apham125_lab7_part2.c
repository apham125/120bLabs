/*      Author: Ashley Pham
 *  Partner(s) Name: 
 *      Lab Section:
 *      Assignment: Lab 7  Exercise 2
 *      Exercise Description: [optional - include for your own benefit]
 *
 *      I acknowledge all content contained herein, excluding template or example
 *      code, is my own original work.
 *	Demo Link: https://drive.google.com/file/d/1rdmbedBiGtgz9BVgqy5EscJ80N-5GgP2/view?usp=sharing
 */
#include <avr/io.h>
#include <avr/interrupt.h>
#ifdef _SIMULATE_
#include "timer.h"
#include "simAVRHeader.h"
#endif

enum state{start, light1, light2, light3, buttonPress, buttonRelease, restart} state;
unsigned char i;
unsigned char score;
unsigned char flag;

void tick(){
	switch (state){
		case start:
			PORTB = 0x00;
			i = 0;
			score = 5;
			LCD_ClearScreen();
			LCD_WriteData(score + '0');
			state = light1;
			break;
		case light1:
			PORTB = 0x01;
			if ((~PINA & 0x01) == 1){
				state = buttonPress;
			}
			else{
				state = light2;
			}
			break;

		case light2:
			PORTB = 0x02;
			i++;
			if ((~PINA & 0x01) == 0x01){
				state = buttonPress;
			}
			else if (i%2 == 1){
				state = light3; 
			}
			else {
				state = light1;
			}
			break;
		case light3:
			PORTB = 0x04;
                       	if ((~PINA & 0x01) == 1){
                                state = buttonPress;
                        }
                        else{
                                state = light2;
                        }
			break;
		case buttonPress:
			if ((~PINA & 0x01) == 1){
				state = buttonPress;
			}
			else{
				state = buttonRelease;
			}
			break;
		case buttonRelease:
			if (flag == 0){
				if (PORTB == 0x01 || PORTB == 0x04){
					if (score >0){
						score--;
					}
					LCD_ClearScreen();
					LCD_WriteData(score+'0');
				}
				else{
					score++;
					LCD_ClearScreen();
					LCD_WriteData(score+'0');
				}

				if (score == 9){
					LCD_ClearScreen();
					LCD_DisplayString(1, "WINNER!!");
					score = 5;
				}
			}
			flag = 1;	

			if ((~PINA & 0x01) == 0){
				state = buttonRelease;
			}
			else{
				state = restart;
				flag = 0;
			}
			break;
		case restart:
			if ((~PINA & 0x01) == 1){
				state = restart;
			}
			else{
				state = light1;
				i=0;
			}
			break;
	}
}


int main(void) {
    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0xFF; PORTB = 0x00;
    TimerSet(300);
    TimerOn();

    LCD_init();
    LCD_Cursor(1);
	
    state = start;
    while (1){
	    
	tick();
	   while(!TimerFlag){}
	    TimerFlag = 0;
    }
    
    return 1;
}

