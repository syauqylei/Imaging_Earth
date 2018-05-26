all: main.o coeff.o arrayman.o wavesim.o source_function.o hider.o
	g++ -std=c++11 *.o -o wve_nacd

coeff.o : coeff.cc
	g++ -std=c++11 -c coeff.cc

arrayman.o : arrayman.cc
	g++ -std=c++11 -c arrayman.cc

wavesim.o : wavesim.cc
	g++ -std=c++11 -c wavesim.cc

source_function.o : source_function.cc
	g++ -std=c++11 -c source_function.cc

hider.o : hider.cc
	g++ -std=c++11 -c hider.cc
	
main.o : main.cc
	g++ -std=c++11 -c main.cc

clean :
	rm *.o
