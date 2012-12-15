#ifndef HIGHTSCORE_H
#define HIGHTSCORE_H
#include <string>
#include <map>
#include <fstream>
#include "Render/ScreenRender.h"
class Highscore{
	typedef std::multimap<int, std::string > Highlist;
	Highlist highscores;
	std::string fileName;
public:
	void addNew(std::string name, int score){
		if(name == "") return;
		for (Highlist::value_type &i: highscores)
			if(i.second == name)
				highscores.erase(highscores.find(i.first));
		highscores.insert(std::pair<int, std::string >(score, name));
	}
	Highlist::iterator getFirst(){
		return highscores.begin();
	}
	Highlist::iterator getLast(){
		return highscores.end();
	}
	std::string getFileName(){
		return fileName;
	}
	int readFile(std::string name){
		highscores.clear();
		std::ifstream f(name.c_str());
		if(!f.good())
			return -1;
		fileName = name;
		while(!f.eof()){
			int score;
			std::string sname;

			f >> score;
			getline(f, sname);
			if(sname != "")
				addNew(sname, score);
		}
		f.close();
		return 0;
	}
	int saveFile(std::string name){
		fileName = name;
		std::ofstream f(name.c_str());
		for (Highlist::value_type &i: highscores)
			f << i.first << " " << i.second << '\n';
		f.close();
		return 0;
	}
	void print(SR::ScreenRender &sr){
		sr.clearScreen();
		sr.printString(10, 2, "Score", BLACK);
		sr.printString(30, 2, "Name", BLACK);
		int j = 0;
		for(Highlist::iterator i = getFirst(); i != getLast(); i++,j++){
			sr.printString(10, 4 + j, i->first, GREEN);
			sr.printString(30, 4 + j, (i->second).c_str(), BLUE);
		}
	}
};
#endif