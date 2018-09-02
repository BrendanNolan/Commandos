blotto: main.o blotto.o
	g++ -o blotto main.o blotto.o

main.o: main.cpp blotto.h
	g++ -c main.cpp

blotto.o: blotto.cpp blotto.h
	g++ -c blotto.cpp

