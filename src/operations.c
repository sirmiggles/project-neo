/*
    File Name:      operations.c
    Description:    Source file for the matrix operations to be executed
    Author:         MIGUEL ARIES SAMBAT TABADERO (22240204)
    Last Modified:  13/9/2019
*/

#include <stdio.h>
#include <float.h>
#include <omp.h>

#include "matrix.h"

/*  Calculate the trace of a square matrix  */
float trace(Matrix matrix, int numThreads) {
    float trace = FLT_MAX;                      //  Initialize value for error throwing
    if (matrix.numRows != matrix.numCols) {
        return trace;
    }
    int i = 0;
    long int numElements = matrix.numRows * matrix.numCols;
    trace = 0.0;
    for (i = 0; i < numElements; i++) {
        if (matrix.coo[i].i == matrix.coo[i].j)
            trace += matrix.coo[i].value;
    }
    return trace;
}