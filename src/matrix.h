/*
    File Name:      matrix.h
    Description:    Main header file for matrix that links all the source files
    Author:         MIGUEL ARIES SAMBAT TABADERO (22240204)
    Last Modified:  11/9/2019
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <getopt.h>

enum MatrixType {
    ERR = -1, 
    INT, 
    FLOAT
};
typedef enum MatrixType MatrixType;

enum EXEC_FLAG_VALUES {
    UD = -1,
    SC,
    TR,
    AD,
    TS,
    MM,
    FN,
    LOG,
    TH
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

/*  The constants defined in globals.c  */
extern struct option EXEC_OPTIONS[];
extern const char*  AUTHOR_SN;
extern const int TH_FLAG_BUFSIZ;
extern const int FILEPATH_MAX;
extern const int DEFAULT_THREAD_COUNT;

/*  Utility function definitions  */
extern void usage(void);
extern bool sufficientArgs(int, int);

/*  File I/O function definitiions */
extern void parseFileName(int*, char*);
extern bool fileAccessible(char*);