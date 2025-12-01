playfair: main.o playfair.o
	g++ main.o playfair.o -o playfair

playfair.o: playfair.cpp playfair.h
	g++ -g -O0 -c playfair.cpp -o playfair.o

main.o: playfair.h main.cpp
	g++ -g -O0 -c main.cpp -o main.o

clean:
	rm -rf *.o playfair