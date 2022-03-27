
/*	Author: Ashley Pham
 *  Partner(s) Name: 
 *	Lab Section:23
 *	Assignment: Lab 3  Exercise 2
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif
//Zybooks example 2.7.1

unsigned char GetBit(unsigned char x, unsigned char i){
	return ((x & (0x01 << i)) !=0);
}

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF;
	DDRC = 0xFF; PORTC = 0x00;

    unsigned char tempA;
    while(1){

        tempA = (~PINA) & 0x0F;
        
        if (tempA == 0x00){
            PORTC = 0x40;
        }
        else if (0x00 <= tempA  && tempA <= 0x02){
            PORTC = 0x60;
        }
        else if(0x03 <= tempA && tempA<= 0x04){
            PORTC = 0x70;
        }
        else if(0x05 <= tempA && tempA <=0x06){
            PORTC = 0x38;
        }
        else if(0x07 <= tempA && tempA <= 0x09){
            PORTC =0x3C;
        }
        else if(0x0A <= tempA && tempA <= 0x0D){
            PORTC = 0x3E;
        }
        else if (0x0E <= tempA && tempA <= 0x0F){
            PORTC = 0x3F;
        }

    }
    return 1;
}