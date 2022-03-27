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
        DDRA = 0x00; PORTA = 0xFF; 
        DDRB = 0x00; PORTB = 0xFF; 
		DDRC = 0x00; PORTC = 0xFF;
		DDRD = 0xFF; PORTD = 0x00;

		unsigned char totalWeight;

		while(1){
			PORTD = 0x00;

			totalWeight = PINA + PINB + PINC;

			if (totalWeight > 0x8C){ 
				PORTD = PORTD | 0x01;
			}

			if (((PINA-PINC) > 0x50) || ((PINC-PINA) > 0x50)){
				PORTD = PORTD | 0x02;
			}

			if (totalWeight > 0x0F){
				totalWeight = (totalWeight >> 2) & 0xFC;
			}
			else {
				totalWeight = (totalWeight << 2) & 0xFC;
			}

			
			PORTD = PORTD | totalWeight;

		}

	return 1;
}


