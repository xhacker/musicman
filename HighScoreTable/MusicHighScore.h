/*
	HighScore data storage format
*/

#ifndef MusicHighScore_H_
#define MusicHighScore_H_

#include <iostream>
#include <string>

using namespace std;

class HighScore{
	public:
		HighScore();//Callingof HighScore Class

		//These set general HighScore Info
		void setMusicName(string MusicName);
		void setHighScore(int HighScore);
		void setPlayer(string playername);
		
		//These return General HighScore Info
		string getMusicName();
		int getHighScore();
		string getPlayer();
		
	private:
		string musicname;
		int score;
		string player;

};

#endif MusicHighScore_H_


