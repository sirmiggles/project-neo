CC    = gcc
MAIN  = matrix
OBJS  = matrix.o fileReader.o
FLAGS = -fopenmp -Wall -Werror -pedantic

matrix : matrix.o fileReader.o
	$(CC) $(FLAGS) -o matrix matrix.o fileReader.o

matrix.o : matrix.c matrix.h
	$(CC) $(FLAGS) -c matrix.c

fileReader.o : fileReader.c matrix.h
	$(CC) $(FLAGS) -c fileReader.c

clean :
	rm -f $(OBJS) 

