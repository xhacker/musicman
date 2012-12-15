/*
Header file for Play.cpp
*/

#define PLAY_H_
#ifndef PLAY_H_

#include <iostream>
#include <Windows.h>
#include <MMSystem.h>
#include<conio.h>
#include <string>

using namespace std;

void Play(wstring MusicFile);

void Resume(wstring MusicFile);

void VolumeSet(wstring MusicFile);

void Volume(wstring MusicFile, int vlevel);

#endif PLAY_H_