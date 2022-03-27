#ifndef _TITLE_SCREEN_H_
#define _TITLE_SCREEN_H_


int TitleScreenTick(int state){
	switch(state){
		case start:
			state = titleScreen;
			break;
		case titleScreen:
			if (titleFlag){
				for (i = 0; i <= 16; i++){
					LCD_Cursor(i);
					LCD_WriteData(titleMsg[menuCnt + i]);
				}
				menuCnt++;
				if(menuCnt == 43){
					menuCnt = 0;
				}
				
				if (menuk > 3){
					if(menuk == 4){
						for (i = 18; i < 32; i++){
							LCD_Cursor(i);
							LCD_WriteData(titleMsg2[i-18]);
						}
					}
					if (menuk >= 6){
						menuk = 0;
					}
				}
				else{
					for (i = 18; i <32; i++){
						LCD_Cursor(i);
						LCD_WriteData(' ');
					}
				}
				menuk++;
					LCD_Cursor(17);
					LCD_WriteData(0);
					LCD_Cursor(32);
					LCD_WriteData(1);
			
			}
			else{
				menuk = 0;
			}
			state = titleScreen;
		default:
			state = start;
			break;
	}

	return state;
}
#endif
