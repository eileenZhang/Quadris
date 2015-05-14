
#include "grid.h"
#include <iostream>
#include "window.h"
using namespace std;

Grid::Grid(){
	g = 0;
	y = x = 0;
}

Grid::Grid(int r, int c, bool fill, char a){
	x = r;
	y = c;
	type = a;
	g = new char*[r];
	for(int i = 0; i < r; i++){
		g[i] = new char [c];
		for(int j = 0; j < c; j++){
			if(fill) g[i][j] = a;
			else {g[i][j] = ' ';}
		}
	}
}

Grid::Grid(int r, int c){
	x = r;
	y = c;
	type = ' ';
	g = new char*[r];
	for(int i = 0; i < r; i++){
		g[i] = new char [c];
		for(int j = 0; j < c; j++){
			g[i][j] = ' ';
		}
	}
}

Grid::~Grid(){
	for(int i = 0; i < x; i++){
		delete g[i];
	}
	delete g;
}

char Grid::at(int r, int c){
	return g[r][c];
}

void Grid::setPos(int r , int c){
	g[r][c] = type;
}

void Grid::setPos(int r , int c, char ch){
	g[r][c] = ch;
}

void Grid::clearPos(int r, int c){
	g[r][c] = ' ';
}

int Grid::getX(){
	return x;
}
int Grid::getY(){
	return y;
}

void Grid::draw(Xwindow* w, int a, int b, bool check){
	int width = 20;
	int height= 20;
	int n,m;
	if(w){
		for(int i = 0; i < y; i++){
			for(int j = 0; j < x; j++){
				char type = g[j][i];
				n = (i+b)*20;
				m = (j+a)*20;
				if (check && type == ' ' ){
					w->fillRectangle(n, m, width, height, Xwindow::White);
			   	}
			   	else if (type == 'I'){
				  	w->fillRectangle(n, m, width, height, Xwindow::Cyan);
			   	}
			   	else if (type == 'J'){
				  	w->fillRectangle(n, m, width, height, Xwindow::Green);
			   	}
			   	else if (type == 'L'){
				  	w->fillRectangle(n, m, width, height, Xwindow::Blue);
			   	}
			   	else if (type == 'Z'){
				  	w->fillRectangle(n, m, width, height, Xwindow::Yellow);
			   	}
			   	else if (type == 'S'){
				  	w->fillRectangle(n, m, width, height, Xwindow::Red);
			   	}
			   	else if (type == 'O'){
				  	w->fillRectangle(n, m, width, height, Xwindow::Magenta);
			   	}
			   	else if (type == 'T'){
				  	w->fillRectangle(n, m, width, height, Xwindow::Orange);
			   }
			}
		}
	}
}

