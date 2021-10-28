all: block_counter

block_counter: block_counter.o barrier.o
	gcc -Wall -o block_counter block_counter.o barrier.o -lpthread

block_counter.o: block_counter.c
	gcc -Wall -I. -c block_counter.c

barrier.o: barrier.c
	gcc -Wall -I. -c barrier.c

dist: 
	tar -cvzf block_counter.tar.gz block_counter.c barrier.c barrier.h Makefile

clean:
	rm *.o block_counter 2>/dev/null
