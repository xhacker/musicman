/*
	Accesss to HighScore table functions
*/

#ifndef ReadWriteScore_H_
#define ReadWriteScore_H_

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

void ReadScore(string songscores);
void WriteScore(int newscore, string newuser, string newsong);

#endif ReadWriteScore_H_