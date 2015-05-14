
#include <iostream>
#include <string>
#include <cmath>
#include "window.h"
#include "board.h"
using namespace std;

int convertToString(string s){
	int digits=0;
	int num =0;
   	for (int j=s.length()-1; j>=0; j--){
    	if ((s[j]-'0') >= 0 && (s[j] - '0') <= 9){
       		num += (pow (10, digits)) * (s[j] - '0');
       		digits += 1;
    	}
   	}
   	if (digits==0){
    	num = 1;
   	}
	return num;
}

int main(int argc, char *argv[]){
	Xwindow *w; 
	bool onlyText = false;
	string fname = "sequence.txt";
	int level = 0;
	int seed = 2665422225;
	// gets the arugments
	for(int i = 1; i < argc; i++){
		string command = argv[i];
		if (command == "-text"){
			onlyText = true;
		}
		else if(command == "-seed"){
			i++;
			seed = convertToString(argv[i]);
		}
		else if(command == "-scriptfile"){
			i++;			
			fname = argv[i];
		}
		else if(command == "-startlevel"){
			i++;
			level = convertToString(argv[i]);
		}
	}
	// sets up the board and see if there's graphics
	if(!onlyText){
		w = new Xwindow(200, 500);
	}
	else{
		w = NULL;		
	}
	Board b(level, fname, seed,w);
	if(!onlyText){ 
		b.draw();
		w->fillRectangle(0, 360, 200, 140, Xwindow::Brown);
	} 
	// the actual game
	while(1){
	
		// Print the board first
   		b.display();
   		

		// ======== Geting the commands =====
		string commandList []= {"left", "right", "down", "counterclockwise", "clockwise",
								"drop", "levelup", "leveldown", "restart"};
		int numOfCommands = 9;
		string command = "";
		int mulitplier = 0;
		cin >> command;

		// ====== Gets the number before the command === 
   		mulitplier = convertToString(command);
		// ====== Gets the string part of the command
		//int i = 0;
		while ((command[0]-'0') >= 0 && (command[0] - '0') <= 9){
         	command = command.substr (1);
     	}
		// ===== find out what the command is =====


		for(int i = 0; i < numOfCommands; i++){
			string tmp = "";
			for(int j= 0; j < commandList[i].length(); j++){
				tmp += commandList[i][j];
				if (command == tmp){
					command = commandList[i];
					break;	
				}
			}
			if (command == commandList[i]) break;
		}

		if (command == "restart" && mulitplier != 0){
			b.clear();
		}

		// runs the command n times
		for(int i = 0; i < mulitplier; i++){
			if(command == "left" || command == "right"|| command == "down"){
				b.moveBlock(command);
			}
			else if (command == "drop"){
				b.dropBlock();
			}
			else if(command == "levelup" || command == "leveldown"){
				b.changeLevel(command);
			}
			else if(command == "counterclockwise" || command ==  "clockwise"){
				b.rotateBlock(command);
			}
		}

	}
}
