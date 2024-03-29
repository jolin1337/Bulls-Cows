#ifndef HEADER_H
#define HEADER_H
#include "Render/ScreenRender.h"
#include <string>

/*
	int logo(SR::ScreenRender &sr, int x = 0, int y = 0);
		skriv ut loggan Bulls and Cows på positionen x,y
		med det activa screenrender objectet sr
*/
int logo(SR::ScreenRender &sr, int x = 0, int y = 0);

/*
	void drawTable(SR::ScreenRender &sr);
		skriver ut strukturen i tabellen med
		sr reference.
*/
void drawTable(SR::ScreenRender &sr);
void drawSucess(SR::ScreenRender &sr, int tryes);

bool whantToContinueChallange(SR::ScreenRender &sr, keyboard &keys);
std::string whatsYourName(SR::ScreenRender &sr, keyboard &keys);

#endif