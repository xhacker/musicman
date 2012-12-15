/*
Open and Play MIDI file
Change volume settings

TODO: Delay to play song is long
*/

#include <iostream>
#include <Windows.h>
#include <MMSystem.h>
#include<conio.h>
#include <string>
#include "Play.h"


using namespace std;

void Play(wstring MusicFile){

	//input for mciSendString MUST be wstring in order to convert to wchat_t*
	//Failure for such WILL cause the program to break
	// commands inside music1 must be input in order

	//additional commands may include: repeat (after file location)

	wstring music1 =L"open "+MusicFile+L" type mpegvideo alias MediaFile";//mpeg allows program to be play mp3 and change settings
	const wchar_t* music2 (music1.c_str());
	mciSendString(music2, NULL, 0, NULL);

	wstring music3=L"play "+MusicFile;//after opening, use play command to start song
	const wchar_t* music4(music3.c_str());
	mciSendString(music4,NULL, 0, NULL);

	return;
}

void Resume(wstring MusicFile){

	//resume file from paused point

	wstring music1=L"resume "+MusicFile;//FILE MUST BE PAUSED BEFORE CALLING THIS FUNCTION
	const wchar_t* music2(music1.c_str());
	mciSendString(music2,NULL, 0, NULL);

	return;
}

void VolumeSet(const wstring MusicFile, const wstring MusicFile2){

	wstring music1=L"status "+MusicFile+L" volume";//set volume level of first mp3 file
	const wchar_t* music2(music1.c_str());
	mciSendString(music2,NULL,255,0);

	wstring music3=L"status "+MusicFile2+L" volume";//set volume of second mp3 file
	const wchar_t* music4(music3.c_str());
	mciSendString(music4,NULL,255,0);
}



void Volume(wstring MusicFile, const int vlevel){
	string music1;
	
	switch(vlevel){
		case 0:{
			waveOutSetVolume(0x0000,0x0000);
			break;
			   }
		case 1:{
			waveOutSetVolume(0x0000,2000);
			break;
			   }
		case 2:{
			waveOutSetVolume(0x0000,3000);
			break;
			   }
		case 3:{
			waveOutSetVolume(0x0000,4000);
			break;
			   }
		case 4:{
			waveOutSetVolume(0x0000,5000);
			break;
			   }
		case 5:{
			waveOutSetVolume(0x0000,0xFFFF);
			break;
			   }
		default:{
			waveOutSetVolume(0x0000,0xFFFF);
			break;
				}
	}
}
