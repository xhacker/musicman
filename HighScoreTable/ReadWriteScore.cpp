/*High Scores, Song Names and Player Names stored in HighScoreTable.txt*/

/*
	ReadScore reads out top ten scores
	WriteScore takes in three variables, newscore, newuser and newsong
	these variables will then be added to the txt file
*/

#include <iostream>
#include <string>
#include <fstream>
#include "MusicHighScore.h"
#include "ReadWriteScore.h"

#define maxscores 100

using namespace std;

void ReadScore(string songscores){
	string musicname, playername;
	int score, i;
	int numscores=0, count=0;

	ofstream fout;
	ifstream fin;
	fin.open("HighScoreTable.txt");
	fout.close();

	HighScore list[maxscores];

	for(i=0; i<=(maxscores-1)&&!fin.eof(); i++){//record all the data from the file and send to User class
		fin >> musicname >> playername >> score; //These are the variable found in txt file
		list[i].setMusicName(musicname);
		list[i].setPlayer(playername);
		list[i].setHighScore(score);
		numscores++;
	}
	for(i=0; i<=(maxscores-1)&&numscores>=0;i++,numscores--){
		if(list[i].getMusicName()==songscores&&count<=10){//only print out relavent song scores
			cout<<"\n\t"<<". "<<list[i].getPlayer()<<" with a score of: "<<list[i].getHighScore();
			count++;
		}
	}
	cout<<endl;
	return;
}

void WriteScore(int newscore, string newuser, string newsong){
	string musicname, playername;
	int score, i;
	bool check=false;

	ofstream fout;
	ifstream fin;
	fin.open("HighScoreTable.txt");
	fout.close();

	HighScore list[maxscores];

	for(i=0; i<(maxscores-1)&&!fin.eof(); i++){
		fin >> musicname >> playername >> score;
		list[i].setMusicName(musicname);
		list[i].setPlayer(playername);
		list[i].setHighScore(score);
	}

	for(i=0; i<(maxscores-1); i++){
		if(newscore>list[i].getHighScore()&&check!=true){
			for(int j=(maxscores-1);j>i;j--){
				list[j]=list[j-1];
			}
			list[i].setPlayer(newuser);
			list[i].setMusicName(newsong);
			list[i].setHighScore(newscore);
			check=true;
		}
	}

	fstream ftmp;//delete all score data
	ftmp.open("HighScoreTable.txt", ios::out | ios::trunc );
	ftmp.close();
	cout<<endl;
	for(i=0; i<(maxscores-1);i++){
		ftmp.open ("HighScoreTable.txt", fstream::in | fstream::out | fstream::app);
		ftmp<<list[i].getMusicName()<<" "<<list[i].getPlayer()<<" "<<list[i].getHighScore()<<"\t"<<"\n";
		ftmp.close();
	}
	return;
}

/*Example of Main to call High Score Table*/
//void ReadScore(string songscores);
//void WriteScore(int newscore, string newuser, string newsong);
//
//int main(void){
//	int exit=0;
//	string songscores;
//
//	cin>>exit;
//	while(exit!=1){
//		if(exit==2)
//			cin>>songscores;
//			ReadScore(songscores);
//		if(exit==3){
//			string newuser, newsong;
//			int newscore;
//			cin>>newuser;
//			cin>>newsong;
//			cin>>newscore;
//			WriteScore(newscore, newuser, newsong);
//		}
//		cin>>exit;
//
//	}
//
//
//	return 0;
//}