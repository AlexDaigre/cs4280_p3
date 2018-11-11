#include <stdio.h>
#include "parser.h"
#include "token.h"
#include "scanner.h"

void parser(FILE* sourceFile){
    struct token newToken;
    lineNumber = 1;
    do {
        newToken = getNextToken(sourceFile);
        printf("%s: %s - Token Instance: %s - Line Number: %d\n", getTokenName(newToken.tokenId), getTokenDescription(newToken.tokenId), newToken.tokenInstance, newToken.lineNum);
    } while ( newToken.tokenId != 1003);
}