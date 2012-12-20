#include "BullsCows.h" 
#include "DistinktNumber/DistinktNumber.h"
#include "header.h"
using namespace std;
using SR::ScreenRender;

BullsCows::BullsCows():menues(&sr, &keys), solveres(&sr, &keys){
	playing = true;									// så länge spelet håller igång är denna true, så nu startas spelt
	resultPos.X = 10;								// tabellen börgar på X=10
	resultPos.Y = sr.height-15;						// Y = 100%-15rows
	highscore.readFile("highscore.txt");			// initiera highscore listan
}
BullsCows::BullsCows(string file):menues(&sr, &keys), solveres(&sr, &keys){
	playing = true;									// så länge spelet håller igång är denna true, så nu startas spelt
	resultPos.X = 10;								// tabellen börgar på X=10
	resultPos.Y = sr.height-15;						// Y = 100%-15rows
	highscore.readFile(file.c_str());				// initiera highscore listan
}
BullsCows::~BullsCows(){
	highscore.saveFile(highscore.getFileName());	// spara tillbaks highscore listan när programmet avslutas
}

int BullsCows::start(){
	while(playing){									// main-loop
		int scores;									// antal poäng för nuvarande spelare
		string name; 								// namnet för nuvarande spelare

		sr.clearScreen();							// ränsa skärmen
		
		menues.logoEnd = logo(sr, sr.width/2-68/2, 2);// skriv ut loggan och skicka värdet till menyn så att den skrivs ut på rätt position
		menues.printMenu();							// skriv ut menyrubrikerna
		int opt = menues.menu();					// starta interaktion med användaren 
		switch(opt){								// vad har användaren valt?
			case 0:									// Start Think of
				solveres.solve();					//   starta minispelet solver
				break;
			case 1:									// Start Guess of
				creater();							//   starta minispelet creater
				break;
			case 2:									// Challange computer
				scores = challangeComputer();		//   starta utmaningen för datorn
													//   spara poängen från spelet i score
				name = whatsYourName(sr, keys);		//   ta reda på namnet på den som spelat
				if(name != "")						//   om namnet inte är tomt
					highscore.addNew(name, scores);	//   spara spelaren

													//   spara spelaren, för säkerhetens skull
				highscore.saveFile(highscore.getFileName());
			case 3:									// Instructions
				docs();								//   visa hur man spelar Bulls and Cows spelet
				break;
			case 4:									// Hightscore
				highscore.print(sr);				//   visa highscore listan i screenbuffern
				sr.render();						//   skriv ut highscore listan på skärment
				while(keys.getch() != '\n');		//   vänta på användaren trycker enter/retur tangenten
				break;
			case 5:									// About
				about();							//   visa vem som är awsome och har programmerat detta program
				break;
			case 6:									// Exit
				playing = false;					//   stäng programmet
				break;
			default:								// ett okänt returvärde från användaren....
				docs();								//   vi visar då docs
		} 
	}
	return 0;
}
void BullsCows::docs(){
	sr.clearScreen();								// ränsa bufferten i ScreenRender och ränsa skärmen
	int i=2;										// deklarera i som definerar vilken rad som skall skrivas
		// skriv ut förklarande text på vad spelet går ut på och vad det är för spel.
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
	int x=1,								// låt x och y definera vilken position som
		y=1;								// texten skall skrivas ut på.
	sr.clearScreen();
	sr.printString(x,y++,"          ____     __  ");
	sr.printString(x,y++,"         |    \\.-``  ) ");
	sr.printString(x,y++,"         |---``\\  _.'  ");
	sr.printString(x,y++,"      .-`'---``_.'     ");
	sr.printString(x,y++,"     (___..--``        ");
	y++; x += 25;
	sr.printString(x,2,"Programmer/Designer of this game is", BLACK);
	sr.printString(x,3," Johannes Linden.", RED);
	sr.printString(x,4,"johannes.93.1337@gmail.com", BLUE);
	sr.printString(x,5,"http://johannes.pastorn.nu/#Projects", GREEN);
	sr.printString(x,y++,"This source code can be found on github:", BLACK);
	sr.printString(x,y++,"https://github.com/jolin1337", GREEN);
	sr.render();							// visa för användaren
	keys.getch();							// vänta på vilken knappnedtryckning som helst
}




