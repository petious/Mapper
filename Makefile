CXX = g++
CXXFLAGS = -Wall -Wextra -Werror -pedantic -pedantic-errors -O3


ProjetCpp: main.o Mapper.o
	$(CXX) -o mon_prog main.o Mapper.o
	g++ $(CXXFLAGS) -c main.cpp

Mapper.o :
	g++ $(CXXFLAGS) -c Mapper.cpp

clean:
	rm *.o
	rm mon_prog
