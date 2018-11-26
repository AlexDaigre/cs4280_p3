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
    Node* root = new Node;
    sourceFile = incomingSourceFile;
    lineNumber = 1;
    newToken = getNextToken(sourceFile);
    root = program();
    if (newToken.tokenId != eofTk){
        error((char*)"End of file");
        return NULL;
    } else {
        printf((char*)"okay\n");
        return root;
    }
}



Node* program(){
    Node* node = new Node;
    node->nodeType = (char*)"program";
    if( newToken.tokenId == keywordTK && (strcmp(newToken.tokenInstance, "void") == 0)){
        newToken = getNextToken(sourceFile);
        node->child0 = vars();
        node->child1 = block();
        return node;
    } else {
        error((char*)"void");
        return NULL;
    }
}

Node* block(){
    Node* node = new Node;
    node->nodeType = (char*)"block";
    if( newToken.tokenId == keywordTK && (strcmp(newToken.tokenInstance, "start") == 0)){
        newToken = getNextToken(sourceFile);
        node->child0 = vars();
        node->child1 = stats();
        if( newToken.tokenId == keywordTK && (strcmp(newToken.tokenInstance, "stop") == 0)){
            newToken = getNextToken(sourceFile);
            return node;
        } else {
            error((char*)"stop");
            return NULL;
        }
    } else {
        error((char*)"start");
        return NULL;
    }
}

Node* vars(){
    Node* node = new Node;
    node->nodeType = (char*)"vars";
    if (newToken.tokenId == keywordTK && (strcmp(newToken.tokenInstance, "var") == 0)){
        newToken = getNextToken(sourceFile);
        if (newToken.tokenId == idTk){
            node->token0 = newToken;
            newToken = getNextToken(sourceFile);
            if (newToken.tokenId == opDelTk && (strcmp(newToken.tokenInstance, ":") == 0)){
                newToken = getNextToken(sourceFile);
                if (newToken.tokenId == intTk){
                    node->token1 = newToken;
                    newToken = getNextToken(sourceFile);
                    node->child0 = vars();
                    return node;
                } else {
                    error((char*)"Integer");
                    return NULL;
                }
            } else {
                error((char*)":");
                return NULL;
            }
        } else {
            error((char*)"Identifier");
            return NULL;
        }
    }
    return NULL;
}

Node* expr(){
    Node* node = new Node;
    node->nodeType = (char*)"expr";
    node->child0 = A();
    if (newToken.tokenId == opDelTk && (strcmp(newToken.tokenInstance, "/") == 0)){
        node->token0 = newToken;
        newToken = getNextToken(sourceFile);
        node->child1 = expr();
    } else if (newToken.tokenId == opDelTk && (strcmp(newToken.tokenInstance, "*") == 0)){
        node->token0 = newToken;
        newToken = getNextToken(sourceFile);
        expr();
        node->child1 = expr();
    }
    return node;
}

Node* A(){
    Node* node = new Node;
    node->nodeType = (char*)"expr";
    node->child0 = M();
    if (newToken.tokenId == opDelTk && (strcmp(newToken.tokenInstance, "+") == 0)){
        node->token0 = newToken;
        newToken = getNextToken(sourceFile);
        node->child1 = A();
    } else if (newToken.tokenId == opDelTk && (strcmp(newToken.tokenInstance, "-") == 0)){
        node->token0 = newToken;
        newToken = getNextToken(sourceFile);
        node->child1 = A();
    }
    return node;
}

Node* M(){
    Node* node = new Node;
    node->nodeType = (char*)"M";
    if (newToken.tokenId == opDelTk && (strcmp(newToken.tokenInstance, "-") == 0)){
        node->token0 = newToken;
        newToken = getNextToken(sourceFile);
        node->child0 = M();
    } else {
        node->child0 = R();
    }
    return node;
}

Node* R(){
    Node* node = new Node;
    node->nodeType = (char*)"R";
    if (newToken.tokenId == opDelTk && (strcmp(newToken.tokenInstance, "(") == 0)){
        newToken = getNextToken(sourceFile);
        node->child0 = expr();
        if (newToken.tokenId == opDelTk && (strcmp(newToken.tokenInstance, ")") == 0)){
            newToken = getNextToken(sourceFile);
        } else {
            error((char*)")");
            return NULL;
        }
    } else if (newToken.tokenId == idTk){
        node->token0 = newToken;
        newToken = getNextToken(sourceFile);
    } else if (newToken.tokenId == intTk){
        node->token1 = newToken;
        newToken = getNextToken(sourceFile);
    } else {
        error((char*)"(, Identifier, or Integer");
        return NULL;
    }
    return node;
}

