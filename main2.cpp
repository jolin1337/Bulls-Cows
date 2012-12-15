#include "BullsCows.h"
using namespace std;

int main(int argc, char const *argv[]) {
	BullsCows bc;
	if(argc >= 3 && (string)(argv[1]) == "-f")
		bc = BullsCows(argv[2]);
	bc.start();
	return 0;
}