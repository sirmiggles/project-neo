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
    output->colIndex    = (int*)    malloc(numElements * sizeof(int) + 1);
    if (output->colIndex == NULL) {
        return NULL;
    }

    output->rowPtr      = (int*)    malloc(matrix->numRows * sizeof(int) + 1);
    if (output->rowPtr == NULL) {
        return NULL;
    }

    output->rowPtr[0] = 0;
    output->numNonZero = 0;
    int valIndex = 0;
    int rowPtrIndex = 1;
    int rowNNZ = 0;

    for (unsigned long i = 0; i < numElements; i++) {
        CoordForm c = matrix->coo[i];
        // If it's not zero, add it's value to A, and column to JA
        if (c.value != 0.0) {
            output->values[valIndex]    = c.value;
            output->colIndex[valIndex]  = c.j;
            valIndex++;
            rowNNZ++;
        }
        
        //  If new row, reset number of elements in row, update output NNZ
        if (c.j % matrix->numCols == 0) {
            output->rowPtr[rowPtrIndex] = output->rowPtr[rowPtrIndex - 1] + rowNNZ;
            output->numNonZero += rowNNZ;
            rowNNZ = 0;
            rowPtrIndex++;
        }
    }
    
    //  Resize array to be smaller
    if (output->numNonZero < numElements) {
        resizeCSR(output, output->numNonZero + 1);
    }
   
    for (int i = 0; i < matrix->numRows; i++) {
        printf("%d ", output->rowPtr[i]);
    }

    for (int i = 0; i < matrix->numRows; i++) {
        printf("%d  || %d\n", i, output->rowPtr[i]);
    }
    printf("\n");
    return output;
}