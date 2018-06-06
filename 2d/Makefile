CC=/opt/pgi/linux86-64/2018/bin/pgc++

all: main.o coeff.o wavesim.o arrayman.o source_function.o hider.o abcon.o rnw.o
	$(CC) -Wall -std=c++11 *.o -pg -o wve_nacd

arrayman.o : arrayman.cc
	$(CC) -std=c++11 -c arrayman.cc

rnw.o : rnw.cc
	$(CC) -std=c++11 -c rnw.cc

abcon.o : abcon.cc
	$(CC) -std=c++11 -c abcon.cc

coeff.o : coeff.cc
	$(CC) -std=c++11 -c coeff.cc

wavesim.o : wavesim.cc
	$(CC) -std=c++11 -c wavesim.cc

source_function.o : source_function.cc
	$(CC) -std=c++11 -c source_function.cc

hider.o : hider.cc
	$(CC) -std=c++11 -c hider.cc
	
main.o : main.cc
	$(CC) -std=c++11 -c main.cc

clean :
	rm *.o
