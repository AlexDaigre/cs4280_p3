#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "testScanner.h"

void invokeScannerFromFile(char* fileName);

int main (int argc, char* argv[]) {
    if (argc == 2) {
        invokeScannerFromFile(argv[1]);
    } else if (argc == 1){
        testScanner(stdin);
    } else {
        printf("A sourcefile is requred as an argument. No additional arguments are allowed.\n");
        return 1;
    }
}

void invokeScannerFromFile(char* fileName){
    // char* sourceFileName = "P1_test4.fs182";
    char sourceFileName[256] = "";;
    char* fileExtention = ".fs182";
    
    strcpy(sourceFileName, fileName);
    strcat(sourceFileName, fileExtention);

    FILE* sourceFile = fopen(sourceFileName, "r");
    if (sourceFile == NULL){
        printf("Could not open %s: %d\n", sourceFileName, errno);
    }

    // printf("Reading: %s\n", sourceFileName);
    testScanner(sourceFile);

    fclose(sourceFile);
}