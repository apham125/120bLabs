/*	Author: Ashley Pham
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Final Project Demo 1
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 *	
 *	I used https://www.electronicwings.com/avr-atmega/lcd-custom-character-display-using-atmega-16-32- as a reference
 * 	For this demo, I created the menu I will use to navigate through songs and difficulty selection and implemented custom characters.
 *	Demo Link: https://drive.google.com/file/d/1371Pp8gQtxMftL4qZOR3Cy3TNaJsfC7J/view?usp=sharing
 */
#include <avr/io.h>
#include <scheduler.h>
#include <avr/interrupt.h>
#ifdef _SIMULATE_
#include <timer.h>
#include "simAVRHeader.h"
#endif

unsigned char CustomMusicNote1[8] = {0x04,0x06,0x05,0x04,0x04,0x0C,0x1C,0x18};
unsigned char CustomMusicNote2[8] = {0x01,0x03,0x05,0x09,0x0B,0x0B,0x18,0x18};
unsigned char CustomDot[8] = {0x00,0x04,0x0A,0x11,0x11,0x0A,0x04,0x00};
unsigned char CustomRightArrow[8]={0x18,0x14,0x12,0x11,0x11,0x12,0x14,0x18};
unsigned char CustomLeftArrow[8] ={0x03,0x05,0x09,0x11,0x11,0x09,0x05,0x03};

unsigned char titleFlag = 1;
unsigned char menui;
unsigned char k;
unsigned char menuCnt;
unsigned char titleMsg[59] = "               WELCOME TO BREADBOARD HERO!!                ";
unsigned char titleMsg2[16] = " PRESS START!!! "; 
unsigned char displayM[32];
enum TitleScreenSM{start, titleScreen, menu};

unsigned char button1Click = 0;
unsigned char button2Click = 0;
unsigned char button3Click = 0;
enum ButtonSM{start2, buttonRelease, button1, button2, button3, button4};

unsigned char i;
unsigned char ssMsg[32] = "      SONG         SELECTION!   ";
unsigned char songName1[5] = "Song1";
unsigned char songName2[5] = "Song2";
unsigned char highScore[9] = "HI-SCORE:";
unsigned char score[6] = "SCORE:";
unsigned char songScore1 = 0000;
unsigned char songScore2 = 0000;
unsigned char songNum = 1;
unsigned char diff[10]="DIFFICULTY";
unsigned char normal[7]= " NORMAL";
unsigned char hard[5]= " HARD";
unsigned char curPos;
unsigned char gameStartFlag = 0;
enum SongSelectSM{start3, songText, songPick1, songPick2, difficultyPick};

unsigned char comboText[7] = "COMBO:";
unsigned char fullCombo[32] = "      FULL          COMBO!!!    ";
unsigned char combo = 0;
enum ScoreSM{start4, gameStartText, gameStart};

int TitleScreenTick(int state){
	switch(state){
		case start:
			state = titleScreen;
			break;
		case titleScreen:
			if (titleFlag){
				for (menui = 0; menui <16; menui++){
					displayM[menui] = titleMsg[menuCnt + menui];
				}
				menuCnt++;
				if (menuCnt == 43){
					menuCnt = 0;
				}
				if ( k % 3 == 0){
					for (menui = 16; menui <32; menui++){
						displayM[menui] = titleMsg2[menui - 16];
					}	

				}
				else{
					for (menui = 16; menui <32; menui++){
						displayM[menui] = ' ';
					}
				}
				k++;
				LCD_DisplayString(1, displayM);
					LCD_Cursor(17);
					LCD_WriteData(0);
					LCD_Cursor(32);
					LCD_WriteData(1);
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
				LCD_Cursor(26);
				LCD_WriteData(songScore1 + '0');
				LCD_Cursor(32);
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
				LCD_Cursor(26);
				LCD_WriteData(songScore2 + '0');
				LCD_Cursor(32);
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
			if (titleFlag || gameStartFlag){
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
					gameStartFlag = 1;
				}
				LCD_Cursor(curPos);
				state = difficultyPick;
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
				LCD_WriteData(songScore1 + '0');
				LCD_Cursor(0);
				state = gameStart;
			}
			break;
		case gameStart:
			if (titleFlag){
				gameStartFlag = 0;
				state = start4;
			}
			else{
				state = gameStart;
			}
			break;
		default:
			state = start4;
			break;
	}
	return state;
}
int main(void) {
	DDRA = 0xFF; PORTA = 0x00;
	DDRC = 0xF0; PORTC = 0x0F;


	static task task1, task2,task3,task4;
	task *tasks[] = {&task1, &task2,&task3, &task4};
	const unsigned short numTasks = sizeof(tasks)/sizeof(task*);

	const char start = -1;

	//TitleScreen
	task1.state = start;
	task1.period = 200;
	task1.elapsedTime = task1.period;
	task1.TickFct = &TitleScreenTick;

	//Button
	task2.state = start;
	task2.period = 50;
	task2.elapsedTime = task1.period;
	task2.TickFct = &ButtonTick;

	//Song Selection 
	task3.state = start;
	task3.period = 50;
	task3.elapsedTime = task1.period;
	task3.TickFct = &SongSelectTick;
	
	//Score Display
	task4.state = start;
	task4.period = 50;
	task4.elapsedTime = task1.period;
	task4.TickFct = &ScoreTick;

	TimerSet(50);
	TimerOn();

	LCD_init();
	LCD_Custom_Char(0, CustomMusicNote1);
	LCD_Custom_Char(1, CustomMusicNote2);
	LCD_Custom_Char(2, CustomDot);
	LCD_Custom_Char(3, CustomRightArrow);
	LCD_Custom_Char(4, CustomLeftArrow);
;
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
