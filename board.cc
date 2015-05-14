#include "grid.h"
#include "score.h"
#include "board.h"
//#include "block.h"

#include "level.h"
#include <iostream>
#include "window.h"
#include <sstream>
using namespace std;

Board::Board(int n, string fname, int seed, Xwindow* w = NULL){
	r = 18;
	c = 10;
	gBoard = new Grid(r,c);
	level = n;
	gameOver = false;
	s = new Score;
	this->fname = fname;	
	if(level <= 0){
		level = 0;
		l = new Level0(fname);
	}
	else if(level == 1){
		l = new Level1;
	}
	else if(level == 2){
		l = new Level2;
	}
	else{
		l = new Level3;
		level = 3;
	}
	if ( seed != -1){
		l->setSeed(seed);
		this->seed = seed;
	}
	current = l->getBlock();
	next = l->getBlock();
	vector <Block*> allPieces;
	this->w = w;
}

Board::~Board(){
	delete gBoard;
	delete l;
	delete current;
	delete next;
	delete s;
}


void Board::moveBlock(string command){
	if (w!=NULL){
		Grid tmp(current->getLen(), current->getWidth());
		tmp.draw(w,current->getX(), current->getY(),true);
	}
	if (command == "left"){
		current->left(gBoard);
	}
	else if (command == "right"){
		current->right(gBoard);
	}
	else if (command == "down"){
		current->down(gBoard);
	}
	current->drawColour(w); //
}

void Board::rotateBlock(string command){
	if (w!=NULL){
		Grid tmp(current->getLen(), current->getWidth());
		tmp.draw(w,current->getX(), current->getY(),true);
	}
	current->rotate(command, gBoard);
	current->drawColour(w);
}

// checks the board and resets the level
void Board::clear(){
	delete l;
	l = new Level0(fname);
	for(int i = 0; i <r; i++){
		for(int j = 0; j < c;j++){
			gBoard->clearPos(i,j);
		}
	}
	delete current;
	delete next;
	current = l->getBlock();
	next = l->getBlock();
	allPieces.clear();
	s->reset();
	draw();
}

void Board::dropBlock(){
	// cover up the orginal position the block	
	if (w!=NULL){
		Grid tmp(current->getLen(), current->getWidth());
		tmp.draw(w,current->getX(), current->getY(),true);
	}
	gameOver = current->drop(gBoard);
	allPieces.push_back(current);
	//clearRow();	
	if (w!=NULL) current->drawColour(w);	//
	clearRow();	
	current = next;
	if (w!=NULL) current->drawColour(w);//
	next = l->getBlock();
	//cout << "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n\n\n\n\n\n\n\n\n\n\n";
	//next->draw(w,0,370);	
	// if the player lost the game
	if(gameOver){
		cout << "Game Over" << endl;
		clear();
		gameOver = false;
	}
}

// Changes the level
void Board::changeLevel(string command){
	if (command == "levelup"){
		if(level == 2){
			level++;
			delete l;
			l = new Level3;
			if (seed != -1) l->setSeed(seed);
		}
		else if(level == 1){
			level++;
			delete l;
			l = new Level2;
			if (seed != -1) l->setSeed(seed);
		}
		else if(level == 0){
			level++;
			delete l;
			l = new Level1;
			if (seed != -1) l->setSeed(seed);
		}
	}
	// command == "leveldown"
	else{
		if (level==3){
			level--;
			delete l;
			l = new Level1;
			if (seed != -1) l->setSeed(seed);
		}
		else if(level == 2){
			level--;
			delete l;
			l = new Level3;
			if (seed != -1) l->setSeed(seed);
		}
		else if(level == 1){
			level--;
			delete l;
			l = new Level0(fname);
		}
	}

}

// prints the next block on the screen
void Board::displayNext(){
	next->display();
	if(w!=NULL) {
		w->fillRectangle(0, 360, 200, 140, Xwindow::Brown);
		w->drawString(20, 19*20, "Next:", Xwindow::Black);
		next->draw(w,20,1);
		stringstream ss;
		ss << "Level:    " << level;
		string n = ss.str();
		ss.str("");
		w->drawString(100, 19*20,n, Xwindow::White);
		//stringstream ss;
		int a = s->getScore();
		ss << "Score:    " << a;
		n = ss.str();
		ss.str("");
		w->drawString(100, 390,n, Xwindow::White);
		a = s->getHighScore();
		//stringstream ss;
		ss << "High Score:    " << a;
		n = ss.str();
		ss.str("");
		w->drawString(100, 400,n, Xwindow::White);
	}
}
// prints the board and other information
void Board::display(){
	cout << "Level:    " << level << endl;
	s->display();
   	cout << "*--------*" << endl;
	bool check;
	int x = current->getX();
	int y = current->getY();
	int len = current->getLen();
	int wid = current->getWidth();
	//======== Prints the board ========
	for(int i = 3; i < r; i++) {
		for(int j = 0; j < c; j++){
			check = false;

			if ((x <= i) && (i < x+len) && (y <= j) && (j < y+wid)) {
				if (current->getPos(i-x,j-y) != ' ') {
					check = true;
					cout << current->getPos(i-x,j-y);
				}
			}
			if (!check) {
				cout << gBoard->at(i,j);
			}
		}
		cout << endl;
	}
	// ===============================
	cout << "*--------*" << endl;
	cout << "Next: " << endl;
	displayNext();
}

void Board::clearRow(){
	bool fullRow;
	int rowsClear = 0;
	// checks if a row is full
	for(int i = 3; i < r; i++) {
		fullRow = true;
		for(int j = 0; j < c; j++){
			if(gBoard->at(i,j) == ' '){
				fullRow = false;
			}
		}
		if(fullRow){
			removeRow(i);
			rowsClear++;
		}
		cout << endl;
	}
	// if there is at least one row full
	// add the score
	if(rowsClear!= 0){
		int score = level+rowsClear;
		s->add(score*score);
		// if the whole block is off the board
		for(int i =allPieces.size()-1; i <= 0 ; i--){
			allPieces.at(i)->addX(rowsClear);
			if(allPieces.at(i)->getX() >= 18){
				s->add(allPieces.at(i)->getLevel());
				allPieces.erase(allPieces.begin()+i,allPieces.begin()+1+i);
			}
		}
	}
}

// removes one row in the board
void Board::removeRow(int n){
	for(int i = n; i >0; i--){
		for(int j = 0; j < c; j++){
			gBoard->setPos(i,j, gBoard->at(i-1,j));
		}
	}
	if (w!=NULL) gBoard->draw(w, 0 ,0,true);
}

void Board::draw(){
	gBoard->draw(w, 0 ,0,true);
	current->drawColour(w); //
}

