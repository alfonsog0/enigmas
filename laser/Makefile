laser: main.o laser.o
	g++ main.o laser.o -o laser

laser.o: laser.cpp laser.h
	g++ -c laser.cpp -o laser.o

main.o: main.cpp laser.h
	g++ -c main.cpp -o main.o

clean:
	rm -rf *.o laser