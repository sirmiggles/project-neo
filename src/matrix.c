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

    enum EXEC_FLAG_VALUES efv;          //  Execution flag value, based on enum
    bool log = false;                   //  Will the execution output a log file

    int matrixCount = 0;                //  Current number of matrices
    int requiredMatrices = 1;           //  Operations require at least 1.

    int numThreads;
    numThreads = DEFAULT_THREAD_COUNT;
    char* thOpt     = calloc(TH_FLAG_BUFSIZ, sizeof(char));
    
    /*
    char* fileNames[2];
    fileNames[0] = calloc(FILEPATH_MAX, sizeof(char));
    fileNames[1] = calloc(FILEPATH_MAX, sizeof(char));
    */

    int opt, optIndex;
    //  Loop through execution options
    while ((opt = getopt_long_only(argc, argv, "", EXEC_OPTIONS, &optIndex)) != -1) {
        if (opt == FN || opt == LOG || opt == TH) {
            switch (opt) {
                case FN:
                    for(int index = optind - 1 ; index < argc && *argv[index] != '-'; index++) {
                        parseFileName(&matrixCount, argv[index]);
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
            }
        }
        else {
            efv = opt;
        }
    }

    if (!sufficientArgs(matrixCount, requiredMatrices)) {
        printf("Incorrect number of matrices:\n");
        printf("> %d provided : %d required\n", matrixCount, requiredMatrices);
    }

    printf("Log?: %s\n", (log) ? "true" : "false");
    printf("Operation: %d\n", efv);          //  Simple checker for testing
    return 0;
}