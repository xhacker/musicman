/*
Open and Play MIDI file

TODO: Play multiple files at once
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
	// commands inside s1 must be input in order

	//additional commands may include: repeat (after file location)

	wstring s1 =L"open "+MusicFile+L" type mpegvideo alias MediaFile";//mpeg allows program to be play mp3
	const wchar_t* s2 (s1.c_str());
	mciSendString(s2, NULL, 0, NULL);

	wstring s3=L"play "+MusicFile;//after opening, use play command to start song
	const wchar_t* s4(s3.c_str());
	mciSendString(s4,NULL, 0, NULL);

	return;
}

void Resume(wstring MusicFile){

	//resume file from paused point

	wstring s3=L"resume "+MusicFile;//FILE MUST BE PAUSED BEFORE CALLING THIS FUNCTION
	const wchar_t* s4(s3.c_str());
	mciSendString(s4,NULL, 0, NULL);


	return;
}