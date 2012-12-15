#ifndef _LINUX_
#define _LINUX_
#include <cstdlib>
#include <termios.h>

struct COORD{
	short X,Y;
	COORD(short x=0, short y=0):X(x),Y(y){}
};
class SMALL_RECT{
public:
	short Left, Right, Top, Bottom;
};


typedef wchar_t WCHAR;
typedef char CHAR;
typedef unsigned short WORD;

#ifndef KBHITh
#define KBHITh

class keyboard {
public:

      keyboard();
    ~keyboard();
    int kbhit();
    int getch();

    int peek_character;
private:

    struct termios initial_settings, new_settings;

};

#endif

void Sleep(float ms);
bool GetAsyncKeyState(int key);
#define VK_UP "\033[A"    // W-key
#define VK_DOWN "\033[B"  // S-key
#define VK_LEFT "\033[D"  // A-key
#define VK_RIGHT "\033[C" // D-key
#define VK_ESCAPE 27
#define VK_RETURN 10


// ANSI ESC Codes
#define BLACK 	"\033[30m"
#define RED 	"\033[31m"
#define GREEN 	"\033[32m"
#define YELLOW 	"\033[33m"
#define BLUE 	"\033[34m"
#define MAGENTA	"\033[35m"
#define CYAN	"\033[36m"
#define WHITE	"\033[37m"
#define COLOR_LENGTH 8

#endif
