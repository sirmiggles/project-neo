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
    double trace = 0.0;
    int i;
    #pragma omp parallel for reduction (+:trace)
    for (i = 0; i < matrix.numNonZero; i++) {
        if (matrix.coo[i].i == matrix.coo[i].j) {
            trace += matrix.coo[i].value;
        }
    }
    return (float) trace;
}

/*  Scalar Multiply a given matrix  */
/*  Generic Case - O(n) | n = numNonZero  */
/*  In SM terms, O((w x h) / 10)            */
void scalarMultiply(Matrix* matrix, float scalar) {
    int i;
    float value;
    #pragma omp parallel for private(value)
    for (i = 0; i < matrix->numNonZero; i++) {
        value = matrix->coo[i].value * scalar;
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
    int i;
    #pragma omp parallel
    {
        #pragma omp for 
        for (i = 0; i < matrix->numNonZero; i++) {
            swapNumbers(&matrix->coo[i].i, &matrix->coo[i].j);
        }
    }
    qsort(matrix->coo, matrix->numNonZero, sizeof(CoordForm), cooComparator);
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

    int minIndex = 0;               //  Minimum Index
    int noMatchIndex = 0;

    int i, j;
    #pragma omp parallel shared(minIndex, noMatchIndex)
    {
        #pragma omp for
        for (i = 0; i < output.numNonZero; i++) {
            for (j = minIndex; j < matrix2.numNonZero; j++) {
                //  Match found
                if (output.coo[i].i == matrix2.coo[j].i && output.coo[i].j == matrix2.coo[j].j) {
                    output.coo[i].value += matrix2.coo[j].value;
                    minIndex += 1;
                    break;
                }
                //  No longer in the same row as element, so skip it from now on
                if (output.coo[i].i > matrix2.coo[j].i) {
                    noMatch[noMatchIndex] = matrix2.coo[j];
                    noMatchIndex += 1;
                    minIndex += 1;
                }
            }
        }
    }
        

    //  Copy noMatches, if no matches exist
    if (noMatchIndex > 0) {
        memcpy(output.coo + output.numNonZero, noMatch, sizeof(CoordForm) * (noMatchIndex + 1));
        output.numNonZero += noMatchIndex;
    }

    free(noMatch);                      // no matches no longer used free it
    qsort(output.coo, output.numNonZero, sizeof(CoordForm), cooComparator);
    return output;
}

Matrix matrixMultiply(Matrix matrix1, Matrix matrix2) {
    Matrix output;
    output.sourceFile = NULL;
    output.type = matrix1.type;
    output.numRows = matrix1.numRows;
    output.numCols = matrix2.numCols;
    output.coo = malloc(sizeof(CoordForm) * (output.numRows * output.numCols));
    if (!output.coo) {
        output.type = ERR;
        return output;
    }
    
    CoordForm** m1Rows = malloc(sizeof(CoordForm) * (matrix1.numRows + matrix1.numCols));
    for (int i = 0; i < matrix1.numRows; i++) {
        m1Rows[i] = malloc(sizeof(CoordForm) * matrix1.numCols);
    }

    int m1NZIndex = 0;
    for (int i = 0; i < matrix1.numRows; i++) {
        CoordForm* currRow = m1Rows[i];
        int elemInRow = 0;
        for (int j = m1NZIndex; j < matrix1.numNonZero; j++) {
            CoordForm coo = matrix1.coo[j];
            if (coo.i == i) {
                currRow[elemInRow] = coo;
                elemInRow += 1;
            }
            if (coo.j + 1 == matrix1.numCols) {
                m1NZIndex += 1;
                break;
            }
        }

        for (int j = 0; j < elemInRow; j++) {
            printf("%d | %d : %10.6f\n", currRow[j].i, currRow[j].j, currRow[j].value);
        } 
    }

    return output;
}



