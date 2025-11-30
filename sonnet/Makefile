sonnet: sonnet.o main.o
	g++ sonnet.o main.o -o sonnet

sonnet.o: sonnet.cpp sonnet.h
	g++ -g -c sonnet.cpp -o sonnet.o

main.o: main.cpp sonnet.h
	g++ -g -c main.cpp -o main.o

clean:
	rm -rf *.o sonnet