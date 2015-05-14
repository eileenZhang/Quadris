#ifndef __GRID_H__
#define __GRID_H__
class Xwindow;
class Grid{
	int x,y;	// Len and width of g
	char **g;	// 2D array to store info
	char type;
	public:
	Grid();
	Grid(int r, int c,bool fill, char a);
	Grid(int r, int c);
	~Grid();
	void setPos(int i, int j, char ch); 	// sets the position of (i, j) to ch
	void setPos(int, int);
	void clearPos(int, int);
	char at(int i, int j);						// get the position at (i, j)
	int getX();
	int getY();
	void draw(Xwindow* ,int ,int,bool);
};

#endif
