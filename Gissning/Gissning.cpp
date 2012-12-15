#include "Gissning.h"
#include <stdexcept>

int Gissning::length(){
	if (giss < 0) 
		giss *=-1;
	int num = giss, 
		l = 0;
	while (num) {
		num /= 10;
		l++;
	}
	return l;
}

int Gissning::getPos(int index){
	index = length() - index -1;
	int l=1;
	for(int j=0;j<index;j++) 
		l*=10;

	return (giss%(l*10))/l;
}
int Gissning::operator[](int index){
	if(!(index < 0 || index > length()))
		return getPos(index);
	else
		throw std::out_of_range("Index ot of range.");
}


int Gissning::toRes(){
	return cows*10 + bulls;
}