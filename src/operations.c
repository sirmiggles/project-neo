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
double trace(Matrix matrix) {
    double trace = 0.0;
    int i;
    #pragma omp parallel for reduction (+:trace)
    for (i = 0; i < matrix.numNonZero; i++) {
        if (matrix.coo[i].i == matrix.coo[i].j) {
            trace += matrix.coo[i].value;
        }
    }
    return trace;
}

/*  Scalar Multiply a given matrix  */
/*  Generic Case - O(n) | n = numNonZero  */
/*  In SM terms, O((w x h) / 10)            */
void scalarMultiply(Matrix* matrix, double scalar) {
    matrix->type = FLOAT;
    int i;
    double value;
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
    #pragma omp parallel firstprivate(minIndex, noMatchIndex)
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
    
    //  Filter and sort the NZ elements of M2 by column
    int* m2NZInCol = (int *) calloc(matrix2.numCols, sizeof(CoordForm));
    if (!m2NZInCol) {
        output.type = ERR;
        return output;
    }

    CoordForm** m2Cols = colFilter(matrix2, m2NZInCol);
    if (!m2Cols) {
        output.type = ERR;
        return output;
    }

    int* m1NZInRow = (int *) calloc(matrix1.numRows, sizeof(CoordForm));
    if(!m1NZInRow) {
        output.type = ERR;
        return output;
    }

    CoordForm** m1Rows = rowFilter(matrix1, m1NZInRow);
    if (!m1Rows) {
        output.type = ERR;
        return output;
    }
    
    output.numNonZero = 0;
    int i, j;
    for (i = 0; i < matrix1.numRows; i++) {
        for (j = 0; j < matrix2.numCols; j++) {
            double dot = dotProduct(m1Rows[i], m2Cols[j], m1NZInRow[i], m2NZInCol[j]);
            if (dot != 0) {
                CoordForm c = {i, j, dot};
                output.coo[output.numNonZero] = c;
                output.numNonZero += 1;
            }
        }
    }

    resizeCOO(output.coo, output.numNonZero);
    return output;
}

/*  Return the dot product of two vectors  */
/*  Average Case - O(m(n - m + 1))         */
double dotProduct(CoordForm* v1, CoordForm* v2, int v1NZ, int v2NZ) {
    int v2Head = 0;
    double dotP = 0.0;
    /*  Shrinking search for matching rows  */
    #pragma omp parallel firstprivate(v2Head)
    {
        #pragma omp for reduction (+:dotP)
        for (int i = 0; i < v1NZ; i++) {
            for (int j = v2Head; j < v2NZ; j++) {
                if (v1[i].j == v2[j].i) {
                    dotP += v1[i].value * v2[j].value;
                    v2Head += 1;
                    break;
                }
                if (v1[i].j > v2[j].i) {
                    v2Head += 1;
                }
            }
        }
    }
    return (double) dotP;
}



