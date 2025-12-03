soundex: soundex.o main.o
	g++ soundex.o main.o -o soundex

soundex.o: soundex.cpp soundex.h
	g++ -g -O0 -c soundex.cpp -o soundex.o

main.o: soundex.h main.cpp
	g++ -g -O0 -c main.cpp -o main.o

clean:
	rm -rf *.o soundex
