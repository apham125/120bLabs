/*	Author: Ashley Pham
 *  Partner(s) Name: 
 *	Lab Section:23
 *	Assignment: Lab 4  Exercise 2
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum state {start, init, increment, decrement, reset} state;

void tick(){
    switch (state){
        case start:
            state = init;
            PORTC = 7;
            break;
        case init:
            if (PINA == 1){
                state = increment;
                if (PORTC < 9){
                    PORTC++;
                }
            }
            else if (PINA == 2){
                state = decrement;
                if (PORTC > 0){
                    PORTC--;
                }
            }
            else if (PINA == 3){
                state = reset;
                PORTC = 0x00;
            }
            else{
                state = init;
            }
            break;

        case increment:
            if(PINA == 2){
                state = decrement;
                if (PORTC > 0){
                    PORTC--;
                }
            }
            else if (PINA == 3){
                state = reset;
                PORTC = 0x00;
            }
            else if (PINA == 0){
                state = init;
            }
        break;

        case decrement:
            if (PINA == 1){
                state = increment;
                if (PORTC < 9){
                    PORTC++;
                }
            }
            else if (PINA == 3){
                state = reset;
                PORTC = 0x00;
            }
            else if (PINA ==0){
                state = init;
            }
            
        break;
        case reset:
            if (PINA ==1){
                state = increment;
                if (PORTC < 9){
                    PORTC++;
                }
            }
            else if(PINA == 2){
                state = decrement;
                if (PORTC > 0){
                    PORTC--;
                }
            }
            else if (PINA == 0){
                state = init;
            }
        break;
    }
}
int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0xFF;
    DDRC = 0xFF; PORTC = 0x00;

    state = start;
    while(1){
        tick();
    }
    return 1;
}