int BullsCows::challangeComputer(){
	bool compsTurn = false,					// avgör vem det är som skall gissa
		 whanaPlay = true;					// avgör hur länge användaren vill spela
	int scoreU = 0, 						// poängen för användaren
		scoreC = 0,							// poängen för datorn
		turns = 0;							// antal rundor som har körts
	while(whanaPlay){						// så länge spelaren vill spela
		sr.clearScreen();					// ränsa skärmen och bufferten i ScreenRender
	

			// skriv ut poäng för spelarna
		sr.printString(sr.width - 27, resultPos.Y, "Scores:", YELLOW);
		sr.drawRect(sr.width - 28, resultPos.Y+1, 20, 3);
		sr.printString(sr.width - 27, resultPos.Y+2, "Computer: ", YELLOW);
		sr.printString(sr.width - 26, resultPos.Y+3, scoreC, YELLOW);
		sr.printString(sr.width - 14, resultPos.Y+2, "You: ", YELLOW);
		sr.printString(sr.width - 13, resultPos.Y+3, scoreU, YELLOW);
		sr.render();

			// program
		int tscore = 0; 					// temporär variabel för poängen
		if(compsTurn){						// om det är datorns tur att gissa?
			tscore = solveres.solve(0, false);// kör igång minigame: Solver
			if(tscore != -1)				// om datorn löste pusslet
				scoreC += tscore;			// datorn får poäng
			else
				scoreU += 5;				// annars ger vi användaren poäng för fel inmatning
		}
		else{								// om det är användarens tur att gissa?
			tscore = creater(false);		// kör igång minigame: Solver
			if(tscore != -1)				// om användaren inte lyckades gissa numret
				scoreU += tscore;			// användaren får poäng
			else
				scoreU += 5;				// annars ger vi anändaren 5 extra poäng
		}

		turns++;							// öka till nästa runda vi spelar.
		if(!whantToContinueChallange(sr, keys))// ska de spelas igen?
			whanaPlay = false;				// om inte så sätts whanaPlay till false
		compsTurn = !compsTurn;				// byt turer om vem som skall gissa
	}

	// returnera antal poäng användaren är värd
	return (scoreU - turns*5) + scoreC;
}
int BullsCows::creater(bool practice){// default: practice = true
	Gissning random = DistinktNumber::selectDistinkt(rand()%9877 + 50000); // create random number
	int guess = 50000,						// användarens gissning
		tryes = 10,							// antal försök som användaren får
		pos = 1000;							// positionen som användaren kan ändra på vid nästa input
	int lnPos = length(pos);				// längden på pos, dvs 4
	SR::PIX px;								// en ScreenRender class för att skriva ut en punkt i förnstret
	px.Char.AsciiChar = 'v';				// v är tecknet som skrivs ut. i PIX objectet
	if(practice)							// om det är practice mode så vill vi ränsa skärmen nu
		sr.clearScreen();					// ränsa skärmnen
	drawTable(sr);							// skriv ut strukturen av tabellen för gissning och resultat(bc)

		// en beskrivning om vad som förväntas av användaren
	sr.printString(resultPos.X+35, resultPos.Y+3, "Number", CYAN);
	sr.printString(resultPos.X+20, resultPos.Y+7, "You input a guess of the");
	sr.printString(resultPos.X+20, resultPos.Y+8, "generated number by typing");
	sr.printString(resultPos.X+20, resultPos.Y+9, " it in the right box.Use ");
	sr.printString(resultPos.X+20, resultPos.Y+10,"the arrow keys to navigate");
	sr.printString(resultPos.X+20, resultPos.Y+11,"between the numbers.");
	if(practice)							// om det är practice mode så säger vi det till användaren också
		sr.printString(3, sr.height-3, "Practice guess numbers.", BLACK);
	while(true){							// tills användaren har gissat tryes gånger eller gissat rätt.
			// skriv ut gissningen som användaren nuvarande vill gissa på
		sr.printString(resultPos.X+35, resultPos.Y+1, guess, CYAN);

															// skriv en fyrkant runt gissningen
		sr.drawRect(resultPos.X+35, resultPos.Y+0, 5, 2);	// används i loopen för att skriva över 5:an i guess

			// rensa positionen av pilen v 
		sr.printString(resultPos.X+36, resultPos.Y -1, "    ");
			// skriv pilen v igen på rätt position
		px.Char.AsciiChar = 'v';
		sr.setPixel(resultPos.X+39 - lnPos, resultPos.Y -1, &px);
		sr.render();										// visa på skärmen

		int num = keys.getch();								// vänta på input från användaren

		// rensa statusbaren
		sr.printString(sr.width/2 - 72/2, sr.height - 2, "                                                                        ", GREEN);
		sr.render();										// visa på skärmen
		if(num >='0' && num <='9'){						// om num är ett nummer
			guess -= getPos(guess, (4-lnPos), 5)*pos; 	// rensa positionen pos från guess
			guess += pos*(num-48);						// sätt positionen	pos från guess
			pos = (pos/10);								// minska positionen med 1
			if(pos == 0)								// om positionen inte går att minska längre
				pos = 1000;								// resetta positionen till 1000;
			lnPos = length(pos);						// längden av pos 
		}
		else if(num == '\n'){							// om num är enter/retur tangenten
			Gissning o_guess = guess;					// convertera gissningen till ett object Gissning
			// bc får antal bulls och cows i random och o_guess.
			int bc = solveres.BullsCowsContain(&random, &o_guess);
			if(guess == DistinktNumber::selectDistinkt(guess)){	// om bc är ett distinkt nummer
				if(bc%10 == 4){							// om bulls är 4
					tryes = 10 - tryes;					// omvandla tryes till antal försök som har gjorts
					drawSucess(sr,tryes);				// skriv ett medelande till användaren om att den har lyckats
					sr.printString(sr.width/2 - 28/2, sr.height - 2, "Press any key to continue...", RED);
					sr.render();						// visa på skärmen
					while(keys.kbhit())keys.getch();	// rensa bufferten
					keys.getch();						// vänta på en knapptryckning 
					return tryes;						// returnera "poängen"
				}

				sr.printString(resultPos.X + 2, resultPos.Y + (10-tryes) +2, guess);		// skriv ut gissningen 
				sr.printString(resultPos.X + 2, resultPos.Y + (10-tryes) +2, " ");			// ta bort 5:an
				sr.printString(resultPos.X + 10, resultPos.Y + (10-tryes) +2, bc%10, GREEN);// skriv ut bulls
				sr.printString(resultPos.X + 12, resultPos.Y + (10-tryes) +2, bc/10, CYAN);	// skriv ut cows
				// skriv ut en hint om vad som är bulls och cows
				sr.printString(sr.width/2 - 72/2, sr.height - 2, "HINT: Green clue means count of bulls and blue clue means count of cows.", GREEN);
				sr.render();								// visa på skärmen

				tryes--;									// minska antal försök med 1
				if(!tryes){									// om det inte är några försök kvar
					sr.clearScreen();						// rensa skärmen och bufferten i ScreenRender
					drawSucess(sr,-1);						// visa ett medelande för användaren, att den har förlorat
					sr.printString(sr.width/2 - 28/2, sr.height - 2, "Press any key to continue...", RED);
					sr.render();							// visa på skärmen
					while(keys.kbhit())keys.getch();		// rensa alla lagrade tangentnedtryckningar
					keys.getch();							// vänta på en knapptryckning från användaren
					if(!practice || !whantToContinueChallange(sr, keys))	// om det är en utmaning med datorn eller användaren inte vill spela igen
						break;
					sr.clearScreen();						// rensa skärmen
					drawTable(sr);							// skriv ut strukturen för tabellen med gissningar, bulls och cows
						// en beskrivning om vad som förväntas av användaren
					sr.printString(resultPos.X+35, resultPos.Y+3, "Number", CYAN);
					sr.printString(resultPos.X+20, resultPos.Y+7, "You input a guess of the");
					sr.printString(resultPos.X+20, resultPos.Y+8, "generated number by typing");
					sr.printString(resultPos.X+20, resultPos.Y+9, " it in the right box.Use ");
					sr.printString(resultPos.X+20, resultPos.Y+10,"the arrow keys to navigate");
					sr.printString(resultPos.X+20, resultPos.Y+11,"between the numbers.");
						// eftersom det är garanterat att det inte är en challange så skriver vi ut att det är practice
					sr.printString(3, sr.height-3, "Practice guess numbers.", BLACK);
					tryes = 10;								// resetta anta försök
				}
			}
			else{
						// när det inte är ett distinkt numer så skriver vi ut att det inte är ett distinkt nummer
				sr.printString(sr.width/2 - 46/2, sr.height - 2, "You need to guess a number of distinct numbers", RED);
				sr.render();								// visa på skärmen
			}
		}
		else if(num == 'q' || num == 'Q')					// om användaren avbryter spelomgången med q tangenten
			return -1;
		else{
			// för att samla ihop all tillgängnlig data så att det går att avgöra om det är en 
			string kp;
			kp +=  num;										// lägg till det inlästa värdet i kp
			while(keys.kbhit())								// läs in alla knapptryckningar som finns i bufferten för termios
				kp += keys.getch();							// lägg de inlästa värdena i kp
			if(kp == VK_RIGHT){								// om de inlästa värdena matchar värdet för höger tangenten
				pos = (pos/10);								// minska pos positionen med 1
				if(pos == 0)								// om det inte går att minska mera
					pos = 1000;								// sätt positionen till max igen
				lnPos = length(pos);						// längden på positionen pos 
			}
			else if(kp == VK_LEFT){							// om de inlästa värdena matchar värdet för vänster tangenten
				pos = (pos*10);								// öka positionen pos med 1
				if(pos == 10000)							// om det inte ska gå att öka pos med 1
					pos = 1;								// sätt pos till det minsta talet igen
				lnPos = length(pos);						// längden på positionen pos
			}
		}
		Sleep(60);											// vänta 60ms för att förhindra seg updatering
	}
	return -1;
}
int BullsCows::doStats(string toFile){
	int max = 0, 											//
		tal = 0;
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
	int i=n, 												// sätt i till talet som ska valideras
		l =0;												// l kommer att bli längden av l
	while((i /= 10))										// så länge som i är mer än 0
		l++;												// öka längden l med 1
	return l;												// returnera längden
}
int BullsCows::getPos(int &num, int pos, int &len){
	pos = len - pos - 1;									// positionen inverteras eftersom talet räknas från höger till vänster
															// -1 är bara där för att talet börgar med ett tal som inte skall finnas med i talet
	int in=1;												// vilket tal representerar positionen
	for(int inj=0;inj<pos;inj++) in*=10;					// in representerar nu positionen för pos
	return (num%(in*10))/in;								// returnerar värdet för positionen pos.
}