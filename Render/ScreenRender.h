#ifndef __SR__
#define __SR__

#ifdef _WIN32
#include <Windows.h>
#define BLACK 	0
#define BLUE 	9
#define GREEN 	10
#define CYAN	11
#define RED 	12
#define MAGENTA	13
#define YELLOW 	14
#define WHITE	15
#define COLOR_LENGTH 8
#else
#include "Linux.h"
#endif

#include <iostream>
#include <string>
#include <vector>
namespace SR{
	using std::vector;
	
#ifdef _WIN32
	typedef int COLOR_TYPE;
	#else
	typedef std::string COLOR_TYPE;
#endif
	typedef struct _PIX { 
		union { // Unicode or ANSI character 
			WCHAR UnicodeChar; 
			CHAR AsciiChar; 
		} Char; 
#ifdef _WIN32
		WORD Attributes; // text and background colors 
#else
		COLOR_TYPE Attributes;
#endif
	} PIX, *PPIX;
	const double rel = 8.0/14.0;
	const bool useRelativePositins = true;
	class ScreenRender {
	public:
		COLOR_TYPE COLURS[COLOR_LENGTH];
		int width,height;
		ScreenRender();

		virtual int render();

		int setPixel(int,int, PIX *color = 0);
		int printString(int, int, const char*, COLOR_TYPE color = BLUE);
		int printString(int, int, const int, COLOR_TYPE color = BLUE);
		int fillRect(int, int, int, int, char = 'a', COLOR_TYPE color = BLUE);
		int drawRect(int, int, int, int, char = 'a', COLOR_TYPE color = BLUE);

		PIX *getPixel(int x, int y){
			if(!inBoundary(x,y))
				return NULL;
			return &(buffer[y][x]);
		}
		bool inBoundary(int x, int y){
			return x > 0 && x < width && y > 0 && y < height;
		}
		void clearScreen();
		~ScreenRender(void);

	#ifdef _WIN32
		HANDLE getHandle(){
			return console;
		}
	private:
		HANDLE console;
	public:
	#endif
		COORD dwBufferSize;
		COORD dwBufferCoord;
		SMALL_RECT rcRegion;
	protected:
		PIX buffer[50][150];
		//PIX **buffer;
	};
}

#endif
