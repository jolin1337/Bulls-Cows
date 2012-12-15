#include <string>
#include "Render/Linux.h"
#include "Render/ScreenRender.h"
class Menu{
	int current,
		maxLength;
	SR::ScreenRender *sr;
	const int mnitemLength, startitem;
	keyboard *keys;
public:
	int logoEnd;
	Menu(SR::ScreenRender *sr, keyboard *keys):current(0), maxLength(0), mnitemLength(7), startitem(2), logoEnd(0){
		this->sr = sr;
		this->keys = keys;
		
		this->sr->clearScreen();
	}
	~Menu(){
		sr->clearScreen();
	}
	int menu(){
		while(true){
			printCurrent();
			int inp = keys->getch();
			if(inp == '\n')
				return current;
			else if(inp == 'q' || inp == 'Q')
				return 6;
			else{
				std::string kb = "";
				kb += inp;
				//if(keys.kbhit())
				while(keys->kbhit())
					kb += keys->getch();
				if( kb == VK_UP || kb == VK_DOWN){
					int dir = (kb[kb.length()-1]) - 'A';
					if(dir)
						next();
					else
						previous();
				}
			}
		}
		return current;
	}
	int next(){
		current++;
		current %= mnitemLength;
		return current;
	}
	int previous(){
		current--;
		if(current <0)
			current += mnitemLength;
		return current;
	}
	void printCurrent(){
		for(int j = 0; j<mnitemLength;j++)
			sr->printString(sr->width/2-maxLength/2-3, (j)*2 + logoEnd + startitem, " ");
		sr->printString(sr->width/2-maxLength/2-3, current*2 + logoEnd + startitem, ">", GREEN);
		sr->render();
	}
	void printMenu(){
		std::string mnitem[] = {"Start Think of", "Start Guess of", "Challange computer", "Instructions", "Hightscore", "About", "Exit"};
		for(int j = 0; j<mnitemLength;j++){
			int ln = (mnitem[j]).length();
			this->sr->printString(this->sr->width/2 - ln/2, j*2 + logoEnd + startitem, (mnitem[j]).c_str(), MAGENTA);
			if(ln > maxLength)
				maxLength = ln;
		}
	}
};