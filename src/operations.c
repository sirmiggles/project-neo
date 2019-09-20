/*
    File Name:      operations.c
    Description:    Source file for the matrix operations to be executed
    Author:         MIGUEL ARIES SAMBAT TABADERO (22240204)
    Last Modified:  13/9/2019
*/

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <float.h>
#include <omp.h>

#include "matrix.h"

/*  Calculate the trace of a square matrix  */
/*  Generic case - O(n) | n = numNonZero    */
/*  In SM terms, O((w x h) / 10)            */
float trace(Matrix matrix) {
    float trace = 0.0;
    int i = 0;
    for (i = 0; i < matrix.numNonZero; i++) {
        if (matrix.coo[i].i == matrix.coo[i].j)
            trace += matrix.coo[i].value;
    }
    return trace;
}

/*  Scalar Multiply a given matrix  */
/*  Generic Case - O(n) | n = numNonZero  */
/*  In SM terms, O((w x h) / 10)            */
void scalarMultiply(Matrix* matrix, float scalar) {
    unsigned long numElements = matrix->numCols * matrix->numRows;
    for (unsigned long i = 0; i < numElements; i++) {
        float value = matrix->coo[i].value * scalar;
        matrix->coo[i].value = value;
    }
}

/*  Memory address swap  */
void swapNumbers(int* i, int* j) {
    int temp = *i;
    *i = *j;
    *j = temp;
}

/*  Transpose a given matrix  */
/*  Generic case - O(n)       */
/*  In SM terms, O((w x h) / 10)            */
void transpose(Matrix* matrix) {
    unsigned long numElements = matrix->numCols * matrix->numRows;
    for (unsigned long i = 0; i < numElements; i++) {
        printf("Before : %d  ||  %d\n", matrix->coo[i].i, matrix->coo[i].j);
        swapNumbers(&matrix->coo[i].i, &matrix->coo[i].j);
        printf("After  : %d  ||  %d\n", matrix->coo[i].i, matrix->coo[i].j);
    }
}

/*  Add two given matrices  */
/*  Best case       -  O(n) | n = numNonZero, n(m1) == n(m2)  */
/*  Generic Case    =  O(m(n-m+1))                            */
Matrix add(Matrix matrix1, Matrix matrix2) {
    //  Initialize output matrix
    Matrix output = matrix1;
    int maxSize = matrix1.numNonZero + matrix2.numNonZero;
    CoordForm* newCOO = realloc(output.coo, maxSize * sizeof(CoordForm));
    if (!newCOO) {
        output.type = ERR;
        return output;
    }
    output.coo = newCOO;

    //  Initialize buffer for unmatched cells
    CoordForm* noMatch = malloc(sizeof(CoordForm) * matrix2.numNonZero);
    if (noMatch == NULL) {
        output.type = ERR;
        return output;
    }

    int minIndex = 0;
    int noMatchIndex = 0;
    //  Linear search for matches
    //  Generic     = O(m(n - m + 1))
    //  Best case   = O(m) | m = numNonZeros of Matrix 1
    //  Worst case  = O(m(n + 1)) | None of the cells match
    for (int i = 0; i < output.numNonZero; i++) {
        for (int j = minIndex; j < matrix2.numNonZero; j++) {
            //  Match found
            if (output.coo[i].i == matrix2.coo[j].i && output.coo[i].j == matrix2.coo[j].j) {
                output.coo[i].value += matrix2.coo[j].value;
                minIndex++;
                break;
            }
            //  No longer in the same row as element, so skip it from now on
            if (output.coo[i].i > matrix2.coo[j].i) {
                noMatch[noMatchIndex++] = matrix2.coo[j];
                minIndex++;
            }
        }
    }

    //  Copy noMatches, if no matches exist
    if (noMatchIndex > 0) {
        memcpy(output.coo + output.numNonZero, noMatch, sizeof(CoordForm) * (noMatchIndex + 1));
        output.numNonZero += noMatchIndex;
    }
    free(noMatch);                      // no matches no longer used free it
    return output;
}



