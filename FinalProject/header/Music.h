#ifndef _MUSIC_H_
#define _MUSIC_H_

int MusicTick(int state){
	switch (state){
		case start6:
			set_PWM(0);
			state = idle;
			break;
		case idle:
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
				if (songI % 2 == 0){
					set_PWM(song1Freq[songK]);
					songK++;
					if (songK == 30){
						state = done;
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
				if (songI % 2 == 0){
					set_PWM(song1Freq[songK]);
					songK++;
					if (songK == 30){
						state = done;
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
				songI = 0;
				songK = 0;
			}
			break;
		default:
			state = start6;
			break;
	}
	return state;
}
#endif
