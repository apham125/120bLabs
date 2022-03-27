/*	Author: Ashley Pham
 *  Partner(s) Name: 
 *	Lab Section:23
 *	Assignment: Lab 4  Exercise 1
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
//#include "rims.h"
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum state {start, init, press1, release, press2} state;

void tick(){
    switch (state){
        case start:
            state = init;
            PORTB = 0x01;
            break;
        case init:
            if(!PINA){
                state = init;
                PORTB = 0x01;
            }
            else{
                state = press1;
                PORTB = 0x02;
            }
            break;
        case press1:
            if(PINA){
                state = press1;
                PORTB = 0x02;
            }
            else {
                state = release;
                PORTB = 0x01;
            }
            break;
        case release:
            if(!PINA){
                state = release;
                PORTB = 0x02;
            }
            else{
                state = press2;
                PORTB = 0x01;
            }
            break;
        case press2:
            if(PINA){
                state = press2;
                PORTB = 0x01;
            }
            else{
                state = init;
                PORTB = 0x01;
            }
            break;
    }
}
int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0xFF; PORTB = 0x00;

    state = start;
    while(1){
        tick();
    }
    return 1;
}