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
    long int numElements = matrix.numRows * matrix.numCols;
    for (i = 0; i < numElements; i++) {
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

/*  Convert from COO to CSR  */
CSR* convertToCSR(Matrix* matrix) {
    CSR* output = malloc(sizeof(CSR));
    long numElements = matrix->numCols * matrix->numRows;

    //  Malloc the pointers inside the CSR format
    output->values      = (float*)  malloc(numElements * sizeof(float));
    if (output->values == NULL) {
        return NULL;
    }
    output->colIndex    = (int*)    malloc(numElements * sizeof(int));
    if (output->colIndex == NULL) {
        return NULL;
    }

    output->rowPtr      = (int*)    malloc(matrix->numRows * sizeof(int));
    if (output->rowPtr == NULL) {
        return NULL;
    }

    output->numNonZero = 0;
    int colIndex = 0;
    int rowPtrIndex = 0;
    int valIndex = 0;
    for (unsigned long i = 0; i < numElements; i++) {
        CoordForm c = matrix->coo[i];
        if (c.value == 0) {
            continue;
        }
        colIndex = i % matrix->numCols;
        output->numNonZero++;
        output->values[valIndex]    = c.value;
        output->colIndex[valIndex]  = colIndex;
        //  New row
        if (colIndex == 0) {
            output->rowPtr[rowPtrIndex++] = valIndex;
        }
        valIndex++;
    }
    if (valIndex + 1 < numElements) {
        resizeCSR(output, valIndex + 1);
    }
    return output;
}