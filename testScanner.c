#include <stdio.h>
#include "testScanner.h"
#include "token.h"
#include "scanner.h"

void testScanner(FILE* sourceFile){
    struct token newToken;
    lineNumber = 1;
    do {
        newToken = getNextToken(sourceFile);
        printf("%s: %s - Token Instance: %s - Line Number: %d\n", getTokenName(newToken.tokenId), getTokenDescription(newToken.tokenId), newToken.tokenInstance, newToken.lineNum);
    } while ( newToken.tokenId != 1003);
}