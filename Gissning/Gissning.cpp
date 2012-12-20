#include "Gissning.h"
#include <stdexcept>

int Gissning::length(){
	if (giss < 0) 				// om gissning har satts till ett negativt tal
		giss *=-1;				// invertera talet
	int num = giss, 			// copierar giss till num för operationer inte skall påverka giss
		l = 0;					// längden på giss
	while (num) {				// så länge num inte är 0
		num /= 10;
		l++;					// ökar längden med 1
	}
	return l;					// returnerar längden på giss
}

int Gissning::getPos(int index){
	index = length() - index -1;// inverterar positionen eftersom ett tal räknas från höger till vänster som inte indexering gör
								// -1 för att ignorera första talet så att 0 kan vara den första positionen
	int l=1;					// längden på giss l
	for(int j=0;j<index;j++) 	// loopa igenom tills vi hittar indexet index
		l*=10;

	return (giss%(l*10))/l;		// returnera positionen index
}
int Gissning::operator[](int index){
								// en check för att index med säkerhet skall vara inom spanet 0 - length()
	if(!(index < 0 || index > length()))
		return getPos(index);	// returnerar positionen
	else						// kasta ett felmedelande
		throw std::out_of_range("Index ot of range on giss.");
}


int Gissning::toRes(){
	return cows*10 + bulls;	// returnera cows*10 + bulls
}