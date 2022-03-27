/*      Author: Ashley Pham
 *  Partner(s) Name: none
 *      Lab Section:23
 *      Assignment: Lab 2  Exercise #1
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

        unsigned char tempA = 0x00;
        unsigned char tempB = 0x00; 
		unsigned char tempC = 0x00;
while(1) {
              tempA = PINA & 0x01; //Reads PA0
	      	  tempB = PINA & 0x02; //Reads PA1

	      if (tempA == 0x01 && tempB == 0x00){ //light only turns on if PA0 == 1 and PA1 == 0
			tempC = (tempC & 0xFC) | 0x01;  //light on
	      }
	      else {
	      		tempC = ( tempC & 0xFC) | 0x00; //light off
	      }

	      PORTB = tempC;
        }
        return 1;
}

