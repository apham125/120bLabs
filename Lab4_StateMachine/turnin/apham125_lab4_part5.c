/*	Author: Ashley Pham
 *  Partner(s) Name: 
 *	Lab Section:23
 *	Assignment: Lab 4  Exercise 4
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum state {start, locked, inputPress, inputRelease, unlocked} state;
unsigned char tempA;
unsigned char i;
unsigned char input[4];
unsigned char cntInput = 0;

//start(0), locked(1), inputPress(2), inputRelease(3), unlocked(4)
void tick(){
    switch (state){
        case start:
            PORTC = 0;
            state = locked;
            break;
        case locked:
            PORTC = 1;
            PORTB = 0;
            cntInput = 0;
            tempA = PINA & 0x07;
            input[0]=0;
            input[1]=0;
            input[2]=0;
            input[3]=0;

            if (tempA == 0){
                state = locked;
            }
            else{
                state = inputPress;
                input[cntInput]=tempA;
                cntInput++;
            }
            break;
        case inputPress:
            PORTC = 2;
            tempA = PINA & 0x07;

            if(tempA == 0){
                state = inputRelease;
            }
            else{
                state = inputPress;
            }
            break;
        case inputRelease:
            PORTC = 3;
            tempA = PINA & 0x07;            
                if (tempA == 0){
                    state = inputRelease;
                }
                else{                   
                    state = inputPress;
                    input[cntInput] = tempA;
                    cntInput++;

                    if (cntInput == 4){
                        if (input[0] == 0x04 && input[1] == 0x01 && input[2] == 0x02 && input[3] == 0x01){
                            state = unlocked;
                        }
                        else{
                            state = locked;
                        }
                    }


                }
            
            break;
        case unlocked:
            PORTC = 4;
            PORTB = 1;
            tempA = PINA & 0x80;
            if (tempA == 0x80){
                state = locked;
            }
            else{
                state = unlocked;
            }
            break;
    }
}
int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0xFF; PORTB = 0x00;
    DDRC = 0xFF; PORTC = 0x00;

    state = start;
    while(1){
        tick();
    }
    return 1;
}