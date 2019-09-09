/*
    File Name:      matrix.c
    Description:    Main C File for matrix
                    > Contains the entry point (main) for the program
    Author:         MIGUEL ARIES SAMBAT TABADERO (22240204)
    Last Modified:  09/9/2019
*/

#include <stdio.h>
#include <stdbool.h>
#include <errno.h>
#include <unistd.h>
#include <sys/time.h>

#include "matrix.h"

int main(int argc, char **argv) {
    //  If insufficient number of arguments, throw usage message
    if (argc < 3) {
        fprintf(stderr, "Invalid number of arguments\n");
        usage();
        return -1;
    }

    //  Execution flag booleans
    bool sc = false;
    bool tr = false;
    bool ad = false;
    bool ts = false;
    bool mm = false;
    bool log = false;

    int matrixCount = 0;        //  Current number of matrices
    int requiredMatrices = 1;   //  Operations require at least 1.

    int numThreads;
    numThreads = DEFAULT_THREAD_COUNT;

    char* filePath  = calloc(FILEPATH_MAX, sizeof(char)); 
    char* thOpt     = calloc(TH_FLAG_BUFSIZ, sizeof(char));

    int opt, optIndex;
    //  Loop through execution options
    while ((opt = getopt_long_only(argc, argv, "", EXEC_OPTIONS, &optIndex)) != -1) {
        switch (opt) {
            case FN:
                filePath = optarg;
                printf("%s\n", filePath);
                //  Use STRTOK to split args by spaces
                break;
            
            case LOG :
                log = true;
                break;

            case TH:
                //  get parameter, then convert parameter to int
                //  make this into a function?
                thOpt = optarg;
                int val;
                val = atoi(thOpt);
                if (val < 1) {
                    fprintf(stderr, "Invalid parameter for thread number\n");
                    return -1;
                }
                else {
                    printf("Number of threads changed from %d to %d\n", numThreads, val);
                    numThreads = val;
                }
                break;

            case SC:
                sc = true;
                break;

            case TR:
                tr = true;
                break;

            case AD:
                ad = true;
                requiredMatrices = 2;
                break;

            case TS:
                ts = true;
                break;

            case MM:
                mm = true;
                requiredMatrices = 2;
                break;

            default :
                break;
        }
    }

    if (matrixCount < requiredMatrices) {
        fprintf(stderr, "Error: Invalid Number of Matrices Provided\n");  
        fprintf(stderr, "> %d provided, %d required\n", matrixCount, requiredMatrices);
        return -1;
    }

    int x = log - log;
    printf("SUM : %d\n", x = sc + tr + ad + ts + mm);            //  Simple checker for testing
    return x;
}