#include "grid.h"
#include "block.h"
#include <string>
#include <iostream>
#include <map>
#include "window.h"
using namespace std;

Block::Block(char c, int n){
	x = 3;
	y = 0;
	type = c;
	level = n;
	if(c =='I'){
		g = new Grid(1,4,true, 'I');
	}
	else if(c =='T'){
		g = new Grid(2,3,true, 'T');
		g->clearPos(1,0);
		g->clearPos(1,2);
	}
	else if(c =='J'){
		g = new Grid(2,3,true, 'J');
		g->clearPos(0,1);
		g->clearPos(0,2);
	}
	else if(c =='L'){
		g = new Grid(2,3,true, 'L');
		g->clearPos(0,1);
		g->clearPos(0,0);
	}
	else if(c =='Z'){
		g = new Grid(2,3,true, 'Z');
		g->clearPos(0,2);
		g->clearPos(1,0);	
	}
	else if(c =='S'){
		g = new Grid(2,3,true, 'S');	
		g->clearPos(0,0);
		g->clearPos(1,2);
	}
	else if(c =='O'){
		g = new Grid(2,2,true, 'O');	
	}
	len = g->getX();
	width = g->getY();
}	
//*
Block::~Block(){
	delete g;
}//*/


// moves the block down by one
bool Block::down(Grid* board){
	bool check = true;
	if (x+len+1 > 18) check = false;
	if (check){
		for(int i = 0; i < len; i++){
			for(int j = 0; j < width; j++){	
				if(g->at(i,j) != ' ' && board->at(x+i+1,y+j) != ' '){
					check = false;
				}
			}
		}
	}
	if (check){
		x= x+1;
	}
	return check;
}
// moves the block left one unit
void Block::left(Grid* board){
	bool check = true;
	if (y == 0) check = false;
	for(int i = 0; i < len; i++){
		for(int j = 0; j < width; j++){			
			if(board->at(x+i,y+j-1) != ' ' && board->at(x+i,y+j) != ' '){
				check = false;
			}
		}
	}
	if (check){
		y--;
	}
}

// moves the block right one unit
void Block::right(Grid* board){
	bool check = true;
	if (y+1+width > 10) check = false;
	for(int i = 0; i < len; i++){
		for(int j = 0; j < width; j++){			
			if(board->at(x+i,y+j+1) != ' ' && board->at(x+i,y+j) != ' '){
				check = false;
			}
		}
	}
	if (check){
		y++;
	}
	
}

// move the block down until it can't be moved down anymore
bool Block::drop(Grid* board){
	int count = 0;
	bool check;
	while(1){		
		check = down(board);
		if (!check){
			break;
		}
		count++;
	}
	for(int i =0; i < len; i++){
		for(int j = 0; j < width; j++){
			if(g->at(i,j)!=' '){
				board->setPos(x+i,y+j,type);
			}
		}
	}
	if(count == 0){
		return true;
	}
	return false;
}

char Block::getPos(int r, int c){
	return g->at(r,c);
}

int Block::getX(){
	return x;
}

int Block::getY(){
	return y;
}

int Block::getLen(){
	return len;
}	
int Block::getWidth(){
	return width;
}


//Prints the block on the screen
void Block::display(){
	for(int i = 0; i < len; i++){
		for(int j = 0; j < width; j++){
			cout << g->at(i,j);
		}
		cout << endl;
	}
}

// Rotates the blocks 
void Block::rotate(string command, Grid* board){
	Grid* tmp = new Grid(width,len, false, type);
	if (command == "counterclockwise"){
		for(int i = len-1; i >=0; i--){
			for(int j = 0; j <width; j++){
				if(g->at(i,j) == type){
					tmp->setPos(width-j-1,i,type);
				}
			}
		}

	}
	else if (command ==  "clockwise"){
		for(int i = len-1; i >=0; i--){
			for(int j = 0; j <width; j++){
				if(g->at(i,j) == type){
					tmp->setPos(j,len-i-1,type);
				}
			}
		}
	}
	
	// =====
	bool hit = false;
	// check if the block can rotate not
	for(int i = 0; i < len; i++){
		for(int j = 0; j < width; j++){
			if(board->at(x+i,y+j)!=' ' && tmp->at(i,j)!=' '){
				hit = true;
			}
		}
	}
	if (x+len >= 18 || y+width >=10){
		hit = true;
	}

	// ====
	if(!hit){
		x = x-(width-len);
		len = tmp->getX();
		width = tmp->getY();
		delete g;
		g = tmp;
	}
}

void Block::addX(int n){
	x+=n;
}

int Block::getLevel(){
	return level;
}

void Block::draw(Xwindow* w){
	if (w){
		g->draw(w,x,y,true);
	}
}

void Block::drawColour(Xwindow *w){
	if (w){
		g->draw(w,x,y,false);
	}
}

void Block::draw(Xwindow* w, int a, int b){
	if (w){
		g->draw(w,a,b,false);
	}
}