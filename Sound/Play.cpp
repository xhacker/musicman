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

void Play(wstring MIDIFile){

	wstring s1 =L"open "+MIDIFile+L" type mpegvideo alias MediaFile";
	const wchar_t* s2 (s1.c_str());
	mciSendString(s2, NULL, 0, NULL);

	wstring s3=L"play "+MIDIFile;
	const wchar_t* s4(s3.c_str());
	mciSendString(s4,NULL, 0, NULL);

	return;
}