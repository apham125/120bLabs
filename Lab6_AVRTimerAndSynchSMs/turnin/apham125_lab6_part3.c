/*	Author: Ashley Pham
 *  Partner(s) Name: 
 *	Lab Section:23
 *	Assignment: Lab 6  Exercise 3
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 *	Demo Link: https://drive.google.com/file/d/112z_kpHRB4TlyktrBpit8jYBKQcNDBfA/view?usp=sharing
 */
#include <avr/io.h>
#include <avr/interrupt.h>
#ifdef _SIMULATE_
#include "timer.h"
#include "simAVRHeader.h"
#endif

unsigned char i;
enum state {start, init, increment, decrement, reset} state;

void tick(){
    switch (state){
        case start:
            PORTB = 7;
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
                PORTB = 0x00;
            }
            else { 
                state = init;
            }
        break;

        case increment:
	    if (i == 10){
		    if (PORTB < 9){
		            PORTB++;
		    }
		    i = 0;
	    }

            if ((PINA) == 0xFF){
                state = init;
            	if (PORTB < 9){
                    	PORTB++;
		}
            }
            else if ((PINA) == 0xFC){
                state = reset;
                PORTB = 0x00;
            }
            else{
                state = increment;
		i++;
		
            }
            break;

        case decrement:
	    if (i == 10){
            	if (PORTB > 0){
                    	PORTB--;
		}
		i = 0;
            }
            if ((PINA) == 0xFF){
                state = init;
            	if (PORTB > 0){
                    	PORTB--;
		}
            }
            else if ((PINA) == 0xFC){
                state = reset;
                PORTB = 0x00;
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
    DDRB = 0xFF; PORTB = 0x00;

    TimerSet(100);
    TimerOn();
	
    state = start;
    while(1){
        tick();
	while(!TimerFlag){}
	TimerFlag = 0;
    }
    return 1;
}

