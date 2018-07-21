CC=/opt/pgi/linux86-64/2017/bin/pgc++
TIMER=/usr/bin/time
OPT=-ta:tesla:cc60
NOPT=-fast -Minfo=opt $(OPT)

all: main.o coeff.o wavesim.o arrayman.o source_function.o hider.o abcon.o rnw.o clean
	$(CC) -std=c++11 -pg *.o -o wve_nacd $(OPT)

exec : wve_nacd
	$(TIMER) ./wve_nacd

arrayman.o : arrayman.cc
	$(CC) -std=c++11 -c -pg $(OPT) arrayman.cc

rnw.o : rnw.cc
	$(CC) -std=c++11 -c -pg $(OPT) rnw.cc

abcon.o : abcon.cc
	$(CC) -std=c++11 -c -pg $(OPT) abcon.cc

coeff.o : coeff.cc
	$(CC) -std=c++11 -c -pg $(OPT) coeff.cc

wavesim.o : wavesim.cc
	$(CC) -std=c++11 -c -pg $(OPT)  wavesim.cc

source_function.o : source_function.cc
	$(CC) -std=c++11 -c -pg $(OPT) source_function.cc

hider.o : hider.cc
	$(CC) -std=c++11 -c -pg $(OPT) hider.cc
	
main.o : main.cc
	$(CC) -std=c++11 -c -pg $(OPT) main.cc

clean :
	rm *.o
