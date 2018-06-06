CC=/opt/pgi/linux86-64/2018/bin/pgc++

all: main.o coeff.o wavesim.o arrayman.o source_function.o hider.o abcon.o rnw.o
	$(CC) -std=c++11 -pg *.o -o wve_nacd

arrayman.o : arrayman.cc
	$(CC) -std=c++11 -c -pg arrayman.cc

rnw.o : rnw.cc
	$(CC) -std=c++11 -c -pg rnw.cc

abcon.o : abcon.cc
	$(CC) -std=c++11 -c -pg abcon.cc

coeff.o : coeff.cc
	$(CC) -std=c++11 -c -pg  coeff.cc

wavesim.o : wavesim.cc
	$(CC) -std=c++11 -c -pg  wavesim.cc

source_function.o : source_function.cc
	$(CC) -std=c++11 -c -pg source_function.cc

hider.o : hider.cc
	$(CC) -std=c++11 -c -pg hider.cc
	
main.o : main.cc
	$(CC) -std=c++11 -c -pg main.cc

clean :
	rm *.o
