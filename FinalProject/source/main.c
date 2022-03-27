/*	Author: Ashley Pham
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Final Project Demo 2
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 *	
 *	I used https://www.electronicwings.com/avr-atmega/lcd-custom-character-display-using-atmega-16-32- 
 *		https://embedds.com/interfacing-shift-register-with-avr/
 *		as a reference
 * 	For this demo, I installed the led matrix with a shift register and created a beatmap for one song and added a combo and score counter.
 *	Demo Link: https://drive.google.com/file/d/118g5zl80c4tX_8tITvpPc-mhhgVNgqEL/view?usp=sharing
 */
#include <avr/io.h>
#include <scheduler.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>
#include <util/delay.h>
#ifdef _SIMULATE_
#include <timer.h>
#include "simAVRHeader.h"

#include "shift.h"
#include "variables.h"
#include "beatmap.h"
/*#include "titleScreen.h"
#include "button.h"
#include "SongSelection.h"
#include "ScoreDisplay.h"
#include "LEDMatrixDisplay.h"
#include "Music.h"*/
#include "PWM.h"
#endif
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
int MusicTick(int state){
	switch (state){
		case start6:
			set_PWM(0);
			state = idle;
			break;
		case idle:
				songI = 0;
				songK = 0;
			if (gameStartFlag){
				if (songNum == 1){
					state = playSong1;
				}
				else{
					state = playSong2;
				}
			}
			else{
				state = idle;
			}
			break;
		case playSong1:
			if (!titleFlag){
				songI++;
				if (songI % 4 == 0){
					set_PWM(song1Freq[songK]);
					songK++;
					if (songK == 52){
						state = done;
						set_PWM(0);
					}
					else{
						state = playSong1;
					}
				}
				else{
					state = playSong1;
				}
			}
			else{
				state = start6;
			}
			break;
		case playSong2:
			if (!titleFlag){
				songI++;
				if (songI % 4 == 0){
					set_PWM(song2Freq[songK]);
					songK++;
					if (songK == 52){
						state = done;
						set_PWM(0);
					}
					else{
						state = playSong2;
					}
				}
				else{
					state = playSong2;
				}
			}
			else{
				state = start6;
			}
			break;
		case done:
			if (titleFlag){
				state = start6;
			}
			state = done;
			if (!gameStartFlag){
				state = start6;
			}
			break;
		default:
			state = start6;
			break;
	}
	return state;
}

int main(void) {
	DDRA = 0xFF; PORTA = 0x00;
	DDRB = 0xFF; PORTB = 0x00;
	DDRC = 0xF0; PORTC = 0x0F;
	DDRD = 0xFF; PORTD = 0x00;

	static task task1, task2, task3, task4, task5, task6;
	task *tasks[] = {&task1, &task2,&task3, &task4, &task5, &task6};
	const unsigned short numTasks = sizeof(tasks)/sizeof(task*);

	const char start = -1;
	songScore1 = eeprom_read_float((float*)6);
	songScore2 = eeprom_read_float((float*)7);

	//TitleScreen
	task1.state = start;
	task1.period = 200;
	task1.elapsedTime = task1.period;
	task1.TickFct = &TitleScreenTick;

	//Button
	task2.state = start2;
	task2.period = 50;
	task2.elapsedTime = task1.period;
	task2.TickFct = &ButtonTick;

	//Song Selection 
	task3.state = start3;
	task3.period = 50;
	task3.elapsedTime = task1.period;
	task3.TickFct = &SongSelectTick;
	
	//Score Display
	task4.state = start4;
	task4.period = 100;
	task4.elapsedTime = task1.period;
	task4.TickFct = &ScoreTick;

	//LED Matrix Display
	task5.state = start5;
	task5.period = 100;
	task5.elapsedTime = task5.period;
	task5.TickFct = &LEDTick;

	//Music
	task6.state = start6;
	task6.period = 100;
	task6.elapsedTime = task6.period;
	task6.TickFct = &MusicTick;

	TimerSet(50);
	TimerOn();

	LCD_Custom_Char(0, CustomMusicNote1);
	LCD_Custom_Char(1, CustomMusicNote2);
	LCD_Custom_Char(2, CustomDot);
	LCD_Custom_Char(3, CustomRightArrow);
	LCD_Custom_Char(4, CustomLeftArrow);

	LCD_init();
	shiftInit();
	PWM_on();

	unsigned short i;
    	while (1) {
		for ( i = 0; i <numTasks; i++){
			if (tasks[i]->elapsedTime >= tasks[i]->period){
				tasks[i]->state = tasks[i]->TickFct(tasks[i]->state);
				tasks[i]->elapsedTime = 0;
			}
			tasks[i]->elapsedTime += 50;
		}
		while(!TimerFlag);
		TimerFlag = 0;
    }
    return 1;
}
