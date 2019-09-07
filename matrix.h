#include <stdio.h>

struct Matrix {
    int* dim;
    int** matrix;
};

typedef struct Matrix Matrix;

extern Matrix getMatrixFromFile(char*);