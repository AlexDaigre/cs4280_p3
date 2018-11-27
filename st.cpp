#include <set>
#include <stdio.h>
#include "st.h"
#include "node.h"

std::set <char*> variables;

int verify(char* var){
    if(variables.count(var) != 0){
      return 1;
    }
    return -1;
}

int insert(char* var){
    if(variables.count(var) != 0){
      return -1;
    }
    variables.insert(var);
    return 1;
}

void checkVarsInTree(Node* node){
    if (node == NULL) {
        return; 
    }

    if (strcmp(node->nodeType, (char*)"vars") == 0){
        if (insert(node->token0.tokenInstance) < 0){
            printf("ERROR: Variable already initialised.\n");
            return;
        }
    } else if (strcmp(node->nodeType, (char*)"R") == 0){
        if (verify(node->token0.tokenInstance) < 0){
            printf("ERROR: Variable not declaired.\n");
            return;
        }
    } else if (strcmp(node->nodeType, (char*)"in") == 0){
        if (verify(node->token0.tokenInstance) < 0){
            printf("ERROR: Variable not declaired.\n");
            return;
        }
    } else if (strcmp(node->nodeType, (char*)"assign") == 0){
        if (verify(node->token0.tokenInstance) < 0){
            printf("ERROR: Variable not declaired.\n");
            return;
        }
    }

    checkVarsInTree(node->child0); 
    checkVarsInTree(node->child1);
    checkVarsInTree(node->child2); 
    checkVarsInTree(node->child3);
}