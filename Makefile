LIBS = $(wildcard libs/*)
INCLUDE_PATH = libs/

fin_proj: libraries
	gcc main.c $(wildcard libraries/* ) -I$(INCLUDE_PATH) -o fin_proj -lm 

libraries:
	mkdir libraries/
	for dir in $(LIBS); do\
		cd $$dir;\
		gcc -c *.c -I../ ;\
		mv *.o ../../libraries;\
		cd -;\
	done

clean:
	rm -rf libraries/ ;\
	rm fin_proj;
	rm *.txt
	
