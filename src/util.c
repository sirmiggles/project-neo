/* 
    File Name:      util.c 
    Description:    Contains Utility functions for the matrix program
    Author:         MIGUEL ARIES SAMBAT TABADERO (22240204)
    Last Modified:  13/9/2019
*/

#include <stdio.h>
#include <errno.h>
#include <string.h>

#include "matrix.h"

/*  Prints a usage/help text to stderr  */
void usage(void) {
    fprintf(stderr, "Usage: ./matrix <exec_opts>\n");
    fprintf(stderr, "Execution flags:\n");
    fprintf(stderr, "  -f <file_1> (<file_2>)      ||    use the specified plaintext file(s) as matrix(/matrices)\n");
    fprintf(stderr, "  -l                          ||    log the output to a file\n");
    fprintf(stderr, "  -t <num_of_threads>         ||    set the number of threads to num_of_threads\n");

    fprintf(stderr, "\nSingle Matrix Operations:\n");
    fprintf(stderr, "  -sc, -s          ||    perform scalar multiplication on a matrix\n");
    fprintf(stderr, "  -tr              ||    calculate the trace of a matrix\n");
    fprintf(stderr, "  -ts              ||    transpose a matrix\n");

    fprintf(stderr, "\nTwo Matrix Operations:\n");
    fprintf(stderr, "  -ad, -a          ||    add two matrices\n");
    fprintf(stderr, "  -mm, -m          ||    perform matrix multiplication with two matrices\n");
}

/*  Checks if there are an appropriate number of arguments provided */
bool sufficientArgs(int numProvided, int numRequired) {
    return (numProvided != numRequired) ? false : true;
}

/*  Convert char* to a positive int  */
int strToInt(char* str) {
    int val;
    if ((val = atoi(str)) != 0) {
        return (val > 0) ? val : 0;
    }
    return -1;
}
