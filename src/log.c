/* 
    File Name:      util.c 
    Description:    Contains Utility functions for the matrix program
    Author:         MIGUEL ARIES SAMBAT TABADERO (22240204)
    Last Modified:  18/9/2019
*/

#include "matrix.h"

#include <stdio.h>
#include <time.h>

/*  Open a file for logging  */
FILE* openLogFile(struct tm *time, enum EXEC_FLAG_VALUES efv) {
    char* fileName;
    size_t mem = snprintf(NULL, 0, "%s_%02d%02d%04d_%02d%02d_%s.out",    \
                          AUTHOR_SN, time->tm_mday, time->tm_mon, 1900 + time->tm_year, \
                          time->tm_hour, time->tm_min, FLAGS[efv]);
    fileName = malloc(sizeof(char) * (mem + 1));
    sprintf(fileName, "%s_%02d%02d%04d_%02d%02d_%s.out",    \
                        AUTHOR_SN, time->tm_mday, time->tm_mon, 1900 + time->tm_year, \
                        time->tm_hour, time->tm_min, FLAGS[efv]);
    
    FILE* logFile = fopen(fileName, "w+");
    return logFile;
}

/*  Output to log for trace  */
void outputToLogTR(FILE* logFile, Matrix mat, int numThreads, float tr, float delta_io, float delta_op) {
    fprintf(logFile, "tr\n");
    fprintf(logFile, "%s\n", mat.sourceFile);
    fprintf(logFile, "%d\n", numThreads);
    if (mat.type == FLOAT) {
        fprintf(logFile, "%10.6f\n", tr);
    }
    else {
        fprintf(logFile, "%d\n", (int) tr);
    }

    fprintf(logFile, "%10.6f\n", delta_io);
    fprintf(logFile, "%10.6f", delta_op);
}

/*  Output to log for scalar multiplication and transpose  */
void outputToLogSMTS(FILE* logFile, Matrix mat, int numThreads, float delta_io, float delta_op, enum EXEC_FLAG_VALUES efv) {
    fprintf(logFile, "%s\n", FLAGS[efv]);
    fprintf(logFile, "%s\n", mat.sourceFile);
    fprintf(logFile, "%d\n", numThreads);
    printAsMatrix(logFile, mat);
    fprintf(logFile, "%10.6f\n", delta_io);
    fprintf(logFile, "%10.6f", delta_op);
}

void outputToLogADMM(FILE* logFile, Matrix mat[2], Matrix out, int numThreads, float delta_io, float delta_op, enum EXEC_FLAG_VALUES efv) {
    fprintf(logFile, "%s\n", FLAGS[efv]);
    for (int i = 0; i < 2; i++) {
        fprintf(logFile, "%s\n", mat[i].sourceFile);
    }
    fprintf(logFile, "%d\n", numThreads);
    printAsMatrix(logFile, out);
    fprintf(logFile, "%10.6f\n", delta_io);
    fprintf(logFile, "%10.6f", delta_op);
}

void printAsMatrix(FILE* logFile, Matrix mat) {
    int nnzIndex = 0;
    for (int i = 0; i < mat.numRows; i++) {
        for (int j = 0; j < mat.numCols; j++) {
            CoordForm c = mat.coo[nnzIndex];
            if (c.i == i && c.j == j) {
                nnzIndex += 1;
                if (mat.type == FLOAT) {
                    fprintf(logFile, "%10.6f", c.value);
                }
                else {
                    fprintf(logFile, "%d", (int) c.value);
                }
            }
            else {
                fprintf(logFile, "%s", (mat.type == FLOAT) ? "0.0" : "0");
            }
            if (!(i == mat.numRows - 1 && j == mat.numCols - 1)) {
                fprintf(logFile, " ");
            }
        }
    }
    fprintf(logFile, "\n");
}

