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
void transpose(Matrix* matrix) {
    unsigned long numElements = matrix->numCols * matrix->numRows;
    for (unsigned long i = 0; i < numElements; i++) {
        printf("Before : %d  ||  %d\n", matrix->coo[i].i, matrix->coo[i].j);
        swapNumbers(&matrix->coo[i].i, &matrix->coo[i].j);
        printf("After  : %d  ||  %d\n", matrix->coo[i].i, matrix->coo[i].j);
    }
}

/*  Add two given matrices  */
/*  Best case  -  O(n), where n = numNonZero, n(m1) == n(m2)  */
/*  Worst case -  O(n1 + n2), n1 = m1NumNonZero and n2 = m2NumNonZero  */
Matrix add(Matrix matrix1, Matrix matrix2) {
    //  Initialize output matrix
    Matrix output;
    output.sourceFile = NULL;
    output.type     = matrix1.type;
    output.numRows  = matrix1.numRows;
    output.numCols  = matrix1.numCols;
    output.numNonZero = 0;

    int maxSize = matrix1.numNonZero + matrix2.numNonZero;
    output.coo = malloc(sizeof(CoordForm) * maxSize);
    if (output.coo == NULL) {
        output.type = ERR;
        return output;
    }

    //  Copy the elements of matrix 1 (technically O(n))
    memcpy(output.coo, matrix1.coo, sizeof(CoordForm) * matrix1.numNonZero);
    output.numNonZero = matrix1.numNonZero;

    //  Before matrix 2
    printf("Before: \n");
    for (int i = 0; i < output.numNonZero; i++) {
        printf("%d | %d  : %10.6f\n", output.coo[i].i, output.coo[i].j, output.coo[i].value);
    }
    printf("\n");

    CoordForm* noMatch = malloc(sizeof(CoordForm) * matrix2.numNonZero);
    if (noMatch == NULL) {
        output.type = ERR;
        return output;
    }
    printf("Malloc'd noMatch!\n");

    int minIndex = 0;
    int noMatchIndex = 0;
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
                noMatch[noMatchIndex] = matrix2.coo[j];
                noMatchIndex++;
                minIndex++;
            }
        }
    }

    //  Cells with no match
    for (int i = 0; i < noMatchIndex; i++) {
        printf("%d | %d : %10.6f\n", noMatch[i].i, noMatch[i].j, noMatch[i].value);
    }

    //  Copy noMatches
    memcpy(output.coo + output.numNonZero, noMatch, sizeof(CoordForm) * (noMatchIndex + 1));
    output.numNonZero += noMatchIndex;
    free(noMatch);

    printf("After: \n");
    for (int i = 0; i < output.numNonZero; i++) {
        printf("%d | %d  : %10.6f\n", output.coo[i].i, output.coo[i].j, output.coo[i].value);
    }
    printf("\n");
    return output;
}

