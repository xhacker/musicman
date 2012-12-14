#include <iostream>
#include <Windows.h>
#include <MMSystem.h>
#include <string>
#include <conio.h>

#include "Sound.h"
#include "Play.h"
#include "Mute.h"


using namespace std;

int Sound(wchar_t* MidiFile, int argc, char** argv);

int main(int argc, char** argv) {
   
	wchar_t* MidiFile = L"C:\\Users\\Simone\\Downloads\\EspanjaPrelude.mid";

	cout<<Sound(MidiFile,argc,argv);


	_getch();
	return 0;
}