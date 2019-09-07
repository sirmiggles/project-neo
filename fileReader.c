#include "matrix.h"

#include <stdio.h>
#include <stdlib.h>

Matrix getMatrixFromFile(char* filePath) {
    Matrix m;
    m.dim = (int*) calloc(2, sizeof(int));
    printf("Got here\n");
    return m;
}