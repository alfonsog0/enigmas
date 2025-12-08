multitap: main.o multitap.o
	g++ main.o multitap.o -o multitap

multitap.o: multitap.cpp multitap.h
	g++ -g -O0 -c multitap.cpp -o multitap.o

main.o: main.cpp multitap.h
	g++ -g -O0 -c main.cpp -o main.o

clean:
	rm -rf *.o multitap