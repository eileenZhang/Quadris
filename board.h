#ifndef __BOARD_H__
#define __BOARD_H__
#include "score.h"
#include "grid.h"
#include "block.h"
#include "level.h"
#include <vector>
class Xwindow;
//class Block;


class Board{
	int r,c;		// how big the board is
	// in this game, it doesn't change, but it would be really easy to change if needed
	Grid *gBoard;
	Block *current;
	Block *next;
	int level; 		// the current level
	int seed;
	Level* l;
	std::string fname;
	Xwindow* w;
	Score *s;		// Score of the game
	bool gameOver;	// check the player lost the game
	std::vector<Block*> allPieces; 
	void displayNext();
	// ==== Clears the row ====
	void clearRow();
	void removeRow(int n);

	public:
	Board(int, std::string, int, Xwindow* w);
	~Board();
	void clear(); 	// To restart the game
	// ==== Moving the Block ==== 
	void moveBlock(std::string);
	void rotateBlock(std::string);
	void dropBlock();
	void changeLevel(std::string);
	// ==========================
	void display(); // prints the grid and other information
	void draw();
};
#endif
