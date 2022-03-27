/*	Author:Aslhey
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab 5 Exercise 3
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.

 * demo link: https://drive.google.com/file/d/1cuYWRaN6Guht_rrqSKhBHCvfv_18gKig/view?usp=sharing
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

unsigned char i;
unsigned char lights[11] = {0x01, 0x05, 0x15, 0x17, 0x1F, 0x3F, 0x00, 0x15, 0x2A, 0x15, 0x2A};
	
enum state{start, init, light} state;

void tick(){
	switch(state){
		case start:
			state = init;
			PORTB = 0x00;
			i = 0;
			break;
		case init:
			if((~PINA & 0x01) == 0x00){
                                state = init;
                        }
                        else{
                                state = light;
                                PORTB = lights[i];
                                i++;
                        }
                        break;
                case light:
                        if ((~PINA & 0x01) == 0x00){
                                state = init;
				if (i == 11){
					i = 0;
					PORTB = 0x00;
				}
			}
                        else{
                                state = light;
                        }
                        break;
		default:
			state = start;
			break;

	}
}

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF; 
	DDRB = 0xFF; PORTB = 0x00;
    /* Insert your solution below */

	state = start;
    while (1) {
	    tick();

    }
    return 1;
}