#ifndef _SONG_SELECTION_H_
#define _SONG_SELECTION_H_


int SongSelectTick(int state){
	switch(state){
		case start3:
			if (!titleFlag && !gameStartFlag){
				state = songText;
				k = 0;
				songNum = 1;
				curPos = 17;
				for (i = 1; i <=32; i++){
				 	LCD_Cursor(i);
					LCD_WriteData(ssMsg[i-1]);
				}
					LCD_Cursor(5); //Display Custom Note
					LCD_WriteData(0);
					LCD_Cursor(12);
					LCD_WriteData(0);

					LCD_Cursor(18); //Display Custom Note 2
					LCD_WriteData(1);
					LCD_Cursor(31);
					LCD_WriteData(1);
					LCD_Cursor(0);
			}	

			else{
				state = start3;
			}
			break;
		case songText: //Display "Song Selection" message for 1 second"
			if (titleFlag){
				state = start3;
			}
			if (k < 20){
				state = songText;
				k++;
			}
			else{
				state = songPick1;
				i = 0;
			}
			break;
		case songPick1:
			if (titleFlag){
				state = start3;
			}
			LCD_ClearScreen();
			if (songNum == 1){ //Display Song1
				LCD_Cursor(1);
				LCD_WriteData(1 + '0');
				LCD_Cursor(2);
				LCD_WriteData(0x2D); //'-'
				for (i = 3; i < 8; i++){ 
					LCD_Cursor(i);
					LCD_WriteData(songName1[i-3]);
				}
				for (i = 17; i < 26; i++){
					LCD_Cursor(i);
					LCD_WriteData(highScore[i-17]);
				}
				LCD_Cursor(26); //Displays HighScore1
				
				if (songScore1 < 100){
					LCD_WriteData(songScore1/10 + '0');
					LCD_Cursor(27);
					LCD_WriteData(songScore1%10 + '0');
					LCD_Cursor(28);
					LCD_WriteData(' ');
				}
				else if (songScore1 < 1000){
					LCD_WriteData(songScore1/100 + '0');
					LCD_Cursor(27);
					if (songScore1 % 100 == 0){
						LCD_WriteData(0 + '0');
						LCD_Cursor(28);
						LCD_WriteData(0 + '0');
					}
					else{
						LCD_WriteData((songScore1%100)/10 + '0');
						LCD_Cursor(28);
						LCD_WriteData(0 + '0');
					}
				}
				else{
					LCD_WriteData(songScore1/1000 + '0');
					LCD_Cursor(27);
					if ((songScore1%1000) < 100){
						LCD_WriteData(0 + '0');
					}
					else{
						LCD_WriteData((songScore1%1000)/100 + '0');
					}
					LCD_Cursor(28);
					if (songScore1%100 == 0){
						LCD_WriteData(0 + '0');
					}
					else{
						LCD_WriteData(5 + '0');
					}
					LCD_Cursor(29);
					LCD_WriteData(0 + '0');
				}

				LCD_Cursor(32);//Ouput Arrow
				LCD_WriteData(3);
				LCD_Cursor(0);
			}
			if (songNum == 2){ //Display Song2
				LCD_Cursor(1);
				LCD_WriteData(2 + '0');
				LCD_Cursor(2);
				LCD_WriteData(0x2D); //'-'
				for (i = 3; i < 8; i++){
					LCD_Cursor(i);
					LCD_WriteData(songName2[i-3]);
				}
				for (i = 17; i < 26; i++){
					LCD_Cursor(i);
					LCD_WriteData(highScore[i-17]);
				}
				LCD_Cursor(26);//Displays HighScore2

				if (songScore2 < 100){
					LCD_WriteData(songScore2/10 + '0');
					LCD_Cursor(27);
					LCD_WriteData(songScore2%10 + '0');
					LCD_Cursor(28);
					LCD_WriteData(' ');
				}
				else if (songScore2 < 1000){
					LCD_WriteData(songScore2/100 + '0');
					LCD_Cursor(27);
					if (songScore2 % 100 == 0){
						LCD_WriteData(0 + '0');
						LCD_Cursor(28);
						LCD_WriteData(0 + '0');
					}
					else{
						LCD_WriteData((songScore2%100)/10 + '0');
						LCD_Cursor(28);
						LCD_WriteData(0 + '0');
					}
				}
				else{
					LCD_WriteData(songScore2/1000 + '0');
					LCD_Cursor(27);
					if ((songScore2%1000) < 100){
						LCD_WriteData(0 + '0');
					}
					else{
						LCD_WriteData((songScore2%1000)/100 + '0');
					}
					LCD_Cursor(28);
					if (songScore2%100 == 0){
						LCD_WriteData(0 + '0');
					}
					else{
						LCD_WriteData(5 + '0');
					}
					LCD_Cursor(29);
					LCD_WriteData(0 + '0');
				}
				

				LCD_Cursor(32); //Output ARrow
				LCD_WriteData(4);
				LCD_Cursor(0);
			}				
			state = songPick2;
			break;
		case songPick2:
			if (titleFlag){
				state = start3;
			}
			else{
				if (button1Click){
					if (songNum == 2){
						songNum--;
					state = songPick1;
					}
				}
				else if (button2Click){
					if (songNum == 1){
						songNum++;
						state = songPick1;
					}
				}
				else if (button3Click){
					state = difficultyPick;

					LCD_ClearScreen(); //Print "Difficulty"
					for (i=1; i<11; i++){
						LCD_Cursor(i);
						LCD_WriteData(diff[i-1]);
					}	
					for (i=17; i<24; i++){ //Print "*Normal"
						LCD_Cursor(i);
						LCD_WriteData(normal[i-17]);
					}
					for (i=25; i<30; i++){ //Print "*Hard"
						LCD_Cursor(i);
						LCD_WriteData(hard[i-25]);
					}
					LCD_Cursor(17);
					LCD_WriteData(2);
					LCD_Cursor(25);
					LCD_WriteData(2);
				}
				else{
					state = songPick2;
				}
			}
			break;
		case difficultyPick:
			if (titleFlag){
				state = start3;
			}
			else{
				if (button1Click){
					if (curPos == 25){
						curPos = 17;
					}
				}
				else if(button2Click){
					if (curPos == 17){
						curPos = 25;
					}
				}
				else if (button3Click){
					if (curPos == 17){
						difficultyChosen = 1;
						
					}
					else{
						difficultyChosen = 2;
					}
					gameStartFlag = 1;
					state = start3;
				}
				else{
					LCD_Cursor(curPos);
					state = difficultyPick;
				}
			}				
			break;
		default:
			state = start3;
			break;
	}
	return state;
}
#endif
