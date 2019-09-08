#include "matrix.h"
#include <getopt.h>

//  Execution flags
struct option execOptions[] = {
    {"sc", no_argument, 0, 0},
    {"tr", no_argument, 0, 0},
    {"ad", no_argument, 0, 0},
    {"ts", no_argument, 0, 0},
    {"mm", no_argument, 0, 0},
    {"f",  required_argument, 0, 0},
    {"l",  no_argument, 0, 0}    
};



