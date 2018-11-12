#include <stdio.h>
#include <string.h>
#include "node.h"
#include "parser.h"
#include "token.h"
#include "scanner.h"

Node* program();
Node* block();
Node* vars();
Node* expr();
Node* A();
Node* M();
Node* R();
Node* stats();
Node* mStat();
Node* stat();
Node* in();
Node* out();
Node* ifGram();
Node* loop();
Node* assign();
Node* RO();
void error(char* expectedToken);

struct token newToken;
FILE* sourceFile;

Node* parser(FILE* incomingSourceFile){
    Node* root;
    sourceFile = incomingSourceFile;
    lineNumber = 1;
    newToken = getNextToken(sourceFile);
    root = program();
    if (newToken.tokenId != eofTk){
        error("End of file");
    } else {
        printf("okay\n");
    }
}



Node* program(){
    if( newToken.tokenId == keywordTK && (strcmp(newToken.tokenInstance, "void") == 0)){
        newToken = getNextToken(sourceFile);
        vars();
        block();
    } else {
        error("void");
    }
}

Node* block(){
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

Node* vars(){
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

Node* expr(){
    A();
    if (newToken.tokenId == opDelTk && (strcmp(newToken.tokenInstance, "/") == 0)){
        newToken = getNextToken(sourceFile);
        expr();
    } else if (newToken.tokenId == opDelTk && (strcmp(newToken.tokenInstance, "*") == 0)){
        newToken = getNextToken(sourceFile);
        expr();
    }
}

Node* A(){
    M();
    if (newToken.tokenId == opDelTk && (strcmp(newToken.tokenInstance, "+") == 0)){
        newToken = getNextToken(sourceFile);
        A();
    } else if (newToken.tokenId == opDelTk && (strcmp(newToken.tokenInstance, "-") == 0)){
        newToken = getNextToken(sourceFile);
        A();
    }
}

Node* M(){
    if (newToken.tokenId == opDelTk && (strcmp(newToken.tokenInstance, "-") == 0)){
        newToken = getNextToken(sourceFile);
        M();
    } else {
        R();
    }
}

Node* R(){
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

Node* stats(){
    stat();
    mStat();
}

Node* mStat(){
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

Node* stat(){
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

Node* in(){
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

Node* out(){
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

Node* ifGram(){
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

Node* loop(){
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

Node* assign(){
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

Node* RO(){
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