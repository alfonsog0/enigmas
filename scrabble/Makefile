scrabble: scrabble.o main.o
	g++ scrabble.o main.o -o scrabble

scrabble.o: scrabble.cpp scrabble.h
	g++ -c scrabble.cpp -o scrabble.o

main.o: scrabble.h main.cpp
	g++ -c main.cpp -o main.o

clean:
	rm -rf *.o scrabble