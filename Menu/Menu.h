#ifndef MENU_H
#define MENU_H
#include <string>
#include "../Render/ScreenRender.h"
class Menu{
	int current,						// nuvarande position i menyn
		maxLength;						// längden på det längsta strängen av menyalternativen
	SR::ScreenRender *sr;				// pekare till ett screenrender object
	keyboard *keys;						// pekare till ett tangentbords object

	int mnitemLength, 					// antal menyalternativ
		startitem;						// beskriver avståndet från loggans slut till menyn ska börga
public:
	int logoEnd;						// beskriver när loggan tar slut
	Menu(SR::ScreenRender *sr, keyboard *keys){
		current = 0; maxLength = 0; logoEnd = 0;
		mnitemLength = 7;
		startitem = 2;
		this->sr = sr;					// sätt sr att peka på nuvarande screenrender
		this->keys = keys;				// sätt keys att peka på nuvarande "tangentbordshanterare"
		sr->clearScreen();				// resna skärmen
	}
	~Menu(){
		sr->clearScreen();				// rensa skärmen
	}
	/*
		int menu();
			huvufunktionen för att välja ett menyval
			Returnerar vilket val man har gjort
	*/
	int menu();
	/*
		int next();
			välj nästa menyval 
			returnerar nuvarande menyval
	*/
	int next();
	/*
		int previous();
			välj föregående menyval
			returnerar nuvarande menyval
	*/
	int previous();
	/*
		void printCurrent();
			skriver ut markören för nuvarande
			menyval
	*/
	void printCurrent();
	/*
		void printMenu();
			skriver ut övrig info som menytext
			osv till användaren
	*/
	void printMenu();
};
#endif