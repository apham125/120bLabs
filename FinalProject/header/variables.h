#ifndef _VARIABLES_H_
#define _VARIABLES_H_

unsigned char CustomMusicNote1[8] = {0x04,0x06,0x05,0x04,0x04,0x0C,0x1C,0x18};
unsigned char CustomMusicNote2[8] = {0x01,0x03,0x05,0x09,0x0B,0x0B,0x18,0x18};
unsigned char CustomDot[8] = {0x00,0x04,0x0A,0x11,0x11,0x0A,0x04,0x00};
unsigned char CustomRightArrow[8]={0x18,0x14,0x12,0x11,0x11,0x12,0x14,0x18};
unsigned char CustomLeftArrow[8] ={0x03,0x05,0x09,0x11,0x11,0x09,0x05,0x03};

unsigned char titleFlag = 1;
unsigned char menuk = 0;
unsigned char k = 0;
unsigned char menuCnt = 0;
unsigned char titleMsg[59] = "               WELCOME TO BREADBOARD HERO!!                ";
unsigned char titleMsg2[14] = "PRESS START!!!"; 
unsigned char displayM[32];
enum TitleScreenSM{start, titleScreen, menu};

unsigned char button1Click = 0;
unsigned char button2Click = 0;
unsigned char button3Click = 0;
enum ButtonSM{start2, buttonRelease, button1, button2, button3, button4};

unsigned char i = 0;;
unsigned char ssMsg[32] = "      SONG         SELECTION!   ";
unsigned char songName1[5] = "beans";
unsigned char songName2[5] = "bindy";
unsigned char highScore[9] = "HI-SCORE:";
unsigned char score[6] = "SCORE:";
unsigned short songScore1 = 0000;
unsigned short songScore2 = 0000;
unsigned short ingameScore = 0000;
unsigned char songNum = 1;
unsigned char diff[10]="DIFFICULTY";
unsigned char normal[7]= " NORMAL";
unsigned char hard[5]= " HARD";
unsigned char hit[4]=" Hit";
unsigned char miss[4]="Miss";
unsigned char difficultyChosen = 0;
unsigned char curPos;
unsigned char gameStartFlag = 0;
enum SongSelectSM{start3, songText, songPick1, songPick2, difficultyPick};

unsigned char hitFlag = 0;
unsigned char perfectHit = 0;
unsigned char comboText[7] = "COMBO:";
unsigned char combo = 0;
enum ScoreSM{start4, gameStartText, gameStartNormal, gameStartHard, displayScore};

unsigned char loadingScreen[8] = {0x01, 0x03, 0x07, 0x0F, 0x1F, 0x3F, 0x7F, 0xFF};
unsigned char loadingi;
unsigned char row;
unsigned char columnCnt = 0;
unsigned char rowCnt = 0 ;
unsigned char normalCnt = 0;
enum LEDSM{start5, loadingLight,normalSong, hardSong, doneSong};

unsigned char songI = 0;
unsigned char songK = 0;
unsigned short song1Freq[52] = {
523.25, 466.16, 440, 466.16,440,349.23,261.63,261.63,293.66, 261.63,
293.66,329.63,349.23,523.25,523.25,523.25, 587.33, 523.25,587.33,659.25,
698.45,523.25,523.25,523.25,466.16,440,392,349.23,523.25,523.2,
523.25,523.25,349.23,0,349.23,0,349.23,0,349.230,0,
261.63,392,440,392,349.23,349.23,349.23,349.23,349.23,349.23,349.23,349.23
};

unsigned short song2Freq[52] = {
440,440, 349.23, 349.23, 261.63, 293.66, 349.23, 0, 349.23, 293.66, 261.63, 349.23,
0, 349.23, 523.25, 440, 440, 392.00, 392.00, 440,440, 349.23, 349.23, 261.63, //24
293.66, 349.23, 0, 349.23, 293.66, 261.63, 349.23, 466.16, 440,392, 349.23,349.23,349.23, //37
440,440, 349.23, 349.23, 261.63, 440,440, 349.23, 349.23, //46 
261.63,261.63,523.25,523.25,523.25,523.25,
};
enum MusicSM{start6,idle,playSong1,playSong2,done};

#endif
