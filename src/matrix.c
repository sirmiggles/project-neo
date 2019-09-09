#include "matrix.h"
#include <stdio.h>
#include <stdbool.h>
#include <errno.h>
#include <unistd.h>
#include <sys/time.h>

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Too few number of execution arguments/flags\n");
        return -1;
    }

    //  Execution flag booleans
    bool sc = false;
    bool tr = false;
    bool ad = false;
    bool ts = false;
    bool mm = false;
    bool log = false;

    int opt, optIndex;
    printf("Flags found are...\n");
    //  Loop through execution options
    while ((opt = getopt_long_only(argc, argv, "", EXEC_OPTIONS, &optIndex)) != -1) {
        printf("optind is %d\n", optind);
        switch (opt) {
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

            case FN:
                /*  Insert file I/O operations here  */
                break;
            
            case LOG :
                log = true;
                break;

            default :
                //  Do nothing/ignore flag
                printf("%s is not a valid argument\n", argv[optind]);
                break;
                
        }
    }
    int x = log - log;
    printf("SUM : %d\n", x = sc + tr + ad + ts + mm);            //  Simple checker for testing
    return x;
}