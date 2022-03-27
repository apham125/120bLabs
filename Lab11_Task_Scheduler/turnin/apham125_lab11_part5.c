/*	Author: Ashley Pham
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab 11 Exercise 5
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 *	Demo Link: https://drive.google.com/file/d/1MWTTJU-IlCJsIvcFbaDwMHmBCStOkPsB/view?usp=sharing
 */
#include <avr/io.h>
#include <keypad.h>
#include <scheduler.h>
#include <avr/interrupt.h>
#ifdef _SIMULATE_
#include <timer.h>
#include "simAVRHeader.h"
#endif

unsigned char i;
unsigned char lane1[32] = "             #         #        ";
unsigned char loseMssge[32] = "    YOU LOSE!!    PRESS RESET!!!";
unsigned char pos = 0;
unsigned char pause = 1;
unsigned char charPos = 1;
unsigned char loseFlag = 0;

enum ObstacleSM{start,display, pauseGame, loseGame};
enum ButtonTick{buttonStart, buttonUp, buttonDown, buttonRelease, buttonPause};

int obstacleTick(int state){
	switch (state){
		case start:
			state = display;
			break;
		case display:
			for (i = 1; i < 33; i++){
				LCD_Cursor(i);
				if ((pos + i) < 32){
					LCD_WriteData(lane1[i+pos]);
				}
				else{
					LCD_WriteData(lane1[i + pos - 32]);
				}
			}
			LCD_Cursor(charPos);
			if ((lane1[pos + charPos]) == '#'){
				for (i = 0; i <32; i++){
					LCD_Cursor(i);
					LCD_WriteData(loseMssge[i]);
				}	
				loseFlag = 1;
				state = loseGame;
			}
			else{
				pos++; 
				if (pos == 32){
					pos = 0;
				}	
				if (pause == 1){
					state = pauseGame;
				}	
				else{		
					state = display;
				}
			}

			break;
		case pauseGame:
			if (pause){
				state = pauseGame;
			}
			else{
				state = start;
			}
			break;
		case loseGame:
			if (loseFlag){
				state = loseGame;
			}
			else{
				state = start;
				pos = 0;
				charPos = 1;
			}
			break;
		default:
			state = start;
			break;
	}
	return state;
}

int buttonTick(int state){
	switch (state){
		case start: 
			state = buttonRelease;
			break;
		case buttonRelease:
			if ((~PINA & 0x07) == 0x01){
				if (pause == 1){
					pause = 0;
				}
				else{
					pause = 1;
				}
				if (loseFlag){
					loseFlag = 0;
				}
				state = buttonPause;
			} 
			else if ((~PINA & 0x07) == 0x02){
				charPos = 17;
				state = buttonDown;
			}
			else if ((~PINA & 0x07) == 0x04){
				charPos = 1;
				state = buttonUp;
			}
			else{
				state = buttonRelease;
			}
			break;
		case buttonPause:
			if ((~PINA & 0x07) == 0x00){
				state = buttonRelease;
			}
			else{
				state = buttonPause;
			}
			break;
		case buttonUp:
			if ((~PINA & 0x07) == 0x00){
				state = buttonRelease;
			}
			else{
				state = buttonUp;
			}
			break;
		case buttonDown:
			if ((~PINA & 0x07) == 0x00){
				state = buttonRelease;
			}
			else{
				state = buttonDown;
			}
			break;
		default:
			state = start;
			break;
	}
	return state;
}

int main(void) {
	DDRA = 0x00; PORTA = 0xFF;
	DDRC = 0xFF; PORTC = 0x00;
	DDRD = 0xFF; PORTD = 0x00;

	static task task1, task2;
	task *tasks[] = {&task1, &task2};
	const unsigned short numTasks = sizeof(tasks)/sizeof(task*);

	const char start = -1;

	task1.state = start;
	task1.period = 200;
	task1.elapsedTime = task1.period;
	task1.TickFct = &obstacleTick;

	task2.state = start;
	task2.period = 50;
	task2.elapsedTime = task2.period;
	task2.TickFct = &buttonTick;
	
	TimerSet(50);
	TimerOn();

	LCD_init();

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

