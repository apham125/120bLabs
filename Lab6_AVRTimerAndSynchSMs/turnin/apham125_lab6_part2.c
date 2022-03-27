/*      Author: Ashley Pham
 *  Partner(s) Name: 
 *      Lab Section:
 *      Assignment: Lab 6  Exercise 1
 *      Exercise Description: [optional - include for your own benefit]
 *
 *      I acknowledge all content contained herein, excluding template or example
 *      code, is my own original work.
 *	Demo link https://drive.google.com/file/d/1dzvD-fUyW5aNsHGWRpCrOk5oG7pWC1LN/view?usp=sharing
 */
#include <avr/io.h>
#include <avr/interrupt.h>
#ifdef _SIMULATE_
#include "timer.h"
#include "simAVRHeader.h"
#endif

enum state{start, light1, light2, light3, buttonPress, buttonRelease, restart} state;
unsigned char i;

void tick(){
	switch (state){
		case start:
			PORTB = 0x00;
			i = 0;
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
			if ((~PINA & 0x01) == 0){
				state = buttonRelease;
			}
			else{
				state = restart;
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
	
    state = start;
    while (1){
	    
	tick();
	   while(!TimerFlag){}
	    TimerFlag = 0;
    }
    
    return 1;
}

