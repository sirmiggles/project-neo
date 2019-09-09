#include "matrix.h"
#include <stdio.h>
#include <stdbool.h>
#include <errno.h>
#include <unistd.h>
#include <sys/time.h>

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
                printf("%s is not a valid argument\n", argv[optind-1]);
                break;
        }
    }
    int x = log - log;
    printf("SUM : %d\n", x = sc + tr + ad + ts + mm);            //  Simple checker for testing
    return x;
}