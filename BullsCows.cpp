#include "BullsCows.h" 
#include "DistinktNumber/DistinktNumber.h"
#include "header.h"
using namespace std;
using SR::ScreenRender;

BullsCows::BullsCows():menues(&sr, &keys), solveres(&sr, &keys){
	playing = true;
	resultPos.X = 10;
	resultPos.Y = sr.height-15;
	highscore.readFile("highscore.txt");
}
BullsCows::BullsCows(string file):menues(&sr, &keys), solveres(&sr, &keys){
	playing = true;
	resultPos.X = 10;
	resultPos.Y = sr.height-15;
	highscore.readFile(file.c_str());
}
BullsCows::~BullsCows(){
	highscore.saveFile(highscore.getFileName());
}

int BullsCows::start(){
	while(playing){
		int scores;
		string name; 
		int opt = menu();
		switch(opt){
			case 0:
				solveres.solve();
				break;
			case 1:
				creater();
				break;
			case 2:
				scores = challangeComputer();
				name = whatsYourName(sr, keys);
				if(name != "")
					highscore.addNew(name, scores);
				highscore.saveFile(highscore.getFileName());
			case 3:
				docs();
				break;
			case 4:
				highscore.print(sr);
				sr.render();
				while(keys.getch() != '\n');
				break;
			case 5:
				about();
				break;
			case 6:
				playing = false;
				break;
			default:
				docs();
		} 
	}
	return 0;
}
void BullsCows::docs(){
	sr.clearScreen();
	int i=2;
	sr.printString(sr.width/2 - 44/2,0,"This is a guide to the game \"Bulls and cows\"", RED);
	sr.printString(10, i++,"The Game consist of very simple rules. To guess the secret number.", BLACK);
	sr.printString(10, i++,"Each part in this number is a distinkt number 0-9. You have 10 ", BLACK);
	sr.printString(10, i++,"guesses to guess the number with no time limits.", BLACK);
	i++;
	sr.printString(10, i++,"There are 2 practice modes and one mode to challange the", BLACK);
	sr.printString(10, i++,"computer(that consist of both practice modes). To challange", BLACK);
	sr.printString(10, i++,"the computer you need to get as low scores as possible.", BLACK);
	sr.printString(10, i++,"You get one score/guess and minus one score/computer guess.", BLACK);
 	i++;
	sr.printString(12, i++,"Mode 1, Guess of:", BLUE);
	sr.printString(12, i++,"In this mode you need to ", BLACK);
	sr.printString(12, i++,"guess the number that the", BLACK);
	sr.printString(12, i++,"computer generates", BLACK);
	i -=4;
	sr.printString(45, i++,"Mode 2, Think of:", BLUE);
	sr.printString(45, i++,"In this mode you need to ", BLACK);
	sr.printString(45, i++,"think of a number that the", BLACK);
	sr.printString(45, i++,"computer will guess.", BLACK);
	sr.printString(45, i++,"Then tell the computer ", BLACK);
	sr.printString(45, i++,"how many bulls and cows ", BLACK);
	sr.printString(45, i++,"the number got  in it.", BLACK);
	i++;
	sr.printString(10, i++,"Example: ", GREEN);
	sr.printString(10, i++,"The current number is 1342 and the guess is 3641.", BLACK);
	sr.printString(10, i++,"Then the result/outputs are one bull and two cows.", BLACK);
	sr.printString(10, i++,"And so on untill the number is guessed.", BLACK);
	sr.render();
	keys.getch();
}
void BullsCows::about(){
	int x=1,y=1;
	sr.clearScreen();
	sr.printString(x,y++,"          ____     __  ");
	sr.printString(x,y++,"         |    \\.-``  ) ");
	sr.printString(x,y++,"         |---``\\  _.'  ");
	sr.printString(x,y++,"      .-`'---``_.'     ");
	sr.printString(x,y++,"     (___..--``        ");
	y++;
	sr.printString(x + 25,2,"Programmer/Designer of this game is", BLACK);
	sr.printString(x + 25,3," Johannes Linden.", RED);
	sr.printString(x + 25,4,"johannes.93.1337@gmail.com", BLUE);
	sr.printString(x + 25,5,"http://johannes.pastorn.nu/#Projects", GREEN);
	sr.printString(x + 25,y++,"This source code can be found on github:", BLACK);
	sr.printString(x + 25,y++,"https://github.com/jolin1337", GREEN);
	sr.render();
	keys.getch();
}

