#include <stdio.h>
#include <string.h>
#include "parser.h"
#include "token.h"
#include "scanner.h"

void program();
void block();
void vars();
void expr();
void A();
void M();
void R();
void stats();
void mStat();
void stat();
void in();
void out();
void ifGram();
void loop();
void assign();
void RO();
void error(char* expectedToken);

struct token newToken;
FILE* sourceFile;

void parser(FILE* incomingSourceFile){
    sourceFile = incomingSourceFile;
    lineNumber = 1;
    newToken = getNextToken(sourceFile);
    program();
    if (newToken.tokenId != eofTk){
        error("End of file");
    }
    printf("okay\n");
}



void program(){
    if( newToken.tokenId == keywordTK && (strcmp(newToken.tokenInstance, "void") == 0)){
        newToken = getNextToken(sourceFile);
        vars();
        block();
    } else {
        error("void");
    }
}

void block(){
    if( newToken.tokenId == keywordTK && (strcmp(newToken.tokenInstance, "start") == 0)){
        newToken = getNextToken(sourceFile);
        vars();
        stats();
        if( newToken.tokenId == keywordTK && (strcmp(newToken.tokenInstance, "stop") == 0)){
            newToken = getNextToken(sourceFile);
        } else {
            error("stop");
        }
    } else {
        error("start");
    }
}

void vars(){
    if (newToken.tokenId == keywordTK && (strcmp(newToken.tokenInstance, "var") == 0)){
        newToken = getNextToken(sourceFile);
        if (newToken.tokenId == idTk){
            newToken = getNextToken(sourceFile);
            if (newToken.tokenId == opDelTk && (strcmp(newToken.tokenInstance, ":") == 0)){
                newToken = getNextToken(sourceFile);
                if (newToken.tokenId == intTk){
                    newToken = getNextToken(sourceFile);
                    vars();
                } else {
                    error("Integer");
                }
            } else {
                error(":");
            }
        } else {
            error("Identifier");
        }
        vars();
    }
}

void expr(){
    A();
    if (newToken.tokenId == opDelTk && (strcmp(newToken.tokenInstance, "/") == 0)){
        newToken = getNextToken(sourceFile);
        expr();
    } else if (newToken.tokenId == opDelTk && (strcmp(newToken.tokenInstance, "*") == 0)){
        newToken = getNextToken(sourceFile);
        expr();
    }
}

void A(){
    M();
    if (newToken.tokenId == opDelTk && (strcmp(newToken.tokenInstance, "+") == 0)){
        newToken = getNextToken(sourceFile);
        A();
    } else if (newToken.tokenId == opDelTk && (strcmp(newToken.tokenInstance, "-") == 0)){
        newToken = getNextToken(sourceFile);
        A();
    }
}

void M(){
    if (newToken.tokenId == opDelTk && (strcmp(newToken.tokenInstance, "-") == 0)){
        newToken = getNextToken(sourceFile);
        M();
    } else {
        R();
    }
}

void R(){
    if (newToken.tokenId == opDelTk && (strcmp(newToken.tokenInstance, "(") == 0)){
        newToken = getNextToken(sourceFile);
        expr();
        if (newToken.tokenId == opDelTk && (strcmp(newToken.tokenInstance, ")") == 0)){
            newToken = getNextToken(sourceFile);
        } else {
            error(")");
        }
    } else if (newToken.tokenId == idTk){
        newToken = getNextToken(sourceFile);
    } else if (newToken.tokenId == intTk){
        newToken = getNextToken(sourceFile);
    } else {
        error("(, Identifier, or Integer");
    }
}

void stats(){
    stat();
    mStat();
}

void mStat(){
    if (newToken.tokenId == keywordTK && (strcmp(newToken.tokenInstance, "scan") == 0)){
        stat();
        mStat();
    } else if (newToken.tokenId == keywordTK && (strcmp(newToken.tokenInstance, "out") == 0)){
        stat();
        mStat();
    }  else if (newToken.tokenId == keywordTK && (strcmp(newToken.tokenInstance, "start") == 0)){
        stat();
        mStat();
    } else if (newToken.tokenId == keywordTK && (strcmp(newToken.tokenInstance, "if") == 0)){
        stat();
        mStat();
    } else if (newToken.tokenId == keywordTK && (strcmp(newToken.tokenInstance, "loop") == 0)){
        stat();
        mStat();
    } else if (newToken.tokenId == keywordTK && (strcmp(newToken.tokenInstance, "let") == 0)){
        stat();
        mStat();
    }
}

void stat(){
    if (newToken.tokenId == keywordTK && (strcmp(newToken.tokenInstance, "scan") == 0)){
        in();
    } else if (newToken.tokenId == keywordTK && (strcmp(newToken.tokenInstance, "out") == 0)){
        out();
    }  else if (newToken.tokenId == keywordTK && (strcmp(newToken.tokenInstance, "start") == 0)){
        block();
    } else if (newToken.tokenId == keywordTK && (strcmp(newToken.tokenInstance, "if") == 0)){
        ifGram();
    } else if (newToken.tokenId == keywordTK && (strcmp(newToken.tokenInstance, "loop") == 0)){
        loop();
    } else if (newToken.tokenId == keywordTK && (strcmp(newToken.tokenInstance, "let") == 0)){
        assign();
    } else {
        error("scan, out, start, if, loop, or let");
    }
}