Node* stats(){
    Node* node = new Node;
    node->nodeType = (char*)"stats";
    node->child0 = stat();
    node->child1 = mStat();
    return node;
}

Node* mStat(){
    Node* node = new Node;
    node->nodeType = (char*)"mStat";
    if (newToken.tokenId == keywordTK && (strcmp(newToken.tokenInstance, "scan") == 0)){
        node->child0 = stat();
        node->child1 = mStat();
        return node;
    } else if (newToken.tokenId == keywordTK && (strcmp(newToken.tokenInstance, "out") == 0)){
        node->child0 = stat();
        node->child1 = mStat();
        return node;
    }  else if (newToken.tokenId == keywordTK && (strcmp(newToken.tokenInstance, "start") == 0)){
        node->child0 = stat();
        node->child1 = mStat();
        return node;
    } else if (newToken.tokenId == keywordTK && (strcmp(newToken.tokenInstance, "if") == 0)){
        node->child0 = stat();
        node->child1 = mStat();
        return node;
    } else if (newToken.tokenId == keywordTK && (strcmp(newToken.tokenInstance, "loop") == 0)){
        node->child0 = stat();
        node->child1 = mStat();
        return node;
    } else if (newToken.tokenId == keywordTK && (strcmp(newToken.tokenInstance, "let") == 0)){
        node->child0 = stat();
        node->child1 = mStat();
        return node;
    }
    return NULL;
}

Node* stat(){
    Node* node = new Node;
    node->nodeType = (char*)"stat";
    if (newToken.tokenId == keywordTK && (strcmp(newToken.tokenInstance, "scan") == 0)){
        node->child0 = in();
        return node;
    } else if (newToken.tokenId == keywordTK && (strcmp(newToken.tokenInstance, "out") == 0)){
        node->child0 = out();
        return node;
    }  else if (newToken.tokenId == keywordTK && (strcmp(newToken.tokenInstance, "start") == 0)){
        node->child0 = block();
        return node;
    } else if (newToken.tokenId == keywordTK && (strcmp(newToken.tokenInstance, "if") == 0)){
        node->child0 = ifGram();
        return node;
    } else if (newToken.tokenId == keywordTK && (strcmp(newToken.tokenInstance, "loop") == 0)){
        node->child0 = loop();
        return node;
    } else if (newToken.tokenId == keywordTK && (strcmp(newToken.tokenInstance, "let") == 0)){
        node->child0 = assign();
        return node;
    } else {
        error((char*)"scan, out, start, if, loop, or let");
        return NULL;
    }
}

Node* in(){
    Node* node = new Node;
    node->nodeType = (char*)"in";
    if (newToken.tokenId == keywordTK && (strcmp(newToken.tokenInstance, "scan") == 0)){
        newToken = getNextToken(sourceFile);
        if (newToken.tokenId == idTk) {
            node->token1 = newToken;
            newToken = getNextToken(sourceFile);
            if (newToken.tokenId == opDelTk && (strcmp(newToken.tokenInstance, ".") == 0)){
                newToken = getNextToken(sourceFile);
                return node;
            } else {
                error((char*)".");
                return NULL;
            }
        } else {
            error((char*)"Identifier");
            return NULL;
        }
    } else {
        error((char*)"scan");
        return NULL;
    }
}

Node* out(){
    Node* node = new Node;
    node->nodeType = (char*)"out";
    if (newToken.tokenId == keywordTK && (strcmp(newToken.tokenInstance, "out") == 0)){
        newToken = getNextToken(sourceFile);
        if (newToken.tokenId == opDelTk && (strcmp(newToken.tokenInstance, "[") == 0)){
            newToken = getNextToken(sourceFile);
            node->child0 = expr();
            if (newToken.tokenId == opDelTk && (strcmp(newToken.tokenInstance, "]") == 0)){
                newToken = getNextToken(sourceFile);
                if (newToken.tokenId == opDelTk && (strcmp(newToken.tokenInstance, ".") == 0)){
                    newToken = getNextToken(sourceFile);
                    return node;
                } else {
                    error((char*)".");
                    return NULL;
                }
            } else {
                error((char*)"]");
                return NULL;
            }
        } else {
            error((char*)"[");
            return NULL;   
        }
    } else {
        error((char*)"out");
        return NULL;
    }
}

