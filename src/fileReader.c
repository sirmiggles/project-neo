/*
    Name:           fileReader.c
    Description:    Contains the functions for File I/O
    Author:         MIGUEL ARIES SAMBAT TABADERO (22240204)
    Last Modified:  13/9/2019
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
void parseMatrixFile(FILE* matrixFile, Matrix* targetMatrix, char* fileName) {
    int err;
    char* strMatType = (char *) calloc(5, sizeof(char));
    err = fscanf(matrixFile,"%s", strMatType);
    if (err != 1) {
        free(strMatType);
        targetMatrix->type = ERR;
        return;
    }
    allocateDataType(targetMatrix, strMatType);
    free(strMatType);                               //  Free strMatType as it is no longer needed
    if (targetMatrix->type == ERR) {
        return;
    }

    char* strNumRows = (char*) malloc(DIM_BUFSIZ);
    char* strNumCols = (char*) malloc(DIM_BUFSIZ);

    if (strNumRows == NULL || strNumCols == NULL) {
        fprintf(stderr, "Error could no allocate memory for matrix conversion\n");
        targetMatrix->type = ERR;
        return;
    }
    /*  Read the dimensions and add them in */
    err = fscanf(matrixFile, "%s %s", strNumRows, strNumCols);    
    if (err != 2) {
        free(strNumRows);
        free(strNumCols);
        return;
    }

    allocateDimensions(targetMatrix, strNumRows, strNumCols);
    if (targetMatrix->type == ERR) {
        return;
    }

    long int numElements = targetMatrix->numCols * targetMatrix->numRows;
    targetMatrix->coo = malloc(sizeof(CoordForm) * numElements);
    int i = 0, j = 0;
    char* strElement = (char *) malloc(sizeof(char) * ELEMENT_SIZE);
    for (int k = 0; k < numElements; k++) {
        int errno = fscanf(matrixFile, "%s ", strElement);
        if (errno != 1) {
            fprintf(stderr, "Error: Could not read value");
            return;
        }
        char* temp;
        float val = strtod(strElement, &temp);
        CoordForm c = {i, j, val};
        targetMatrix->coo[k] = c;
        if (i > 0 && i % targetMatrix->numCols == 0) {
            j++;
        }
    }
}

/*  Allocate a matrixType to the destination matrix  */
void allocateDataType(Matrix* targetMatrix, char* matType) {
    if (strcmp(matType, "int") == 0) {
        targetMatrix->type = INT;
        return;
    }
    else if (strcmp(matType, "float") == 0) {
        targetMatrix->type = FLOAT;
        return;
    }
    else {
        targetMatrix->type = ERR;
        return;
    }
}

void allocateDimensions(Matrix* targetMatrix, char* strNumRows, char* strNumCols) {
    int numRows = strToInt(strNumRows);
    int numCols = strToInt(strNumCols);
    //  If any dimensions are invalid -- don't do them anymore
    if (numRows < 0 || numCols < 0) {
        targetMatrix->type = ERR;
        return;
    }
    else {
        targetMatrix->numRows = numRows;
        targetMatrix->numCols = numCols;
    }
}