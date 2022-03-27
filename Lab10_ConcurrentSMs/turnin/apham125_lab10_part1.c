/*	Author: Ashley Pham
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab 10  Exercise 1
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 *	Demo Link: https://drive.google.com/file/d/11Zt74Yo6k4Kjfd_XvTPuFJKD2F6wTSf5/view?usp=sharing
 */
#include <avr/io.h>
#include <avr/interrupt.h>
#ifdef _SIMULATE_
#include "timer.h"
#include "simAVRHeader.h"
#endif

enum ThreeLEDsSM {start1, light1, light2, light3} threeLed_state;
enum BlinkingLEDSM{start2, blink1, blink2} blinkingLed_state;
enum CombineLedsSM {start3, combine} combineLed_state;

unsigned char threeLEDs;
unsigned char blinkingLED;

void threeLed_tick(){
	switch(threeLed_state){
		case start1:
			threeLed_state = light1;
			threeLEDs = 0x01;
			break;
		case light1:
			threeLed_state = light2;
			threeLEDs = 0x02;
			break;
		case light2:
			threeLed_state = light3;
			threeLEDs = 0x04;
			break;
		case light3:
			threeLed_state = light1;
			threeLEDs = 0x01;
			break;
	}	
}

void blinkingLed_tick(){
	switch (blinkingLed_state){
		case start2:
			blinkingLed_state = blink1;
			blinkingLED = 0x00;
			break;
		case blink1:
			blinkingLed_state = blink2;
			blinkingLED = 0x08;
			break;
		case blink2:
			blinkingLed_state = blink1;
			blinkingLED = 0x00;
			break;
	}
}

void combineLed_tick(){
	switch(combineLed_state){
		case start3:
			combineLed_state = combine;
			break;
		case combine:
			PORTB = threeLEDs | blinkingLED;
			combineLed_state = combine;
			break;
	}
}

int main(void) {
	DDRB = 0xFF; PORTB = 0x00;
	TimerSet(1000);
	TimerOn();

    while (1) {
	threeLed_tick();
	blinkingLed_tick();
	combineLed_tick();

	while(!TimerFlag){}
	TimerFlag = 0;
	
    }
    return 1;
}
