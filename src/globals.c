/*
    File Name:      globals.c
    Description:    Global variable files that contains all the constants for the matrix program
    Author:         MIGUEL ARIES SAMBAT TABADERO (22240204)
    Last Modified:  09/9/2019
*/

#include <getopt.h>

#include "matrix.h"

//  Execution flags
struct option EXEC_OPTIONS[] = {
    {"sc", no_argument, 0, SC},
    {"tr", no_argument, 0, TR},
    {"ad", no_argument, 0, AD},
    {"ts", no_argument, 0, TS},
    {"mm", no_argument, 0, MM},
    {"f",  required_argument, 0, FN},
    {"l",  no_argument, 0, LOG},
    {"t", required_argument, 0, TH}
};

const char* AUTHOR_SN = "22240204";
const int TH_FLAG_BUFSIZ = 1000;
const int DEFAULT_THREAD_COUNT = 4;





