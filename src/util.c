/* 
    File Name:      util.c 
    Description:    Contains Utility functions for the matrix program
    Author:         MIGUEL ARIES SAMBAT TABADERO (22240204)
    Last Modified:  25/9/2019
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
    int val = INT_MAX;
    char* buff;
    val = strtol(str, &buff, 0);
    return val;
}

/*  Convert char* to a double  */
double strToDouble(char* str) {
    char* buff;
    double val = strtod(str, &buff);
    return val;
}

/*  Resizes the Matrix's COO pointer  */
void resizeCOO(CoordForm* coo, int newSize) {
    CoordForm* cooBuffer = malloc(sizeof(CoordForm) * newSize);
    if (cooBuffer == NULL) {
        coo = NULL;
        return;
    }

    memcpy(cooBuffer, coo, sizeof(CoordForm) * newSize);
    coo = cooBuffer;
}


/*  For sorting back to order  */
int cooComparator(const void *p, const void *r) {
    int pRow = ((CoordForm*)p)->i;
    int pCol = ((CoordForm*)p)->j;
    int rRow = ((CoordForm*)r)->i;
    int rCol = ((CoordForm*)r)->j;
    
    if (pRow == rRow) {
        return (pCol - rCol);
    }
    else {
        return (pRow - rRow);
    }
}

/*  Filter Matrix by Column  */
CoordForm** colFilter(Matrix mat, int* nzInCol) {
    CoordForm** output = malloc(sizeof(CoordForm) * (mat.numCols * mat.numRows));
    for (int i = 0; i < mat.numCols; i++) {
        output[i] = malloc(sizeof(CoordForm) * mat.numRows);
        if (!output[i]) {
            return NULL;
        }
    }

    for (int i = 0; i < mat.numNonZero; i++) {
        CoordForm c = mat.coo[i];
        int colOfC = c.j;
        CoordForm* col = output[colOfC];
        col[nzInCol[colOfC]] = c;
        nzInCol[colOfC] += 1;
    }

    //  Resize and save space
    for (int i = 0; i < mat.numCols; i++) {
        if (nzInCol[i] < mat.numRows) {
            resizeCOO(output[i], nzInCol[i]);
        }
    }

    return output;
}

CoordForm** rowFilter(Matrix mat, int* nzInRow) {
    CoordForm** output = malloc(sizeof(CoordForm) * (mat.numRows + mat.numCols));
    for (int i = 0; i < mat.numRows; i++) {
        output[i] = malloc(sizeof(CoordForm) * mat.numCols);
        if (!output[i]) {
            return NULL;
        }
    }

    for (int i = 0; i < mat.numNonZero; i++) {
        CoordForm c = mat.coo[i];
        int rowOfC  = c.i;
        CoordForm* row = output[rowOfC];
        row[nzInRow[rowOfC]] = c;
        nzInRow[rowOfC] += 1;
    }

    for (int i = 0; i < mat.numRows; i++) {
        if (nzInRow[i] < mat.numRows) {
            resizeCOO(output[i], nzInRow[i]);
        }
    }

    return output;
}

/*  Convert NZ elements to strings  */
char** nzToStr(Matrix mat) {
    int numberSize = 10;            //  Length of INT_MAX is 10 char
    if (mat.type == FLOAT) {
        numberSize = 17;            //  10 dig, 6 dp, 1 . = 17 char
    }
    char** nzAsStr = malloc(sizeof(char) * (mat.numNonZero * numberSize));
    if (!nzAsStr) {
        return NULL;
    }

    if (mat.type == FLOAT) {
        for (int i = 0; i < mat.numNonZero; i++) {
            size_t memNeeded = snprintf(NULL, 0, "%10.6f", mat.coo[i].value);
            nzAsStr[i] = (char*) malloc(sizeof(char) * (memNeeded + 1));
            sprintf(nzAsStr[i], "%10.6f", mat.coo[i].value);
        }
    }
    else {
        for (int i = 0; i < mat.numNonZero; i++) {
            size_t memNeeded = snprintf(NULL, 0, "%d", (int) mat.coo[i].value);
            nzAsStr[i] = (char*) malloc(sizeof(char) * (memNeeded + 1));
            sprintf(nzAsStr[i], "%d", (int) mat.coo[i].value);
        }
    }

    return nzAsStr;
}
