/*
Stop/Pause MIDI file

TODO: close individual files
*/

#include <iostream>
#include <Windows.h>
#include <MMSystem.h>
#include <conio.h>
#include <string>
#include "Mute.h"


using namespace std;

void Stop(wstring MusicFile){

	wstring s1 =L"close "+MusicFile;//close file to stop it from playing
	const wchar_t* s2 (s1.c_str());
	mciSendString(s2, NULL, 0, NULL);

	return;
}

void Pause(wstring MusicFile){

	wstring s1 =L"pause "+MusicFile;//temporarily pause file, it may be resumed.
	const wchar_t* s2 (s1.c_str());
	mciSendString(s2, NULL, 0, NULL);

	return;
}