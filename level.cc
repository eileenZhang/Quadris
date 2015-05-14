#include "level.h"
#include <fstream>
#include <iostream>
#include "PRNG.h"
#include <vector>
using namespace std;

PRNG r; 

Level::Level(){}

Level::~Level(){

}

void Level::setSeed(int n){
	r.seed(n);
}

Level0::Level0(string n){
	fname = n;
	current = -1;
	len = 0;
}

Level0::~Level0(){
	delete position;
}

void Level0::getBlockOrder(){
	ifstream f (fname.c_str());
	position = new char[20];
	int max = 20;
	char c;
	while(f>>c){
		position[len] = c;
		len++;
		if(len == max){
			char*tmp = new char[max*2];
			max*=2;
			for(int i = 0; i < len;i++){
				tmp[i]==position[i];
			}
			delete position;
			position = tmp; 
		}
	}
}

Block* Level0::getBlock(){
	if(len ==0){
		getBlockOrder();
	}
	current++;
	if(current == len) current = 0;
	char type = position[current];
	Block* tmp = new Block(type,1);
	return tmp;
}

Level1::Level1(){}

Block* Level1::getBlock(){
	int rand = r()%12;
	char c;
	if (rand == 0 || rand==1){
		c ='I';  
	}
	else if (rand == 2 || rand==3){
		c = 'J';
	}
	else if (rand == 4 || rand==5){
		c = 'L';
	}
  	else if (rand == 6){
	  	c = 'Z';
   	}
   	else if (rand == 7 || rand == 8){
	  	c = 'O';
   	}
   	else if (rand == 9){
	  	c = 'S';
   	}
   	else if (rand == 10 || rand == 11){
	  	c = 'T';
  	}
	Block* tmp = new Block(c,1);
	return tmp;
}

Level2::Level2(){}

Block* Level2::getBlock(){
	int rand = r()%7;
	char c;
	if (rand == 0){
		c ='I';  
	}
	else if (rand == 1){
		c = 'J';
	}
	else if (rand == 2){
		c = 'L';
	}
  	else if (rand == 3){
	  	c = 'Z';
   	}
   	else if (rand == 4){
	  	c = 'O';
   	}
   	else if (rand == 5){
	  	c = 'S';
   	}
   	else if (rand == 6){
	  	c = 'T';
  	}
	Block* tmp = new Block(c,2);
	return tmp;
}

Level3::Level3(){}

Block* Level3::getBlock(){
	int rand = r()%9;
	char c;
	if (rand == 0){
		c ='I';  
	}
	else if (rand == 1){
		c = 'J';
	}
	else if (rand == 2){
		c = 'L';
	}
  	else if (rand == 3 || rand == 4 ){
	  	c = 'Z';
   	}
   	else if (rand == 5){
	  	c = 'O';
   	}
   	else if (rand == 6 || rand == 7){
	  	c = 'S';
   	}
   	else if (rand == 8){
	  	c = 'T';
  	}
	Block* tmp = new Block(c,3);
	return tmp;
}


