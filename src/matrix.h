/*
    File Name:      matrix.h
    Description:    Main header file for matrix that links all the source files
    Author:         MIGUEL ARIES SAMBAT TABADERO (22240204)
    Last Modified:  09/9/2019
*/

#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>

enum MatrixType {
    ERR, 
    INT, 
    FLOAT
};
typedef enum MatrixType MatrixType;

enum EXEC_FLAG_VALUES {
    SC = 0,
    TR = 1,
    AD = 2,
    TS = 3,
    MM = 4,
    FN = 5,
    LOG  = 6,
    TH = 7
};

/*  Struct holding the key matrix information */
struct Matrix {
    char* sourceFile;
    MatrixType dataType;
    int width;
    int column;
    double** matrix;
};
typedef struct Matrix Matrix;

extern struct option EXEC_OPTIONS[];
extern const char*  AUTHOR_SN;
extern const int TH_FLAG_BUFSIZ;

extern void usage(void);
