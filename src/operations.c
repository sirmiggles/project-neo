/*
    File Name:      operations.c
    Description:    Source file for the matrix operations to be executed
    Author:         MIGUEL ARIES SAMBAT TABADERO (22240204)
    Last Modified:  13/9/2019
*/

#include <stdio.h>
#include <stdbool.h>
#include <float.h>
#include <omp.h>

#include "matrix.h"

/*  Calculate the trace of a square matrix  */
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
void scalarMultiply(Matrix* matrix, float scalar) {
    unsigned long numElements = matrix->numCols * matrix->numRows;
    for (unsigned long i = 0; i < numElements; i++) {
        float value = matrix->coo[i].value * scalar;
        matrix->coo[i].value = value;
    }
}

void swapNumbers(int* i, int* j) {
    int temp = *i;
    *i = *j;
    *j = temp;
}

/*  Transpose a given matrix  */
void transpose(Matrix* matrix) {
    unsigned long numElements = matrix->numCols * matrix->numRows;
    for (unsigned long i = 0; i < numElements; i++) {
        printf("Before : %d  ||  %d\n", matrix->coo[i].i, matrix->coo[i].j);
        swapNumbers(&matrix->coo[i].i, &matrix->coo[i].j);
        printf("After  : %d  ||  %d\n", matrix->coo[i].i, matrix->coo[i].j);
    }
}

/*  Add two given matrices  */
Matrix add(Matrix matrix1, Matrix matrix2) {
    Matrix output;
    output.sourceFile = NULL;
    output.numRows = matrix1.numRows;
    output.numCols = matrix1.numCols;

    unsigned int numElements = output.numRows * output.numCols;
    output.coo = malloc(sizeof(CoordForm)* numElements);
    if (output.coo == NULL) {
        output.type = ERR;
        return output;
    }

    for (int i = 0; i < numElements; i++) {
        output.coo[i].i = matrix1.coo[i].i;
        output.coo[i].j = matrix1.coo[i].j;
        output.coo[i].value = matrix1.coo[i].value + matrix2.coo[i].value;
    }

    return output;
}

