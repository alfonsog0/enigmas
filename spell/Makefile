spell: main.o spell.o
	g++ main.o spell.o -o spell

spell.o: spell.cpp spell.h
	g++ -g -O0 -c spell.cpp -o spell.o

main.o: spell.h main.cpp
	g++ -g -O0 -c main.cpp -o main.o

clean:
	rm -rf *.o spell