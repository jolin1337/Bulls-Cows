srcs=Menu/Menu.cpp Solver.cpp header.cpp Gissning/Gissning.cpp main2.cpp BullsCows.cpp Render/ScreenRender.cpp Render/Linux.cpp 
head=BullsCows.h header.h Gissning/Gissning.h Render/Linux.h Render/ScreenRender.h Menu/Menu.h DistinktNumber/DistinktNumber.h Highscore.h
op=cowGame

all: ${op}

${op}: ${head} ${srcs}
	 g++ -W -Wall -Wextra -pedantic -std=c++0x -o ${op} ${srcs}
