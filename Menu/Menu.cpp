#include "Menu.h"
int Menu::menu(){
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

int Menu::next(){
	current++;
	current %= mnitemLength;
	return current;
}
int Menu::previous(){
	current--;
	if(current <0)
		current += mnitemLength;
	return current;
}

void Menu::printCurrent(){
	for(int j = 0; j<mnitemLength;j++)
		sr->printString(sr->width/2-maxLength/2-3, (j)*2 + logoEnd + startitem, " ");
	sr->printString(sr->width/2-maxLength/2-3, current*2 + logoEnd + startitem, ">", GREEN);
	sr->render();
}

void Menu::printMenu(){
	std::string mnitem[] = {"Start Think of", "Start Guess of", "Challange computer", "Instructions", "Hightscore", "About", "Exit"};
	for(int j = 0; j<mnitemLength;j++){
		int ln = (mnitem[j]).length();
		this->sr->printString(this->sr->width/2 - ln/2, j*2 + logoEnd + startitem, (mnitem[j]).c_str(), MAGENTA);
		if(ln > maxLength)
			maxLength = ln;
	}
}