all: proj4.exe

proj4.exe: project4.o
	g++ project4.o -o proj4.exe

project4.o: project4.cpp FIFOQueueClass.h FIFOQueueClass.inl LinkedNodeClass.h  LinkedNodeClass.inl SortedListClass.h SortedListClass.inl 
	g++ -std=c++98 -Wall -c project4.cpp -o project4.o



clean:
	rm -rf *.o *.exe


