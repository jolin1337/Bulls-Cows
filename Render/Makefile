names=ScreenRender Linux 
srcs=ScreenRender.cpp Linux.cpp
objs=bin/ScreenRender.o bin/Linux.o 
head=Linux.h ScreenRender.h

lib/lib2: ${head} ${srcs}
	./createBins ${names}
	ar crfv lib/lib2d ${objs}

prgm: ${objs} test.cpp lib/lib2d.a
	make lib/lib2
	g++ -L./lib -l2d test.cpp -o prgm