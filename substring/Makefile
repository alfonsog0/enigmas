substring: substring.o main.o
	g++ substring.o main.o -o substring

substring.o: substring.cpp substring.h
	g++ -g -O0 -c substring.cpp -o substring.o

main.o: main.cpp substring.h
	g++ -g -c -O0 main.cpp -o main.o

clean:
	rm -rf *.o substring