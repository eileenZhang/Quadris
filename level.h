#ifndef __LEVEL_H__
#define  __LEVEL_H__

#include "block.h"
#include <string>

// Level is a pure virtual class
class Level{
	public:
	Level();	
	virtual ~Level() ;	
	virtual Block *getBlock()=0;
	void setSeed(int n);
};

class Level0: public Level{
	std::string fname;
	char * blockOrder;
	int current;
	void getBlockOrder();
	int len;
	char *position;
	public:
	Level0(std::string n);
	~Level0();
	Block *getBlock();	
};

class Level1: public Level{
	public:
	Level1();
	Block *getBlock();
};

class Level2: public Level{
	public:
	Level2();
	Block *getBlock();	
};

class Level3: public Level{
	public:
	Level3();
	Block *getBlock();
	
};

#endif

