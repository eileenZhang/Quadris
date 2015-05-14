#ifndef __BLOCK_H__
#define __BLOCK_H__

#include <string>
#include "grid.h"
#include <map>

class Block{
	Grid *g;
	char type;	// iBlock, oBlock, etc
	int len, width;	// len and width of g
	int x,y;	// Where the Block is on the Board
	int level;	// What level the piece was placed on the Board
	bool onBoard;	// keep track if the piece is on the board or not
	public:
	Block(char c,int);
	~Block();
	// === Gets all private members ====
	int getLen();
	int getWidth();
	int getX();
	int getY();
	int getLevel();
	// =====
	void addX(int n);
	char getPos(int, int);
	// === Moving the piece ======
	bool down(Grid *board);
	void left(Grid *board);
	void right(Grid *board);
	bool drop(Grid *board);
	void rotate(std::string command, Grid* board);
	// ===================
	void display(); 	// prints the block
	void draw(Xwindow *);
	void drawColour(Xwindow *);
	void draw(Xwindow*, int, int);

};


#endif
