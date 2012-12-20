#ifndef BULLSCOWS_H
#define BULLSCOWS_H

#include "Render/ScreenRender.h"	// används för den grafiska stylen(okomenterad p.g.a att det inte tillhör uppgiften)
#include "Gissning/Gissning.h"		// en class av en gissning
#include "Menu/Menu.h"				// classen som hanterar menyval från användaren
#include "Solver.h"					//! ett minispel av två
#include "Highscore.h"				// hantering av poäng från/till användarna som har spelat spelet tidigare
#include <iostream>
#include <vector>

class BullsCows {
public:
	COORD resultPos;				// ett X och Y värde för positionen av tabellen som visar gissning, bulls och cows
	BullsCows();					// construktorn för spelet
	BullsCows(std::string name);	// construktorn med highscore filnamnet som parameter till spelet
	~BullsCows();					// destruktorn för spelet

	/*
		int start();
			spelets huvudfunktion/ när denna funktionen är 
			klar har spelet slutat. 
			returvärdet är 0 i alla fallen.
	*/
	int start();
	/*
		void doStats();
			denna funktionen beräknar vilket tal som tar längst 
			tid för datorn att fixa. Desutom för den statistik 
			på hur många gissningar datiorn beöver för övriga 
			gissningar också.
	*/
	int doStats(std::string toFile = "");
private:
	bool playing;					// avgör om spelet fortfarande är igång
	SR::ScreenRender sr;			// kontroll object för utskrift på skärm
	keyboard keys;					// input hantering av events och annat
	Menu menues;					// menyobjekt av programmet
	Solver solveres;				// presentation av minispelet där datorn gissar användarens tal
	Highscore highscore;			// highscore hantering

	/*
		void docs();
			Visar hur man spelar bulls and cows
	*/
	void docs();
	/*
		void about();
			Visar vem johannes linden är....
	*/
	void about();

	typedef std::vector<Gissning > G;//en mängd av gissningar G={gi, ai}, där gi är gissningen och ai är antal bulls och cows i gissningen.

	/*
		int length(int n);
			returnerar antal gånger n går att dividera på 10.
	*/
	int length(int n);
	/*
		int getPos(int num, int pos, int len);
			returnerar ett nummer mellan 0 och 9 som finns på
			positionen pos i num. då num har längden len dvs 
			length(num).
	*/
	int getPos(int &num, int pos, int &len);

	/*
		int challangeComputer();
			denna funktionen är utmaningen där användaren har
			chans att samla ihop poäng och sätta sitt namn på 
			highscorelistan. denna utmaning består av två min-
			spel(dvs Solver och Creater).
	*/
	int challangeComputer();
	/*
		int creater(bool practice = true);
			denna funktionen är en representation av minispelet
			där användaren gissar ett tal och datorn svarar med
			antal bulls och cows från ett tal som datorn har
			genererat. practice avgör om vi är inne i challange 
			mode eller ej.
			returvärdet är antalet poäng användaren har fått under spelomgången
	*/
	int creater(bool practice = true);
};

#endif