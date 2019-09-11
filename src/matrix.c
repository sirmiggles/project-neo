/*
    File Name:      matrix.c
    Description:    Main C File for matrix
                    > Contains the entry point (main) for the program
    Author:         MIGUEL ARIES SAMBAT TABADERO (22240204)
    Last Modified:  11/9/2019
*/

#include <stdio.h>
#include <stdbool.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <sys/time.h>

#include "matrix.h"

int main(int argc, char **argv) {
    //  If insufficient number of arguments, throw usage message
    if (argc < 3) {
        fprintf(stderr, "Invalid number of arguments\n");
        usage();
        return -1;
    }

    enum EXEC_FLAG_VALUES efv = UD;         //  Execution flag value, based on enum
    bool operationFound = false;            //  Checker for if an exec. flag has been found
    bool log = false;                       //  Will the execution output a log file

    int matrixCount = 0;                    //  Current number of matrices
    int requiredMatrices = 1;               //  Operations require at least 1.

    int numThreads;                         //  The default number of threads that the program will run in
    numThreads = DEFAULT_THREAD_COUNT;

    char* thOpt     = calloc(FLAG_ARG_BUFSIZ, sizeof(char));    //  -t argument buffer
    char* flagArg   = calloc(FLAG_ARG_BUFSIZ, sizeof(char));    //  -sm argument buffer
    float scalar = 0.0;
    
    char* fileNames[2];
    fileNames[0] = calloc(FILEPATH_MAX, sizeof(char));
    fileNames[1] = calloc(FILEPATH_MAX, sizeof(char));
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
                    if ((numThreads = setNumberOfThreads(thOpt)) < 1) {
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
                if ((scalar = getScalarFactor(flagArg)) == 0.0 ) {
                    fprintf(stderr, "Scalar factor must not be 0.0\n");
                    return -1;
                }
                operationFound = true;
                continue;
            }
            if (efv == AD || efv == MM) {
                requiredMatrices = 2;
            }
            operationFound = true;
        }
    }
    //  Free the buffer files for reading command line arguments
    free(thOpt);
    free(flagArg);

    //  If no operations are found, exit
    if (!operationFound) {
        fprintf(stderr, "No matrix operations specified\n");
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

    FILE** readFiles = calloc(matrixCount, sizeof(FILE));
    openFiles(readFiles, fileNames, matrixCount);

    for (int i = 0; i < matrixCount; i++) {
        printf("File %d:\n", i);
        char c;
        while ((c = fgetc(readFiles[i])) != '\0') {
            if (feof(readFiles[i]))
                break;
            printf("%c", c);
        }
        printf("\n");
    }

    closeFiles(readFiles, matrixCount);

    printf("Log?: %s\n", (log) ? "true" : "false");
    printf("Operation: %d\n", efv);          //  Simple checker for testing
    return 0;
}