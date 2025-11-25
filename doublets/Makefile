doublets: main.o doublets.o
	g++ main.o doublets.o -o doublets

doublets.o: doublets.cpp doublets.h dictionary.h
	g++ -g -O0 -c doublets.cpp -o doublets.o

main.o: main.cpp doublets.h
	g++ -g -O0 -c main.cpp -o main.o

clean:
	rm -rf *.o doublets