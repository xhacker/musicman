/*
	Editing HighScore data functions
*/

#include <iostream>
#include <string>
#include "MusicHighScore.h"
#include "ReadWriteScore.h"

using namespace std;

HighScore::HighScore(){}

string HighScore::getMusicName(){
	return musicname;
}

int HighScore::getHighScore(){//returns the neame of a given HighScore
	return score;
}

string HighScore::getPlayer(){//returns the author of a given HighScore
	return player;
}

////////////////////////////

void HighScore::setMusicName(string Music){
	musicname=Music;
}

void HighScore::setHighScore(int HighScore){//sets HighScorename from a text file
	score=HighScore;
}

void HighScore::setPlayer(string playername){//sets author of HighScore from txt file
	player=playername;
}