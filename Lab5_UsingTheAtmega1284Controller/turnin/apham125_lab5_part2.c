/*	Author: Ashley Pham
 *  Partner(s) Name: 
 *	Lab Section:23
 *	Assignment: Lab 5  Exercise 2
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum state{start, init, increment, decrement, reset} state;

void tick(){
    switch (state){
        case start:
            PORTC = 7;
            state = init;
        break;

        case init:
            if (PINA== 0xFE){
                state = increment;
                if (PORTC < 9){
                    PORTC++;
                }
            }
            else if ((PINA) == 0xFD){
                if (PORTC > 0){
                    PORTC--;
                }
                state = decrement;

            }
            else if ((PINA) == 0xFC){
                state = reset;
                PORTC = 0x00;
            }
            else { 
                state = init;
            }
        break;

        case increment:
            if ((PINA) == 0xFF){
                state = init;
            }
            else if ((PINA) == 0xFC){
                state = reset;
                PORTC = 0x00;
            }
            else{
                state = increment;
            }
            break;

        case decrement:
            if ((PINA) == 0xFF){
                state = init;
            }
            else if ((PINA) == 0xFC){
                state = reset;
                PORTC = 0x00;
            }
            else{
                state = decrement;
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
int main(){
    DDRA = 0x00; PORTA = 0xFF;
    DDRC = 0xFF; PORTC = 0x00;

    state = start;
    while(1){
        tick();
    }
    return 1;
}