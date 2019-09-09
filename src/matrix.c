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

    int matrixCount = 0;        //  Number of matrices
    printf("Matrix Count: %d\n", matrixCount);

    int numThreads;
    numThreads = DEFAULT_THREAD_COUNT;
    printf("Number of Threads = %d\n", numThreads);

    char* thOpt = calloc(TH_FLAG_BUFSIZ, sizeof(char));

    int opt, optIndex;
    //  Loop through execution options
    while ((opt = getopt_long_only(argc, argv, "", EXEC_OPTIONS, &optIndex)) != -1) {
        switch (opt) {
            case FN:
                /*  Insert file I/O operations here  */
                break;
            
            case LOG :
                log = true;
                break;

            case TH:
                //  get parameter, then convert parameter to int
                thOpt = optarg;
                int val;
                val = atoi(thOpt);
                if (val < 1) {
                    fprintf(stderr, "Invalid parameter for thread number");
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
                break;

            case TS:
                ts = true;
                break;

            case MM:
                mm = true;
                break;

            default :
                //  Do nothing/ignore flag
                break;
        }
    }
    int x = log - log;
    printf("SUM : %d\n", x = sc + tr + ad + ts + mm);            //  Simple checker for testing
    return x;
}