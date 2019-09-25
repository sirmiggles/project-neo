/*
    File Name:      globals.c
    Description:    Source file that contains all the constants for the matrix program
    Author:         MIGUEL ARIES SAMBAT TABADERO (22240204)
    Last Modified:  18/9/2019
*/

#include <getopt.h>

#include "matrix.h"

//  Execution flags
struct option EXEC_OPTIONS[] = {
    {"sm", required_argument, 0, SM},
    {"tr", no_argument, 0, TR},
    {"ad", no_argument, 0, AD},
    {"ts", no_argument, 0, TS},
    {"mm", no_argument, 0, MM},
    {"f",  required_argument, 0, FN},
    {"l",  no_argument, 0, LOG},
    {"t", required_argument, 0, TH}
};

const char* FLAGS[5] = {"sm", "tr", "ad", "ts", "mm"};

const char* AUTHOR_SN = "22240204";                 //  User signature for when producing .out file

const int FLAG_ARG_BUFSIZ   = 1000;                 //  Buffer size for taking in arguments for -t
const int FILEPATH_MAX      = 256;                  //  Buffer size for file paths, i.e. max char length of FPs
const int DIM_BUFSIZ        = 256;                  //  Maximum characters for the dimensions lines
const int ELEMENT_SIZE      = 256;                  //  Maximum No. of characters for an element;

const int DEFAULT_THREAD_COUNT = 1;                 //  The default number of threads to create