#ifndef BULLSCOWS_H
#define BULLSCOWS_H

#include "Render/ScreenRender.h"
#include "Gissning/Gissning.h"
#include "Menu/Menu.h"
#include "Solver.h"
#include "Highscore.h"
#include <iostream>
#include <vector>

class BullsCows {
public:
	COORD resultPos;
	BullsCows();
	BullsCows(std::string name);
	~BullsCows();
	int start();
private:
	bool playing;
	SR::ScreenRender sr;
	keyboard keys;
	Menu menues;
	Solver solveres;
	Highscore highscore;
	void docs();
	void about();

	typedef std::vector<Gissning > G;
	//typedef map<string, string> G;

	int length(int n);
	int rvlength(int n);
	int getPos(int num, int pos, int len);


	int challangeComputer();
	int creater(bool practice = true);
	void getMaxT();

	int menu();
};

#endif