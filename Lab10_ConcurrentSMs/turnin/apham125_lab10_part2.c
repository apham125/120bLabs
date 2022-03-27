/*	Author: Ashley Pham
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab 10  Exercise 1
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 *	Demo Link: https://drive.google.com/file/d/1ns7TzakRk3Wa9-JjiIapb4SDHLtc1u_Y/view?usp=sharing
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
	unsigned long threeLed_elaspedTime = 0;
	unsigned long blinkingLed_elaspedTime = 0;
	
	const unsigned long TimerPeriod = 100;
	
	TimerSet(TimerPeriod);
	TimerOn();
	
    while (1) {
	if (threeLed_elaspedTime == 300){
		threeLed_tick();
		threeLed_elaspedTime = 0;
	}
	if (blinkingLed_elaspedTime == 1000){
		blinkingLed_tick();
		blinkingLed_elaspedTime = 0;
	}
	combineLed_tick();

	while(!TimerFlag){}
	TimerFlag = 0;

	threeLed_elaspedTime += TimerPeriod;
	blinkingLed_elaspedTime += TimerPeriod;
	
    }
    return 1;
}
