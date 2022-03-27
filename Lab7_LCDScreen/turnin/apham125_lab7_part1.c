/*	Author: Ashley Pham
 *  Partner(s) Name: 
 *	Lab Section:23
 *	Assignment: Lab 7  Exercise 1
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 *	Demo link: https://drive.google.com/file/d/1wYwmIbLnLOdCB0Ny4qFV-j6k3mHBybP-/view?usp=sharing
 */
#include <avr/io.h>
#include <avr/interrupt.h>
#ifdef _SIMULATE_
#include "timer.h"
#include "simAVRHeader.h"
#endif

unsigned char i;
unsigned char temp;

enum state {start, init, increment, decrement, reset} state;

void tick(){
    switch (state){
        case start:
	    temp = 7;
	    LCD_ClearScreen();
	    LCD_WriteData(temp + '0');
	    i = 0;
            state = init;
        break;

        case init:
            if (PINA == 0xFE){
                state = increment;
            }
            else if ((PINA) == 0xFD){
                state = decrement;

            }
            else if ((PINA) == 0xFC){
                state = reset;
		temp = 0;
		LCD_ClearScreen();
	        LCD_WriteData(temp + '0');
            }
            else { 
                state = init;
            }
        break;

        case increment:
	    if (i == 10){
		    if (temp < 9){
		            temp++;
			    LCD_ClearScreen();
	        	    LCD_WriteData(temp + '0');
		    }
		    i = 0;
	    }

            if ((PINA) == 0xFF){
                state = init;
            	if (temp < 9){
                    	temp++;
		        LCD_ClearScreen();
	        	LCD_WriteData(temp + '0');
		}
            }
            else if ((PINA) == 0xFC){
                state = reset;
                temp = 0x00;
		LCD_ClearScreen();
	        LCD_WriteData(temp + '0');
            }
            else{
                state = increment;
		i++;
		
            }
            break;

        case decrement:
	    if (i == 10){
            	if (temp > 0){
                    	temp--;
		        LCD_ClearScreen();
		        LCD_WriteData(temp + '0');
		}
		i = 0;
            }
            if ((PINA) == 0xFF){
                state = init;
            	if (temp > 0){
                    	temp--;
		        LCD_ClearScreen();
	        	LCD_WriteData(temp + '0');
		}
            }
            else if ((PINA) == 0xFC){
                state = reset;
                temp = 0x00;
		LCD_ClearScreen();
	        LCD_WriteData(temp + '0');
            }
            else{
                state = decrement;
		i++;
            }
            break;

        case reset:
            if (PINA == 0xFF){
                state = init;
            }
            else{
                state = reset;
            }
            break;
        
        default:
            state = start;
        break;
    }

}
int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0xFF;
    DDRC = 0xFF; PORTC = 0x00;
    DDRD = 0xFF; PORTD = 0x00;

    TimerSet(100);
    TimerOn();
    LCD_init();
    LCD_Cursor(1);

    state = start;
    while(1){
        tick();
	while(!TimerFlag){}
	TimerFlag = 0;
    }
    return 1;
}

