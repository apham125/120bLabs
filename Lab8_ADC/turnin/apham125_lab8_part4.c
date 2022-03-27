/*	Author: ashley pham
 *  Partner(s) Name: 
 *	Lab Section:23
 *	Assignment: Lab 8  Exercise 3
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 *	Demo Link: https://drive.google.com/file/d/1oUmtwcaWdU8vR2KWeldoKlSn2C3e1lvD/view?usp=sharing
 */
#include <avr/io.h>
#include <avr/interrupt.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif
void ADC_init(){
	ADCSRA |= (1 << ADEN) | (1 << ADSC) | (1 << ADATE);
}

int main(void) {
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	DDRD = 0xFF; PORTD = 0x00;
	ADC_init();
	unsigned short val;
	unsigned short max = 0xC8;

    while (1) {
	val = ADC;
	unsigned char temp =(char)val;

	if (temp >= (max)){
		PORTB = 0xFF;
	}
	else if (temp >= 7*(max/8)){
		PORTB = 0x7F;
	}
	else if (temp >= 6*(max/8)){
		PORTB = 0x3F;
	}
	else if (temp >= 5*(max/8)){
		PORTB = 0x1F;
	}
	else if (temp >= 4*(max/8)){
		PORTB = 0x0F;
	}
	else if (temp >= 3*(max/8)){
		PORTB = 0x07;
	}
	else if (temp >= 2*(max/8)){
		PORTB = 0x03;
	}
	else if (temp >= (max/8)){
		PORTB = 0x01;
	}

/*
	if (temp <= (max/8)){
		PORTB = 0x01;
	}
	else if (temp <= 2*(max/8)){
		PORTB = 0x03;
	}
	else if (temp <= 3*(max/8)){
		PORTB = 0x07;
	}
	else if (temp <= 4*(max/8)){
		PORTB = 0x0F;
	}
	else if (temp <= 5*(max/8)){
		PORTB = 0x1F;
	}
	else if (temp <= 6*(max/8)){
		PORTB = 0x3F;
	}
	else if (temp <= 7*(max/8)){
		PORTB = 0x7F;
	}
	else if (temp <= (max)){
		PORTB = 0xFF;
	}
*/

    }
    return 0;
}




