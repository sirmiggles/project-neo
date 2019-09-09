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

    int opt, opt_index;
    printf("Flags found are...\n");
    //  Loop through execution options
    while ((opt = getopt_long_only(argc, argv, "", EXEC_OPTIONS, &opt_index)) != -1) {
        switch (opt) {
            case SC:
                printf("%d\n", SC);
                break;
            case TR:
                printf("%d\n", TR);
                break;
            case AD:
                printf("%d\n", AD);
                break;
            case TS:
                printf("%d\n", TS);
                break;
            case MM:
                printf("%d\n", MM);
                break;
            default :
                printf("That's all folks!\n");
                break;
        }
    }
    return sc + tr + ad + ts + mm;
}