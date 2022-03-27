/*	Author: ashley pham
 *  Partner(s) Name: 
 *	Lab Section:23
 *	Assignment: Lab 8  Exercise 2
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 *	Demo Link: https://drive.google.com/file/d/1BvF0q8aEXFfSnDZ6k3M6E2DD2joOg1Bv/view?usp=sharing
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

    while (1) {
	val = ADC;
	PORTB = (char)val;
	PORTD = (char)(val >>8);
    }
    return 0;
}




