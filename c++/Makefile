all: main.o arrayman.o arrayopr.o source_function.o fin_diff.o
	g++ -std=c++11 *.o -o fin_proj

source_function.o : source_function.cc
	g++ -std=c++11 -c source_function.cc
	
arrayman.o : arrayman.cc
	g++ -std=c++11 -c arrayman.cc
	
arrayopr.o : arrayopr.cc
	g++ -std=c++11 -c arrayopr.cc

fin_diff.o : fin_diff.cc
	g++ -std=c++11 -c fin_diff.cc

main.o : main.cc
	g++ -std=c++11 -c main.cc

clean : 
	rm *.o
	rm fin_proj
