blotto: main.o blotto.o
	g++ -o blotto main.o blotto.o

main.o: main.cpp blotto.hpp
	g++ -c main.cpp

blotto.o: blotto.cpp blotto.hpp
	g++ -c blotto.cpp

