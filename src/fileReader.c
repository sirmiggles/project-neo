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

/*  Add the opened files to the file array  */
void openFiles(FILE** files, char** fileNames, int numFiles) {
    for (int i = 0; i < numFiles; i++) {
        files[i] = fopen(fileNames[i], "r");
    }
}

/*  Close the files in the file array  */
void closeFiles(FILE** files, int numFiles) {
    for (int i = 0; i < numFiles; i++) {
        fclose(files[i]);
    }
}

/*  Converts the said file into a matrix format  */
void parseMatrixFile(FILE* matrixFile, Matrix* destMatrix, char* fileName) {
    int err;
    char* strMatType = (char *) calloc(5, sizeof(char));
    err = fscanf(matrixFile,"%s", strMatType);
    if (err != 1) {
        return;
    }
    allocateDataType(strMatType, destMatrix);
    if (destMatrix->dataType = ERR) {
        return;
    }
}

/*  Allocate a matrixType to the destination matrix  */
void allocateDataType(char* matType, Matrix* destMatrix) {
    if (strcmp(matType, "int") == 0) {
        destMatrix->dataType = INT;
        return;
    }
    else if (strcmp(matType, "float") == ) {
        destMatrix->dataType = FLOAT;
        return;
    }
    else {
        destMatrix->dataType = ERR;
        return;
    }
}