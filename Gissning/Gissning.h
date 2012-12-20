#ifndef GISSNING_H
#define GISSNING_H
class Gissning{
	int giss;				// gissningen av classen
	int bulls, 				// antal bulls för gissningen
		cows;				// antal cows för gissningen
public:
	// construktorn för Gissning för initering av variabler
	Gissning():giss(0),bulls(0),cows(0){}
	Gissning(int i):giss(i),bulls(0),cows(0){}

	/*
		int length();
			returnerar antal gånger gissningen går 
			att dividera på 10. dvs längden på giss.
	*/
	int length();
	
	/*
		int getPos(int index);
			returnerar ett nummer mellan 0 och 9 som finns på
			positionen pos i giss.
	*/
	int getPos(int index);
	/*
		int operator[](int index);
			samma som getPos fast med ett säkerhets-vilkor som
			kastar felet std::out_of_range.
	*/
	int operator[](int index);
	/*
		operator int();
			returnerar giss vilket gör det möjlig att använda 
			classen som en integer
	*/
	operator int(){return giss;}
	/*
		int toRes();
			returnerar bulls och cows
	*/
	int toRes();

	/*
		int getGissning();
			returnerar giss dvs gissningen för objectet.
	*/
	int getGissning(){return giss;}
	/*
		void setGissning(int g);
			sätter gissningen till g
	*/
	void setGissning(int g){giss = g;}
	/*
		int getBulls();
			returnerar bulls
	*/
	int getBulls(){return bulls;}
	/*
		int getCows();
			returnerar cows
	*/
	int getCows(){return cows;}
	/*
		void setBullsCows(int b, int c);
			sätter bulls till b och cows till c
	*/
	void setBullsCows(int b, int c){bulls = b;cows = c;}
};

#endif