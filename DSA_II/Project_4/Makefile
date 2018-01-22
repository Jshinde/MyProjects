CFLAGS = -g -Wall
CC = gcc

objects = structures.o binPacking.o

binPacking: $(objects)
	$(CC) -o binPacking $(objects)
       
structures.o: structures.c structures.h
binPacking.o: binPacking.c structures.h

.PHONY : clean
clean : 
	rm binPacking $(objects)
