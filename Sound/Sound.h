/*
Header file for Sound.cpp
*/

#define SOUND_H_
#ifndef SOUND_H_

#include <iostream>
#include <Windows.h>
#include <MMSystem.h>
#include <conio.h>
#include <string>
#include "Play.h"
#include "Mute.h"


using namespace std;

int Sound(wstring MIDIFile, int argc, char** argv);

#endif SOUND_H_