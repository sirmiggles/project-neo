#include "matrix.h"
#include <getopt.h>

//  Execution flags
 struct option EXEC_OPTIONS[] = {
    {"sc", no_argument, 0, SC},
    {"tr", no_argument, 0, TR},
    {"ad", no_argument, 0, AD},
    {"ts", no_argument, 0, TS},
    {"mm", no_argument, 0, MM},
    {"f",  required_argument, 0, FN},
    {"l",  no_argument, 0, LOG}    
};

const char* AUTHOR_SN = "22240204";




