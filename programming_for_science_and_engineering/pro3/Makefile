all: projec3.exe
	valgrind --leak-check=full ./project3.exe

projec3.exe: ColorClass.o ColorImageClass.o project3.o
	g++ ColorClass.o ColorImageClass.o project3.o -o project3.exe

project3.o: project3.cpp constants.h ColorImageClass.h ColorClass.h
	g++ -std=c++98 -Wall -c project3.cpp -o project3.o


ColorClass.o: ColorClass.cpp constants.h ColorClass.h 
	g++ -std=c++98 -Wall -c ColorClass.cpp -o ColorClass.o

ColorImageClass.o: ColorImageClass.cpp constants.h ColorImageClass.h 
	g++ -std=c++98 -Wall -c ColorImageClass.cpp -o ColorImageClass.o

clean:
	rm -rf *.o *.exe


