/*	Author: Ashley Pham
 *  Partner(s) Name: 
 *	Lab Section:23
 *	Assignment: Lab 9  Exercise 1
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#include <avr/interrupt.h>
#ifdef _SIMULATE_
#include "timer.h"
#include "simAVRHeader.h"
#endif

enum state{start, init, buttonPress, playSong, hold} state;
/*
 G = 392,
 F = 349.23,
 A = 440,
 D = 293.66,
 E = 329.63,
 C = 261.63,
 C = 523.25,
 A# = 466.16,
*/
unsigned short song[32] = {
523.25, 466.16, 440, 466.16,440,349.23,261.63,261.63,293.66, 261.63,
293.66,329.63,349.23,523.25,523.25,523.25, 587.33, 523.25,587.33,
659.25, 698.45,523.25,523.25,523.25, 466.16, 440,392,349.23,
523.25,523.25
};
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
			i = 0;
			if((~PINA & 0x01) == 0x01){
				state = buttonPress;
			}
			else{
				state = init;
			}
			break;
		case buttonPress:
			if ((~PINA &0x01) == 0x00){
				state = playSong;
				set_PWM(song[i]);
			}
			else{
				state = buttonPress;
			}
			break;
		case playSong:
			if (i == 32){
				if (~PINA & 0x01 == 0x01){ state = hold;}
				else{ state = init;}
			}
			else{
				i++;
				set_PWM(song[i]);
			}
			break;
		case hold:
			if ((~PINA & 0x01) == 0x01){
				state = hold;
			}
			else{
				state = init;
			}
	}	
}
int main(void) {
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x40;
	
	state = start;

	TimerSet(350);
	TimerOn();
	PWM_on();
    while (1) {
	tick();
	while(!TimerFlag){}
		TimerFlag = 0;
    }
    return 1;
}
