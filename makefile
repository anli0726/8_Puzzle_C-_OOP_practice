main: main.o Puzzle.o
	g++ -std=c++17 -o main main.o Puzzle.o

main.o: main.cpp Puzzle.h
	g++ -std=c++17 -c main.cpp

Puzzle.o: Puzzle.cpp Puzzle.h
	g++ -std=c++17 -c Puzzle.cpp

clean: 
	rm main main.o Puzzle.o