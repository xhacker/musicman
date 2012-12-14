#pragma comment( lib, "winmm" )

#include <iostream>
#include <Windows.h>
#include <MMSystem.h>
#include <string>
#include <conio.h>

#include "Sound.h"
#include "Play.h"
#include "Mute.h"


using namespace std;

void Play(wchar_t* MIDIFile);

int Sound(string MIDIFile, int argc, char** argv){

    int playing;     
    int MIDINote;      
    int flag;          
    HMIDIOUT device;    
	
	//const basic_string <wchar_t> s1 ( MIDIFile);
	//wstring s2 ( L"open "+  s1 + L" type mpegvieo alias MediaFile"); 
	

	/*string s1 ("open " + MIDIFile + " type mpegvideo alias MediaFile"));
	const wchar_t* s2 (s1.c_str());*/

	wchar_t* MIDIopen=L"open C:\\Users\\Simone\\Downloads\\EspanjaPrelude.mid type mpegvideo alias MediaFile";
    wchar_t* MIDIplay=L"play MediaFile";
    mciSendString(MIDIopen, NULL, 0, NULL);
    mciSendString(MIDIplay,NULL, 0, NULL); 

	//mciSendString(L"play C:\\Users\\Simone\\Downloads\\EspanjaPrelude.mid",NULL,0,NULL);

	string path = "play C:\\Users\\Simone\\Downloads\\EspanjaPrelude.mid";

	//midiOutOpen(&device, C:\Users\Simone\Downloads\EspanjaPrelude.mid,0,0,CALLBACK_NULL);

	//const char *c=path.c_str();
	//mciSendString(c,NULL,0,NULL);





	union { unsigned long word; unsigned char data[4]; } 
	message;
	message.data[0] = 0x90;  
	message.data[1] = 60;   
	message.data[2] = 100;  
	message.data[3] = 0;   
		

	if (argc < 2) {
		MIDINote = 0;
	} else {
		MIDINote = atoi(argv[1]);//converts string into integer
	}
	flag = midiOutOpen(&device, MIDINote, 0, 0, CALLBACK_NULL);
	if (flag != MMSYSERR_NOERROR) {
		printf("MIDI did not open.\n");
	}

	printf("Press \"q\" to quit.\n");
	while (1) {        
		if (_kbhit()) { 
			playing = _getch();
			if (playing=='p') {
				message.data[2] = 60;
				printf("ON.\n");
				flag = midiOutShortMsg(device, message.word);
			} 
			else if(playing=='s') {
				message.data[2] = 0; 
				printf("OFF.\n");
				flag = midiOutShortMsg(device, message.word);
			}
			else{}


			if (flag != MMSYSERR_NOERROR) {
				printf("No sound file.");
			}
			if (playing == 'q') break;
		}
	}

  
	midiOutReset(device);
	midiOutClose(device);

	return 0;
}
