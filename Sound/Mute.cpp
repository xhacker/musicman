/*
Stop/Pause MIDI file

TODO: close individual files
*/

#include <iostream>
#include <Windows.h>
#include <MMSystem.h>
#include<conio.h>
#include <string>
#include "Mute.h"


using namespace std;

void Pause(wstring MIDIFile){

	wstring s1 =L"close "+MIDIFile;
	const wchar_t* s2 (s1.c_str());
	mciSendString(s2, NULL, 0, NULL);

	return;
}