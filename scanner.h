#ifndef SCANNER_H
#define SCANNER_H

    #include <stdio.h>

    int currentFSAPosition;
    int currentFilePosition;
    char nextChar;
    int lineNumber;

    struct token getNextToken(FILE* fileName);

#endif