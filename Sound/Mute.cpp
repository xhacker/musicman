/*
Stop/Pause/Mute MIDI file
*/

#include <iostream>
#include <Windows.h>
#include <MMSystem.h>
#include <conio.h>
#include <string>
#include "Mute.h"


using namespace std;

void Stop(wstring MusicFile){

	wstring music1 =L"close "+MusicFile;//close file to stop it from playing
	const wchar_t* music2 (music1.c_str());
	mciSendString(music2, NULL, 0, NULL);

	return;
}

void Pause(wstring MusicFile){

	wstring music1 =L"pause "+MusicFile;//temporarily pause file, it may be resumed.
	const wchar_t* music2 (music1.c_str());
	mciSendString(music2, NULL, 0, NULL);

	return;
}

void Mute(){

	waveOutSetVolume(0x0000,0x0000);//Will end all audio output

	return;
}

void UnMute(){
	waveOutSetVolume(0x0000,0xFFFF);//Will allow all audio output again at max
	return;
}