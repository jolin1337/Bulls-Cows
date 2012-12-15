#ifndef SOLVER_H
#define SOLVER_H
#include "Render/ScreenRender.h"
#include "DistinktNumber/DistinktNumber.h"
#include "Gissning/Gissning.h"
class Solver{
public:
	COORD resultPos;
	Solver(SR::ScreenRender *sr, keyboard *key){
		this->sr = sr;
		this->keys = key;
		resultPos.X = 10;
		resultPos.Y = sr->height-15;
	}

	int solve(Gissning *real=0, bool practice=true);
	int BullsCowsContain(Gissning *x, Gissning *y);
private:
	typedef std::vector<Gissning > G;
	keyboard *keys;
	SR::ScreenRender *sr;
	bool goodGuess(Gissning gv, G *g);
	int generateGuess(G *g);
	bool input(Gissning *gi);
};

#endif