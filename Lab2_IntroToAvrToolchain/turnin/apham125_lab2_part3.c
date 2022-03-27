/*      Author: Ashley Pham
 *  Partner(s) Name: none
 *      Lab Section:23
 *      Assignment: Lab 2  Exercise #3
 *      Exercise Description: [optional - include for your own benefit]
 *
 *      I acknowledge all content contained herein, excluding template or example
 *      code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

int main(void) {
        DDRA = 0x00; PORTA = 0xFF; // Configure port A's 8 pins as inputs
        DDRB = 0xFF; PORTB = 0x00; // Configure port B's 8 pins as outputs, initialize to 0s

		unsigned char i;
		unsigned char cntavail;

		while (1){
			cntavail = 0;

			for (i=0; i <4; i++){
				if ((PINA &(0x01 << i)) ==0)
				cntavail++;
			}

			PORTC = cntavail;

            if (cntavail == 0){
                PORTC = (0x00 & PORTC) | 0x80;
            }
		}
        return 1;
}

//zybooks example 2.7.1: parking lot
