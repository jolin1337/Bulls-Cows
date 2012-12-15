#include "header.h"
#include "Solver.h"

int Solver::solve(Gissning *real, bool practice){ // default: real = 0, practice = true
	if(practice){
		sr->clearScreen();
		sr->printString(3, sr->height-3, "Practice thinking numbers.", BLACK);
	}
	drawTable(*sr);
	sr->printString(resultPos.X+28, resultPos.Y+3, "Bulls", GREEN);
	sr->drawRect(resultPos.X+30, resultPos.Y+0, 2, 2);
	sr->printString(resultPos.X+35, resultPos.Y+3, "Cows", CYAN);
	sr->drawRect(resultPos.X+35, resultPos.Y+0, 2, 2);

	sr->printString(resultPos.X+20, resultPos.Y+7, "You input some clues for the guessed");
	sr->printString(resultPos.X+20, resultPos.Y+8, "number by typing it in the right resp. ");
	sr->printString(resultPos.X+20, resultPos.Y+9, "left box. Use the arrow keys to ");
	sr->printString(resultPos.X+20, resultPos.Y+10,"navigate between the numbers.");
	G gis;
	for(int i=0; i < 10; i++){

		Gissning gi = generateGuess(&gis);
		if(gi.getGissning() == -1 || gi.getBulls() + gi.getCows() > 4){
			sr->clearScreen();
			if(!practice || !whantToContinueChallange(*sr, *keys))
				break;
			sr->clearScreen();
			drawTable(*sr);
			sr->printString(resultPos.X+28, resultPos.Y+3, "Bulls", GREEN);
			sr->drawRect(resultPos.X+30, resultPos.Y+0, 2, 2);
			sr->printString(resultPos.X+35, resultPos.Y+3, "Cows", CYAN);
			sr->drawRect(resultPos.X+35, resultPos.Y+0, 2, 2);

			sr->printString(resultPos.X+20, resultPos.Y+7, "You input some clues for the guessed");
			sr->printString(resultPos.X+20, resultPos.Y+8, "number by typing it in the right resp. ");
			sr->printString(resultPos.X+20, resultPos.Y+9, "left box. Use the arrow keys to ");
			sr->printString(resultPos.X+20, resultPos.Y+10,"navigate between the numbers.");
			sr->printString(3, sr->height-3, "Practice thinking numbers.", BLACK);
			i = 0;
			gis.clear();
			continue;
		}
		if(real){
			int bc = BullsCowsContain(real, &gi);
			gi.setBullsCows(bc%10, bc/10);
		}
		else{ 
			int lg = gi.getGissning()%50000;
			if( lg < 1000){
				sr->printString(resultPos.X + 2, resultPos.Y + i +2, 0);
				sr->printString(resultPos.X + 3, resultPos.Y + i +2, lg);
			}
			else
				sr->printString(resultPos.X + 2, resultPos.Y + i +2, lg);
			if(input(&gi))
				break;
			sr->printString(resultPos.X + 10, resultPos.Y + i +2, gi.getBulls(), GREEN);
			sr->printString(resultPos.X + 12, resultPos.Y + i +2, gi.getCows(), CYAN);

			sr->render();
		}
		if(gi.getBulls() == 4 && gi.getCows() == 0){
			drawSucess(*sr, i);
			sr->printString(sr->width/2 - 28/2, sr->height - 2, "Press any key to continue...", RED);
			sr->render();
			while(keys->kbhit())keys->getch();
			keys->getch();
			sr->clearScreen();
			if(!practice || !whantToContinueChallange(*sr, *keys))
				return i;
			i = 0;
		}

		gis.push_back(gi);
	}
	return -1;
}

int Solver::BullsCowsContain(Gissning *x, Gissning *y){
	int bulls = 0,cows = 0;
	bool taken[] = {false, false, false, false};
	for(int len=0; len<x->length()-1; len++)
		if( (*x)[len+1] == (*y)[len+1]){
			taken[len] = true;
			bulls++;
		}
	for(int len=0; len<x->length()-1; len++)
		for(int i=0; i<y->length()-1; i++)
			if((*x)[len+1] == (*y)[i+1] && !taken[i]){
				taken[i] = true;
				cows++;
				break;
			}
	return cows*10 + bulls;
}
bool Solver::goodGuess(Gissning gv, G *g){
	for(unsigned int z=0; z< g->size(); z++){
		Gissning *gi = &(g->at(z));
		if(BullsCowsContain(&gv, gi) != gi->toRes()){
			return false;
		}
	} 
	return true;
}
int Solver::generateGuess(G *g){
	DistinktNumber dnum;
	if(g->size())
		dnum.setNum(g->at(g->size()-1).getGissning());
	else
		return 50123;
	do{
		// öka till nästa distinkta tal
		int new_num = dnum+1;
		if( new_num == -1){
			sr->fillRect(sr->width/2 - 18/2 -4, 7, 25, 6, ' ');
			sr->drawRect(sr->width/2 - 18/2 -3, 9, 21, 4, 'a', RED);
			sr->printString(sr->width/2 - 18/2, 8, "Ye cheatin' scum!", RED);
			sr->printString(sr->width/2 - 18/2, 10, "There are no", RED);
			sr->printString(sr->width/2 - 18/2, 11, "solutions to this ", RED);
			sr->printString(sr->width/2 - 18/2, 12, "puzzle -_-", RED);
			sr->printString(sr->width/2 - 28/2, sr->height - 2, "Press any key to continue...", RED);
			sr->render();
			while(keys->kbhit())keys->getch();
			keys->getch();
			// handle errors in inputs here!
			return -1;
		}
		dnum.setNum(new_num);
	}while(!goodGuess(dnum.getNum(), g));// skapar en gissnings objekt med gv
	return dnum.getNum();
}
bool Solver::input(Gissning *gi){
		int bulls=gi->getBulls(), cows=gi->getCows();
		SR::PIX bl;
		bool pos = false;
		while(true){
			
			bl.Char.AsciiChar = cows+48;
			bl.Attributes = CYAN;
			sr->setPixel(resultPos.X+36, resultPos.Y+1, &bl);
			bl.Char.AsciiChar = bulls+48;
			bl.Attributes = GREEN;
			sr->setPixel(resultPos.X+31, resultPos.Y+1, &bl);
			bl.Char.AsciiChar = '>';
			bl.Attributes = BLUE;
			sr->setPixel(resultPos.X+29 + pos*5, resultPos.Y+1, &bl);
			bl.Char.AsciiChar = ' ';
			sr->setPixel(resultPos.X+29 + (!pos)*5, resultPos.Y+1, &bl);
			sr->render();
			int inp = keys->getch();
			if(inp == '\n')
				break;
			else if(inp >= '0' && inp <= '4'){
				if(pos)
					cows = inp - '0';
				else 
					bulls = inp - '0';
				pos = !pos;
			}
			else if(inp == 'q' || inp == 'Q')
				return 1;
			else{
				std::string key;
				key+=inp;
				while(keys->kbhit())
					key += keys->getch();
				if(key == VK_LEFT || key == VK_RIGHT)
					pos = !pos;
			}
		}
		gi->setBullsCows(bulls, cows);
		return 0;
	}