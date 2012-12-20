/********************************
	
	 ____        _ _                       _    _____                  
	|  _ \      | | |                     | |  / ____|                 
	| |_) |_   _| | |___    __ _ _ __   __| | | |     _____      _____ 
	|  _ <| | | | | / __|  / _` | '_ \ / _` | | |    / _ \ \ /\ / / __|
	| |_) | |_| | | \__ \ | (_| | | | | (_| | | |___| (_) \ V  V /\__ \
	|____/ \__,_|_|_|___/  \__,_|_| |_|\__,_|  \_____\___/ \_/\_/ |___/
	Skapad av: Johannes Lindén

	Projekt i programmering för studier i C++, 
	syftet är att lära sig programmera och 
	framför allt bli en bättre programmerare.

*********************************/
#include "BullsCows.h"	// Includera spelets classer och funktioner

int main(int argc, char const *argv[]) {
	BullsCows bc;									// skapa spelobjectet
	if(argc >= 3 && (std::string)(argv[1]) == "-f")	// om vi ska skriva till en speciell highscore fil
		bc = BullsCows(argv[2]);					// skapa spelobjectet med den filen istället
	if(argc >= 3 && (std::string)(argv[1]) == "doStats")
		return bc.doStats();
	return bc.start();								// starta spelet
}