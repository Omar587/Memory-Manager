
all: memManager 

CFLAGS = -Wall -g -std=gnu99

CC= gcc



memManager.o: memManager.h memManager.c
	$(CC) $(CFLAGS) -c memManager.c


freeHelper.o: freeHelper.h freeHelper.c	
	$(CC) $(CFLAGS) -c freeHelper.c	


mallocHelper.o: mallocHelper.c mallocHelper.h
	$(CC) $(CFLAGS) -c mallocHelper.c

memManager: memManager.o freeHelper.o mallocHelper.o
	 $(CC) $(CFLAGS) freeHelper.c mallocHelper.c memManager.c -o memManager 


A2.tar.gz:
	tar -czvf A2.tar.gz *.c *.h Makefile Test design.txt README


test:
	./memManager
	xxd memMap > ./Test/memMapOut #redirects memMap output to testing directory	   


clean:
	rm *.o 

