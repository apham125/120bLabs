/*	Author: Ashley Pham
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab 11 Exercise 2
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 *	Demo Link: https://drive.google.com/file/d/1Av2zY7IeFLWYo3e5z9QJdHPCEsi51NGC/view?usp=sharing
 */
#include <avr/io.h>
#include <keypad.h>
#include <scheduler.h>
#include <avr/interrupt.h>
#ifdef _SIMULATE_
#include <timer.h>
#include "simAVRHeader.h"
#endif

unsigned char message[53] = "                CS120B is Legend... wait for it DARY!";
unsigned char i;
unsigned char pos;
unsigned char displayM[16];

enum LCDSM{start, display};

int LCDTick(int state){
	switch (state){
		case start:
			i =0;
			pos = 0;
			state = display;
			break;
		case display:
			for (i = 0; i <16; i++){
				displayM[i] = message[pos + i];
			}
			pos++;
			if (pos == 53){
				pos = 0;
			}

			LCD_DisplayString(1, displayM);
			state = display;
			break;
		default:
			state = start;
			break;
	}
	return state;
}

int main(void) {
	DDRA = 0xFF; PORTA = 0x00;
	DDRB = 0xFF; PORTB = 0x00;
	DDRC = 0xF0; PORTC = 0x0F;
	DDRD = 0xFF; PORTD = 0x00;

	static task task1;
	task *tasks[] = {&task1};
	const unsigned short numTasks = sizeof(tasks)/sizeof(task*);

	const char start = -1;

	task1.state = start;
	task1.period = 400;
	task1.elapsedTime = task1.period;
	task1.TickFct = &LCDTick;
	
	TimerSet(50);
	TimerOn();

	LCD_init();
        LCD_Cursor(1);

	unsigned short i;
    while (1) {
	for ( i = 0; i <numTasks; i++){
		if (tasks[i]->elapsedTime >= tasks[i]->period){
			tasks[i]->state = tasks[i]->TickFct(tasks[i]->state);
			tasks[i]->elapsedTime = 0;
		}
		tasks[i]->elapsedTime += 50;
	}
	while(!TimerFlag);
	TimerFlag = 0;
    }
    return 1;
}

