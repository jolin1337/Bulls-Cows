#include "header.h"
#include <stdexcept>
using namespace std;
int logo(SR::ScreenRender &sr, int x, int y){ // default: x = 0, y = 0;
	sr.printString(x, y++, " ____        _ _                       _    _____                  ");
	sr.printString(x, y++, "|  _ \\      | | |                     | |  / ____|                 ");
	sr.printString(x, y++, "| |_) |_   _| | |___    __ _ _ __   __| | | |     _____      _____ ");
	sr.printString(x, y++, "|  _ <| | | | | / __|  / _` | '_ \\ / _` | | |    / _ \\ \\ /\\ / / __|");
	sr.printString(x, y++, "| |_) | |_| | | \\__ \\ | (_| | | | | (_| | | |___| (_) \\ V  V /\\__ \\");
	sr.printString(x, y++, "|____/ \\__,_|_|_|___/  \\__,_|_| |_|\\__,_|  \\_____\\___/ \\_/\\_/ |___/");
	return y;
}

void drawTable(SR::ScreenRender &sr){
	COORD resultPos;
	resultPos.X = 10;
	resultPos.Y = sr.height-15;
	logo(sr, sr.width/2-68/2, 2);
	sr.printString(resultPos.X+2, resultPos.Y, "Guess");
	sr.printString(resultPos.X+10, resultPos.Y, "Clue");
	sr.printString(resultPos.X, resultPos.Y+1, "------------------");

	// input instr
	sr.printString(resultPos.X+20, resultPos.Y+5, "Input");
	sr.printString(resultPos.X+20, resultPos.Y+6, "----------------");
}

void drawSucess(SR::ScreenRender &sr, int tryes){
	sr.fillRect(sr.width/2 - 18/2 -4, 7, 25, 6, ' ');
	sr.drawRect(sr.width/2 - 18/2 -3, 9, 21, 4, 'a', MAGENTA);
	if(tryes != -1){
		sr.printString(sr.width/2 - 18/2, 8, "Success!", MAGENTA);
		sr.printString(sr.width/2 - 20/2, 10, "I got your secret", MAGENTA);
		sr.printString(sr.width/2 - 20/2, 11, "number in", MAGENTA);
		sr.printString(sr.width/2 - 20/2 + 10, 11, tryes+1, MAGENTA);
		sr.printString(sr.width/2 - 20/2, 12, "moves.", MAGENTA);
	}
	else{
		sr.printString(sr.width/2 - 18/2, 8, "Failiure!", MAGENTA);
		sr.printString(sr.width/2 - 20/2, 10, "Faild to solve", MAGENTA);
		sr.printString(sr.width/2 - 20/2, 11, "the secret ", MAGENTA);
		sr.printString(sr.width/2 - 20/2, 12, "number.", MAGENTA);
	}
}

bool whantToContinueChallange(SR::ScreenRender &sr, keyboard &keys){
	sr.fillRect(sr.width/2 - 18/2 -4, 7, 25, 6, ' ');
	sr.drawRect(sr.width/2 - 18/2 -3, 9, 21, 4, 'a', BLACK);
	sr.printString(sr.width/2 - 18/2, 8, "Continue playing?", GREEN);
	bool yes = true;
	while(true){
		if(yes)
			sr.printString(sr.width/2 - 20/2, 10, "> Yes     No", MAGENTA);
		else
			sr.printString(sr.width/2 - 20/2, 10, "  Yes   > No", MAGENTA);
		sr.render();
		std::string key;
		key += keys.getch();
		while(keys.kbhit())
			key += keys.getch();
		if(key == VK_RIGHT || key == VK_LEFT)
			yes = !yes;
		else if(key == "\n")
			return yes;
	}
}

string whatsYourName(SR::ScreenRender &sr, keyboard &keys){
	string name;
	while(true){
		sr.clearScreen();
		//int adjust = (name.length() >7?name.length()-7:0);
		sr.printString(sr.width/2 - 18/2, 8, "What's your name?", GREEN);
		sr.printString(sr.width/2 - name.length()/2, 10, name.c_str(), MAGENTA);
		sr.drawRect(sr.width/2 - name.length()/2-2, 9, name.length()+3, 2, 'a', BLACK);
		sr.render();

		int key = keys.getch();
		cout << key << endl;
		try{
			if(key == '\n')
				return name;
			if(key == 127)	// ta bort tangenten
				name.erase(name.length()-1,1);
			else if((int)name.length() > sr.width - 10*2);
			else if(isalpha(key) && key != ' ')
				name += key;
		}
		catch(std::out_of_range &e){
			name = "";
		}
	}
}