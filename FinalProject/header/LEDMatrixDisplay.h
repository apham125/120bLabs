#ifndef _LED_MATRIX_DISPLAY_H_
#define _LED_MATRIX_DISPLAY_H_

int LEDTick(int state){
	switch (state){
		case start5:
			state = loadingLight;
			loadingi = 0;
			row = 0xFF;
			columnCnt = 0;
			rowCnt = 0;
			normalCnt = 0;
			break;
		case loadingLight:
			PORTD = ~row;
			shiftWrite(loadingScreen[loadingi]);
			loadingi++;
			if (loadingi >= 8){
				loadingi = 0;
			}

			if (gameStartFlag && !titleFlag){
				shiftWrite(0x00);
				if (difficultyChosen == 1){
					state = normalSong;
				}
				else {//if (curPos == 25){
					state = hardSong;
				}
			}
			else{
				state = loadingLight;
			}
			break;
		case normalSong:
			if (!titleFlag){
				if (normalCnt % 2 == 0){ 
					shiftWrite(Columns[columnCnt]);
					PORTD = ~(Rows[normalBeatMap[rowCnt]]);
					columnCnt++;
					rowCnt++;
					if (Columns[columnCnt-1] == 0b00000001){
						hitFlag = 1;
						if (Rows[normalBeatMap[rowCnt-1]] == 0b00001 && button3Click){
							perfectHit = 1;
						}
						else if (Rows[normalBeatMap[rowCnt-1]] == 0b00100 && button2Click){
							perfectHit = 1;
						}
						else if (Rows[normalBeatMap[rowCnt-1]] == 0b10000 && button1Click){
							perfectHit = 1;
						}
						else{
							perfectHit = 0;
						}
					}
					else{
						hitFlag = 0;
					}
				}
				normalCnt++;
				if (columnCnt == 8){
					columnCnt = 0;
				}
				if (rowCnt == 105){
					state = doneSong;
				}
				else{
					state = normalSong;
				}
			}
			else{
				state = start5;
			}	
			break;
		case hardSong:
			if (!titleFlag){ 
				shiftWrite(Columns[columnCnt]);
				PORTD = ~(Rows[hardBeatMap[rowCnt]]);
				columnCnt++;
				rowCnt++;
				if (Columns[columnCnt-1] == 0b00000001){
					hitFlag = 1;
					if (Rows[hardBeatMap[rowCnt-1]] == 0b00001 && button3Click){
						perfectHit = 1;
					}
					else if (Rows[hardBeatMap[rowCnt-1]] == 0b00100 && button2Click){
						perfectHit = 1;
					}
					else if (Rows[hardBeatMap[rowCnt-1]] == 0b10000 && button1Click){
						perfectHit = 1;
					}
					else{
						perfectHit = 0;
					}
				}
				else{
					hitFlag = 0;
				}
				normalCnt++;
				if (columnCnt == 8){
					columnCnt = 0;
				}
				if (rowCnt == 209){
					state = doneSong;
				}
				else{
					state = hardSong;
				}
			}
			else{
				state = start5;
			}	
			break;
		case doneSong:
			if (!titleFlag){
				if (!gameStartFlag){
					state = start5;
				}
				else{
					state = doneSong;
				}
			}
			else{
				state = start5;
			}
			break;
		default:
			state = start5;
			break;
	}
	return state;
}
#endif