int BullsCows::menu(){
	sr.clearScreen();
	menues.logoEnd = logo(sr, sr.width/2-68/2, 2);
	menues.printMenu();
	return menues.menu();
}



int BullsCows::challangeComputer(){
	bool compsTurn = false,
		 whanaPlay = true;
	int scoreU = 0, scoreC = 0,
		turns = 0;
	while(whanaPlay){
		// score presentation
		sr.clearScreen();
		sr.printString(sr.width - 27, resultPos.Y, "Scores:", YELLOW);
		sr.drawRect(sr.width - 28, resultPos.Y+1, 20, 3);
		sr.printString(sr.width - 27, resultPos.Y+2, "Computer: ", YELLOW);
		sr.printString(sr.width - 26, resultPos.Y+3, scoreC, YELLOW);
		sr.printString(sr.width - 14, resultPos.Y+2, "You: ", YELLOW);
		sr.printString(sr.width - 13, resultPos.Y+3, scoreU, YELLOW);
		sr.render();

		// program
		int tscore = 0;
		if(compsTurn){
			tscore = solveres.solve(0, false);
			if(tscore != -1)
				scoreC += tscore;
			else
				scoreU += 5;
		}
		else{
			tscore = creater(false);
			if(tscore != -1)
				scoreU += tscore;
			else
				scoreU += 5;
		}

		turns++;
		if(!whantToContinueChallange(sr, keys))
			whanaPlay = false;
		compsTurn = !compsTurn;
	}
	return (scoreU - turns*5) + scoreC;
}
int BullsCows::creater(bool practice){// default: practice = true
	Gissning random = DistinktNumber::selectDistinkt(rand()%9877 + 50000); // create random number
	int guess = 50000,
		tryes = 10,
		pos = 1000;
	int lnPos = rvlength(pos);
	SR::PIX px;
	px.Char.AsciiChar = 'v';
	if(practice)
		sr.clearScreen();
	drawTable(sr);
	sr.printString(resultPos.X+35, resultPos.Y+3, "Number", CYAN);
	sr.printString(resultPos.X+20, resultPos.Y+7, "You input a guess of the");
	sr.printString(resultPos.X+20, resultPos.Y+8, "generated number by typing");
	sr.printString(resultPos.X+20, resultPos.Y+9, " it in the right box.Use ");
	sr.printString(resultPos.X+20, resultPos.Y+10,"the arrow keys to navigate");
	sr.printString(resultPos.X+20, resultPos.Y+11,"between the numbers.");
	if(practice)
		sr.printString(3, sr.height-3, "Practice guess numbers.", BLACK);
	while(true){

		sr.printString(resultPos.X+35, resultPos.Y+1, guess, CYAN);
		sr.drawRect(resultPos.X+35, resultPos.Y+0, 5, 2);	// används i loopen för att skriva över 5:an i guess

		px.Char.AsciiChar = ' ';
		for(int i=0; i<4; i++)
			sr.setPixel(resultPos.X+39 - i, resultPos.Y -1, &px);
		px.Char.AsciiChar = 'v';
		sr.setPixel(resultPos.X+39 - lnPos, resultPos.Y -1, &px);

		sr.render();
		int num = keys.getch();
		sr.printString(sr.width/2 - 72/2, sr.height - 2, "                                                                        ", GREEN);
		sr.render();
		if(num >='0' && num <='9'){
			guess -= getPos(guess, (4-lnPos), 5)*pos; 	// ränsa positionen pos
			guess += pos*(num-48);						// sätt positionen
			pos = (pos/10);								// deincr pos med 1
			if(pos == 0)
				pos = 1000;
			lnPos = rvlength(pos);	// TODO!!!!
		}
		else if(num == '\n'){
			Gissning o_guess = guess;
			int bc = solveres.BullsCowsContain(&random, &o_guess);
			if(guess == DistinktNumber::selectDistinkt(guess)){				// om bc är ett distinkt nummer
				if(bc%10 == 4){							// bulls is 4
					tryes = 10 - tryes;
					drawSucess(sr,tryes);
					sr.printString(sr.width/2 - 28/2, sr.height - 2, "Press any key to continue...", RED);
					sr.render();
					while(keys.kbhit())keys.getch();
					keys.getch();
					return tryes;
				}
				sr.printString(resultPos.X + 2, resultPos.Y + (10-tryes) +2, guess);
				sr.printString(resultPos.X + 2, resultPos.Y + (10-tryes) +2, " ");		// ta bort 5:an
				sr.printString(resultPos.X + 10, resultPos.Y + (10-tryes) +2, bc%10, GREEN);
				sr.printString(resultPos.X + 12, resultPos.Y + (10-tryes) +2, bc/10, CYAN);
				sr.printString(sr.width/2 - 72/2, sr.height - 2, "HINT: Green clue means count of bulls and blue clue means count of cows.", GREEN);
				sr.render();
				//sr.printString()
				tryes--;
				if(!tryes){
					sr.clearScreen();
					drawSucess(sr,-1);
					sr.printString(sr.width/2 - 28/2, sr.height - 2, "Press any key to continue...", RED);
					sr.render();
					while(keys.kbhit())keys.getch();
					keys.getch();
					if(!practice || !whantToContinueChallange(sr, keys))
						break;
					sr.clearScreen();
					drawTable(sr);
					sr.printString(resultPos.X+35, resultPos.Y+3, "Number", CYAN);
					sr.printString(resultPos.X+20, resultPos.Y+7, "You input a guess of the");
					sr.printString(resultPos.X+20, resultPos.Y+8, "generated number by typing");
					sr.printString(resultPos.X+20, resultPos.Y+9, " it in the right box.Use ");
					sr.printString(resultPos.X+20, resultPos.Y+10,"the arrow keys to navigate");
					sr.printString(resultPos.X+20, resultPos.Y+11,"between the numbers.");

					sr.printString(3, sr.height-3, "Practice guess numbers.", BLACK);
					tryes = 10;
				}
			}
			else{
				sr.printString(sr.width/2 - 46/2, sr.height - 2, "You need to guess a number of distinct numbers", RED);
				sr.render();
			}
		}
		else if(num == 'q' || num == 'Q')
			return -1;
		else{
			string kp;
			kp +=  num;
			while(keys.kbhit())
				kp += keys.getch();
			if(kp == VK_RIGHT){
				pos = (pos/10);								// deincr pos med 1
				if(pos == 0)
					pos = 1000;
				lnPos = rvlength(pos);	// TODO!!!!
			}
			else if(kp == VK_LEFT){
				pos = (pos*10);								// deincr pos med 1
				if(pos == 10000)
					pos = 1;
				lnPos = rvlength(pos);	// TODO!!!!
			}
		}
		Sleep(60);
	}
	return -1;
}
void BullsCows::getMaxT(){
	int max = 0, tal = 0;
	for(DistinktNumber j = 50123; j.getNum() < 59877; j=j+1){
		if(j == -1 )
			break;
		Gissning real(j);
		int tmax = solveres.solve(&real);
		if( tmax> max)
			max = tmax, tal = j;
	}
	cout << "TAL = " << tal << ", MAX = " << max << endl;
}

int BullsCows::length(int n){
	int l=1;
	for(int k = 0; k < n; k++)
		l *= 10;
	return l;
}
int BullsCows::rvlength(int n){
	int i=n, l =0;
	while((i /= 10))
		l++;
	return l;
}
int BullsCows::getPos(int num, int pos, int len){
	pos = len - pos - 1;
	int in=1;
	for(int inj=0;inj<pos;inj++) in*=10;
	return (num%(in*10))/in;
}