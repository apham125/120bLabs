#ifndef SHIFT_H
#define SHIFT_H

#include <avr/io.h>
//#include <util/delay.h>
#define PORT   PORTD
#define DDR    DDRD
#define DS_POS PD5      //Data pin (DS) pin location
#define SH_CP_POS PD6      //Shift Clock (SH_CP) pin location
#define ST_CP_POS PD7      //Store Clock (ST_CP) pin location

void shiftInit(){
   DDR |= (( 1 << SH_CP_POS) | (1 << ST_CP_POS) | (1 << DS_POS));
}

#define DataHigh() (PORT|=(1<<DS_POS))
#define DataLow() (PORT&=(~(1<<DS_POS)))

void shiftPulse(){
   PORT |=(1<<SH_CP_POS);//HIGH
   PORT &=(~(1<<SH_CP_POS));//LOW
}
void shiftLatch(){
   PORT |= (1<<ST_CP_POS);//HIGH
   _delay_loop_1(1);
   PORT &= (~(1<<ST_CP_POS));//LOW
   _delay_loop_1(1);
}
void shiftWrite(unsigned char data){
   for(unsigned char i=0; i<8; i++){
      if(data & 0b10000000){
         DataHigh();
      }
      else{
         DataLow();
      }
      shiftPulse();  //Pulse the Clock line
      data = data<<1;  //Now bring next bit at MSB position
   }
   shiftLatch();
}
void wait(){
   for(unsigned char i=0; i<50; i++){
      _delay_loop_2(0);
   }
}

#endif
