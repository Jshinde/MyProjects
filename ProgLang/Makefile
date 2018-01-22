CFLAGS = -g -Wall
CC = gcc

objects = LexAnalyzer.o LexTester.o

LexAnalyzer: $(objects)
	$(CC) -o LexAnalyzer $(objects)
       
LexAnalyzer.o: LexAnalyzer.c LexAnalyzer.h
LexTester.o: LexTester.c LexAnalyzer.h

.PHONY : clean
clean : 
	rm LexAnalyzer $(objects)
