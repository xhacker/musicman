/*
//Function for calling Play and Pause functions
//Play function: plays midi file
//Pause function: stops file

//Sound takes in wstring MIDIFile. wstring must contain address of MIDI File to be played.
//Sound file will play individual note on queue if no file is specified.

//Example:

//wstring MidiFile = L"C:\\Users\\Simone\\Downloads\\EspanjaPrelude.mid";
//cout<<Sound(MidiFile,argc,argv);\

Or, to play mp3 files:

Input should be:


wstring MidiFile = L"C:\\Users\\Simone\\Downloads\\EspanjaPrelude.mp3";
Sound(MidiFile,argc,argv);

TODO:
Play two MIDI files at same time still doesn't work
*/

#pragma comment( lib, "winmm" )//library

#include <iostream>
#include <Windows.h>
#include <MMSystem.h>
#include <string>
#include <conio.h>

#include "Sound.h"
#include "Play.h"
#include "Mute.h"


using namespace std;

void Play(wstring MIDIFile);
void Pause(wstring MIDIFile);

int Sound(wstring MIDIFile, int argc, char** argv){
	//variables for midiOutOpen & midiOutShortMsg
	//TODO: add midiOutLongMsg
    int playing;     
    int MIDINote;      
    int flag;          
    HMIDIOUT device; 

	char playmidi;
	cin>>playmidi;

	//loop for playing specified midi file
	while(playmidi!='q'){
		if(playmidi=='p')//play
			Play(MIDIFile);

		else if(playmidi=='s')//stop
			Pause(MIDIFile);
		cin>>playmidi;
	}
 
	//default
	/*wchar_t* MIDIopen=L"open C:\\Users\\Simone\\Downloads\\EspanjaPrelude.mid type mpegvideo alias MediaFile";
    wchar_t* MIDIplay=L"play MediaFile";
    mciSendString(MIDIopen, NULL, 0, NULL);
    mciSendString(MIDIplay,NULL, 0, NULL);*/ 

	//midi file from loop must be closed for the following to function
	union { 
		unsigned long word; 
		unsigned char data[4]; 
	} message;

	//declare note value, volume, length, and empty  (88 possible)
	message.data[0] = 0x90;  
	message.data[1] = 60;   
	message.data[2] = 100;  
	message.data[3] = 0;   
		
	//input value from system (taken from main)
	//if main has no such value to offer, will not work
	if (argc < 2){
		MIDINote = 0;
		} 

	else {
		MIDINote = atoi(argv[1]);//converts string into integer
		}

	//open note file
	flag = midiOutOpen(&device, MIDINote, 0, 0, CALLBACK_NULL);
	if (flag != MMSYSERR_NOERROR) {
		printf("MIDI did not open.\n");
	}

	playmidi=' ';
	printf("q will exit the loop.\n");
	while (1) {        
		if (_kbhit()) { 
			playing = _getch();
			if (playing=='p') {
				message.data[2] = 60;
				cout<<"On"<<endl;
				flag = midiOutShortMsg(device, message.word);
			} 
			else if(playing=='s') {
				message.data[2] = 0; 
				cout<<"Off"<<endl;
				flag = midiOutShortMsg(device, message.word);
			}
			else{}//base case... todo


			if (flag != MMSYSERR_NOERROR) {
				printf("No sound file.");
			}
			if (playing == 'q') 
				break;
		}
	}
  
	midiOutReset(device);
	midiOutClose(device);//must close file after completion
	return 0;
}


/*
Note:

Main.cpp used for testing

#include <iostream>
#include <Windows.h>
#include <MMSystem.h>
#include <string>
#include <conio.h>

#include "Sound.h"
#include "Play.h"
#include "Mute.h"


using namespace std;

int Sound(wstring MidiFile, int argc, char** argv);

int main(int argc, char** argv) {
   
	wstring MidiFile = L"C:\\Users\\Simone\\Downloads\\EspanjaPrelude.mid";

	cout<<Sound(MidiFile,argc,argv);


	_getch();
	return 0;
}

*/