/*	Author: Ashley Pham
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab 11 Exercise 4
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 *	Demo Link: https://drive.google.com/file/d/1sRB5acPlwi0IEt1ugCS5yx2MRYb19otL/view?usp=sharing
 */
#include <avr/io.h>
#include <keypad.h>
#include <scheduler.h>
#include <timer.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

unsigned char x;
unsigned char i;
enum KeypadSm{start, press};
enum LCDTick{startLCD, display};

int KeypadTick(int state){
	switch (state){
		case start:
			x = 0;
			state = press;
			break;
		case press:
			x = GetKeypadKey();
			break;
		default:
			state = start;
			break;
	}
	return state;
}

int LCDTick(int state){
	switch(state){
		case startLCD:
			LCD_DisplayString(1,"Congratulations!");
			state = display;
			break;
		case display:
			if (x != '\0'){
				LCD_Cursor(i);
				LCD_WriteData(x);
				i++;
				if (i == 17){
					i = 0;
				}
			}
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

	static task task1, task2;
	task *tasks[] = {&task1, &task2};
	const unsigned short numTasks = sizeof(tasks)/sizeof(task*);

	const char start = -1;

	task1.state = start;
	task1.period = 50;
	task1.elapsedTime = task1.period;
	task1.TickFct = &KeypadTick;

	task2.state = start;
	task2.period = 200;
	task2.elapsedTime = task1.period;
	task2.TickFct = &LCDTick;
	
	LCD_init();
        LCD_Cursor(1);

	TimerSet(50);
	TimerOn();

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
