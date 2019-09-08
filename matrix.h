#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>

enum MatrixType {
    ERR, 
    INT, 
    FLOAT
};
typedef enum MatrixType MatrixType;

struct Matrix {
    MatrixType dataType;
    double* dim;
    double** matrix;
};
typedef struct Matrix Matrix;

extern struct option execOptions[];


extern Matrix getMatrixFromFile(char*);