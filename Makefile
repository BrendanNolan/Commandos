commando: main.o commando.o
	g++ -g -o commando main.o commando.o

main.o: main.cpp commando.h
	g++ -g -c main.cpp

commando.o: commando.cpp commando.h
	g++ -g -c commando.cpp