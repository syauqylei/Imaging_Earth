CC=/opt/pgi/linux86-64/2017/bin/pgc++
TIMER=/usr/bin/time
OPT=-ta:tesla:cc60
NOPT=-fast -Minfo=opt $(OPT)

all: main.o coeff.o wavesim.o arrayman.o source_function.o hider.o abcon.o rnw.o 
	$(CC) -std=c++11 -pg *.o -o  wve_nacd $(NOPT)

exec : wve_nacd
	$(TIMER) ./wve_nacd

arrayman.o : arrayman.cc
	$(CC) -std=c++11 -c -pg $(NOPT) arrayman.cc

rnw.o : rnw.cc
	$(CC) -std=c++11 -c -pg $(NOPT) rnw.cc

abcon.o : abcon.cc
	$(CC) -std=c++11 -c -pg $(NOPT) abcon.cc

coeff.o : coeff.cc
	$(CC) -std=c++11 -c -pg $(NOPT) coeff.cc

wavesim.o : wavesim.cc
	$(CC) -std=c++11 -c -pg $(NOPT)  wavesim.cc

source_function.o : source_function.cc
	$(CC) -std=c++11 -c -pg $(NOPT) source_function.cc

hider.o : hider.cc
	$(CC) -std=c++11 -c -pg $(NOPT) hider.cc
	
main.o : main.cc
	$(CC) -std=c++11 -c -pg $(NOPT) main.cc

clean :
	rm *.o
