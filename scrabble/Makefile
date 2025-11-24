scrabble: scrabble.o main.o
	g++ scrabble.o main.o -o scrabble

scrabble.o: scrabble.cpp scrabble.h
	g++ -g -O0 -c scrabble.cpp -o scrabble.o

main.o: scrabble.h main.cpp
	g++ -g -O0 -c main.cpp -o main.o

clean:
	rm -rf *.o scrabble