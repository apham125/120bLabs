/*	Author: Ashley Pham
 *  Partner(s) Name: 
 *	Lab Section:23
 *	Assignment: Lab 9  Exercise 1
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 *	demo Link: https://drive.google.com/file/d/1WZ5ejKYVmYK4Een9GB89HxwSNXjINzev/view?usp=sharing
 */
#include <avr/io.h>
#include <avr/interrupt.h>
#ifdef _SIMULATE_
#include "timer.h"
#include "simAVRHeader.h"
#endif

enum state{start, init, cNote, dNote,eNote} state;

void set_PWM(double frequency) {
	static double current_frequency;
	if (frequency != current_frequency) {
		if (!frequency) { TCCR3B &= 0x08;}
		else {TCCR3B |= 0x03;}

		if (frequency < 0.954) { OCR3A = 0xFFFF;}
		else if (frequency > 31250) { OCR3A = 0x0000;}

		else { OCR3A = (short) (8000000 / (128 * frequency)) -1;}
		TCNT3 = 0;
		current_frequency = frequency;
	}
}
void PWM_on() {
	TCCR3A = (1 << COM3A0);
	TCCR3B = (1 << WGM32) | (1 << CS31) | (1 << CS30);
	set_PWM(0);
}

void PWM_off() {
	TCCR3A = 0x00;
	TCCR3B = 0x00;
}

void tick(){
	switch(state){
		case start:
			state = init;
			break;
		case init:
			set_PWM(0.0);
			if((~PINA & 0x07) == 0x01){
				state = cNote;
				set_PWM(261.63);
			}
			else if((~PINA & 0x07) == 0x02){
				state = dNote;
				set_PWM(293.66);
			}
			else if((~PINA & 0x07) == 0x04){
				state = eNote;
				set_PWM(329.63);
			}
			else{
				state = init;
			}
			break;
		case cNote:
			if ((~PINA & 0x07) == 0x01){
				state = cNote;
				set_PWM(261.63);
			}
			else{
				state = init;
			}
			break;
		case dNote:
			if ((~PINA & 0x07) == 0x02){
				state = dNote;
				set_PWM(293.66);
			}
			else{
				state = init;
			}
			break;
		case eNote:
			if ((~PINA & 0x07) == 0x04){
				state = eNote;
				set_PWM(329.63);
			}
			else{
				state = init;
			}
			break;
	}
}
int main(void) {
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x40;
	
	state = start;
	PWM_on();
    while (1) {
	tick();
    }
    return 1;
}
