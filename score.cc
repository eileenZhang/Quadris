#include "score.h"
#include <iostream>
using namespace std;

Score::Score(){
	score = 0;
	highScore = 0;
}


void Score::add(int n){
	score+=n;
	if (score > highScore){
		highScore = score;
	}
}

void Score::display(){
	cout << "Score:    " << score << endl;
   	cout << "HiScore:  " << highScore << endl;
}

void Score::reset(){
	score = 0;
}

int Score::getHighScore(){
	return highScore;
}
int Score::getScore(){
	return score;
}
