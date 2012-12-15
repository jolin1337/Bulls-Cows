#include "ScreenRender.h"
#include <sstream>
#ifndef _WIN32
#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>
#endif
namespace SR{

#ifdef _WIN32
	void ScreenRender::clearScreen(){ 
		PIX p;
		p.Char.AsciiChar = ' ';
		p.Attributes = BLACK;
		for(int i=0; i<height;i++)
			for(int j=0;j < width; j++)
				setPixel(j,i,&p);
	}
#else
	void ScreenRender::clearScreen() {
		PIX p;
		p.Char.AsciiChar = ' ';
		p.Attributes = BLACK;
		for(int i=0; i<height;i++)
			for(int j=0;j < width; j++)
				setPixel(j,i,&p);
		std::cout << "\033[2J\033[1;1H";
	}
#endif

	ScreenRender::ScreenRender(void) {
		 COLURS[0] = BLACK;
		 COLURS[1] = RED;
		 COLURS[2] = GREEN;
		 COLURS[3] = YELLOW;
		 COLURS[4] = BLUE;
		 COLURS[5] = MAGENTA;
		 COLURS[6] = CYAN;
		 COLURS[7] = WHITE;
#ifdef TIOCGSIZE
		struct ttysize ts;
		ioctl(STDIN_FILENO, TIOCGSIZE, &ts);
		width = ts.ts_cols;
		height = ts.ts_lines;
#elif defined(TIOCGWINSZ)
		struct winsize ts;
		ioctl(STDIN_FILENO, TIOCGWINSZ, &ts);
		width = ts.ws_col;
		height = ts.ws_row;
#else
		console = GetStdHandle(STD_OUTPUT_HANDLE);
		CONSOLE_SCREEN_BUFFER_INFO csbi;
	
	
		//SetConsoleDisplayMode(console, CONSOLE_FULLSCREEN_MODE, NULL);
		//SetWindowLong(GetConsoleWindow(), 0, WS_EX_WINDOWEDGE);

		GetConsoleScreenBufferInfo(console, &csbi);
		width = 1 + csbi.srWindow.Right - csbi.srWindow.Left;
		height = csbi.srWindow.Bottom - csbi.srWindow.Top;
#endif 
/* TIOCGSIZE */

		// reading console screen
		dwBufferSize.X = width;
		dwBufferSize.Y = height; 
		dwBufferCoord.X = 0;
		dwBufferCoord.Y = 0; 
		rcRegion.Left = 0;
		rcRegion.Right = width-1;
		rcRegion.Top = 0;
		rcRegion.Bottom = height-1; 

		//ReadConsoleOutput( console, (PCHAR_INFO)buffer, dwBufferSize, dwBufferCoord, &rcRegion ); 
		PIX color;
		color.Char.AsciiChar = ' ';
		color.Attributes = BLACK;
		/*
		buffer = new PIX*[height];
		for(int i=0;i<height;i++)
			buffer[i] = new PIX[width];
		*/
		for(int i=0;i<height;i++)
			for(int j=0;j<width;j++){
				buffer[i][j].Char.UnicodeChar = ' ';
				buffer[i][j].Attributes = YELLOW;
			}
	}
	int ScreenRender::setPixel(int x, int y, PIX *c){
		int ret = 0;
		if( x < 0 || y < 0 || x > width || y > height )	// out of bounds
			return -1;
		if( c!= 0 ){
			buffer[y][x].Attributes = c->Attributes;
			buffer[y][x].Char.AsciiChar = c->Char.AsciiChar;
		}
		else{
			buffer[y][x].Attributes = BLUE;
			buffer[y][x].Char.AsciiChar = '0';
		}
		return ret;
	}
	int ScreenRender::printString(int x, int y, const char *str, COLOR_TYPE color){ // color == BLUE
		for(int i=0; str[i] != '\0';i++){
			buffer[y][(x + i)%width].Char.AsciiChar = str[i];
			buffer[y][(x + i)%width].Attributes = color;
		}
		return  0;
	}
	int ScreenRender::printString(int x, int y, const int integ, COLOR_TYPE color){ // color == BLUE
		std::stringstream s;
		s << integ;
		printString(x, y, s.str().c_str(), color);
		return  0;
	}

	int ScreenRender::fillRect(int x, int y, int w, int h, char c, COLOR_TYPE color){
		PIX blank;
		blank.Char.AsciiChar = c;
		blank.Attributes = color;
		for(int i=y; i < y + h; i++)
			for(int j = x; j < x + w; j++)
				setPixel(j,i, &blank);
		return 0;
	}
	int ScreenRender::drawRect(int x, int y, int w, int h, char c, COLOR_TYPE color){
		PIX blank;
		if(c == 'a')
			blank.Char.AsciiChar = '|';
		else
			blank.Char.AsciiChar = c;
		blank.Attributes = color;
		for(int i=y + 1; i < y + h; i++){
			setPixel(x,i, &blank);
			setPixel(x + w,i, &blank);
		}
		if(c == 'a')
			blank.Char.AsciiChar = '-';
		for(int i=x; i <= x + w; i++){
			setPixel(i,y, &blank);
			setPixel(i,y + h, &blank);
		}
		if(c == 'a'){
			blank.Char.AsciiChar = '+';
			setPixel(x, y, &blank);
			setPixel(x, y+h, &blank);
			setPixel(x+w, y+h, &blank);
			setPixel(x+w, y, &blank);
		}
		return 0;
	}

	int ScreenRender::render(){
#ifdef _WIN32
		WriteConsoleOutput( console, (CHAR_INFO *)buffer, dwBufferSize, dwBufferCoord, &rcRegion ); 
#else
		for(int i=0; i < height-1; i++){
			for (int j = 0; j < width; j++){
				std::cout << buffer[i][j].Attributes <<
							buffer[i][j].Char.AsciiChar;
			}
			std::cout << std::endl;
		}
#endif
		return 0;
	}


	ScreenRender::~ScreenRender() {
		std::cout << "\033[30m" << std::endl;
		/*for(int i=0; i< height; i++)
			delete [] buffer[i];
		delete []buffer;*/
	}
}
