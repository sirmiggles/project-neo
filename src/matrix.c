/*
    File Name:      matrix.c
    Description:    Main C File for matrix
                    > Contains the entry point (main) for the program
    Author:         MIGUEL ARIES SAMBAT TABADERO (22240204)
    Last Modified:  18/9/2019
*/

#include <stdio.h>
#include <stdbool.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <sys/time.h>
#include <omp.h>

#include <limits.h>
#include <float.h>

#include "matrix.h"

int main(int argc, char **argv) {
    //  If insufficient number of arguments, throw usage message
    if (argc < 3) {
        fprintf(stderr, "Invalid number of arguments\n");
        usage();
        return -1;
    }

    enum EXEC_FLAG_VALUES efv = UD;         //  Execution flag value, based on enum
    bool log = false;                       //  Will the execution output a log file

    int matrixCount = 0;                    //  Current number of matrices
    int requiredMatrices = 1;               //  Operations require at least 1.

    int numThreads;                         //  The default number of threads that the program will run in
    numThreads = DEFAULT_THREAD_COUNT;

    char* thOpt     = malloc(FLAG_ARG_BUFSIZ * sizeof(char));    //  -t argument buffer
    char* flagArg   = malloc(FLAG_ARG_BUFSIZ * sizeof(char));     //  -sm argument buffer
    float scalar;
    
    char* fileNames[2];
    fileNames[0] = malloc(FILEPATH_MAX * sizeof(char));
    fileNames[1] = malloc(FILEPATH_MAX * sizeof(char));
    int fnIndex = 0;

    int opt, optIndex;
    //  Loop through execution options
    while ((opt = getopt_long_only(argc, argv, "", EXEC_OPTIONS, &optIndex)) != -1) {
        if (opt == FN || opt == LOG || opt == TH) {
            switch (opt) {
                case FN:
                    for(int index = optind - 1; index < argc && *argv[index] != '-'; index++) {
                        parseFileName(&matrixCount, argv[index], fileNames[fnIndex++]);
                    }
                    break;
                
                case LOG :
                    log = true;
                    break;

                case TH:
                    strcpy(thOpt, optarg);
                    if ((numThreads = strToInt(thOpt)) < 1) {
                        fprintf(stderr, "Number of threads should be greater than 0 and an integer\n");
                        return -1;
                    }
                    break;
            }
        }
        else {
            efv = opt;
            if (efv == SM) {
                strcpy(flagArg, optarg);
                scalar = strToFloat(flagArg);
                continue;
            }
            if (efv == AD || efv == MM) {
                requiredMatrices = 2;
            }
        }
    }
    //  Free the buffer files for reading command line arguments
    free(thOpt);
    free(flagArg);

    //  If no operations are found, exit
    if (efv == UD) {
        fprintf(stderr, "No operations found\n");
        return -1;
    }

    if (!sufficientArgs(matrixCount, requiredMatrices)) {
        fprintf(stderr, "Incorrect number of matrices:\n");
        fprintf(stderr, "> %d provided : %d required\n", matrixCount, requiredMatrices);
        return -1;
    }

    //  Free Unnecessarily allocated second file name
    if (requiredMatrices < 2 && matrixCount < 2) {
        free(fileNames[1]);
        matrixCount = 1;
    }

    omp_set_num_threads(numThreads);
    
    //  Open files for processing and close files after
    struct timeval ioStart, ioEnd;
    gettimeofday(&ioStart, NULL);
    
    FILE** readFiles = malloc(matrixCount * sizeof(FILE));
    openFiles(readFiles, fileNames, matrixCount);
    Matrix matrices[matrixCount];
    for (int i = 0; i < matrixCount; i++) {
        parseMatrixFile(readFiles[i], &matrices[i], fileNames[i]);
    }
    closeFiles(readFiles, matrixCount);
    free(readFiles);

    gettimeofday(&ioEnd, NULL);

    float ioDelta = ((ioEnd.tv_sec  - ioStart.tv_sec) * 1000000u + ioEnd.tv_usec - ioStart.tv_usec) / 1.e6;
    printf("Time taken for I/O: %10.6f\n", ioDelta);

    struct timeval opStart, opEnd;
    float tr; 
    switch (efv) {
        case SM :
            gettimeofday(&opStart, NULL);
            scalarMultiply(&matrices[0], scalar);
            gettimeofday(&opEnd, NULL);
            if (log == true) {} // use log file
            break;

        case TR :
            gettimeofday(&opStart, NULL);
            tr = trace(matrices[0]);
            gettimeofday(&opEnd, NULL);
            printf("%10.6f\n", tr);
            if (log == true) {}
            break;

        case TS :
            //printCOO(matrices[0]);
            gettimeofday(&opStart, NULL);
            transpose(&matrices[0]);
            gettimeofday(&opEnd, NULL);
            if (log == true) {}
            printCOO(matrices[0]);
            break;

        case AD :
            if (matrices[0].numCols != matrices[1].numCols) {
                fprintf(stderr, "Matrix 0 does not have the same number of columns as Matrix 1\n");
                return -1;
            }
            if (matrices[0].numRows != matrices[1].numRows) {
                fprintf(stderr, "Matrix 0 does not have the same number of rows as Matrix 1\n");
                return -1;
            }
            gettimeofday(&opStart, NULL);
            Matrix out = add(matrices[0], matrices[1]);
            matrices[0] = out;
            gettimeofday(&opEnd, NULL);
            printCOO(out);
            break;

        case MM :
            if (matrices[0].numCols != matrices[1].numRows) {
                fprintf(stderr, "Matrix 0's number of columns do not match with Matrix 1's number of rows\n");
                return -1;
            }
            gettimeofday(&opStart, NULL);
            Matrix output = matrixMultiply(matrices[0], matrices[1]);
            gettimeofday(&opEnd, NULL);
            printCOO(output);
            break;

        default :
            fprintf(stderr, "No operation found!\n");
            return -1;
            break;
    }

    float opDelta = ((opEnd.tv_sec  - opStart.tv_sec) * 1000000u + opEnd.tv_usec - opStart.tv_usec) / 1.e6;
    printf("Time for operation: %10.6fs\n", opDelta);
    return 0;
}