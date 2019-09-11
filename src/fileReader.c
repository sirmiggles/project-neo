/*
    Name:           fileReader.c
    Description:    Contains the functions for File I/O
    Author:         MIGUEL ARIES SAMBAT TABADERO (22240204)
    Last Modified:  11/9/2019
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "matrix.h"

/*  Parses the file name to check if it's valid  */
void parseFileName(int *matrixCount, char* passedArgument, char* progFileName) {
    bool fileIsAccessible = fileAccessible(passedArgument);
    if (fileIsAccessible) {
        strcpy(progFileName, passedArgument);
        (*matrixCount)++;
    }
}

/*  Check if file exists and can be read */
bool fileAccessible(char* fileName) {
    return (access(fileName, F_OK) != -1 && access(fileName, R_OK) != -1)   \
            ? true : false;
}