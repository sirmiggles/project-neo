/* 
    File Name:      util.c 
    Description:    Contains Utility functions for the matrix program
    Author:         MIGUEL ARIES SAMBAT TABADERO (22240204)
    Last Modified:  14/9/2019
*/

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <limits.h>
#include <float.h>

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
    unsigned int val = UINT_MAX;
    char* buff;
    val = strtoul(str, &buff, 0);
    return val;
}

/*  Convert char* to a float  */
float strToFloat(char* str) {
    float val = FLT_MAX;
    char* buff;
    val = strtof(str, &buff);
    return val;
}

/*  Prints out the matrix in COO form  */
void printCOO(Matrix matrix) {
    unsigned long numElements = matrix.numCols * matrix.numRows;
    printf("[");
    for (int i = 0; i < numElements; i++) {
        printf("(%d, %d, %10.6f) \n", matrix.coo[i].i, matrix.coo[i].j, matrix.coo[i].value);
        if (i + 1 < numElements)
            printf(" "); 
    }
    printf("]\n");
}

/*  Expand the CSR pointer  */
void resizeCSR(CSR* csr, long newSpace) {
    float* valuesBuffer = (float*) realloc(csr->values, newSpace);
    if (valuesBuffer == NULL) {
        csr->values = NULL;
    }
    csr->values = valuesBuffer;
    
    float* colsBuffer = (float*) realloc(csr->colIndex, newSpace);
    if (colsBuffer == NULL) {
        csr->colIndex = NULL;
    }
}
