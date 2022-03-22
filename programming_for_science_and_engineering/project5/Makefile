all: proj5.exe

proj5.exe: project5.o EventClass.o IntersectionSimulationClass.o CarClass.o random.o
	g++ project5.o EventClass.o IntersectionSimulationClass.o CarClass.o random.o -o proj5.exe

project5.o: project5.cpp FIFOQueueClass.h FIFOQueueClass.inl LinkedNodeClass.h  LinkedNodeClass.inl SortedListClass.h SortedListClass.inl IntersectionSimulationClass.h
	g++ -std=c++98 -Wall -c project5.cpp -o project5.o

EventClass.o: EventClass.cpp  EventClass.h constants.h 
	g++ -std=c++98 -Wall -c EventClass.cpp -o EventClass.o

IntersectionSimulationClass.o: IntersectionSimulationClass.cpp  IntersectionSimulationClass.h random.h SortedListClass.h SortedListClass.inl EventClass.h FIFOQueueClass.h  FIFOQueueClass.inl  CarClass.h
	g++ -std=c++98 -Wall -c IntersectionSimulationClass.cpp -o IntersectionSimulationClass.o

CarClass.o: CarClass.cpp CarClass.h constants.h
	g++ -std=c++98 -Wall -c CarClass.cpp -o CarClass.o

random.o: random.cpp random.h
	g++ -std=c++98 -Wall -c  random.cpp -o random.o

clean:
	rm -rf *.o *.exe


