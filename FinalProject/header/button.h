#ifndef _BUTTON_H_
#define _BUTTON_H_

int ButtonTick(int state){
	switch(state){
		case start2:
			state = buttonRelease;
			break;
		case buttonRelease:
			button1Click = 0;
			button2Click = 0;
			button3Click = 0;
			if ((~PINC & 0x0F) == 0x01){
				state = button1;
				button1Click = 1;
			}
			if ((~PINC & 0x0F) == 0x02){
				state = button2;
				button2Click = 1;
			}
			if ((~PINC & 0x0F) == 0x04){
				state = button3;
				button3Click = 1;
			}
			if ((~PINC & 0x0F) == 0x08){
				titleFlag = !titleFlag;
				state = button4;
			}
			else{
				state = buttonRelease;
			}
			break;
		case button1:
			if ((~PINC & 0x0F) == 0x00){
				state = buttonRelease;
			}
			else {
				state = button1;
			}
			break;
		case button2:
			if ((~PINC & 0x0F) == 0x00){
				state = buttonRelease;
			}
			else {
				state = button2;
			}
			break;
		case button3:
			if ((~PINC & 0x0F) == 0x00){
				state = buttonRelease;
			}
			else {
				state = button3;
			}
			break;
		case button4:
			if ((~PINC & 0x0F) == 0x00){
				state = buttonRelease;
			}
			else {
				state = button4;
			}
			break;
		default:
			state = start2;
			break;
	}	
	return state;
}

#endif
