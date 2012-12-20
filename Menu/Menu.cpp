#include "Menu.h"
int Menu::menu(){
	while(true){				// så länge användaren inte har gjort ett menyval
		printCurrent();			// skriv ut markören
		int inp = keys->getch();// vänta på inputs
		if(inp == '\n')			// om det är enter/retur knappen 
			return current;		// användaren har valt current menyalternativ
		else if(inp == 'q' || inp == 'Q')// om det är q tangenten så avslutas programmet
			return 6;
		else{					// anars läser vi in hela bufferten ...
			std::string kb = "";
			kb += inp;			// lägger till den föregående inläsningen
			//if(keys.kbhit())
			while(keys->kbhit())// så länge det finns kvar info att läsa
				kb += keys->getch();//lägg till i kb
			if( kb == VK_UP || kb == VK_DOWN){// om det är upp eller nertangenten
				int dir = (kb[kb.length()-1]) - 'A';// avgör vilken av tangenterna det är
				if(dir)							// om det är ner pilen
					next();						// gå ett steg framot i menyn
				else
					previous();					// annars gå ett steg bakot i menyn
			}
		}
	}
	return current;// kommer aldrig hit
}

int Menu::next(){
	current++;					// öka till nästa menyalternativ
	current %= mnitemLength;	// om alternativet är mer än antal menyenheter börga och räkna från börgan
	return current;				// returnera nuvarande menyalternativ
}
int Menu::previous(){
	current--;					// minska till föregående menyalternativ
	if(current <0)				// om alternativet är mindre än 0
		current += mnitemLength;// börga från max alternativen
	return current;				// returnera nuvarande menyalternativ
}

void Menu::printCurrent(){
	for(int j = 0; j<mnitemLength;j++)	//loopa igenom alla möjliga platser för pilen och ränsa de föregående pilutskriften
		sr->printString(sr->width/2-maxLength/2-3, (j)*2 + logoEnd + startitem, " ");
	// skriv ut nuvarande menyitem
	sr->printString(sr->width/2-maxLength/2-3, current*2 + logoEnd + startitem, ">", GREEN);
	sr->render();			// visa på skärmen
}

void Menu::printMenu(){
	// alla items som finns i menyn
	std::string mnitem[] = {"Start Think of", "Start Guess of", "Challange computer", "Instructions", "Hightscore", "About", "Exit"};
	for(int j = 0; j<mnitemLength;j++){	// loopa igenom items för utskrift.
		int ln = (mnitem[j]).length();	// ln blir längden på nuvarande item
		// skriv ut nuvarande item
		this->sr->printString(this->sr->width/2 - ln/2, j*2 + logoEnd + startitem, (mnitem[j]).c_str(), MAGENTA);
		if(ln > maxLength)	// om längden är mer än maxLength
			maxLength = ln;	// maxlength borde vara den nya maxlängden
	}
}