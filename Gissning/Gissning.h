#ifndef GISSNING_H
#define GISSNING_H
class Gissning{
	int giss;
	int bulls, cows;
public:
	Gissning():giss(0),bulls(0),cows(0){}
	Gissning(int i):giss(i),bulls(0),cows(0){}
	int length();
	int getPos(int index);
	int operator[](int index);
	operator int(){return giss;}
	int toRes();
	int getGissning(){return giss;}
	void setGissning(int g){giss = g;}
	int getBulls(){return bulls;}
	int getCows(){return cows;}
	void setBullsCows(int b, int c){bulls = b;cows = c;}
};

#endif