Node* ifGram(){
    Node* node = new Node;
    node->nodeType = (char*)"ifGram";
    if (newToken.tokenId == keywordTK && (strcmp(newToken.tokenInstance, "if") == 0)){
        newToken = getNextToken(sourceFile);
        if (newToken.tokenId == opDelTk && (strcmp(newToken.tokenInstance, "(") == 0)){
            newToken = getNextToken(sourceFile);
            node->child0 = expr();
            node->child1 = RO();
            node->child2 = expr();
            if (newToken.tokenId == opDelTk && (strcmp(newToken.tokenInstance, ")") == 0)){
                newToken = getNextToken(sourceFile);
                node->child3 = stat();
                return node;
            } else {
                error((char*)")");
                return NULL;
            }
        } else {
            error((char*)"(");
            return NULL;
        }
    } else {
        error((char*)"if");
        return NULL;
    }
}

Node* loop(){
    Node* node = new Node;
    node->nodeType = (char*)"loop";
    if (newToken.tokenId == keywordTK && (strcmp(newToken.tokenInstance, "loop") == 0)){
        newToken = getNextToken(sourceFile);
        if (newToken.tokenId == opDelTk && (strcmp(newToken.tokenInstance, "(") == 0)){
            newToken = getNextToken(sourceFile);
            node->child0 = expr();
            node->child1 = RO();
            node->child2 = expr();
            if (newToken.tokenId == opDelTk && (strcmp(newToken.tokenInstance, ")") == 0)){
                newToken = getNextToken(sourceFile);
                node->child3 = stat();
                return node;
            } else {
                error((char*)")");
                return NULL;
            }
        } else {
            error((char*)"(");
            return NULL;
        }
    } else {
        error((char*)"loop");
        return NULL;
    }
}

Node* assign(){
    Node* node = new Node;
    node->nodeType = (char*)"assign";
    if (newToken.tokenId == keywordTK && (strcmp(newToken.tokenInstance, "let") == 0)){
        newToken = getNextToken(sourceFile);
        if (newToken.tokenId == idTk) {
            node->token0 = newToken;
            newToken = getNextToken(sourceFile);
            if (newToken.tokenId == opDelTk && (strcmp(newToken.tokenInstance, "=") == 0)){
                newToken = getNextToken(sourceFile);
                node->child0 = expr();
                if (newToken.tokenId == opDelTk && (strcmp(newToken.tokenInstance, ".") == 0)){
                    newToken = getNextToken(sourceFile);  
                    return node;
                } else {
                    error((char*)".");
                    return NULL;
                }
            } else {
                error((char*)"=");
                return NULL;
            }
        } else {
            error((char*)"Identifier");
            return NULL;
        }
    } else {
        error((char*)"let");
        return NULL;
    }
}

Node* RO(){
    Node* node = new Node;
    node->nodeType = (char*)"assign";
    if (newToken.tokenId == opDelTk && (strcmp(newToken.tokenInstance, "<") == 0)){
        node->token0 = newToken;
        newToken = getNextToken(sourceFile);
        if (newToken.tokenId == opDelTk && (strcmp(newToken.tokenInstance, "=") == 0)){
            node->token1 = newToken;
            newToken = getNextToken(sourceFile);
        }
        return node;
    } else if (newToken.tokenId == opDelTk && (strcmp(newToken.tokenInstance, ">") == 0)){
        node->token0 = newToken;
        newToken = getNextToken(sourceFile);
        if (newToken.tokenId == opDelTk && (strcmp(newToken.tokenInstance, "=") == 0)){
            node->token1 = newToken;
            newToken = getNextToken(sourceFile);
        }
        return node;
    }  else if (newToken.tokenId == opDelTk && (strcmp(newToken.tokenInstance, "=") == 0)){
        node->token0 = newToken;
        newToken = getNextToken(sourceFile);
        if (newToken.tokenId == opDelTk && (strcmp(newToken.tokenInstance, "=") == 0)){
            node->token1 = newToken;
            newToken = getNextToken(sourceFile);
        }
        return node;
    } else {
        error((char*)"<, <=, >, >=, ==, or =");
        return NULL;
    }
}

void error(char* expectedToken){
    printf("Parser Error\n  Line: %d\n  Expected: %s\n  Found: %s - %s\n", lineNumber, expectedToken, getTokenName(newToken.tokenId), newToken.tokenInstance);
}