all: tp1

tp1: main.o soldado.o cmdline.o estrategia_base.o
	g++ -Wall -pedantic -o tp1 main.o soldado.o cmdline.o estrategia_base.o

soldado.o: soldado.cpp soldado.hpp
	g++ -Wall -pedantic -c -o soldado.o soldado.cpp

cmdline.o: cmdline.cpp cmdline.hpp
	g++ -Wall -pedantic -c -o cmdline.o cmdline.cpp

estrategia_base.o: estrategia_base.cpp estrategia_base.hpp
	g++ -Wall -pedantic -c -o estrategia_base.o estrategia_base.cpp
	
main.o: main.cpp cmdline.hpp estrategia_base.hpp estrategia_evasiva.hpp estrategia_agresiva.hpp estrategia_test.hpp lista.hpp soldado.hpp nodo.hpp entrada_salida.hpp common.hpp
	g++ -Wall -pedantic -c -o main.o main.cpp

