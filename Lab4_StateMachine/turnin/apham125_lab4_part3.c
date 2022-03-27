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

enum state {start, locked, hashPress, hashRelease, yPress, unlocked, wrongPress} state;
unsigned char tempA;

//start(0), init(1), hashPress(2), hashRelease(3), yPress(4), unlocked(5), wrongPress(6)
void tick(){
    switch(state){
        case start:
            state = locked;
            break;
        case locked:
            PORTC = 1;
            PORTB = 0;
            tempA = PINA & 0x07;
            if(tempA == 0x04){ //100
                state = hashPress;
            }
            else if(tempA == 0){
                state = locked;
            }
            else {
                state = wrongPress;
            }
            break;
        case hashPress:
            PORTC = 2;
            tempA = PINA & 0x07;
            if (tempA == 0x04){
                state = hashPress;
            }
            else if (tempA==0){
                state = hashRelease;
            }
            else{
                state = wrongPress;
            }
            break;
        case hashRelease:
            PORTC = 3;
            tempA = PINA & 0x07;
            if(tempA == 0){
                state = hashRelease;
            }
            else if(tempA == 0x02){ //010
                state = yPress;
            }
            else{
                state = wrongPress;
            }
            break;
        case yPress:
            PORTC = 5;
            tempA = PINA & 0x07;
            if (tempA == 0x02){
                state = yPress;
            }
            else if (tempA == 0x00){
                state = unlocked;
            }
            else{
                state = wrongPress;
            }
            break;
        case unlocked:
            PORTC = 5;
            PORTB = 0x01;
            tempA = PINA & 0x80;
            if (tempA == 0x80){
                state = locked;
            }
            else{
                state = unlocked;
            }
            break;
        case wrongPress:
            PORTC = 6;
            tempA = PINA & 0x07;
            if (tempA == 0){
                state = locked;
            }
            else {
                state = wrongPress;
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