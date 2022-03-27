/*      Author: Ashley Pham
 *  Partner(s) Name: 
 *      Lab Section:
 *      Assignment: Lab 6  Exercise 1
 *      Exercise Description: [optional - include for your own benefit]
 *
 *      I acknowledge all content contained herein, excluding template or example
 *      code, is my own original work.
 *	Demo Link: https://drive.google.com/file/d/1o2mnVX1FFMp0MX_SnVp0t9XONhg4tVbP/view?usp=sharing
 */
#include <avr/io.h>
#include <avr/interrupt.h>
#ifdef _SIMULATE_
#include "timer.h"
#include "simAVRHeader.h"
#endif

enum state{start, light1, light2, light3} state;

void tick(){
	switch(state){
		case start:
			state = light1;
			PORTB = 0x01;
			break;
		case light1:
			state = light2;
			PORTB = 0x02;
			break;
		case light2:
			state = light3;
			PORTB = 0x04;
			break;
		case light3:
			state = light1;
			PORTB = 0x01;
			break;
	}
}

int main(void) {
    DDRB = 0xFF;
    PORTB = 0x00;
    TimerSet(1000);
    TimerOn();

	state = start;
    while (1) {
        tick();
        while(!TimerFlag);
        TimerFlag = 0;
    }
    return 1;
}

