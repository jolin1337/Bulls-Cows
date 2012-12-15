#ifndef MENU_H
#define MENU_H
#include <string>
#include "../Render/ScreenRender.h"
class Menu{
	int current,
		maxLength;
	SR::ScreenRender *sr;
	keyboard *keys;

	// ?!?!?!? constanta!!
	int mnitemLength, startitem;
public:
	int logoEnd;
	Menu(SR::ScreenRender *sr, keyboard *keys){
		current = 0; maxLength = 0; logoEnd = 0;
		mnitemLength = 7;
		startitem = 2;
		this->sr = sr;
		this->keys = keys;
		sr->clearScreen();
	}
	~Menu(){
		sr->clearScreen();
	}
	int menu();
	int next();
	int previous();
	void printCurrent();
	void printMenu();
};
#endif