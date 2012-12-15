/*
//Function for calling Play and Pause functions
//Play function: plays midi file
//Pause function: stops file

//Sound takes in wstring MusicFile. wstring must contain address of MIDI File to be played.
//Sound file will play individual note on queue if no file is specified.

//Example:

//wstring MusicFile = L"C:\\Users\\Simone\\Downloads\\EspanjaPrelude.mid";
//cout<<Sound(MusicFile,argc,argv);

NOTE:
1. Can play mp3 and MIDI at the same time, but MIDI is very quiet, can barely hear it if mp3 is a loud song
2. Can play two mp3 files at the same time, individual controls based on the files name.
3. There is no volume control, but both songs can be heard clearly.
4. mciSendString DOES NOT LIKE SPACES. using them without quotes will cause the program to CRASH
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

//Start and stop playing a music file
void Play(wstring MusicFile);
void Stop(wstring MusicFile);

//Pause and resume file from pause point
void Pause(wstring MusicFile);
void Resume(wstring MusicFile);

//Volume Control in Play.cpp
void VolumeSet(wstring MusicFile, wstring MusicFile2);//set so that volume may be changed independently 
void Volume(wstring MusicFile, int vlevel);//choose volume level (goes to 1000)

//Mute the music file
void Mute();
void UnMute();


int Sound(wstring MusicFile, wstring MusicFile2, int argc, char** argv){
	//two different MusicFiles may be called to play two different songs.

	//variables for midiOutOpen & midiOutShortMsg
	//TODO: add midiOutLongMsg
    int Playing=0; 
	int SecondFile=0;
    int MIDINote;      
    int Flag;          
    HMIDIOUT Device; 
	char PlayMusic;
	
	//volume control
	int vlevel;
	bool volumechange=0;

	PlayMusic=_getch();


	//How to call mp3 files:
	//loop for Playing specified music file
	while(PlayMusic!='q'){

		if(PlayMusic=='p')//play
			Play(MusicFile);

		else if(PlayMusic=='n')//stop Playing song
			Stop(MusicFile);

		else if(PlayMusic=='s'){//pause the song
			Pause(MusicFile);
			Playing=1;//pause flag triggered
		}
		else if(PlayMusic=='r'&&Playing==1){
			Resume(MusicFile);
			Playing=0;//no longer paused
		}
		else if(PlayMusic=='m'){
			Mute();
		}
		else if(PlayMusic=='u'){
			UnMute();
		}

		//Controls for the second song
		else if(PlayMusic=='2'){//Play a second mp3 file
			Play(MusicFile2);
		}
		else if(PlayMusic=='3'){//Play a second mp3 file
			Stop(MusicFile2);
		}
		else if(PlayMusic=='4'){//Play a second mp3 file
			Pause(MusicFile2);
			SecondFile=1;
		}
		else if(PlayMusic=='5'&&SecondFile==1){//Play a second mp3 file
			Resume(MusicFile2);
			SecondFile=0;
		}

		else if(PlayMusic=='c'){//Music File 1 volume control
			VolumeSet(MusicFile, MusicFile2);
			volumechange = 1;
		}


		else if(PlayMusic=='v'&&volumechange==1){//Music File 1 volume control
			cout<<"Please enter the volume level you would like to use: From 0 to 5"<<endl;
			cin>>vlevel;//vlevel must be changed to wstring
			cout<<endl;
			Volume(MusicFile, vlevel);
		}

		else if(PlayMusic=='6'&&volumechange==1){//Music File 2 volume Control
			cout<<"Please enter the volume level you would like to use: From 0 to 5"<<endl;
			vlevel=_getch();
			cout<<endl;
			Volume(MusicFile, vlevel);
			
		}

		PlayMusic=_getch();
	}
 
	//default

	/*wchar_t* MIDIopen=L"open C:\\Users\\Simone\\Downloads\\EspanjaPrelude.mid type mpegvideo alias MediaFile";
    wchar_t* MIDIplay=L"play MediaFile";
    mciSendString(MIDIopen, NULL, 0, NULL);
    mciSendString(MIDIplay,NULL, 0, NULL);*/ 


	//Example of how to play MIDI files while mp3 is playing:

	//if a midi file is playing in the loop instead of an mp3, it must be closed for the following to function
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
	Flag = midiOutOpen(&Device, MIDINote, 0, 0, CALLBACK_NULL);
	if (Flag != MMSYSERR_NOERROR) {
		printf("MIDI did not open.\n");//If a different MIDI file is playing that cannot be closed
	}

	PlayMusic=' ';
	printf("q will exit the loop.\n");
	while (1) {        
		if (_kbhit()) { 
			Playing = _getch();
			if (Playing=='p') {
				message.data[2] = 100;
				cout<<"On"<<endl;
				Flag = midiOutShortMsg(Device, message.word);
			} 
			else if(Playing=='s') {
				message.data[2] = 0; 
				cout<<"Off"<<endl;
				Flag = midiOutShortMsg(Device, message.word);
			}
			else{}//base case... todo


			if (Flag != MMSYSERR_NOERROR) {
				printf("No sound file.");
			}
			if (Playing == 'q') 
				break;
		}
	}
  
	midiOutReset(Device);
	midiOutClose(Device);//must close file after completion
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

int Sound(wstring MusicFile, wstring MusicFile2, int argc, char** argv);

int main(int argc, char** argv) {
   
	wstring MusicFile = L"C:\\Users\\Simone\\Music\\Downloads\\mulan.mp3";
	wstring MusicFile2 = L"C:\\Users\\Simone\\Music\\Downloads\\moon.mp3";

	cout<<Sound(MusicFile, MusicFile2, argc, argv);


	_getch();
	return 0;
}

*/