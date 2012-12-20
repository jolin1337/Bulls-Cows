#ifndef HIGHTSCORE_H
#define HIGHTSCORE_H
#include <string>
#include <map>
#include <fstream>
#include "Render/ScreenRender.h"
class Highscore{
	// för enkelhetens skull
	typedef std::multimap<int, std::string > Highlist;
	Highlist highscores;	// en lista som alla poäng + namn sparas i
	std::string fileName;	// namnet på filen där listan, highscores, skall sparas
public:
	/*
		void addNew(std::string name, int score);
			lägger till en ny spelare i listan med namnet name
			och poängen score.
	*/
	void addNew(std::string name, int score){
		if(name == "") return;		// om namnet är tomt? ignorera
		for (Highlist::value_type &i: highscores)	// loopa igenom alla i listan
			if(i.second == name)	// om namnet matchar en annan spelare/samma spelare kanske
				highscores.erase(highscores.find(i.first));	// skriv över den spelaren
		highscores.insert(std::pair<int, std::string >(score, name));	// lägg till den nya spelarens namn
	}
	/*
		Highlist::iterator getFirst()
			returnera en iterator till första spelaren med 
			högst poäng
	*/
	Highlist::iterator getFirst(){
		return highscores.begin();	// returnera en iterator till första spelaren med högst poäng
	}
	/*
		Highlist::iterator getLast()
			returnera en iterator till sista spelaren med 
			lägst poäng
	*/
	Highlist::iterator getLast(){
		return highscores.end();	// returnera en iterator till sista spelaren med lägst poäng
	}
	/*
		std::string getFileName()
			returnera fil-namnet där highscorelistan 
			sparas
	*/
	std::string getFileName(){
		return fileName;			// returnera fil-namnet där highscorelistan sparas
	}
	/*
		int readFile(std::string name)
			läser in filen från name i listan highscores
			och returnerar om inläsningen gick bra.
	*/
	int readFile(std::string name){
		highscores.clear();				// räsa tidigare inläsningar
		std::ifstream f(name.c_str());	// öpna filen
		if(!f.good())					// om det inte gick så bra
			return -1;					// avsluta med ett felmedelande
		fileName = name;
		while(!f.eof()){				// så länge det finns info att hämta från filen
			int score;					// poängen variabel
			std::string sname;			// namn variabel

			f >> score;					// läs in poäng från filen
			getline(f, sname);			// läs in rästen av filen som namnet
			if(sname != "")				// om namnet inte är tomt
				addNew(sname, score);	// lägg till den nye spelaren i listan
		}
		f.close();						// stäng filen
		return 0;						// avsluta inläsningen
	}
	/*
		int saveFile(std::string name);
			sparar alla spelare tillbaks i filen
			och returnerar om det gick bra.
	*/
	int saveFile(std::string name){
		fileName = name;
		std::ofstream f(name.c_str());	// öppna filen
		if(!f.good())					// om det inte gick så bra
			return -1;					// avsluta med ett felmedelande
		for (Highlist::value_type &i: highscores)	// loopa igenom alla spelare
			f << i.first << " " << i.second << '\n';	// skriv ut spelarna och poängen med " " som separator
		f.close();						// stäng filen
		return 0;						// svaluta sparningen
	}
	void print(SR::ScreenRender &sr){
		sr.clearScreen();				// ränsa skärmen och bufferten i screenrender
		// hjälphänvisningar om vad som visas i tabellen under resp. column
		sr.printString(10, 2, "Score", BLACK);
		sr.printString(30, 2, "Name", BLACK);
		int j = 0;						// loopa igenom highscore listan
		for(Highlist::iterator i = getFirst(); i != getLast(); i++,j++){
			sr.printString(10, 4 + j, i->first, GREEN);		// skriv ut scoren på positionen j
			sr.printString(30, 4 + j, (i->second).c_str(), BLUE);// skriv ut namnet på positionen j
		}
	}
};
#endif