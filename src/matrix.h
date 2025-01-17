/*
    File Name:      matrix.h
    Description:    Main header file for matrix that links all the source files
    Author:         MIGUEL ARIES SAMBAT TABADERO (22240204)
    Last Modified:  25/9/2019
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <getopt.h>
#include <sys/time.h>
#include <time.h>

enum MatrixType {
    ERR = -1, 
    INT, 
    FLOAT
};
typedef enum MatrixType MatrixType;

enum EXEC_FLAG_VALUES {
    UD = -1,
    SM,
    TR,
    AD,
    TS,
    MM,
    FN,
    LOG,
    TH
};

struct CoordForm {
    int     i;              //  Row Index
    int     j;              //  Column Index
    double   value;
};

typedef struct CoordForm CoordForm;

/*  Struct holding the key matrix information */
struct Matrix {
    char*       sourceFile;
    int         numNonZero;
    MatrixType  type;
    int         numRows;
    int         numCols;
    CoordForm*  coo;
};
typedef struct Matrix Matrix;

/*  The constants defined in globals.c  */
extern  struct  option      EXEC_OPTIONS[];
extern  const   char*       FLAGS[];
extern  const   char*       AUTHOR_SN;
extern  const   int         FLAG_ARG_BUFSIZ;
extern  const   int         FILEPATH_MAX;
extern  const   int         DIM_BUFSIZ;
extern  const   int         ELEMENT_SIZE;
extern  const   int         DEFAULT_THREAD_COUNT;

/*  Utility function definitions  */
extern  void        usage(void);
extern  bool        sufficientArgs(int, int);
extern  int         strToInt(char*);
extern  double      strToDouble(char*);
extern  void        resizeCOO(CoordForm*, int);
extern  int         cooComparator(const void*, const void*);
extern  void        printCOO(Matrix);
extern  CoordForm** colFilter(Matrix, int*);
extern  CoordForm** rowFilter(Matrix, int*);
extern  char**      nzToStr(Matrix);

/*  Logging function definitions  */
extern  FILE*       openLogFile(struct tm *, enum EXEC_FLAG_VALUES);
extern  void        outputToLogTR(FILE*, Matrix, int, double, double, double);
extern  void        outputToLogSMTS(FILE*, Matrix, char**, int, double, double, enum EXEC_FLAG_VALUES);
extern  void        outputToLogADMM(FILE*, Matrix[2], Matrix, char**, int, double, double, enum EXEC_FLAG_VALUES);
extern  void        printAsMatrix(FILE*, Matrix, char**);

/*  File I/O function definitiions */
extern  void    parseFileName(int*, char*, char*);
extern  bool    fileAccessible(char*);
extern  void    openFiles(FILE**, char**, int);
extern  void    closeFiles(FILE**, int);
extern  void    parseMatrixFile(FILE*, Matrix*, char*);
extern  void    allocateDataType(Matrix*, char*);
extern  void    allocateDimensions(Matrix*, char*, char*);
extern  void    convertToCOO(Matrix*, char*, int, int);

/*  Matrix operation functions definitions  */
extern  double  trace(Matrix);
extern  void    scalarMultiply(Matrix*, double);
extern  void    transpose(Matrix*);
extern  Matrix  add(Matrix, Matrix);
extern  Matrix  matrixMultiply(Matrix, Matrix);
extern  double  dotProduct(CoordForm*, CoordForm*, int, int);