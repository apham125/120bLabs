/*	Author: Ashley Pham
 *  Partner(s) Name: 
 *	Lab Section:23
 *	Assignment: Lab 9  Exercise 1
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 *	Demo Link: https://drive.google.com/file/d/1riA3YqdR_74dfOEdlP-YnYm5jDFvNqjH/view?usp=sharing
 */
#include <avr/io.h>
#include <avr/interrupt.h>
#ifdef _SIMULATE_
#include "timer.h"
#include "simAVRHeader.h"
#endif

enum state{start, init, offPress, onPress,onRelease, increment, decrement} state;
unsigned short frequencies[8] = {261.63, 293.66, 329.63,349.23,392.00,440.00, 493.88,523.25};
unsigned char i;

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
			set_PWM(0);
			i = 0;
			if((~PINA & 0x07) == 0x01){
				state = onPress;
			}
			else { state = init;}
			break;
		case onPress:
			if ((~PINA & 0x07) == 0x01){
				state = onPress;
			}
			else{
				state = onRelease;
				set_PWM(frequencies[i]);
			}
			break;
		case onRelease:
			if ((~PINA & 0x07) == 0x01){
				state = offPress;
			}
			else if ((~PINA & 0x07) == 0x02){
				state = increment;
				if (i<7){
					i++;
				}
				set_PWM(frequencies[i]);
			}
			else if((~PINA & 0x07) == 0x04){
				state = decrement;
				if (i>0){
					i--;
				}
				set_PWM(frequencies[i]);
			}
			break;
		case offPress:
			if ((~PINA & 0x07) == 0x01){
				state = offPress;
			}
			else{
				state = init;
			}
			break;
		case increment:
			if ((~PINA & 0x07) == 0x02){
				state = increment;
			}
			else{
				state = onRelease;
			}
			break;
		case decrement:
			if ((~PINA & 0x07) == 0x04){
				state = decrement;
			}
			else{
				state = onRelease;
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
