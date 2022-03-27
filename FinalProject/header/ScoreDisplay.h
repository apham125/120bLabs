#ifndef _SCORE_DISPLAY_H_
#define _SCORE_DISPLAY_H_


int ScoreTick(int state){
	switch(state){
		case start4:
			combo = 0;
			ingameScore = 0;
			if (gameStartFlag){
				state = gameStartText;
			}
			else{
				state = start4;
			}
			break;
		case gameStartText:
			if (titleFlag){
				gameStartFlag = 0;
				state = start4;
			}
			else{
				LCD_ClearScreen();
				for (i = 1; i < 7; i++){
					LCD_Cursor(i);
					LCD_WriteData(comboText[i-1]);
				}
				LCD_Cursor(7);
				LCD_WriteData(combo + '0');
				for (i = 17; i < 23; i++){
					LCD_Cursor(i);
					LCD_WriteData(score[i-17]);
				}
				LCD_Cursor(23);
				LCD_WriteData(ingameScore + '0');
				LCD_Cursor(0);
				if (difficultyChosen == 1){
					state = gameStartNormal;
				}
				else{
					state=gameStartHard;
				}
			}
			break;
		case gameStartNormal:
			if (titleFlag){
				gameStartFlag = 0;
				state = start4;
			}
			else{	
				if(rowCnt >= 105){
					if (songNum == 1){
						if (ingameScore > songScore1){
							songScore1 = ingameScore;
							eeprom_write_float(6,songScore1);
						}
					}
					else if (songNum ==2){
						if (ingameScore > songScore2){
							songScore2 = ingameScore;
							eeprom_write_float(7,songScore2);
						}
					}
					state = displayScore;
					for (i=13;i<17;i++){
						LCD_Cursor(i);
						LCD_WriteData(' ');
					}
				}
				else{
					if (normalCnt % 2 == 0){
						if (hitFlag == 1){
							if (perfectHit == 1){
								combo++;
								ingameScore+=150;
								for (i=13;i<17;i++){
									LCD_Cursor(i);
									LCD_WriteData(hit[i-13]);
								}
							}
							else{
								combo = 0;
								for (i=13;i<17;i++){
									LCD_Cursor(i);
									LCD_WriteData(miss[i-13]);
								}
							}
						}
						LCD_Cursor(7);
						if (combo < 10){
							LCD_WriteData(combo + '0');
							LCD_Cursor(8);
							LCD_WriteData(' ');
						}
						else{
							LCD_WriteData(combo/10 + '0');
							LCD_Cursor(8);
							LCD_WriteData(combo%10 + '0');
						}
						LCD_Cursor(23);
						if (ingameScore < 100){
							LCD_WriteData(ingameScore/10 + '0');
							LCD_Cursor(24);
							LCD_WriteData(ingameScore%10 + '0');
							LCD_Cursor(25);
							LCD_WriteData(' ');
						}
						else if (ingameScore < 1000){
							LCD_WriteData(ingameScore/100 + '0');
							LCD_Cursor(24);
							if (ingameScore % 100 == 0){
								LCD_WriteData(0 + '0');
								LCD_Cursor(25);
								LCD_WriteData(0 + '0');
							}
							else{
								LCD_WriteData((ingameScore%100)/10 + '0');
								LCD_Cursor(25);
								LCD_WriteData(0 + '0');
							}
						}
						else{
							LCD_WriteData(ingameScore/1000 + '0');
							LCD_Cursor(24);
							if ((ingameScore%1000) < 100){
								LCD_WriteData(0 + '0');
							}
							else{
								LCD_WriteData((ingameScore%1000)/100 + '0');
							}
							LCD_Cursor(25);
							if (ingameScore%100 == 0){
								LCD_WriteData(0 + '0');
							}
							else{
								LCD_WriteData(5 + '0');
							}
							LCD_Cursor(26);
							LCD_WriteData(0 + '0');
						}
						LCD_Cursor(0);
					}
					state = gameStartNormal;
				}
			}
			break;
		case gameStartHard:
			if (titleFlag){
				gameStartFlag = 0;
				state = start4;
			}
			else{	
				if(rowCnt >= 209){
					if (songNum == 1){
						if (ingameScore > songScore1){
							songScore1 = ingameScore;
							eeprom_write_float(6,songScore1);
						}
					}
					else if (songNum == 2){
						if (ingameScore > songScore2){
							songScore2 = ingameScore;
							eeprom_write_float(7,songScore2);
						}
					}
					state = displayScore;
					for (i=13;i<17;i++){
						LCD_Cursor(i);
						LCD_WriteData(' ');
					}
				}
				else{
					if (hitFlag == 1){
						if (perfectHit == 1){
							combo++;
							ingameScore+=150;
							for (i=13;i<17;i++){
								LCD_Cursor(i);
								LCD_WriteData(hit[i-13]);
							}
						}
						else{
							combo = 0;
							for (i=13;i<17;i++){
								LCD_Cursor(i);
								LCD_WriteData(miss[i-13]);
							}
						}
					}
					LCD_Cursor(7);
					if (combo < 10){
						LCD_WriteData(combo + '0');
						LCD_Cursor(8);
						LCD_WriteData(' ');
					}
					else{
						LCD_WriteData(combo/10 + '0');
						LCD_Cursor(8);
						LCD_WriteData(combo%10 + '0');
					}
					LCD_Cursor(23);
					if (ingameScore < 100){
						LCD_WriteData(ingameScore/10 + '0');
						LCD_Cursor(24);
						LCD_WriteData(ingameScore%10 + '0');
						LCD_Cursor(25);
						LCD_WriteData(' ');
					}
					else if (ingameScore < 1000){
						LCD_WriteData(ingameScore/100 + '0');
						LCD_Cursor(24);
						if (ingameScore % 100 == 0){
							LCD_WriteData(0 + '0');
							LCD_Cursor(25);
							LCD_WriteData(0 + '0');
						}
						else{
							LCD_WriteData((ingameScore%100)/10 + '0');
							LCD_Cursor(25);
							LCD_WriteData(0 + '0');
						}
					}
					else{
						LCD_WriteData(ingameScore/1000 + '0');
						LCD_Cursor(24);
						if ((ingameScore%1000) < 100){
							LCD_WriteData(0 + '0');
						}
						else{
							LCD_WriteData((ingameScore%1000)/100 + '0');
						}
						LCD_Cursor(25);
						if (ingameScore%100 == 0){
							LCD_WriteData(0 + '0');
						}
						else{
							LCD_WriteData(5 + '0');
						}
						LCD_Cursor(26);
						LCD_WriteData(0 + '0');
					}
					LCD_Cursor(0);
					state = gameStartHard;
				}
			}	
			break;
		case displayScore:
			if (titleFlag){
				gameStartFlag = 0;
				state = start4;
			}
			else{
				if (button3Click){
					gameStartFlag = 0;
					state = start4;
				}
				else{
					state = displayScore;
				}
			}
			break;
		default:
			state = start4;
			break;
	}
	return state;
}
#endif