void in(){
    if (newToken.tokenId == keywordTK && (strcmp(newToken.tokenInstance, "scan") == 0)){
        newToken = getNextToken(sourceFile);
        if (newToken.tokenId == idTk) {
            newToken = getNextToken(sourceFile);
            if (newToken.tokenId == opDelTk && (strcmp(newToken.tokenInstance, ".") == 0)){
                newToken = getNextToken(sourceFile);
            } else {
                error(".");
            }
        } else {
            error("Identifier");
        }
    } else {
        error("scan");
    }
}

void out(){
    if (newToken.tokenId == keywordTK && (strcmp(newToken.tokenInstance, "out") == 0)){
        newToken = getNextToken(sourceFile);
        if (newToken.tokenId == opDelTk && (strcmp(newToken.tokenInstance, "[") == 0)){
            newToken = getNextToken(sourceFile);
            expr();
            if (newToken.tokenId == opDelTk && (strcmp(newToken.tokenInstance, "]") == 0)){
                newToken = getNextToken(sourceFile);
                if (newToken.tokenId == opDelTk && (strcmp(newToken.tokenInstance, ".") == 0)){
                    newToken = getNextToken(sourceFile);
                } else {
                    error(".");
                }
            } else {
                error("]");
            }
        } else {
            error("[");
        }
    } else {
        error("out");
    }
}

void ifGram(){
    if (newToken.tokenId == keywordTK && (strcmp(newToken.tokenInstance, "if") == 0)){
        newToken = getNextToken(sourceFile);
        if (newToken.tokenId == opDelTk && (strcmp(newToken.tokenInstance, "(") == 0)){
            newToken = getNextToken(sourceFile);
            expr();
            RO();
            expr();
            if (newToken.tokenId == opDelTk && (strcmp(newToken.tokenInstance, ")") == 0)){
                newToken = getNextToken(sourceFile);
                stat();
            } else {
                error(")");
            }
        } else {
            error("(");
        }
    } else {
        error("if");
    }
}

void loop(){
    if (newToken.tokenId == keywordTK && (strcmp(newToken.tokenInstance, "loop") == 0)){
        newToken = getNextToken(sourceFile);
        if (newToken.tokenId == opDelTk && (strcmp(newToken.tokenInstance, "(") == 0)){
            newToken = getNextToken(sourceFile);
            expr();
            RO();
            expr();
            if (newToken.tokenId == opDelTk && (strcmp(newToken.tokenInstance, ")") == 0)){
                newToken = getNextToken(sourceFile);
                stat();
            } else {
                error(")");
            }
        } else {
            error("(");
        }
    } else {
        error("loop");
    }
}

void assign(){
    if (newToken.tokenId == keywordTK && (strcmp(newToken.tokenInstance, "let") == 0)){
        newToken = getNextToken(sourceFile);
        if (newToken.tokenId == idTk) {
            newToken = getNextToken(sourceFile);
            if (newToken.tokenId == opDelTk && (strcmp(newToken.tokenInstance, "=") == 0)){
                newToken = getNextToken(sourceFile);
                expr();
                if (newToken.tokenId == opDelTk && (strcmp(newToken.tokenInstance, ".") == 0)){
                    newToken = getNextToken(sourceFile);  
                } else {
                    error(".");
                }
            } else {
                error("=");
            }
        } else {
            error("Identifier");
        }
    } else {
        error("let");
    }
}

void RO(){
    if (newToken.tokenId == opDelTk && (strcmp(newToken.tokenInstance, "<") == 0)){
        newToken = getNextToken(sourceFile);
        if (newToken.tokenId == opDelTk && (strcmp(newToken.tokenInstance, "=") == 0)){
            newToken = getNextToken(sourceFile);
        }
    } else if (newToken.tokenId == opDelTk && (strcmp(newToken.tokenInstance, ">") == 0)){
        newToken = getNextToken(sourceFile);
        if (newToken.tokenId == opDelTk && (strcmp(newToken.tokenInstance, "=") == 0)){
            newToken = getNextToken(sourceFile);
        }
    }  else if (newToken.tokenId == opDelTk && (strcmp(newToken.tokenInstance, "=") == 0)){
        newToken = getNextToken(sourceFile);
        if (newToken.tokenId == opDelTk && (strcmp(newToken.tokenInstance, "=") == 0)){
            newToken = getNextToken(sourceFile);
        }
    } else {
        error("<, <=, >, >=, ==, or =");
    }
}

void error(char* expectedToken){
    printf("Parser Error\n  Line: %d\n  Expected: %s\n  Found: %s - %s\n", lineNumber, expectedToken, getTokenName(newToken.tokenId), newToken.tokenInstance);
}