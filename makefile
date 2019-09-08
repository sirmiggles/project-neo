#	Makefile for CITS3402 - High Performance Computing's Project I
#	Project:		Matrix Operations
#	Author:			Miguel Aries Sambat Tabadero (22240204)
#	Version:		0.0.1
#	Last Edited:	08/9/2019

CC    = gcc
MAIN  = matrix
OBJS  = matrix.o globals.o fileReader.o
FLAGS = -fopenmp -Wall -Werror -pedantic

matrix : $(OBJS)
	$(CC) $(FLAGS) -o $(MAIN) $(OBJS)

matrix.o : matrix.c matrix.h
	$(CC) $(FLAGS) -c matrix.c

globals.o : globals.c matrix.h
	$(CC) $(FLAGS) -c globals.c

fileReader.o : fileReader.c matrix.h
	$(CC) $(FLAGS) -c fileReader.c

clean :
	rm -f $(OBJS) 

