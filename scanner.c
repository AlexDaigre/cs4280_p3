#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "scanner.h"
#include "token.h"
#include "fsaTable.h"

struct token getNextToken(FILE* sourceFile) {
    nextChar = fgetc(sourceFile);
    int state = 0;
    int nextState;
    struct token newToken;
    char tokenText[9] = "";
    int tokenTextLength = 0;
    while(state<1000) {
        int charGroup = charToColumn(nextChar);
        nextState = fsaTable[charGroup][state];
        // printf("nextState: %d\n", nextState);
        if (nextState < 0){
            printf("SCANNER ERROR: Invalid charecter %c at line %d\n", nextChar, lineNumber);
            exit(1);
        }
        if (nextState >= 1000) {
            ungetc(nextChar, sourceFile);
            if (nextState == 1000) {
                int n;
                for (n = 0; n < keywordListSize; n++){
                    // printf("tokenText: %s keywordList[n]: %s\n", tokenText, keywordList[n]);
                    if (strcmp(tokenText, keywordList[n]) == 0){
                        newToken.tokenId = 1004;
                        strcpy(newToken.tokenInstance, tokenText);
                        newToken.lineNum = lineNumber;
                        // printf("SCANNER:\n  Token ID: %d\n  Token Instance: %s\n  Line Number: %d\n", newToken.tokenId, newToken.tokenInstance, newToken.lineNum);
                        return newToken;
                    }
                }
                newToken.tokenId = nextState;
                strcpy(newToken.tokenInstance, tokenText);
                newToken.lineNum = lineNumber;
                // printf("SCANNER:\n  Token ID: %d\n  Token Instance: %s\n  Line Number: %d\n", newToken.tokenId, newToken.tokenInstance, newToken.lineNum);
                return newToken;
            } else {
                newToken.tokenId = nextState;
                strcpy(newToken.tokenInstance, tokenText);
                newToken.lineNum = lineNumber;
                // printf("SCANNER:\n  Token ID: %d\n  Token Instance: %s\n  Line Number: %d\n", newToken.tokenId, newToken.tokenInstance, newToken.lineNum);
                return (newToken);
            }
        } else {
            state = nextState;
            if (nextChar == '\n'){
                lineNumber++;
            }
            // printf("nextChar: %c\n  tokenTextLength: %d\n", nextChar, tokenTextLength);
            if (isspace(nextChar)){
            } else if (state == 3 || nextChar == '$'){
            } else {
                tokenText[tokenTextLength] = nextChar;
                tokenTextLength++;
            }
            // if (tokenTextLength > 8){
            //     exit(1);
            // }
            nextChar = fgetc(sourceFile);
        }
    }
    printf("SCANNER ERROR: unknown execption at line %d\n", lineNumber);
    exit(1);
}