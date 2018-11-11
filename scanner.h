#ifndef SCANNER_H
#define SCANNER_H

    #include <stdio.h>

    extern int currentFSAPosition;
    extern int currentFilePosition;
    extern char nextChar;
    extern int lineNumber;

    struct token getNextToken(FILE* fileName);

#endif